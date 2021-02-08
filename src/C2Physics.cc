#define C2PhysicsFlag 0
#include "C2Physics.hh"

C2Physics::C2Physics() : G4VUserPhysicsList()
{
	SetVerboseLevel(1);
}

C2Physics::~C2Physics()
{
}

void C2Physics::ConstructParticle()
{
	G4BosonConstructor consBos;
	consBos.ConstructParticle();
	G4LeptonConstructor consLep;
	consLep.ConstructParticle();
	G4MesonConstructor consMes;
	consMes.ConstructParticle();
	G4BaryonConstructor consBar;
	consBar.ConstructParticle();
	G4IonConstructor consIon;
	consIon.ConstructParticle();
	G4ShortLivedConstructor consShL;
	consShL.ConstructParticle();
}

void C2Physics::ConstructProcess()
{
#ifdef C2PhysicsFlag
	G4cout << "PhysicsList::ConstructProcess: is called" << G4endl;
#endif
	AddTransportation();
	G4Decay *theDecayProcess = new G4Decay();
	auto particleIterator = GetParticleIterator(); //new feature in Geant4.10.3 (!!)
	particleIterator->reset();
	while ((*particleIterator)())
	{
		G4ParticleDefinition *particle = particleIterator->value();
#ifdef C2PhysicsFlag
		G4cout << "ConstructProcess: Particle=" << particle->GetParticleName() << G4endl;
#endif
		G4ProcessManager *pmanager = particle->GetProcessManager();
		//Decays
		if (theDecayProcess->IsApplicable(*particle))
		{
			pmanager->AddProcess(theDecayProcess);
			//set ordering for PostStepDoIt and AtRestDoIt
			pmanager->SetProcessOrdering(theDecayProcess, idxPostStep);
			pmanager->SetProcessOrdering(theDecayProcess, idxAtRest);
		}
		G4String particleName = particle->GetParticleName();
		//EM processes
		if (particleName == "gamma") //gamma
		{
			pmanager->AddDiscreteProcess(new G4GammaConversion());	   //Pair Production
			pmanager->AddDiscreteProcess(new G4ComptonScattering());   //Compton Effect
			pmanager->AddDiscreteProcess(new G4PhotoElectricEffect()); //Photo Effect
			//pmanager->AddDiscreteProcess(new G4PhotoNuclearProcess());
		}
		else if (particleName == "e-") //electron
		{
			pmanager->AddProcess(new G4eMultipleScattering(), -1, 1, 1); //ElectronMultipleScattering
			pmanager->AddProcess(new G4eIonisation(), -1, 2, 2);		 //Electron Ionisation
			pmanager->AddProcess(new G4eBremsstrahlung(), -1, -1, 3);	 //Electron BremsStrahlung
		}
		else if (particleName == "e+") //positron
		{
			pmanager->AddProcess(new G4eMultipleScattering(), -1, 1, 1); //PositronMultipleScattering
			pmanager->AddProcess(new G4eIonisation(), -1, 2, 2);		 //Positron Ionisation
			pmanager->AddProcess(new G4eBremsstrahlung(), -1, -1, 3);	 //Positron BremsStrahlung
			G4eplusAnnihilation *theAnnihilation = new G4eplusAnnihilation;
			pmanager->AddDiscreteProcess(theAnnihilation); //Positron Annihilation on Flight
			pmanager->AddRestProcess(theAnnihilation);	   //Positron Annihilation at Rest
		}
		else if (particleName == "mu-")
		{
			pmanager->AddProcess(new G4MuMultipleScattering(), -1, 1, 1); //Muon Multiple Scattering
			pmanager->AddProcess(new G4MuIonisation(), -1, 2, 2);		  //Muon Ionisation
			pmanager->AddProcess(new G4MuBremsstrahlung(), -1, -1, 3);	  //Muon BremsStrahlung
		}
		else if (particleName == "mu+")
		{
			pmanager->AddProcess(new G4MuMultipleScattering(), -1, 1, 1); //Muon Multiple Scattering
			pmanager->AddProcess(new G4MuIonisation(), -1, 2, 2);		  //Muon Ionisation
			pmanager->AddProcess(new G4MuBremsstrahlung(), -1, -1, 3);	  //Muon BremsStrahlung
		}
	}
}

void C2Physics::SetCuts()
{
	if (verboseLevel > 0)
		G4cout << "PhysicsList::SetCuts: default cut length : "
			   << G4BestUnit(defaultCutValue, "Length") << G4endl;
	SetCutsWithDefault();
}
