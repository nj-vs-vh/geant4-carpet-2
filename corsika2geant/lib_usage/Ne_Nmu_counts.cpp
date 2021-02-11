// for each shower we expect two numbers:
// 1. number of electrons/positrons on observation level
// 2. number of muons within 100 m from shower axis with E > 1GeV

#include <vector>
#include <iostream>
#include <math.h>

#include "../corsika2geant.hpp"

using namespace std;


int main(int argc, char **argv) {
  if (argc<2) {
    cout << "specify CORSIKA DAT file path" << endl;
    return 1;
  }
  
  string corsika_file_path = argv[1];

  vector<ShowerData> showers = LoadShowerDataFromFile(corsika_file_path);

  cout << "N_e\tN_mu" << endl;

  const int E_MINUS_ID = 3;
  const int E_PLUS_ID = 2;
  const int MU_MINUS_ID = 6;
  const int MU_PLUS_ID = 5;
  const float MIN_E = 1.0; // GeV

  for(vector<ShowerData>::iterator shower = showers.begin(); shower != showers.end(); ++shower) {
    int N_e = 0;
    int N_mu = 0;

    for(vector<ParticleData>::iterator particle = shower->particles.begin(); particle != shower->particles.end(); ++particle) {
        if (particle->id == E_MINUS_ID || particle->id == E_PLUS_ID) N_e++;
        if (particle->id == MU_MINUS_ID || particle->id == MU_PLUS_ID) {
          if (particle->E > MIN_E) {
            float radius = sqrt(pow((particle->x) / 100, 2.0) + pow((particle->y / 100), 2.0));
            if (radius < 100) {
              N_mu++;
            }
          }
        }
    }
    cout << N_e << "\t" << N_mu << endl;
  }

  return 0;
}

