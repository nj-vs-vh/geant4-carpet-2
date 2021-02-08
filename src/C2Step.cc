#include "C2Step.hh"
#include "C2Detector.hh"
#include "G4ios.hh"
#include "G4Track.hh"
#include "globals.hh"
#include "math.h"
#include "G4SteppingManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4DynamicParticle.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"

C2Step::C2Step()
{}

C2Step::~C2Step()
{}

void C2Step::UserSteppingAction(const G4Step* aStep)
{
    int i,TrackID,ParticleType;
    double Ek1,Ek2,nr,nd;
    double x1[3],x2[3],m[3];
    G4String MyPreStepVolumeName;
//
    G4Track* aTrack= aStep->GetTrack();
    TrackID= aTrack->GetTrackID();
    const G4DynamicParticle* MyDynamicParticle= aTrack->GetDynamicParticle();
    G4StepPoint* MyPreStepPoint=  aStep->GetPreStepPoint();
    G4StepPoint* MyPostStepPoint= aStep->GetPostStepPoint();
    G4VPhysicalVolume* MyPreStepVolume= MyPreStepPoint->GetPhysicalVolume();
    if (MyPreStepVolume!=NULL)
	MyPreStepVolumeName= MyPreStepVolume->GetName();
    Ek1= MyPreStepPoint->GetKineticEnergy();
    Ek2= MyPostStepPoint->GetKineticEnergy();
    for (i=0; i<3; i++)
	x1[i]= MyPreStepPoint->GetPosition()[i];
    for (i=0; i<3; i++)
	x2[i]= MyPostStepPoint->GetPosition()[i];
    for (i=0; i<3; i++)
	m[i]= MyPreStepPoint->GetMomentumDirection()[i];
    if (MyDynamicParticle!=NULL)
    {
	const G4ParticleDefinition* MyParticleDefinition= MyDynamicParticle->GetDefinition();
//	if ((MyParticleDefinition!=NULL)&&(x1[0]>=-4.01e3)&&(x1[0]<=4.01e3)&&
//	    (x1[1]>=-4.01e3)&&(x1[1]<=4.01e3)&&(x1[2]>=-8.01e2)&&(x1[2]<=8.01e2))
	if (MyParticleDefinition!=NULL)
	{
	    const G4String MyParticleName= MyParticleDefinition->GetParticleName();
	    if (MyParticleName=="gamma")    ParticleType= 1;
	    else if (MyParticleName=="e+")  ParticleType= 2;
	    else if (MyParticleName=="e-")  ParticleType= 3;
	    else if (MyParticleName=="mu+") ParticleType= 5;
	    else if (MyParticleName=="mu-") ParticleType= 6;
	    else                            ParticleType= 7;
//
	    nd= x1[2]/10.0;
	    nr= (double) ((int) (x1[2]/10.0));
//	    if ((Ek1>10.0)&&(x1[2]<-1.9e3)&&(x1[2]>-4.5e3)) //[mm]
//	    if ((Ek1>10.0)&&(x1[2]<-1.7e3)&&(x1[2]>-2.151e3)&&(fabs(x1[0])<2.75e3)&&(fabs(x1[1])<2.1e4))
	    if ((x1[2]<-2.01e3)&&(x1[2]>-2.151e3)&&(fabs(x1[0])<2.75e3)&&(fabs(x1[1])<2.1e4))
	    {
		fprintf(fp,"%10d %2d  %13.6e %13.6e %13.6e  %13.6e %13.6e %13.6e  %13.6e %13.6e %13.6e  %13.6e %13.6e\n",
		    TrackID,ParticleType,x1[0],x1[1],x1[2],x2[0],x2[1],x2[2],m[0],m[1],m[2],Ek1,Ek2);
	    }
	}
    }
}
