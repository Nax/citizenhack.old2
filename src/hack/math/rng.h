#ifndef INCLUDED_HACK_MATH_RNG_H
#define INCLUDED_HACK_MATH_RNG_H

#include <cstdint>

class Rng
{
public:
    Rng();
    ~Rng();

    void seed(const char[16]);
    void seed(Rng& other);

    uint64_t rand();

private:
    uint64_t _state[2];
};

#endif
