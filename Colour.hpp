#pragma once

#include <sstream>
#include <iomanip>

#include "Vector.hpp"

namespace MathsCPP {
// TODO: Not only should the base storage include number of elements and type, but also order (ARGB, RGBA, BGRA) and value range (0.0-1.0, 0-255).
// - Otherwise the colour class could just fixed 4 elements and only include type info.

template<typename T, std::size_t N, typename Sfinae = std::enable_if_t<std::is_arithmetic_v<T>>>
class ColourBase;

template<typename T>
class ColourBase<T, 3> {
protected:
	constexpr ColourBase() = default;
	constexpr ColourBase(T r, T g, T b, T a) : r(r), g(g), b(b) {}
public:
	T r{}, g{}, b{};
};

template<typename T>
class ColourBase<T, 4> {
protected:
	constexpr ColourBase() = default;
	constexpr ColourBase(T r, T g, T b, T a = 1) : r(r), g(g), b(b), a(a) {}
public:
	T r{}, g{}, b{}, a{1};
};

template<typename T, std::size_t N>
class Colour : public ColourBase<T, N> {
public:
	constexpr Colour() = default;
	template<typename ...Args, typename = std::enable_if<sizeof...(Args) == N>>
	constexpr Colour(Args... args) : ColourBase<T, N>(static_cast<T>(args)...) {}
	constexpr Colour(uint32_t i) {
		
	}
	Colour(std::string hex) {
		if (hex[0] == '#')
			hex.erase(0, 1);
		assert(hex.size() == 6);
		auto hexValue = std::stoul(hex, nullptr, 16);

		r = static_cast<float>((hexValue >> 16) & 0xff) / 255.0f;
		g = static_cast<float>((hexValue >> 8) & 0xff) / 255.0f;
		b = static_cast<float>((hexValue >> 0) & 0xff) / 255.0f;
	}
	template<typename T1>
	constexpr Colour(const Colour<T1, N> &c) { copy_cast(c.begin(), c.end(), begin()); }
	template<typename T1>
	constexpr explicit Colour(const Vector<T1, N> &c) { copy_cast(c.begin(), c.end(), begin()); }

	template<typename T1>
	constexpr Colour &operator=(const Colour<T1, N> &v) {
		copy_cast(v.begin(), v.end(), begin());
		return *this;
	}

	constexpr const T &operator[](std::size_t i) const { return at(i); }
	constexpr T &operator[](std::size_t i) { return at(i); }

	constexpr auto size() const { return N; }

	auto begin() { return &at(0); }
	auto begin() const { return &at(0); }

	auto end() { return &at(0) + N; }
	auto end() const { return &at(0) + N; }

	constexpr const T &at(std::size_t i) const {
		assert(i < N && "Colour subscript out of range");
		return ((const T *)this)[i];
	}
	constexpr T &at(std::size_t i) {
		assert(i < N && "Colour subscript out of range");
		return ((T *)this)[i];
	}

	template<typename = std::enable_if_t<N >= 3>>
	constexpr const Colour<T, 3> &rgb() const { return *reinterpret_cast<const Vector<T, 3> *>(this); }
	template<typename = std::enable_if_t<N >= 3>>
	constexpr Colour<T, 3> &rgb() { return *reinterpret_cast<Vector<T, 3> *>(this); }
	
	template<typename = std::enable_if_t<N >= 2>>
	constexpr const Vector<T, 2> &xy() const { return *reinterpret_cast<const Vector<T, 2> *>(this); }
	template<typename = std::enable_if_t<N >= 2>>
	constexpr Vector<T, 2> &xy() { return *reinterpret_cast<Vector<T, 2> *>(this); }

	template<typename = std::enable_if_t<N >= 3>>
	constexpr const Vector<T, 3> &xyz() const { return *reinterpret_cast<const Vector<T, 3> *>(this); }
	template<typename = std::enable_if_t<N >= 3>>
	constexpr Vector<T, 3> &xyz() { return *reinterpret_cast<Vector<T, 3> *>(this); }

