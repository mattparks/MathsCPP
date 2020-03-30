#pragma once

#include "Matrix.hpp"

#include "Maths.hpp"

namespace acid {

}

namespace std {
template<typename T, size_t N, size_t M>
struct hash<acid::Matrix<T, N, M>> {
	size_t operator()(const acid::Matrix<T, N, M> &matrix) const {
		size_t seed = 0;
		for (size_t i = 0; i < M; i++)
			acid::Maths::HashCombine(seed, matrix[i]);
		return seed;
	}
};
}
