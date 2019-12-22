#ifndef PARTICLE_HEADER
#define PARTICLE_HEADER

#include <deque>


template <class state>
class Measurement {
private:
  const size_t size_;
  std::deque<state> states_();

public:
  Measurement(size_t s) : size_(s) {}
  state& last() { return states_.back(); }
  const state& at(size_t index) {
    return states_.at(states_.size() - index - 1);
  }
  friend void operator<<(Measurement<state>&, const state&);
};


void operator<<(Measurement<state>& p, const state& s) {
  p.states_.push_front(s);
  if (p.states_.size() > p.size_) {
    p.states_.pop_back();
  }
}


template <class state>
class Particle : Measurement<state> {
public:
  Particle(size_t s) : Measurement(s) {}
  double weight = 1;
  bool operator<(const Particle& other) const {
    return weight < other.weight;
  }
};


#endif /* end of include guard: PARTICLE_HEADER */
