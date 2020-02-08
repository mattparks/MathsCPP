#pragma once

#include "Vector.hpp"

namespace SpauldingCPP {
template<std::size_t N, std::size_t M, typename T>
class Matrix {
public:

private:
	std::array<Vector<N, T>, M> data{};
};

// float2x2, float3x3, float4x4
using Mat2x2f = Matrix<2, 2, float>;
using Mat3x3f = Matrix<3, 3, float>;
using Mat4x4f = Matrix<4, 4, float>;
}
