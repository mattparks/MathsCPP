#pragma once

#include "Vector.hpp"

namespace acid {
template<typename T, std::size_t N, std::size_t M>
class Matrix {
public:

private:
	std::array<Vector<T, N>, M> data{};
};

using Matrix2x2f = Matrix<float, 2, 2>;
using Matrix3x3f = Matrix<float, 3, 3>;
using Matrix4x4f = Matrix<float, 4, 4>;
}
