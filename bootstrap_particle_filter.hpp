#include "particle.hpp"
#include "particle_filter.hpp"
#include <algorithm>


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
  std::sort(particles_.begin(), particles_.end());  // sorting may be unnecessary
  std::vector<Particle<pstate> > new_particles();
  new_particles.reserve(particles_.size());
  double r = 0;
  double a = 0;
  for (size_t i = 0; i < particles_.size(); i++) {
    // replace with correct method name for rng call
    r = rng.random(0, 1);
    a = 0;
    for (Particle j : particles_) {
      a += j.weight;
      if (a >= r) {
        new_particles.push_back(j);
        break;
      }
    }
  }
  particles_ = new_particles;
}


template <class pstate, class mstate, class rng_type>
pstate BootstrapParticleFilter<pstate, mstate, rng_type>::predict() {
  pstate sum();
  for (Particle<pstate>& p : particles_) {
    sum = sum + p.last();
  }
  return sum * (1.0 / particles_.size());
}


#endif
