#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "C2Detector.hh"
#include "C2Physics.hh"
#include "C2Primary.hh"
#include "C2Event.hh"
#include "C2Step.hh"

    int NParticleF;
    double xa,ya;
    C2Primary* MyPrimary;
    C2Step* MyStep;

int main()
{
    G4RunManager* RunMng = new G4RunManager;
    RunMng->SetUserInitialization(new C2Detector);
    RunMng->SetUserInitialization(new C2Physics);
    RunMng->Initialize();
//
    MyPrimary= new C2Primary;
    RunMng->SetUserAction(MyPrimary);
    RunMng->SetUserAction(new C2Event);
    MyStep= new C2Step;
    RunMng->SetUserAction(MyStep);
//
    MyPrimary->fpinp= fopen("Shower","r");
    if (MyPrimary->fpinp==NULL)
    {
	printf("Input file Shower not found!\n");
	return(1);
    }
//axis coordinates [cm]
    //xa= 0.0;
    //xa= 5.0e2;
    //xa= 1.0e3;
    //xa= 2.0e3;
    xa= 5.0e3;
    ya= 0.0;
    MyPrimary->ReadShower();
    NParticleF= MyPrimary->FilterParticles(xa,ya);
    printf("NParticleF= %8d\n",NParticleF);
//
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    UImanager->ApplyCommand("/run/verbose 0");
    UImanager->ApplyCommand("/event/verbose 0");
    UImanager->ApplyCommand("/tracking/verbose 0");
//
    MyStep->fp= fopen("Output","w");
    RunMng->BeamOn(NParticleF);
    fclose(MyStep->fp);
    fclose(MyPrimary->fpinp);
    delete RunMng;
    return(0);
}
