#include <string>

#include "C2Primary.hh"
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

// COAST library files
#include <crsRead/MCorsikaReader.h>
#include <crs/TSubBlock.h>
#include <crs/MRunHeader.h>
#include <crs/MEventHeader.h>
#include <crs/MEventEnd.h>
#include <crs/MParticleBlock.h>
#include <crs/MLongitudinalBlock.h>
#include <crs/MParticle.h>

#define PRINT_SHOWER_METADATA false
#define PRINT_PARTICLE_DATA false
#define PRINT_PARTICLE_FILTERING false

void C2Primary::GeneratePrimaries(G4Event *anEvent)
{
    int n;
    double mx, my, mz, mr;
    //
    n = anEvent->GetEventID();
    printf("n= %8d\n", n);
    if (IDf[n] == 1)
        particleGun->SetParticleDefinition(particleTable->FindParticle("gamma"));
    else if (IDf[n] == 2)
        particleGun->SetParticleDefinition(particleTable->FindParticle("e+"));
    else if (IDf[n] == 3)
        particleGun->SetParticleDefinition(particleTable->FindParticle("e-"));
    else if (IDf[n] == 5)
        particleGun->SetParticleDefinition(particleTable->FindParticle("mu+"));
    else if (IDf[n] == 6)
        particleGun->SetParticleDefinition(particleTable->FindParticle("mu-"));
    else if (IDf[n] == 8)
        particleGun->SetParticleDefinition(particleTable->FindParticle("pi+"));
    else if (IDf[n] == 9)
        particleGun->SetParticleDefinition(particleTable->FindParticle("pi-"));
    else if (IDf[n] == 13)
        particleGun->SetParticleDefinition(particleTable->FindParticle("neutron"));
    else if (IDf[n] == 14)
        particleGun->SetParticleDefinition(particleTable->FindParticle("proton"));
    else
        particleGun->SetParticleDefinition(particleTable->FindParticle("geantino"));
    //
    particleGun->SetParticlePosition(G4ThreeVector(xf[n] * cm, yf[n] * cm, 1.0 * m));
    mr = sqrt(pxf[n] * pxf[n] + pyf[n] * pyf[n] + pzf[n] * pzf[n]);
    mx = pxf[n] / mr;
    my = pyf[n] / mr;
    mz = pzf[n] / mr;
    particleGun->SetParticleMomentumDirection(G4ThreeVector(mx, my, -mz));
    particleGun->SetParticleEnergy(Ef[n] * GeV);
    particleGun->GeneratePrimaryVertex(anEvent);
}

int C2Primary::ReadShower()
/* Reads !one! shower from CORSIKA DAT file using MCorsikaReader object  */
{
    crs::MRunHeader Run;
    if (corsikaFileReader.GetRun(Run))
    {
        crs::MEventHeader Shower;
        if (corsikaFileReader.GetShower(Shower))
        {
            if (PRINT_SHOWER_METADATA)
            {
                std::cout << "Shower data: "
                          << " ID0 = " << (int)Shower.GetParticleId() << "; E0 = " << Shower.GetEnergy()
                          << "; theta0 = " << Shower.GetTheta() << "; phi0 = " << Shower.GetPhi() << std::endl;
            };

            int particleIndex = 0;

            crs::TSubBlock DataBlock;
            while (corsikaFileReader.GetData(DataBlock))
            {
                if (DataBlock.GetBlockType() == crs::TSubBlock::ePARTDATA)
                {
                    // converting generic TSubBlock to specific MParticleBlock
                    const crs::MParticleBlock &ParticleDataBlock = DataBlock;

                    crs::MParticleBlock::ParticleListConstIterator iEntry;
                    for (iEntry = ParticleDataBlock.FirstParticle(); iEntry != ParticleDataBlock.LastParticle(); ++iEntry)
                    {
                        if (iEntry->IsParticle())
                        {
                            crs::MParticle iPart(*iEntry);

                            ID[particleIndex] = iPart.GetParticleID();
                            x[particleIndex] = iPart.GetX();
                            y[particleIndex] = iPart.GetY();
                            px[particleIndex] = iPart.GetPx();
                            py[particleIndex] = iPart.GetPy();
                            pz[particleIndex] = iPart.GetPz();
                            E[particleIndex] = iPart.GetKinEnergy();
                            t[particleIndex] = iPart.GetTime();
                            if (PRINT_PARTICLE_DATA)
                            {
                                std::cout << " id: " << ID[particleIndex] << " x=" << x[particleIndex] << " y=" << y[particleIndex]
                                          << " px=" << px[particleIndex] << " py=" << py[particleIndex] << " pz=" << pz[particleIndex]
                                          << " E=" << E[particleIndex] << " t=" << t[particleIndex] << std::endl;
                            }

                            particleIndex++;
                        }
                    }
                }
            }

            crs::MEventEnd ShowerSummary;
            corsikaFileReader.GetShowerSummary(ShowerSummary);

            if (PRINT_SHOWER_METADATA)
            {
                std::cout << "Shower summary: total particles = " << ShowerSummary.GetParticles() << std::endl
                          << "\n======\n"
                          << std::endl;
            }
        }
    }
}

int C2Primary::FilterParticles(double xa, double ya)
{
    int i, nf;
    double xs, ys;
    double dx, dy, dr;
    //
    nf = 0.0;
    dr = 5.0e2; //delta-distance [cm]= 5 m
    dx = 2.75e2 + dr;
    dy = 2.10e3 + dr;
    for (i = 0; i < NParticle; i++)
    { //filter particle
        xs = x[i] + xa;
        ys = y[i] + ya;
        if (PRINT_PARTICLE_FILTERING)
            printf("%13.6e %13.6e\n", xs, ys);
        if ((xs >= -dx) && (xs <= dx) && (ys >= -dy) && (ys <= dy)) //inject this particle
        {                                                           //energy threshold 500 MeV, in reality close to 1 GeV
            IDf[nf] = ID[i];
            xf[nf] = xs;
            yf[nf] = ys;
            pxf[nf] = px[i];
            pyf[nf] = py[i];
            pzf[nf] = pz[i];
            Ef[nf] = E[i];
            tf[nf] = t[i];
            nf++;
            if (PRINT_PARTICLE_FILTERING)
            {
                printf("%3d %13.6e %13.6e  %13.6e %13.6e %13.6e  %13.6e %13.6e\n",
                       ID[i], xs, ys, px[i], py[i], pz[i], E[i], t[i]);
            }
        }
    }
    if (PRINT_PARTICLE_FILTERING)
        printf("nf= %8d\n", nf);
    return (nf);
}
