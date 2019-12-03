#include "particle.hpp"


#ifndef WORLD_MODEL_HEADER
#define WORLD_MODEL_HEADER


template <class mstate, class pstate>
class WorldModel {
  virtual double probability(const Measurement<mstate>&, Particle<pstate>&)
  const { return 0; }

  virtual void move_particle(const Measurement<mstate>&, Particle<pstate>&)
    const {}

  template <class rng_type>
  virtual void init_particle(Particle<pstate>&, rng_type& rng) {}

  template <class rng_type>
  virtual void jitter(Particle<pstate>&, rng_type& rng) {}

};


#endif /* end of include guard: WORLD_MODEL_HEADER */
