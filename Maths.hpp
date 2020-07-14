#pragma once

#include <cstdint>
#include <cmath>
#include <type_traits>

namespace MathsCPP {
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
	template<typename T>
	static constexpr T PI = static_cast<T>(3.14159265358979323846264338327950288L);

	Maths() = delete;

	/**
	 * Takes the cosign of a number by using the sign and a additional angle.
	 * @tparam T The sin type.
	 * @tparam K The angle type.
	 * @param sin The sin.
	 * @param angle The angle.
	 * @return The resulting cosign.
	 */
	template<typename T, typename K>
	static auto CosFromSin(T sin, K angle) {
		// sin(x)^2 + cos(x)^2 = 1
		auto cos = std::sqrt(1 - sin * sin);
		auto a = angle + (PI<T> / 2);
		auto b = a - static_cast<int32_t>(a / (2 * PI<T>)) * (2 * PI<T>);
		if (b < 0)
			b = (2 * PI<T>) + b;
		if (b >= PI<T>)
			return -cos;
		return cos;
	}
	
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
