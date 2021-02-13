#include <vector>
#include <iostream>
#include <fstream>

#include "../corsika2geant.hpp"

using namespace std;


int main(int argc, char **argv) {
  if (argc<3) {
    cout << "specify CORSIKA DAT file path and outdir" << endl;
    return 1;
  }
  
  string corsika_file_path = argv[1];
  string outdir = argv[2];

  vector<ShowerData> sds = LoadShowerDataFromFile(corsika_file_path);

  ofstream output_file;
  int last_slash_position = corsika_file_path.find_last_of("/");
  string corsika_file_name = corsika_file_path.substr(last_slash_position + 1, corsika_file_path.length() - last_slash_position);
  output_file.open(outdir + "/" + corsika_file_name + ".tsv");

  ShowerData sd = sds[0];

  output_file << "id\tx\ty\tpx\tpy\tpz\tE\tt" << endl;
  for(vector<ParticleData>::iterator particle = sd.particles.begin(); particle != sd.particles.end(); ++particle) {
    output_file <<
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

  output_file.close();

  return 0;
}
