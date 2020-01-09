#ifndef WORLD_SIMPLE_HEADER
#define WORLD_SIMPLE_HEADER

#include "world_model.hpp"
#include "particle.hpp"
#include "linear_state.hpp"
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>


/*

One dimensional world existing between 0 and 1
There exist beacons at 0 and 1, and arbitrary quantity of user-specified
intermediate beacons.
Measurement states: {dist_left_beacon, dist_right_beacon, predicted_movement}
Particle states: {position}

*/


class WorldSimple : public WorldModel<LinearState<3>, LinearState<1> >{
private:
  std::vector<double> beacons_;
  double jitter_variance_;
  double measurement_variance_;
  // clamp to keep 1-d particles inside world
  static void clamp_(LinearState<1>&);
  static double normal_pdf_(double);

public:
  WorldSimple(const std::vector<double>&, double, double);
  double probability(const Measurement<LinearState<3> >&, Particle<LinearState<1> >&) const override;
  void move_particle(const Measurement<LinearState<3> >&, Particle<LinearState<1> >&) const override;
  void init_particle(Particle<LinearState<1> >&, rng&) override;
  void jitter(Particle<LinearState<1> >&, rng&) override;
};


WorldSimple::WorldSimple(const std::vector<double>& b, double jv, double mv) {
  beacons_ = b;
  jitter_variance_ = jv;
  measurement_variance_ = mv;
  beacons_.push_back(0);
  beacons_.push_back(1);
  std::sort(beacons_.begin(), beacons_.end());
}



double WorldSimple::probability (const Measurement<LinearState<3> >& m,
  Particle<LinearState<1> >& p) const {
  double b_lower, b_upper;
  for (size_t i = 1; i < beacons_.size(); i++) {
    if (beacons_[i] >= p.last()[0]) {
      b_lower = beacons_[i - 1];
      b_upper = beacons_[i];
      break;
    }
  }
  return normal_pdf_((m.last()[0] - b_lower) /
         sqrt(measurement_variance_)) *
         normal_pdf_((m.last()[1] - b_upper) /
         sqrt(measurement_variance_));
}

void WorldSimple::move_particle(const Measurement<LinearState<3> >& m,
  Particle<LinearState<1> >& p) const {
  p.last()[0] += m.last()[2];
  clamp_(p.last());
}

void WorldSimple::init_particle(Particle<LinearState<1> >& p, rng& r) {
  LinearState<1> ls;
  ls[0] = r();
  p.push(ls);
}

void WorldSimple::jitter(Particle<LinearState<1> >& p, rng& r) {
  std::normal_distribution<double> nd(0, sqrt(jitter_variance_));
  p.last() = p.last() + nd(r);
  clamp_(p.last());
}

static void WorldSimple::clamp_(LinearState<1>& ls) {
  ls[0] = std::min(1.0, std::max(0.0, ls[0]));
}

static double WorldSimple::normal_pdf_(double z) {
  return (1.0 / (sqrt(2 * M_PI))) * exp(z / sqrt(2));
}

#endif
