#include <vector>
#include <string>

struct ShowerMetadata {
  int id_primary;
  float E_primary;
  float theta_primary;
  float phi_primary;
  float n_particles;
};

struct ParticleData {
  int id;
  float x;
  float y;
  float px;
  float py;
  float pz;
  float E;
  float t;
};

struct ShowerData {
  ShowerMetadata metadata;
  std::vector<ParticleData> particles;

  ShowerData (ShowerMetadata _metadata, std::vector<ParticleData> _particles) :
    metadata(std::move(_metadata)), particles(std::move(_particles)) {}
};


std::vector<ShowerData> LoadShowerDataFromFile(
    std::string corsika_file_path, bool print_metadata = false, bool print_particles_data = false
);
