#pragma once

#include <array>
#include <cstdint>

namespace acid {
template<typename T, std::size_t N>
class VectorBase {
public:
	constexpr VectorBase() = default;
	template<typename ...Args, typename = std::enable_if_t<sizeof...(Args) == N>>
	constexpr VectorBase(Args... args) : data{args...} {}
	constexpr explicit VectorBase(T s) { data.fill(s); }
	template<typename U>
	constexpr VectorBase(const VectorBase<U, N> &v) { std::copy(v.data.begin(), v.data.end(), data.begin()); }

	template<typename U>
	constexpr VectorBase &operator=(const VectorBase &v) {
		std::copy(v.data.begin(), v.data.end(), data.begin());
		return *this;
	}

	constexpr const T &operator[](std::size_t i) const { return data[i]; }
	constexpr T &operator[](std::size_t i) { return data[i]; }

	
	std::array<T, N> data{};
};

template<typename T>
class VectorBase<T, 1> {
public:
	constexpr VectorBase() = default;
	constexpr VectorBase(T x) : x(x) {}
	template<typename U>
	constexpr VectorBase(const VectorBase<U, 1> &v) : VectorBase(static_cast<T>(v.x)) {}

	template<typename U>
	constexpr VectorBase &operator=(const VectorBase &v) {
		x = static_cast<T>(v.x);
		return *this;
	}

	constexpr const T &operator[](std::size_t i) const { return x; }
	constexpr T &operator[](std::size_t i) { return x; }

	
	T x{};
};

template<typename T>
class VectorBase<T, 2> {
public:
	constexpr VectorBase() = default;
	constexpr VectorBase(T x, T y) : x(x), y(y) {}
	constexpr explicit VectorBase(T s) : x(s), y(s) {}
	template<typename U>
	constexpr VectorBase(const VectorBase<U, 2> &v) : VectorBase(static_cast<T>(v.x), static_cast<T>(v.y)) {}

	template<typename U>
	constexpr VectorBase &operator=(const VectorBase &v) {
		x = static_cast<T>(v.x);
		y = static_cast<T>(v.y);
		return *this;
	}

	constexpr const T &operator[](std::size_t i) const { return i == 0 ? x : y; }
	constexpr T &operator[](std::size_t i) { return i == 0 ? x : y; }

	
	T x{}, y{};
};

template<typename T>
class VectorBase<T, 3> {
public:
	constexpr VectorBase() = default;
	constexpr VectorBase(T x, T y, T z) : x(x), y(y), z(z) {}
	constexpr explicit VectorBase(T s) : x(s), y(s), z(s) {}
	constexpr VectorBase(const VectorBase<T, 2> &xy, T z) : x(xy.x), y(xy.y), z(z) {}
	template<typename U>
	constexpr VectorBase(const VectorBase<U, 3> &v) : VectorBase(static_cast<T>(v.x), static_cast<T>(v.y), static_cast<T>(v.z)) {}

	template<typename U>
	constexpr VectorBase &operator=(const VectorBase &v) {
		x = static_cast<T>(v.x);
		y = static_cast<T>(v.y);
		z = static_cast<T>(v.z);
		return *this;
	}

