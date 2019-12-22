#include "bootstrap_particle_filter.hpp"
#include "world_simple.hpp"
#include "linear_state.hpp"
#include "world_simple.hpp"
#include <vector>

typedef LinearState<1> ParticleState;
typedef LinearState<3> MeasurementState;


int main(int argc, char const *argv[]) {

  std::vector<double> beacons;
  WorldSimple world(beacons, 0.1, 0.1);
  MersenneTwisterRNG mtr;
  BootstrapParticleFilter<ParticleState, MeasurementState> bpf(
    world, mtr, 10
  );

  return 0;
}
