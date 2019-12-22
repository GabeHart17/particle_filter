#ifndef RNG_HEADER
#define RNG_HEADER

#include <random>


class rng {
public:
  rng() {}
  virtual double random(double, double); // return a random number in a given range
  double operator()(double a, double b) {
    return random(a, b);
  }
  double operator()() {
    return random(0, 1);
  }
};

class MersenneTwisterRNG : public rng {
private:
  unsigned int seed_ = 1;
  std::mt19937 mtrng(seed_);
public:
  MersenneTwisterRNG() {}
  double random(double a, double b) {
    unsigned int raw = mtrng();
    return a + ((raw - mtrng.min()) * ((b - a) / (mtrng.max() - mtrng.min())));
  }
}


#endif