	constexpr const T &operator[](std::size_t i) const { return i == 0 ? x : i == 1 ? y : z; }
	constexpr T &operator[](std::size_t i) { return i == 0 ? x : i == 1 ? y : z; }

	
	T x{}, y{}, z{};
};

template<typename T>
class VectorBase<T, 4> {
public:
	constexpr VectorBase() = default;
	constexpr VectorBase(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
	constexpr explicit VectorBase(T s) : x(s), y(s), z(s), w(s) {}
	constexpr VectorBase(const VectorBase<T, 2> &xy, T z, T w) : x(xy.x), y(xy.y), z(z), w(w) {}
	constexpr VectorBase(const VectorBase<T, 3> &xyz, T w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
	template<typename U>
	constexpr VectorBase(const VectorBase<U, 4> &v) : VectorBase(static_cast<T>(v.x), static_cast<T>(v.y), static_cast<T>(v.z), static_cast<T>(v.w)) {}

	template<typename U>
	constexpr VectorBase &operator=(const VectorBase &v) {
		x = static_cast<T>(v.x);
		y = static_cast<T>(v.y);
		z = static_cast<T>(v.z);
		w = static_cast<T>(v.w);
		return *this;
	}

	constexpr const T &operator[](std::size_t i) const { return i == 0 ? x : i == 1 ? y : i == 2 ? z : w; }
	constexpr T &operator[](std::size_t i) { return i == 0 ? x : i == 1 ? y : i == 2 ? z : w; }

	
	T x{}, y{}, z{}, w{};
};

template<typename T, std::size_t N>
class Vector : public VectorBase<T, N> {
public:
	constexpr Vector() = default;
	template<typename ...Args, typename = std::enable_if_t<sizeof...(Args) == N>>
	constexpr Vector(Args... args) : VectorBase(args...) {}
	constexpr explicit Vector(T s) : VectorBase(s) {}
	template<typename U, std::size_t S, typename... Args, typename = std::enable_if_t<S < N && sizeof...(Args) == (N - S)>>
	constexpr explicit Vector(const Vector<U, S> &v, Args... args) : VectorBase(v, args...) {}

	constexpr T Dot(const Vector &other) const {
		T result = 0;
		for (std::size_t i = 0; i < N; i++)
			result += (*this)[i] * other[i];
		return result;
	}

	constexpr T Length2() const {
		return Dot(*this);
	}
	auto Length() const {
		return std::sqrt(Length2());
	}

	constexpr auto Normalize() const {
		return *this / Length();
	}

	template<typename = std::enable_if_t<N == 2>>
	constexpr T Cross(const Vector &other) const {
		return x * other.y - y * other.x;
	}
	template<typename = std::enable_if_t<N == 3>>
	constexpr Vector Cross(const Vector &other) const {
		return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
	}

	constexpr T Distance2(const Vector &other) const {
		return (other - *this).Length2();
	}
	constexpr auto Distance(const Vector &other) const {
		return (other - *this).Length();
	}

	constexpr T Uangle(const Vector &other) const {
		const T d = Dot(other);
		return d > 1 ? 0 : std::acos(d < -1 ? -1 : d);
	}
	constexpr T Angle(const Vector &other) const {
		return Normalize().Uangle(other.Normalize());
	}

	constexpr auto Lerp(const Vector &other, T c) const {
		return *this * (1 - c) + other * c;
	}
	constexpr T Nlerp(const Vector &other, T t) const {
		return Lerp(other, t).Normalize();
	}
	constexpr T Slerp(const Vector &other, T t) const {
		T th = Uangle(other);
		return th == 0 ? *this : *this * (std::sin(th * (1 - t)) / std::sin(th)) + other * (std::sin(th * t) / std::sin(th));
	}

	template<typename = std::enable_if_t<N == 2>>
	constexpr Vector Rotate(T a) const {
		const T s = std::sin(a);
		const T c = std::cos(a);
		return {x * c - y * s, x * s + y * c};
	}


	template<typename = std::enable_if_t<N >= 2>>
	constexpr const Vector<T, 2> &xy() const { return *reinterpret_cast<const Vector<T, 2> *>(this); }
	template<typename = std::enable_if_t<N >= 2>>
	constexpr Vector<T, 2> &xy() { return *reinterpret_cast<Vector<T, 2> *>(this); }
	template<typename = std::enable_if_t<N >= 3>>
	constexpr const Vector<T, 3> &xyz() const { return *reinterpret_cast<const Vector<T, 3> *>(this); }
	template<typename = std::enable_if_t<N >= 3>>
	constexpr Vector<T, 3> &xyz() { return *reinterpret_cast<Vector<T, 3> *>(this); }


	static const Vector Zero;
	static const Vector One;
	static const Vector Infinity;
	static const Vector Right;
	static const Vector Left;
	static const Vector Up;
	static const Vector Down;
	static const Vector Front;
	static const Vector Back;

};


template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::Zero = Vector<T, N>(0);
template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::One = Vector<T, N>(1);
template<typename T, std::size_t N>
constexpr Vector<T, N> Vector<T, N>::Infinity = Vector<T, N>(std::numeric_limits<T>::infinity());
template<typename T, std::size_t N> // std::enable_if_t<N <= 2, int> = 0
constexpr Vector<T, N> Vector<T, N>::Right = Vector<T, N>(1, 0);
template<typename T, std::size_t N> // std::enable_if_t<N <= 2, int> = 0
constexpr Vector<T, N> Vector<T, N>::Left = Vector<T, N>(-1, 0);
template<typename T, std::size_t N> // std::enable_if_t<N <= 2, int> = 0
constexpr Vector<T, N> Vector<T, N>::Up = Vector<T, N>(0, 1);
template<typename T, std::size_t N> // std::enable_if_t<N <= 2, int> = 0
constexpr Vector<T, N> Vector<T, N>::Down = Vector<T, N>(0, -1);
template<typename T, std::size_t N> // std::enable_if_t<N <= 3, int> = 0
constexpr Vector<T, N> Vector<T, N>::Front = Vector<T, N>(0, 0, 1);
template<typename T, std::size_t N> // std::enable_if_t<N <= 3, int> = 0
constexpr Vector<T, N> Vector<T, N>::Back = Vector<T, N>(0, 0, -1);


using Vector1f = Vector<float, 1>;
using Vector1i = Vector<int32_t, 1>;

using Vector2f = Vector<float, 2>;
using Vector2i = Vector<int32_t, 2>;

using Vector3f = Vector<float, 3>;
using Vector3i = Vector<int32_t, 3>;

using Vector4f = Vector<float, 4>;
using Vector4i = Vector<int32_t, 4>;
}

#include "Vector.inl"
