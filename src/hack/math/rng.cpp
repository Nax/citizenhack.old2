#include <cstring>
#include <hack/math/rng.h>

Rng::Rng()
: _state{0, 0}
{

}

Rng::~Rng()
{

}

void Rng::seed(const char s[16])
{
    memcpy((char*)(&_state[0]), s + 0, 8);
    memcpy((char*)(&_state[1]), s + 8, 8);
}

void Rng::seed(Rng& other)
{
    _state[0] = other.rand();
    _state[1] = other.rand();
}

uint64_t Rng::rand()
{
    uint64_t s0 = _state[0];
    uint64_t s1 = _state[1];

    _state[0] = s1;
    s0 ^= s0 << 23;
    _state[1] = s0 ^ s1 ^ (s0 >> 17) ^ (s1 >> 26);
    return _state[1] + s1;
}
