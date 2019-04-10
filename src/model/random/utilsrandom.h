#ifndef GENERATION_H
#define GENERATION_H

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <vector>

namespace how {
namespace model {

template <typename random_generator_t, typename int_t = int>
static int_t intInRange(random_generator_t &generator, int_t lower,
                        int_t higher) {
  auto distribution =
      ::boost::random::uniform_int_distribution<int_t>(lower, higher - 1);
  auto value = distribution(generator);
  return value;
}

template <typename random_generator_t, typename int_t = int>
static std::vector<int_t> intsInRange(random_generator_t generator, int_t lower,
                                      int_t higher, int_t count) {
  auto distribution =
      ::boost::random::uniform_int_distribution<int_t>(lower, higher - 1);
  auto values = std::vector<int_t>(count);
  for (int_t i = 0; i < count; i++) {
    values[i] = distribution(generator);
  }
  return values;
}

template <typename random_generator_t, typename floating_t = double>
static floating_t floating01(random_generator_t generator) {
  auto distribution = ::boost::random::uniform_01<floating_t, floating_t>();
  return distribution(generator);
}
} // namespace model
} // namespace how
#endif // GENERATION_H
