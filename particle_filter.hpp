#include <vector>
#include "particle.hpp"
#include "world_model.hpp"


#ifndef PARTICLE_FILTER_HEADER
#define PARTICLE_FILTER_HEADER





template <class pstate, class mstate, class rng_type>
class ParticleFilter {
private:
  std::vector<Particle<pstate> > particles_;
  rng_type& rng_;
  const WorldModel& world_;
  Measurement<mstate> measurement_;

public:
  ParticleFilter(const WorldModel& world, rng_type& r, size_t particle_count=65)
    : world_(world), rng_(r) {
    particles_.reserve(particle_count);
    for (size_t i  = 0; i < particle_count; i++) {
      Particle<pstate> p();
      world_.init_particle(p);
      particles_.push_back(p);
    }
    normalize();
  }

  virtual void resample();
  virtual void jitter();
  void update(mstate&);
  virtual state predict();
  void normalize();
};


void ParticleFilter::normalize() {
  double total_weight = 0;
  for (size_t i = 0; i < particles_.size(); i++) {
    total_weight += particles_.at(i).weight;
  }
  for (size_t i = 0; i < particles_.size(); i++) {
    particles_.at(i).weight /= total_weight;
  }
}


void ParticleFilter::update(mstate& s) {
  measurement_ << s;
  resample();
  for (size_t i = 0; i < particles_.size(); i++) {
    world_.move_particle(measurement_, particles_.at(i));
    world_.jitter(particles_.at(i), rng_);
    world_.probability(measurement_, particles_.at(i));
  }
  normalize();
}


#endif /* end of include guard: PARTICLE_FILTER_HEADER */
