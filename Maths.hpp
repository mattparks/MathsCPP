#pragma once

#include <cstdint>
#include <type_traits>

namespace acid {
/**
 * A implementation of std::copy that static casts the input value type to the output value type.
 * @tparam InputIt, OutputIt Must meet the requirements of LegacyInputIterator and LegacyOutputIterator respectively.
 * @param first, last The range of elements to copy.
 * @param d_first The beginning of the destination range.
 */
template<typename InputIt, typename OutputIt>
OutputIt copy_cast(InputIt first, InputIt last, OutputIt d_first) {
	while (first != last) {
		*d_first++ = static_cast<std::decay_t<decltype(*d_first)>>(*first++);
	}
	return d_first;
}

class Maths {
public:
	/**
	 * Combines a seed into a hash and modifies the seed by the new hash.
	 * @param seed The seed.
	 * @param v The value to hash.
	 */
	template<typename T>
	static void HashCombine(std::size_t &seed, const T &v) noexcept {
		std::hash<T> hasher;
		seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
};
}
