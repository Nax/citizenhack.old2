#ifndef RECT_H
#define RECT_H

#include <hack/math/vector.h>

template <typename T, int N>
class Rect
{
public:
    using Vec = Vector<T, N>;

    Vec     origin;
    Vec     size;
};

using Rect2i = Rect<int, 2>;

#endif
