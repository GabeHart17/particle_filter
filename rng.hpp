#ifndef RNG_HEADER
#define RNG_HEADER


class rng {
public:
  rng() {}
  virtual double random(double, double); // return a random number in a given range
  double operator()(double a, double b) {
    return random(a, b);
  }
}


#endif