	template<typename = std::enable_if_t<N >= 4>>
	constexpr const Vector<T, 4> &xyzw() const { return *reinterpret_cast<const Vector<T, 4> *>(this); }
	template<typename = std::enable_if_t<N >= 4>>
	constexpr Vector<T, 4> &xyzw() { return *reinterpret_cast<Vector<T, 4> *>(this); }

	/**
	 * Gets the hex code from this colour.
	 * @return The hex code.
	 */
	std::string GetHex() const {
		std::stringstream stream;
		stream << "#";

		auto hexValue = ((static_cast<uint32_t>(r * 255.0f) & 0xff) << 16) +
			((static_cast<uint32_t>(g * 255.0f) & 0xff) << 8) +
			((static_cast<uint32_t>(b * 255.0f) & 0xff) << 0);
		stream << std::hex << std::setfill('0') << std::setw(6) << hexValue;

		return stream.str();
	}

	template<typename T1>
	constexpr friend auto operator==(const Colour &lhs, const Colour<T1, N> &rhs) {
		for (std::size_t i = 0; i < N; i++) {
			if (std::abs(lhs[i] - rhs[i]) > 0.0001f)
				return false;
		}
		return true;
	}

	template<typename T1>
	constexpr friend auto operator!=(const Colour &lhs, const Colour<T1, N> &rhs) {
		for (std::size_t i = 0; i < N; i++) {
			if (std::abs(lhs[i] - rhs[i]) <= 0.0001f)
				return true;
		}
		return false;
	}

	constexpr friend auto operator+(const Colour &lhs) {
		Colour result;
		for (std::size_t i = 0; i < N; i++)
			result[i] = +lhs[i];
		return result;
	}

	constexpr friend auto operator-(const Colour &lhs) {
		Colour result;
		for (std::size_t i = 0; i < N; i++)
			result[i] = -lhs[i];
		return result;
	}

	template<typename T1>
	constexpr friend auto operator+(const Colour &lhs, const Colour<T1, N> &rhs) {
		Colour<decltype(lhs[0] + rhs[0]), N> result;
		for (std::size_t i = 0; i < N; i++)
			result[i] = lhs[i] + rhs[i];
		return result;
	}

	template<typename T1>
	constexpr friend auto operator-(const Colour &lhs, const Colour<T1, N> &rhs) {
		Colour<decltype(lhs[0] - rhs[0]), N> result;
		for (std::size_t i = 0; i < N; i++)
			result[i] = lhs[i] - rhs[i];
		return result;
	}

	template<typename T1>
	constexpr friend auto operator*(const Colour &lhs, const Colour<T1, N> &rhs) {
		Colour<decltype(lhs[0] * rhs[0]), N> result;
		for (std::size_t i = 0; i < N; i++)
			result[i] = lhs[i] * rhs[i];
		return result;
	}

	template<typename T1>
	constexpr friend auto operator/(const Colour &lhs, const Colour<T1, N> &rhs) {
		Colour<decltype(lhs[0] / rhs[0]), N> result;
		for (std::size_t i = 0; i < N; i++)
			result[i] = lhs[i] / rhs[i];
		return result;
	}

	template<typename T1, typename = std::enable_if_t<std::is_arithmetic_v<T1>>>
	constexpr friend auto operator*(const Colour &lhs, T1 rhs) {
		Colour<decltype(lhs[0] * rhs), N> result;
		for (std::size_t i = 0; i < N; i++)
			result[i] = lhs[i] * rhs;
		return result;
	}

	template<typename T1, typename = std::enable_if_t<std::is_arithmetic_v<T1>>>
	constexpr friend auto operator/(const Colour &lhs, T1 rhs) {
		Colour<decltype(lhs[0] / rhs), N> result;
		for (std::size_t i = 0; i < N; i++)
			result[i] = lhs[i] / rhs;
		return result;
	}

	template<typename T1, typename = std::enable_if_t<std::is_arithmetic_v<T1>>>
	constexpr friend auto operator*(T1 lhs, const Colour &rhs) {
		Colour<decltype(lhs *rhs[0]), N> result;
		for (std::size_t i = 0; i < N; i++)
			result[i] = lhs * rhs[i];
		return result;
	}

