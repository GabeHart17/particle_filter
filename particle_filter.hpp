#include <vector>
#include "particle.hpp"
#include "world_model.hpp"
#include "rng.hpp"


#ifndef PARTICLE_FILTER_HEADER
#define PARTICLE_FILTER_HEADER



template <class pstate, class mstate>
class ParticleFilter {
protected:
  std::vector<Particle<pstate> > particles_;
  rng& rng_;
  const WorldModel& world_;
  Measurement<mstate> measurement_;
  void normalize();
public:
  ParticleFilter(const WorldModel& world, rng& r, size_t particle_count=65)
    : world_(world), rng_(r) {
    particles_.reserve(particle_count);
    for (size_t i  = 0; i < particle_count; i++) {
      Particle<pstate> p();
      world_.init_particle(p);
      particles_.push_back(p);
    }
    normalize();
  }
private:
  virtual void resample() = 0;
public:
  void update(mstate&);
  virtual state predict() = 0;
};


template <class pstate, class mstate>
void ParticleFilter<pstate, mstate>::normalize() {
  double total_weight = 0;
  for (size_t i = 0; i < particles_.size(); i++) {
    total_weight += particles_.at(i).weight;
  }
  for (size_t i = 0; i < particles_.size(); i++) {
    particles_.at(i).weight /= total_weight;
  }
}


template <class pstate, class mstate>
void ParticleFilter<pstate, mstate>::update(mstate& s) {
  measurement_ << s;
  resample();
  for (Particle<pstate>& p : particles_) {
    world_.move_particle(measurement_, p);
    world_.jitter(p, rng_);
    world_.probability(measurement_, p);
  }
  normalize();
}


#endif /* end of include guard: PARTICLE_FILTER_HEADER */
