#pragma once

#include <cassert>

namespace acid {
template<typename T, std::size_t N> class Vector;

template<typename T>
class Vector<T, 1> {
public:
	constexpr Vector() = default;
	constexpr Vector(T x) : x(x) {}
	template<typename U>
	constexpr explicit Vector(const Vector<U, 1> &v) : Vector(static_cast<T>(v.x)) {}

	constexpr const T &operator[](std::size_t i) const { return x; }
	constexpr T &operator[](std::size_t i) { return x; }

	
	T x{};
};

template<typename T>
class Vector<T, 2> {
public:
	constexpr Vector() = default;
	constexpr Vector(T x, T y) : x(x), y(y) {}
	constexpr explicit Vector(T s) : x(s), y(s) {}
	template<typename U>
	constexpr explicit Vector(const Vector<U, 2> &v) : Vector(static_cast<T>(v.x), static_cast<T>(v.y)) {}

	constexpr const T &operator[](std::size_t i) const { return i == 0 ? x : y; }
	constexpr T &operator[](std::size_t i) { return i == 0 ? x : y; }


	T x{}, y{};
};

template<typename T>
class Vector<T, 3> {
public:
	constexpr Vector() = default;
	constexpr Vector(T x, T y, T z) : x(x), y(y), z(z) {}
	constexpr explicit Vector(T s) : x(s), y(s), z(s) {}
	constexpr Vector(const Vector<T, 2> &xy, T z) : x(xy.x), y(xy.y), z(z) {}
	template<typename U>
	constexpr explicit Vector(const Vector<U, 3> &v) : Vector(static_cast<T>(v.x), static_cast<T>(v.y), static_cast<T>(v.z)) {}

	constexpr const T &operator[](std::size_t i) const { return i == 0 ? x : i == 1 ? y : z; }
	constexpr T &operator[](std::size_t i) { return i == 0 ? x : i == 1 ? y : z; }

	constexpr const Vector<T, 2> &xy() const { return *reinterpret_cast<const Vector<T, 2> *>(this); }
	constexpr Vector<T, 2> &xy() { return *reinterpret_cast<Vector<T, 2> *>(this); }


	T x{}, y{}, z{};
};

template<typename T>
class Vector<T, 4> {
public:
	constexpr Vector() = default;
	constexpr Vector(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
	constexpr explicit Vector(T s) : x(s), y(s), z(s), w(s) {}
	constexpr Vector(const Vector<T, 2> &xy, T z, T w) : x(xy.x), y(xy.y), z(z), w(w) {}
	constexpr Vector(const Vector<T, 3> &xyz, T w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
	template<typename U>
	constexpr explicit Vector(const Vector<U, 4> &v) : Vector(static_cast<T>(v.x), static_cast<T>(v.y), static_cast<T>(v.z), static_cast<T>(v.w)) {}

	constexpr const T &operator[](std::size_t i) const { return i == 0 ? x : i == 1 ? y : i == 2 ? z : w; }
	constexpr T &operator[](std::size_t i) { return i == 0 ? x : i == 1 ? y : i == 2 ? z : w; }

	constexpr const Vector<T, 2> &xy() const { return *reinterpret_cast<const Vector<T, 2> *>(this); }
	constexpr Vector<T, 2> &xy() { return *reinterpret_cast<Vector<T, 2> *>(this); }
	constexpr const Vector<T, 3> &xyz() const { return *reinterpret_cast<const Vector<T, 3> *>(this); }
	constexpr Vector<T, 3> &xyz() { return *reinterpret_cast<Vector<T, 3> *>(this); }
	

	T x{}, y{}, z{}, w{};
};

using Vector1 = Vector<float, 1>;
using Vector2 = Vector<float, 2>;
using Vector3 = Vector<float, 3>;
using Vector4 = Vector<float, 4>;
}

#include "Vector.inl"
