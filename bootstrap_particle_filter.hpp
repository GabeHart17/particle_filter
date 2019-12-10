#include "particle.hpp"
#include "particle_filter.hpp"


#ifndef BOOTSTRAP_PARTICLE_FILTER_HEADER
#define BOOTSTRAP_PARTICLE_FILTER_HEADER


template <class pstate, class mstate, class rng_type>
class BootstrapParticleFilter : public ParticleFilter {
private:
  virtual void resample();
public:
  BootstrapParticleFilter(const WorldModel& world, rng_type& r,
    size_t particle_count=65) : ParticleFilter(world, r, particle_count) {}
  virtual pstate predict();
};


template <class pstate, class mstate, class rng_type>
void BootstrapParticleFilter<pstate, mstate, rng_type>::resample() {

}


template <class pstate, class mstate, class rng_type>
pstate BootstrapParticleFilter<pstate, mstate, rng_type>::predict() {
  pstate sum();
  for (Particle<pstate>& p : particles_) {
    sum = sum + p.;
  }
}


#endif
