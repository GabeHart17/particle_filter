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
  state& last() const { return states_.back(); }
  const state& at(size_t index) {
    return states_.at(states_.size() - index - 1);
  }
  void push(const state&);
};


template <class state>
void Measurement<state>::push(const state& s) {
  states_.push_front(s);
  if (states_.size() > size_) {
    states_.pop_back();
  }
}


template <class state>
class Particle : public Measurement<state> {
public:
  Particle(size_t s) : Measurement<state>(s) {}
  double weight = 1;
  bool operator<(const Particle& other) const {
    return weight < other.weight;
  }
};


#endif /* end of include guard: PARTICLE_HEADER */
