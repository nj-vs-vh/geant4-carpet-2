#include <vector>
#include <iostream>

#include "../corsika2geant.hpp"

using namespace std;


int main(int argc, char **argv) {
  if (argc<2) {
    cout << "specify CORSIKA DAT file path" << endl;
    return 1;
  }
  
  string corsika_file_path = argv[1];
  vector<ShowerData> sds = LoadShowerDataFromFile(corsika_file_path);

  ShowerData sd = sds[0];

  cout << "id\tx\ty\tpx\tpy\tpz\tE\tt" << endl;
  for(vector<ParticleData>::iterator particle = sd.particles.begin(); particle != sd.particles.end(); ++particle) {
    cout <<
      particle->id << "\t" <<
      particle->x << "\t" <<
      particle->y << "\t" <<
      particle->px << "\t" <<
      particle->py << "\t" <<
      particle->pz << "\t" <<
      particle->E << "\t" <<
      particle->t << "\t" <<
      endl;
  }

  return 0;
}
