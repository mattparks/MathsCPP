#pragma once

#include <cstdint>

namespace acid {
class Maths {
public:
	/**
	 * Combines a seed into a hash and modifies the seed by the new hash.
	 * @param seed The seed.
	 * @param v The value to hash.
	 */
	template<typename T>
	static void HashCombine(std::size_t &seed, const T &v) {
		std::hash<T> hasher;
		seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
};
}
