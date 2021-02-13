#include <string>

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

#include <crsRead/MCorsikaReader.h>

#define NMAX 10000000

class C2Primary : public G4VUserPrimaryGeneratorAction
{
public:
    C2Primary(std::string corsika_file_name) :
        corsikaFileReader(corsika_file_name, 0)
    {
        particleGun = new G4ParticleGun(1);
        particleTable = G4ParticleTable::GetParticleTable();
    }
    ~C2Primary()
    {
        delete particleGun;
    }

    void GeneratePrimaries(G4Event *anEvent);
    int ReadShower();
    int FilterParticles(double xa, double ya);
    G4ParticleTable *particleTable;

private:
    int nParticle; //total number of particles in the shower (observation level)
    int ID[NMAX];
    double x[NMAX], y[NMAX];
    double px[NMAX], py[NMAX], pz[NMAX];
    double E[NMAX], t[NMAX];
    //
    int IDf[NMAX];
    double xf[NMAX], yf[NMAX];
    double pxf[NMAX], pyf[NMAX], pzf[NMAX];
    double Ef[NMAX], tf[NMAX];
    //
    crsRead::MCorsikaReader corsikaFileReader;
    G4ParticleGun *particleGun;
};
