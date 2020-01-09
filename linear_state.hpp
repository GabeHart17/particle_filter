#ifndef LINEAR_STATE_HEADER
#define LINEAR_STATE_HEADER

#include <array>


template <int SIZE>
class LinearState {
private:
  std::array<double, SIZE> state;

public:
  LinearState() {
    state.fill(0.0);
  }

  size_t size() {
    return state.size();
  }

  double& operator[](const size_t& i) {
    return state[i];
  }

  LinearState operator+(const LinearState<SIZE>&) const;
  LinearState operator*(const double& other) const;
  friend LinearState<SIZE> operator*(const double&, const LinearState<SIZE>&);
};

template <int SIZE>
LinearState<SIZE> LinearState<SIZE>::operator+(const LinearState<SIZE>& other) const {
  LinearState<SIZE> l;
  for (size_t i = 0; i < SIZE; i++) {
    l.state[i] = state[i] + other.state[i];
  }
  return l;
}

template <int SIZE>
LinearState<SIZE> LinearState<SIZE>::operator*(const double& other) const {
  LinearState<SIZE> l;
  for (size_t i = 0; i < SIZE; i++) {
    l.state[i] = state[i] * other;
  }
  return l;
}

template <int SIZE>
LinearState<SIZE> operator*(const double& d, LinearState<SIZE>& l) {
  LinearState<SIZE> res;
  for (size_t i = 0; i < SIZE; i++) {
    res.state[i] = l[i] * d;
  }
  return res;
}



#endif
