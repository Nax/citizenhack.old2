#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib>
#include <utility>

namespace priv
{

template <typename T, int N>
struct VectorData
{
    union
    {
        T   _data[N];
        struct
        {
            T   x;
            T   y;
            T   z;
            T   w;
        };
    };
};

template <typename T>
struct VectorData<T, 1>
{
    union
    {
        T   _data[1];
        T   x;
    };
};

template <typename T>
struct VectorData<T, 2>
{
    union
    {
        T   _data[2];
        struct
        {
            T   x;
            T   y;
        };
    };
};

template <typename T>
struct VectorData<T, 3>
{
    union
    {
        T   _data[3];
        struct
        {
            T   x;
            T   y;
            T   z;
        };
    };
};

template <typename T, int N>
struct VectorBuilder
{
    template <typename... Args>
    static void build(size_t count, T* ptr)
    {
        (void)count;
        (void)ptr;
    }

    template <typename... Args>
    static void build(size_t count, T* ptr, T head, Args... args)
    {
        ptr[count] = head;
        VectorBuilder<T, N>::build(count + 1, ptr, std::forward<Args>(args)...);
    }
};

}

template <typename T, int N>
class Vector : public priv::VectorData<T, N>
{
public:
    Vector()
    {
        for (size_t i = 0; i < N; ++i)
            this->_data[i] = T();
    }

    template <typename Head, typename... Args>
    Vector(Head head, Args... args)
    {
        priv::VectorBuilder<T, N>::build(0, this->_data, head, std::forward<Args>(args)...);
    }
};

using Vector2   = Vector<float, 2>;
using Vector3   = Vector<float, 3>;
using Vector2i  = Vector<int, 2>;
using Vector3i  = Vector<int, 3>;

#endif
