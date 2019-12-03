#include <deque>


#ifndef PARTICLE_HEADER
#define PARTICLE_HEADER

template <class state>
class Measurement {
private:
  const size_t size_;
  std::deque<state> states_();

public:
  Particle(size_t s) : size_(s) {}

  friend void operator<<(Particle&, const state&);
};

void operator<<(Particle& p, const state& s) {
  p.states_.push_front(s);
  if (p.states_.size() > p.size_) {
    p.states_.pop_back();
  }
}


template <class state>
class Particle : Measurement<state> {
public:
  double weight = 1;
};


#endif /* end of include guard: PARTICLE_HEADER */
