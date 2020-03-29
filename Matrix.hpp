#pragma once

#include "Vector.hpp"

namespace acid {
template<typename T, std::size_t N, std::size_t M>
class MatrixBase {
public:
	constexpr MatrixBase() = default;
	template<typename ...Args, typename = std::enable_if_t<sizeof...(Args) == N>>
	constexpr MatrixBase(Args... args) : data{args...} {}
	constexpr explicit MatrixBase(Vector<T, N> s) { data.fill(s); }
	template<typename U>
	constexpr MatrixBase(const MatrixBase<U, N, M> &v) { std::copy(v.data.begin(), v.data.end(), data.begin()); }

	template<typename U>
	constexpr MatrixBase &operator=(const MatrixBase &v) {
		std::copy(v.data.begin(), v.data.end(), data.begin());
		return *this;
	}

	constexpr const T &operator[](std::size_t i) const { return data[i]; }
	constexpr T &operator[](std::size_t i) { return data[i]; }

	
	std::array<Vector<T, N>, M> data{};
};

template<typename T, std::size_t N>
class MatrixBase<T, N, 1> {
public:
	constexpr MatrixBase() = default;
	constexpr MatrixBase(const Vector<T, N> &x) : x(x) {}
	constexpr explicit MatrixBase(T s) : x(s) {}
	template<typename U>
	constexpr explicit MatrixBase(const MatrixBase<U, N, 1> &m) : MatrixBase(Vector<T, N>(m.x)) {}

	template<typename U>
	constexpr MatrixBase &operator=(const MatrixBase &v) {
		x = static_cast<T>(v.x);
		return *this;
	}

	constexpr const Vector<T, N> &operator[](std::size_t i) const { return x; }
	constexpr Vector<T, N> &operator[](std::size_t i) { return x; }


	Vector<T, N> x;
};

template<typename T, std::size_t N>
class MatrixBase<T, N, 2> {
public:
	constexpr MatrixBase() = default;
	constexpr MatrixBase(const Vector<T, N> &x, const Vector<T, N> &y) : x(x), y(y) {}
	constexpr explicit MatrixBase(T s) : x(s), y(s) {}
	template<typename U>
	constexpr explicit MatrixBase(const MatrixBase<U, N, 2> &m) : MatrixBase(Vector<T, N>(m.x), Vector<T, N>(m.y)) {}

	template<typename U>
	constexpr MatrixBase &operator=(const MatrixBase &v) {
		x = static_cast<T>(v.x);
		y = static_cast<T>(v.y);
		return *this;
	}

	constexpr const Vector<T, N> &operator[](std::size_t i) const { return i == 0 ? x : y; }
	constexpr Vector<T, N> &operator[](std::size_t i) { return i == 0 ? x : y; }


	Vector<T, N> x, y;
};
template<typename T, std::size_t N>
class MatrixBase<T, N, 3> {
public:
	constexpr MatrixBase() = default;
	constexpr MatrixBase(const Vector<T, N> &x, const Vector<T, N> &y, const Vector<T, N> &z) : x(x), y(y), z(z) {}
	constexpr explicit MatrixBase(T s) : x(s), y(s), z(s) {}
	template<typename U>
	constexpr explicit MatrixBase(const MatrixBase<U, N, 3> &m) : MatrixBase(Vector<T, N>(m.x), Vector<T, N>(m.y), Vector<T, N>(m.z)) {}

	template<typename U>
	constexpr MatrixBase &operator=(const MatrixBase &v) {
		x = static_cast<T>(v.x);
		y = static_cast<T>(v.y);
		z = static_cast<T>(v.z);
		return *this;
	}

	constexpr const Vector<T, N> &operator[](std::size_t i) const { return i == 0 ? x : i == 1 ? y : z; }
	constexpr Vector<T, N> &operator[](std::size_t i) { return i == 0 ? x : i == 1 ? y : z; }


	Vector<T, N> x, y, z;
};

template<typename T, std::size_t N>
class MatrixBase<T, N, 4> {
public:
	constexpr MatrixBase() = default;
	constexpr MatrixBase(const Vector<T, N> &x, const Vector<T, N> &y, const Vector<T, N> &z, const Vector<T, N> &w) : x(x), y(y), z(z), w(w) {}
	constexpr explicit MatrixBase(T s) : x(s), y(s), z(s), w(s) {}
	template<typename U>
	constexpr explicit MatrixBase(const MatrixBase<U, N, 4> &m) : MatrixBase(Vector<T, N>(m.x), Vector<T, N>(m.y), Vector<T, N>(m.z), Vector<T, N>(m.w)) {}

	template<typename U>
	constexpr MatrixBase &operator=(const MatrixBase &v) {
		x = static_cast<T>(v.x);
		y = static_cast<T>(v.y);
		z = static_cast<T>(v.z);
		w = static_cast<T>(v.w);
		return *this;
	}

	constexpr const Vector<T, N> &operator[](std::size_t i) const { return i == 0 ? x : i == 1 ? y : i == 2 ? z : w; }
	constexpr Vector<T, N> &operator[](std::size_t i) { return i == 0 ? x : i == 1 ? y : i == 2 ? z : w; }


	Vector<T, N> x, y, z, w;
};

/// Should projection matrices be generated assuming forward is {0,0,-1} or {0,0,1}
enum class ForwardAxis { NegZ, PosZ };
/// Should projection matrices map z into the range of [-1,1] or [0,1]?
enum class ZRange { NegOneToOne, ZeroToOne };

template<typename T, std::size_t N, std::size_t M>
class Matrix : public MatrixBase<T, N, M> {
public:
	constexpr Matrix() = default;
	template<typename ...Args, typename = std::enable_if_t<sizeof...(Args) == N>>
	constexpr Matrix(Args... args) : MatrixBase(args...) {}
	template<typename U, std::size_t S, std::size_t A>
	constexpr explicit Matrix(const Matrix<U, S, A> &m) : MatrixBase(m) {}

	template<typename = std::enable_if_t<N == 4 && M == 4>>
	static Matrix<T, 4, 4> FrustumMatrix(T x0, T x1, T y0, T y1, T n, T f, ForwardAxis a = ForwardAxis::NegZ, ZRange z = ZRange::NegOneToOne) {
		const T s = a == ForwardAxis::PosZ ? T(1) : T(-1);
		const T o = z == ZRange::NegOneToOne ? n : T(0);
		return {
			{2 * n / (x1 - x0), 0, 0, 0},
			{0, 2 * n / (y1 - y0), 0, 0},
			{-s * (x0 + x1) / (x1 - x0), -s * (y0 + y1) / (y1 - y0), s * (f + o) / (f - n), s},
			{0, 0, -(n + o) * f / (f - n), 0}
		};
	}
	template<typename = std::enable_if_t<N == 4 && M == 4>>
	static Matrix<T, 4, 4> PerspectiveMatrix(T fovy, T aspect, T n, T f, ForwardAxis a = ForwardAxis::NegZ, ZRange z = ZRange::NegOneToOne) {
		T y = n * std::tan(fovy / 2);
		T x = y * aspect;
		return FrustumMatrix(-x, x, -y, y, n, f, a, z);
	}
};

using Matrix1x1f = Matrix<float, 1, 1>;
using Matrix2x2f = Matrix<float, 2, 2>;
using Matrix3x3f = Matrix<float, 3, 3>;
using Matrix4x4f = Matrix<float, 4, 4>;
}
