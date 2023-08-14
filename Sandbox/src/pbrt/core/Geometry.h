#pragma once

#include "Error.h"

// Vectors
template <typename T>
class Vector2
{
public:
    T x, y;
};

template <typename T>
class Vector3
{

public:
    Vector3()
    {
        x = y = z = 0;
    }

    Vector3(T x, T y, T z)
        : x(x), y(y), z(z) 
    {
        Assert(!HasNaNs());
    }

    bool HasNaNs() const 
    {
        return std::isnan(x) || std::isnan(y) || std::isnan(z);
    }

public:
    T x, y, z;
    
    T operator[] (int i) const
    {
        Assert(i >= 0 && i <= 2);
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }

    T &operator[] (int i)
    {
        Assert(i >= 0 && i <= 2);
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }

    Vector3<T> operator+ (const Vector3<T> &v) const
    {
        return Vecto3(x + v.x, y + v.y, z + v.z);
    }

    Vector3<T>& operator+= (const Vector3<T> &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;
