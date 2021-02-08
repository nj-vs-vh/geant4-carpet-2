#include "G4ParticleTable.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

#define NMAX 10000000

class G4ParticleGun;

class C2Primary : public G4VUserPrimaryGeneratorAction
{
public:
    C2Primary();
    ~C2Primary();
    void GeneratePrimaries(G4Event *anEvent);
    int ReadShower();
    int FilterParticles(double xa, double ya);
    G4ParticleTable *particleTable;
    FILE *fpinp;

private:
    int NParticle; //total number of particles in the shower (observation level)
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
    G4ParticleGun *particleGun;
    int ReadParticle(int n);
};
