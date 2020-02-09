#pragma once

#include <array>
#include <cstdint>

namespace acid {
template<typename T, std::size_t N>
class VectorBase {
public:
	constexpr VectorBase() = default;
	constexpr VectorBase(const VectorBase &) = default;
	constexpr VectorBase(VectorBase &&) = default;
	template<typename ...Args, typename = std::enable_if_t<sizeof...(Args) == N>>
	constexpr VectorBase(Args... args) : data{args...} {}
	constexpr explicit VectorBase(T s) { data.fill(s); }
	template<typename U>
	constexpr VectorBase(const VectorBase<U, N> &v) { std::copy(v.data.begin(), v.data.end(), data.begin()); }

	constexpr VectorBase &operator=(const VectorBase &) = default;
	constexpr VectorBase &operator=(VectorBase &&) = default;

	constexpr const T &operator[](std::size_t i) const { return data[i]; }
	constexpr T &operator[](std::size_t i) { return data[i]; }

	std::array<T, N> data{};
};

template<typename T>
class VectorBase<T, 1> {
	constexpr VectorBase() = default;
	constexpr VectorBase(const VectorBase &) = default;
	constexpr VectorBase(VectorBase &&) = default;
	constexpr VectorBase(T x) : x(x) {}
	template<typename U>
	constexpr VectorBase(const VectorBase<U, 1> &v) : VectorBase(static_cast<T>(v.x)) {}

	constexpr VectorBase &operator=(const VectorBase &) = default;
	constexpr VectorBase &operator=(VectorBase &&) = default;

	constexpr const T &operator[](std::size_t i) const { return x; }
	constexpr T &operator[](std::size_t i) { return x; }

	T x{};
};

template<typename T>
class VectorBase<T, 2> {
public:
	constexpr VectorBase() = default;
	constexpr VectorBase(const VectorBase &) = default;
	constexpr VectorBase(VectorBase &&) = default;
	constexpr VectorBase(T x, T y) : x(x), y(y) {}
	constexpr explicit VectorBase(T s) : x(s), y(s) {}
	template<typename U>
	constexpr VectorBase(const VectorBase<U, 2> &v) : VectorBase(static_cast<T>(v.x), static_cast<T>(v.y)) {}

	constexpr VectorBase &operator=(const VectorBase &) = default;
	constexpr VectorBase &operator=(VectorBase &&) = default;

	constexpr const T &operator[](std::size_t i) const { return i == 0 ? x : y; }
	constexpr T &operator[](std::size_t i) { return i == 0 ? x : y; }

	T x{}, y{};
};

template<typename T>
class VectorBase<T, 3> {
public:
	constexpr VectorBase() = default;
	constexpr VectorBase(const VectorBase &) = default;
	constexpr VectorBase(VectorBase &&) = default;
	constexpr VectorBase(T x, T y, T z) : x(x), y(y), z(z) {}
	constexpr explicit VectorBase(T s) : x(s), y(s), z(s) {}
	constexpr VectorBase(const VectorBase<T, 2> &xy, T z) : x(xy.x), y(xy.y), z(z) {}
	template<typename U>
	constexpr VectorBase(const VectorBase<U, 3> &v) : VectorBase(static_cast<T>(v.x), static_cast<T>(v.y), static_cast<T>(v.z)) {}

	constexpr VectorBase &operator=(const VectorBase &) = default;
	constexpr VectorBase &operator=(VectorBase &&) = default;

	constexpr const T &operator[](std::size_t i) const { return i == 0 ? x : i == 1 ? y : z; }
	constexpr T &operator[](std::size_t i) { return i == 0 ? x : i == 1 ? y : z; }

	constexpr const VectorBase<T, 2> &xy() const { return *reinterpret_cast<const VectorBase<T, 2> *>(this); }
	constexpr VectorBase<T, 2> &xy() { return *reinterpret_cast<VectorBase<T, 2> *>(this); }

	T x{}, y{}, z{};
};

template<typename T>
class VectorBase<T, 4> {
public:
	constexpr VectorBase() = default;
	constexpr VectorBase(const VectorBase &) = default;
	constexpr VectorBase(VectorBase &&) = default;
	constexpr VectorBase(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
	constexpr explicit VectorBase(T s) : x(s), y(s), z(s), w(s) {}
	constexpr VectorBase(const VectorBase<T, 2> &xy, T z, T w) : x(xy.x), y(xy.y), z(z), w(w) {}
	constexpr VectorBase(const VectorBase<T, 3> &xyz, T w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
	template<typename U>
	constexpr VectorBase(const VectorBase<U, 4> &v) : VectorBase(static_cast<T>(v.x), static_cast<T>(v.y), static_cast<T>(v.z), static_cast<T>(v.w)) {}

	constexpr VectorBase &operator=(const VectorBase &) = default;
	constexpr VectorBase &operator=(VectorBase &&) = default;

	constexpr const T &operator[](std::size_t i) const { return i == 0 ? x : i == 1 ? y : i == 2 ? z : w; }
	constexpr T &operator[](std::size_t i) { return i == 0 ? x : i == 1 ? y : i == 2 ? z : w; }

	constexpr const VectorBase<T, 2> &xy() const { return *reinterpret_cast<const VectorBase<T, 2> *>(this); }
	constexpr VectorBase<T, 2> &xy() { return *reinterpret_cast<VectorBase<T, 2> *>(this); }
	constexpr const VectorBase<T, 3> &xyz() const { return *reinterpret_cast<const VectorBase<T, 3> *>(this); }
	constexpr VectorBase<T, 3> &xyz() { return *reinterpret_cast<VectorBase<T, 3> *>(this); }

	T x{}, y{}, z{}, w{};
};

template<typename T, std::size_t N>
class Vector : public VectorBase<T, N> {
public:
	constexpr Vector() = default;
	template<typename ...Args, typename = std::enable_if_t<sizeof...(Args) == N>>
	constexpr Vector(Args... args) : VectorBase(args...) {}
	template<typename U, std::size_t S,
		typename... Args, typename = std::enable_if_t<(S < N) && (sizeof...(Args) == (N - S))>>
	constexpr explicit Vector(const Vector<U, S> &v, Args... args) : VectorBase(v, args...) {}

	constexpr T Dot(const Vector &other) {
		T result = 0;
		for (std::size_t i = 0; i < N; i++)
			result += (*this)[i] * other[i];
		return result;
	}

	/*template<typename T>
	constexpr T Cross(const Vector<T, 2> &a, const Vector<T, 2> &b) {
		return a.x * b.y - a.y * b.x;
	}
	template<typename T>
	constexpr Vector<T, 2> Cross(T a, const Vector<T, 2> &b) {
		return {-a * b.y, a * b.x};
	}
	template<typename T>
	constexpr Vector<T, 2> Cross(const Vector<T, 2> &a, T b) {
		return {a.y * b, -a.x * b};
	}*/
	template<typename = std::enable_if_t<N == 3>>
	constexpr Vector Cross(const Vector &other) {
		return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
	}

	constexpr T Length2() {
		return dot(*this, *this);
	}
	auto Length() {
		return std::sqrt(Length2());
	}

	constexpr auto Normalize() {
		return *this / Length();
	}

	constexpr T Distance2(const Vector &other) {
		return (other - *this).Length2();
	}
	constexpr auto Distance(const Vector &other) {
		return (other - *this).Length();
	}

};

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
