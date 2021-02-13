#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "C2Detector.hh"
#include "C2Physics.hh"
#include "C2Primary.hh"
#include "C2Event.hh"
#include "C2Step.hh"

#include <iostream>
#include <string>

int NParticleF;
double xa, ya;
C2Primary *MyPrimary;
C2Step *MyStep;

int main(int argc, char **argv)
{
    std::string corsika_file_path;
    if (argc == 2)
    {
        corsika_file_path = argv[1];
    }
    else
    {
        std::cout << "unexpected command-line arguments, expected CORSIKA file name" << std::endl;
        return 1;
    }

    G4RunManager *RunMng = new G4RunManager;
    RunMng->SetUserInitialization(new C2Detector);
    RunMng->SetUserInitialization(new C2Physics);
    RunMng->Initialize();
    //
    MyPrimary = new C2Primary(corsika_file_path);
    RunMng->SetUserAction(MyPrimary);
    RunMng->SetUserAction(new C2Event);
    MyStep = new C2Step;
    RunMng->SetUserAction(MyStep);

    //axis coordinates [cm]
    //xa= 0.0;
    //xa= 5.0e2;
    //xa= 1.0e3;
    //xa= 2.0e3;
    xa = 5.0e3;
    ya = 0.0;
    MyPrimary->ReadShower();
    NParticleF = MyPrimary->FilterParticles(xa, ya);
    printf("NParticleF= %8d\n", NParticleF);
    //
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    UImanager->ApplyCommand("/run/verbose 0");
    UImanager->ApplyCommand("/event/verbose 0");
    UImanager->ApplyCommand("/tracking/verbose 0");
    //
    MyStep->fp = fopen("Output", "w");
    RunMng->BeamOn(NParticleF);
    fclose(MyStep->fp);
    delete RunMng;
    return (0);
}
