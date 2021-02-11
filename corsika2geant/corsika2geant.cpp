#include "corsika2geant.hpp"

#include <iostream>

// COAST imports
#include <crsRead/MCorsikaReader.h>
#include <crs/TSubBlock.h>
#include <crs/MRunHeader.h>
#include <crs/MEventHeader.h>
#include <crs/MEventEnd.h>
#include <crs/MParticleBlock.h>
#include <crs/MLongitudinalBlock.h>
#include <crs/MParticle.h>


using namespace std;


vector<ShowerData>
LoadShowerDataFromFile(string corsika_file_path, bool print_metadata, bool print_particles_data)
{
  crsRead::MCorsikaReader cr(corsika_file_path, 0);

  vector<ShowerData> result;

  crs::MRunHeader Run;
  while (cr.GetRun (Run)) {

    crs::MEventHeader Shower;
    while (cr.GetShower(Shower)) {

      ShowerMetadata meta = {
        .id_primary = (int)Shower.GetParticleId(),
        .E_primary = Shower.GetEnergy(),
        .theta_primary = Shower.GetTheta(),
        .phi_primary = Shower.GetPhi(),
        .n_particles = 0  // to be reassigned when the last block is read
      };
      if (print_metadata){
        cout << "Shower data: " << " ID0 = " << meta.id_primary << "; E0 = " << meta.E_primary
             << "; theta0 = " << meta.theta_primary << "; phi0 = " << meta.phi_primary << endl;
      };

      vector<ParticleData> particles;

      crs::TSubBlock DataBlock;
      while (cr.GetData (DataBlock)) {
        if (DataBlock.GetBlockType () == crs::TSubBlock::ePARTDATA) {

          // converting generic TSubBlock to specific MParticleBlock
          const crs::MParticleBlock& ParticleDataBlock = DataBlock;

          crs::MParticleBlock::ParticleListConstIterator iEntry;
          for (iEntry = ParticleDataBlock.FirstParticle(); iEntry != ParticleDataBlock.LastParticle(); ++iEntry) {
            if (iEntry->IsParticle()) {
              crs::MParticle iPart(*iEntry);
              
              // Particle data ("row")
              ParticleData p = {
                .id = iPart.GetParticleID(),
                .x  = iPart.GetX(),
                .y  = iPart.GetY(),
                .px = iPart.GetPx(),
                .py = iPart.GetPy(),
                .pz = iPart.GetPz(),
                .E = (float)iPart.GetKinEnergy(),
                .t  = iPart.GetTime()
              };

              particles.push_back(p);

              if (print_particles_data) {
                cout << " id: " << p.id << " x=" << p.x << " y=" << p.y
                     << " px=" << p.py << " py=" << p.py << " pz=" << p.py
                     << " E=" << p.E << " t=" << p.t << endl;
              }              
            }
          }
        }
        
      }
      
      crs::MEventEnd ShowerSummary;
      cr.GetShowerSummary(ShowerSummary);

      meta.n_particles = ShowerSummary.GetParticles();
      
      if (print_metadata) {
        cout << "Shower summary: total particles = " << meta.n_particles << endl << "\n======\n" << endl;
      }

      result.emplace_back(meta, particles);
    }
    
  }

  return result;

};


int main (int argc, char **argv)
{
  if (argc<2) {
    cout << "at least one command-line argument is expected (CORSIKA dat file path)" << endl;
    return 1;
  }

  bool verbose;
  string corsika_file_path;

  if (argc == 2) {
    corsika_file_path = argv[1];
    verbose = false;
  } else if (argc == 3) {
    string verbosityOpt(argv[1]);
    if (verbosityOpt.compare("-v") == 0) {
      verbose = true;
      corsika_file_path = argv[2];
    } else {
      cout << "unexpected first command-line argument, expected '-v' or none"<< endl;
      return 1;
    }
  } else {
    cout << "unexpected command-line arguments, expected '<filename>' or '-v <filename>'"<< endl;
    return 1;
  }
  
  LoadShowerDataFromFile(corsika_file_path, true, verbose);
  return 0;
}
