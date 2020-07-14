#pragma once

#include "Vector.hpp"

namespace MathsCPP {
template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
class Rectangle {
public:
	constexpr Rectangle() = default;
	constexpr Rectangle(T x, T y, T w = 0, T h = 0) : x(x), y(y), w(w), h(h) {}
	template<typename T1>
	constexpr Rectangle(const Rectangle<T1> &r) : x(r.x), y(r.y), w(r.w), h(r.h) {}
	template<typename T1, typename T2>
	constexpr Rectangle(const Vector<T1, 2> &xy, const Vector<T2, 2> &wh) : x(xy.x), y(xy.y), w(wh.x), h(wh.y) {}

	template<typename T1>
	constexpr Rectangle &operator=(const Rectangle<T1> &r) {
		x = r.x, y = r.y, w = r.w, h = r.h;
		return *this;
	}

	template<typename T1>
	constexpr friend auto operator+(const Rectangle &lhs, const Rectangle<T1> &rhs) {
		Rectangle<decltype(lhs.x + rhs.x)> result;
		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;
		result.w = lhs.w;
		result.h = rhs.h;
		return result;
	}

	template<typename T1>
	constexpr friend auto operator*(const Rectangle &lhs, const Rectangle<T1> &rhs) {
		Rectangle<decltype(lhs.x + rhs.x)> result;
		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;
		result.w = std::min(lhs.w, rhs.w - lhs.x);
		result.h = std::min(lhs.h, rhs.h - lhs.y);
		return result;
	}

	template<typename T1>
	constexpr friend auto operator+=(Rectangle &lhs, const Rectangle<T1> &rhs) {
		return lhs = lhs + rhs;
	}

	template<typename T1>
	constexpr friend auto operator*=(Rectangle &lhs, const Rectangle<T1> &rhs) {
		return lhs = lhs * rhs;
	}

	constexpr const Vector<T, 2> &xy() const { return *reinterpret_cast<const Vector<T, 2> *>(this); }
	constexpr Vector<T, 2> &xy() { return *reinterpret_cast<Vector<T, 2> *>(this); }

	constexpr const Vector<T, 2> &wh() const { return *reinterpret_cast<const Vector<T, 2> *>(this + (2 * sizeof(T))); }
	constexpr Vector<T, 2> &wh() { return *reinterpret_cast<Vector<T, 2> *>(this + (2 * sizeof(T))); }

	T x{}, y{};
	T w{}, h{};
};

using Rectanglef = Rectangle<float>;
using Rectangled = Rectangle<double>;
using Rectanglei = Rectangle<int32_t>;
using Rectangleui = Rectangle<uint32_t>;
}

namespace std {
template<typename T>
struct hash<MathsCPP::Rectangle<T>> {
	size_t operator()(const MathsCPP::Rectangle<T> &rectangle) const noexcept {
		size_t seed = 0;
		MathsCPP::Maths::HashCombine(seed, rectangle.xy());
		MathsCPP::Maths::HashCombine(seed, rectangle.wh());
		return seed;
	}
};
}
