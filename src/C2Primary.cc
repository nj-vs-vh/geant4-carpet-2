#include "C2Primary.hh"
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

#define PrintFlag 0

C2Primary::C2Primary()
{
    particleGun = new G4ParticleGun(1);
    particleTable = G4ParticleTable::GetParticleTable();
}

C2Primary::~C2Primary()
{
    delete particleGun;
}

void C2Primary::GeneratePrimaries(G4Event* anEvent)
{
    int n;
    double mx,my,mz,mr;
//
    n= anEvent->GetEventID();
    printf("n= %8d\n",n);
    if (IDf[n]==1)		particleGun->SetParticleDefinition(particleTable->FindParticle("gamma"));
    else if (IDf[n]==2)		particleGun->SetParticleDefinition(particleTable->FindParticle("e+"));
    else if (IDf[n]==3)		particleGun->SetParticleDefinition(particleTable->FindParticle("e-"));
    else if (IDf[n]==5)		particleGun->SetParticleDefinition(particleTable->FindParticle("mu+"));
    else if (IDf[n]==6)		particleGun->SetParticleDefinition(particleTable->FindParticle("mu-"));
    else if (IDf[n]==8)		particleGun->SetParticleDefinition(particleTable->FindParticle("pi+"));
    else if (IDf[n]==9)		particleGun->SetParticleDefinition(particleTable->FindParticle("pi-"));
    else if (IDf[n]==13)	particleGun->SetParticleDefinition(particleTable->FindParticle("neutron"));
    else if (IDf[n]==14)	particleGun->SetParticleDefinition(particleTable->FindParticle("proton"));
    else			particleGun->SetParticleDefinition(particleTable->FindParticle("geantino"));
//
    particleGun->SetParticlePosition(G4ThreeVector(xf[n]*cm,yf[n]*cm,1.0*m));
    mr= sqrt(pxf[n]*pxf[n]+pyf[n]*pyf[n]+pzf[n]*pzf[n]);
    mx= pxf[n]/mr;
    my= pyf[n]/mr;
    mz= pzf[n]/mr;
    particleGun->SetParticleMomentumDirection(G4ThreeVector(mx,my,-mz));
    particleGun->SetParticleEnergy(Ef[n]*GeV);
    particleGun->GeneratePrimaryVertex(anEvent);
}

int C2Primary::ReadShower()
{
    int i,f;
    f= fscanf(fpinp,"%d",&NParticle);
    if (PrintFlag>0)
	printf("NParticle= %8d\n",NParticle);
    for (i=0; i<NParticle; i++)
	ReadParticle(i);
    return(0);
}

int C2Primary::ReadParticle(int n)
{
    int ri,f;
    double rd;
//
    f= fscanf(fpinp,"%d",&ri); ID[n] = ri;
    f= fscanf(fpinp,"%lf",&rd); x[n] = rd;
    f= fscanf(fpinp,"%lf",&rd); y[n] = rd;
    f= fscanf(fpinp,"%lf",&rd); px[n]= rd;
    f= fscanf(fpinp,"%lf",&rd); py[n]= rd;
    f= fscanf(fpinp,"%lf",&rd); pz[n]= rd;
    f= fscanf(fpinp,"%lf",&rd); E[n] = rd;
    f= fscanf(fpinp,"%lf",&rd); t[n] = rd;
//
    if (PrintFlag>0)
    {
	printf("%3d %13.6e %13.6e  %13.6e %13.6e %13.6e  %13.6e %13.6e\n",
	    ID[n],x[n],y[n],px[n],py[n],pz[n],E[n],t[n]);
    }
    return(0);
}

int C2Primary::FilterParticles(double xa,double ya)
{
    int i,nf;
    double xs,ys;
    double dx,dy,dr;
//
    nf= 0.0;
    dr= 5.0e2; //delta-distance [cm]= 5 m
    dx= 2.75e2+dr;
    dy= 2.10e3+dr;
    for (i=0; i<NParticle; i++)
    { //filter particle
	xs= x[i]+xa;
	ys= y[i]+ya;
	if (PrintFlag>0)
	    printf("%13.6e %13.6e\n",xs,ys);
	if ((xs>=-dx)&&(xs<=dx)&&(ys>=-dy)&&(ys<=dy)) //inject this particle
	{ //energy threshold 500 MeV, in reality close to 1 GeV
	    IDf[nf]= ID[i];
	    xf[nf] = xs;
	    yf[nf] = ys;
	    pxf[nf]= px[i];
	    pyf[nf]= py[i];
	    pzf[nf]= pz[i];
	    Ef[nf] = E[i];
	    tf[nf] = t[i];
	    nf++;
	    if (PrintFlag>0)
	    {
		printf("%3d %13.6e %13.6e  %13.6e %13.6e %13.6e  %13.6e %13.6e\n",
		    ID[i],xs,ys,px[i],py[i],pz[i],E[i],t[i]);
	    }
	}
    }
    if (PrintFlag>0)
	printf("nf= %8d\n",nf);
    return(nf);
}
