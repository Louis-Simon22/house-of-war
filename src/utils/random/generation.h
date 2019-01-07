#ifndef GENERATION_H
#define GENERATION_H

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_01.hpp>

#include <vector>

namespace how {
namespace random {
    
    template <typename random_generator_t, typename int_t = int>
    static int_t intInRange(random_generator_t& generator, int_t lower, int_t higher) {
        const auto& distribution = ::boost::random::uniform_int_distribution<int_t>(lower, higher - 1);
        auto value = distribution(generator);
        return value;
    }

    template <typename random_generator_t, typename int_t = int>
    static std::vector<int_t> intsInRange(random_generator_t generator, int_t lower, int_t higher, int_t count) {
        const auto& distribution = ::boost::random::uniform_int_distribution<int_t>(lower, higher - 1);
        auto values = std::vector<int_t>(count);
        for(int_t i = 0; i < count; i++) {
            values[i] = distribution(generator);
        }
        return values;
    }
    
    template <typename random_generator_t, typename double_t = double>
    static double_t double01(random_generator_t generator) {
        const auto& distribution = ::boost::random::uniform_01<double_t>();
        return distribution(generator);
    }
} // random
} // how
#endif // GENERATION_H
