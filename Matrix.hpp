#pragma once

#include "Vector.hpp"

namespace acid {
template<typename T, std::size_t N, std::size_t M> class Matrix;

template<typename T, std::size_t N>
class Matrix<T, N, 1> {
public:
	constexpr Matrix() = default;
	constexpr Matrix(const Vector<T, N> &x) : x(x) {}
	constexpr explicit Matrix(T s) : x(s) {}
	template<typename U>
	constexpr explicit Matrix(const Matrix<U, N, 1> &m) : Matrix(Vector<T, N>(m.x)) {}

	constexpr const Vector<T, N> &operator[](std::size_t i) const { return x; }
	constexpr Vector<T, N> &operator[](std::size_t i) { return x; }

	
	Vector<T, N> x;
};

template<typename T, std::size_t N>
class Matrix<T, N, 2> {
public:
	constexpr Matrix() = default;
	constexpr Matrix(const Vector<T, N> &x, const Vector<T, N> &y) : x(x), y(y) {}
	constexpr explicit Matrix(T s) : x(s), y(s) {}
	template<typename U>
	constexpr explicit Matrix(const Matrix<U, N, 2> &m) : Matrix(Vector<T, N>(m.x), Vector<T, N>(m.y)) {}

	constexpr const Vector<T, N> &operator[](std::size_t i) const { return i == 0 ? x : y; }
	constexpr Vector<T, N> &operator[](std::size_t i) { return i == 0 ? x : y; }


	Vector<T, N> x, y;
};

template<typename T, std::size_t N>
class Matrix<T, N, 3> {
public:
	constexpr Matrix() = default;
	constexpr Matrix(const Vector<T, N> &x, const Vector<T, N> &y, const Vector<T, N> &z) : x(x), y(y), z(z) {}
	constexpr explicit Matrix(T s) : x(s), y(s), z(s) {}
	template<typename U>
	constexpr explicit Matrix(const Matrix<U, N, 3> &m) : Matrix(Vector<T, N>(m.x), Vector<T, N>(m.y), Vector<T, N>(m.z)) {}

	constexpr const Vector<T, N> &operator[](std::size_t i) const { return i == 0 ? x : i == 1 ? y : z; }
	constexpr Vector<T, N> &operator[](std::size_t i) { return i == 0 ? x : i == 1 ? y : z; }


	Vector<T, N> x, y, z;
};

template<typename T, std::size_t N>
class Matrix<T, N, 4> {
public:
	constexpr Matrix() = default;
	constexpr Matrix(const Vector<T, N> &x, const Vector<T, N> &y, const Vector<T, N> &z, const Vector<T, N> &w) : x(x), y(y), z(z), w(w) {}
	constexpr explicit Matrix(T s) : x(s), y(s), z(s), w(s) {}
	template<typename U>
	constexpr explicit Matrix(const Matrix<U, N, 4> &m) : Matrix(Vector<T, N>(m.x), Vector<T, N>(m.y), Vector<T, N>(m.z), Vector<T, N>(m.w)) {}

	constexpr const Vector<T, N> &operator[](std::size_t i) const { return i == 0 ? x : i == 1 ? y : i == 2 ? z : w; }
	constexpr Vector<T, N> &operator[](std::size_t i) { return i == 0 ? x : i == 1 ? y : i == 2 ? z : w; }


	Vector<T, N> x, y, z, w;
};

/// Should projection matrices be generated assuming forward is {0,0,-1} or {0,0,1}
enum class ForwardAxis { NegZ, PosZ };
/// Should projection matrices map z into the range of [-1,1] or [0,1]?
enum class ZRange { NegOneToOne, ZeroToOne };
template<typename T>
Matrix<T, 4, 4> FrustumMatrix(T x0, T x1, T y0, T y1, T n, T f, ForwardAxis a = ForwardAxis::NegZ, ZRange z = ZRange::NegOneToOne) {
	const T s = a == ForwardAxis::PosZ ? T(1) : T(-1);
	const T o = z == ZRange::NegOneToOne ? n : T(0);
	return {
		{2 * n / (x1 - x0), 0, 0, 0},
		{0, 2 * n / (y1 - y0), 0, 0},
		{-s * (x0 + x1) / (x1 - x0), -s * (y0 + y1) / (y1 - y0), s * (f + o) / (f - n), s},
		{0, 0, -(n + o) * f / (f - n), 0}
	};
}
template<typename T>
Matrix<T, 4, 4> PerspectiveMatrix(T fovy, T aspect, T n, T f, ForwardAxis a = ForwardAxis::NegZ, ZRange z = ZRange::NegOneToOne) {
	T y = n * std::tan(fovy / 2);
	T x = y * aspect;
	return FrustumMatrix(-x, x, -y, y, n, f, a, z);
}

using Matrix1x1 = Matrix<float, 1, 1>;
using Matrix2x2 = Matrix<float, 2, 2>;
using Matrix3x3 = Matrix<float, 3, 3>;
using Matrix4x4 = Matrix<float, 4, 4>;
}