	template<typename T1, typename = std::enable_if_t<std::is_arithmetic_v<T1>>>
	constexpr friend auto operator/(T1 lhs, const Colour &rhs) {
		Colour<decltype(lhs / rhs[0]), N> result;
		for (std::size_t i = 0; i < N; i++)
			result[i] = lhs / rhs[i];
		return result;
	}

	template<typename T1>
	constexpr friend auto operator+=(Colour &lhs, const T1 &rhs) {
		return lhs = lhs + rhs;
	}

	template<typename T1>
	constexpr friend auto operator-=(Colour &lhs, const T1 &rhs) {
		return lhs = lhs - rhs;
	}

	template<typename T1>
	constexpr friend auto operator*=(Colour &lhs, const T1 &rhs) {
		return lhs = lhs * rhs;
	}

	template<typename T1>
	constexpr friend auto operator/=(Colour &lhs, const T1 &rhs) {
		return lhs = lhs / rhs;
	}

	friend std::ostream &operator<<(std::ostream &stream, const Colour &colour) {
		for (std::size_t i = 0; i < N; i++)
			stream << colour[i] << (i != N - 1 ? ", " : "");
		return stream;
	}

	static const Colour Clear;
	static const Colour Black;
	static const Colour Grey;
	static const Colour Silver;
	static const Colour White;
	static const Colour Maroon;
	static const Colour Red;
	static const Colour Olive;
	static const Colour Yellow;
	static const Colour Green;
	static const Colour Lime;
	static const Colour Teal;
	static const Colour Aqua;
	static const Colour Navy;
	static const Colour Blue;
	static const Colour Purple;
	static const Colour Fuchsia;
};

//template<typename T, std::size_t N>
//const Colour<T, N> Colour<T, N>::Clear(0x00000000, Type::RGBA);
//template<typename T, std::size_t N>
//const Colour<T, N> Colour<T, N>::Black(0x000000FF, Type::RGBA);
template<typename T, std::size_t N>
const Colour<T, N> Colour<T, N>::Grey(0x808080);
template<typename T, std::size_t N>
const Colour<T, N> Colour<T, N>::Silver(0xC0C0C0);
template<typename T, std::size_t N>
const Colour<T, N> Colour<T, N>::White(0xFFFFFF);
template<typename T, std::size_t N>
const Colour<T, N> Colour<T, N>::Maroon(0x800000);
template<typename T, std::size_t N>
const Colour<T, N> Colour<T, N>::Red(0xFF0000);
template<typename T, std::size_t N>
const Colour<T, N> Colour<T, N>::Olive(0x808000);
template<typename T, std::size_t N>
const Colour<T, N> Colour<T, N>::Yellow(0xFFFF00);
template<typename T, std::size_t N>
const Colour<T, N> Colour<T, N>::Green(0x00FF00);
template<typename T, std::size_t N>
const Colour<T, N> Colour<T, N>::Lime(0x008000);
template<typename T, std::size_t N>
const Colour<T, N> Colour<T, N>::Teal(0x008080);
template<typename T, std::size_t N>
const Colour<T, N> Colour<T, N>::Aqua(0x00FFFF);
template<typename T, std::size_t N>
const Colour<T, N> Colour<T, N>::Navy(0x000080);
template<typename T, std::size_t N>
const Colour<T, N> Colour<T, N>::Blue(0x0000FF);
template<typename T, std::size_t N>
const Colour<T, N> Colour<T, N>::Purple(0x800080);
template<typename T, std::size_t N>
const Colour<T, N> Colour<T, N>::Fuchsia(0xFF00FF);

using Colour3f = Colour<float, 3>;
using Colour3d = Colour<double, 3>;
using Colour3i = Colour<int32_t, 3>;
using Colour3ui = Colour<uint32_t, 3>;

using Colour4f = Colour<float, 4>;
using Colour4d = Colour<double, 4>;
using Colour4i = Colour<int32_t, 4>;
using Colour4ui = Colour<uint32_t, 4>;
}

namespace std {
template<typename T, size_t N>
struct hash<MathsCPP::Colour<T, N>> {
	size_t operator()(const MathsCPP::Colour<T, N> &colour) const noexcept {
		size_t seed = 0;
		for (size_t i = 0; i < N; i++)
			MathsCPP::Maths::HashCombine(seed, colour[i]);
		return seed;
	}
};
}
