#pragma once

#include <cmath>
#include <type_traits>

#include "Vector.hpp"

namespace acid {
template<typename T1, typename T2, std::size_t N>
constexpr auto operator==(const Vector<T1, N> &lhs, const Vector<T2, N> &rhs) {
	for (std::size_t i = 0; i < N; i++) {
		if (lhs[i] != rhs[i])
			return false;
	}
	return true;
}

template<typename T1, typename T2, std::size_t N>
constexpr auto operator!=(const Vector<T1, N> &lhs, const Vector<T2, N> &rhs) {
	for (std::size_t i = 0; i < N; i++) {
		if (lhs[i] != rhs[i])
			return true;
	}
	return false;
}

template<typename T, std::size_t N>
constexpr auto operator+(const Vector<T, N> &lhs) {
	Vector<T, N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = +lhs[i];
	return result;
}

template<typename T, std::size_t N>
constexpr auto operator-(const Vector<T, N> &lhs) {
	Vector<T, N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = -lhs[i];
	return result;
}

template<typename T, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T>>>
constexpr auto operator~(const Vector<T, N> &lhs) {
	Vector<T, N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = ~lhs[i];
	return result;
}

template<typename T, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T>>>
constexpr auto operator!(const Vector<T, N> &lhs) {
	Vector<T, N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = !lhs[i];
	return result;
}

template<typename T1, typename T2, std::size_t N>
constexpr auto operator+(const Vector<T1, N> &lhs, const Vector<T2, N> &rhs) {
	Vector<decltype(lhs[0] + rhs[0]), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs[i] + rhs[i];
	return result;
}

template<typename T1, typename T2, std::size_t N>
constexpr auto operator-(const Vector<T1, N> &lhs, const Vector<T2, N> &rhs) {
	Vector<decltype(lhs[0] - rhs[0]), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs[i] - rhs[i];
	return result;
}

template<typename T1, typename T2, std::size_t N>
constexpr auto operator*(const Vector<T1, N> &lhs, const Vector<T2, N> &rhs) {
	Vector<decltype(lhs[0] * rhs[0]), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs[i] * rhs[i];
	return result;
}

template<typename T1, typename T2, std::size_t N>
constexpr auto operator/(const Vector<T1, N> &lhs, const Vector<T2, N> &rhs) {
	Vector<decltype(lhs[0] / rhs[0]), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs[i] / rhs[i];
	return result;
}

template<typename T1, typename T2, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>>>
constexpr auto operator%(const Vector<T1, N> &lhs, const Vector<T2, N> &rhs) {
	Vector<decltype(lhs[0] % rhs[0]), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs[i] & rhs[i];
	return result;
}

template<typename T1, typename T2, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>>>
constexpr auto operator|(const Vector<T1, N> &lhs, const Vector<T2, N> &rhs) {
	Vector<decltype(lhs[0] | rhs[0]), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs[i] | rhs[i];
	return result;
}

template<typename T1, typename T2, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>>>
constexpr auto operator^(const Vector<T1, N> &lhs, const Vector<T2, N> &rhs) {
	Vector<decltype(lhs[0] ^ rhs[0]), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs[i] ^ rhs[i];
	return result;
}

template<typename T1, typename T2, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>>>
constexpr auto operator&(const Vector<T1, N> &lhs, const Vector<T2, N> &rhs) {
	Vector<decltype(lhs[0] & rhs[0]), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs[i] & rhs[i];
	return result;
}

template<typename T1, typename T2, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>>>
constexpr auto operator<<(const Vector<T1, N> &lhs, const Vector<T2, N> &rhs) {
	Vector<decltype(lhs[0] << rhs[0]), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs[i] << rhs[i];
	return result;
}

template<typename T1, typename T2, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>>>
constexpr auto operator>>(const Vector<T1, N> &lhs, const Vector<T2, N> &rhs) {
	Vector<decltype(lhs[0] >> rhs[0]), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs[i] >> rhs[i];
	return result;
}

template<typename T1, typename T2, std::size_t N>
constexpr auto operator*(const Vector<T1, N> &lhs, T2 rhs) {
	Vector<decltype(lhs[0] * rhs), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs[i] * rhs;
	return result;
}

template<typename T1, typename T2, std::size_t N>
constexpr auto operator/(const Vector<T1, N> &lhs, T2 rhs) {
	Vector<decltype(lhs[0] / rhs), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs[i] / rhs;
	return result;
}

template<typename T1, typename T2, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>>>
constexpr auto operator%(const Vector<T1, N> &lhs, T2 rhs) {
	Vector<decltype(lhs[0] % rhs), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs[i] & rhs;
	return result;
}

template<typename T1, typename T2, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>>>
constexpr auto operator|(const Vector<T1, N> &lhs, T2 rhs) {
	Vector<decltype(lhs[0] | rhs), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs[i] | rhs;
	return result;
}

template<typename T1, typename T2, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>>>
constexpr auto operator^(const Vector<T1, N> &lhs, T2 rhs) {
	Vector<decltype(lhs[0] ^ rhs), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs[i] ^ rhs;
	return result;
}

template<typename T1, typename T2, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>>>
constexpr auto operator&(const Vector<T1, N> &lhs, T2 rhs) {
	Vector<decltype(lhs[0] & rhs), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs[i] & rhs;
	return result;
}

template<typename T1, typename T2, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>>>
constexpr auto operator<<(const Vector<T1, N> &lhs, T2 rhs) {
	Vector<decltype(lhs[0] << rhs), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs[i] << rhs;
	return result;
}

template<typename T1, typename T2, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>>>
constexpr auto operator>>(const Vector<T1, N> &lhs, T2 rhs) {
	Vector<decltype(lhs[0] >> rhs), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs[i] >> rhs;
	return result;
}

template<typename T1, typename T2, std::size_t N>
constexpr auto operator*(T1 lhs, const Vector<T2, N> &rhs) {
	Vector<decltype(lhs * rhs[0]), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs * rhs[i];
	return result;
}

template<typename T1, typename T2, std::size_t N>
constexpr auto operator/(T1 lhs, const Vector<T2, N> &rhs) {
	Vector<decltype(lhs / rhs[0]), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs / rhs[i];
	return result;
}

template<typename T1, typename T2, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>>>
constexpr auto operator%(T1 lhs, const Vector<T2, N> &rhs) {
	Vector<decltype(lhs % rhs[0]), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs & rhs[i];
	return result;
}

template<typename T1, typename T2, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>>>
constexpr auto operator|(T1 lhs, const Vector<T2, N> &rhs) {
	Vector<decltype(lhs | rhs[0]), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs | rhs[i];
	return result;
}

template<typename T1, typename T2, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>>>
constexpr auto operator^(T1 lhs, const Vector<T2, N> &rhs) {
	Vector<decltype(lhs ^ rhs[0]), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs ^ rhs[i];
	return result;
}

template<typename T1, typename T2, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>>>
constexpr auto operator&(T1 lhs, const Vector<T2, N> &rhs) {
	Vector<decltype(lhs & rhs[0]), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs & rhs[i];
	return result;
}

template<typename T1, typename T2, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>>>
constexpr auto operator<<(T1 lhs, const Vector<T2, N> &rhs) {
	Vector<decltype(lhs << rhs[0]), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs << rhs[i];
	return result;
}

template<typename T1, typename T2, std::size_t N, typename = std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>>>
constexpr auto operator>>(T1 lhs, const Vector<T2, N> &rhs) {
	Vector<decltype(lhs >> rhs[0]), N> result;
	for (std::size_t i = 0; i < N; i++)
		result[i] = lhs >> rhs[i];
	return result;
}


template<typename T1, typename T2, std::size_t N>
constexpr auto operator+=(Vector<T1, N> &lhs, const T2 &rhs) {
	return lhs = lhs + rhs;
}

template<typename T1, typename T2, std::size_t N>
constexpr auto operator-=(Vector<T1, N> &lhs, const T2 &rhs) {
	return lhs = lhs - rhs;
}

template<typename T1, typename T2, std::size_t N>
constexpr auto operator*=(Vector<T1, N> &lhs, const T2 &rhs) {
	return lhs = lhs * rhs;
}

template<typename T1, typename T2, std::size_t N>
constexpr auto operator/=(Vector<T1, N> &lhs, const T2 &rhs) {
	return lhs = lhs / rhs;
}

template<typename T1, typename T2, std::size_t N>
constexpr auto operator%=(Vector<T1, N> &lhs, const T2 &rhs) {
	return lhs = lhs % rhs;
}

template<typename T1, typename T2, std::size_t N>
constexpr auto operator|=(Vector<T1, N> &lhs, const T2 &rhs) {
	return lhs = lhs | rhs;
}

template<typename T1, typename T2, std::size_t N>
constexpr auto operator^=(Vector<T1, N> &lhs, const T2 &rhs) {
	return lhs = lhs ^ rhs;
}

template<typename T1, typename T2, std::size_t N>
constexpr auto operator&=(Vector<T1, N> &lhs, const T2 &rhs) {
	return lhs = lhs & rhs;
}

template<typename T1, typename T2, std::size_t N>
constexpr auto operator<<=(Vector<T1, N> &lhs, const T2 &rhs) {
	return lhs = lhs << rhs;
}

template<typename T1, typename T2, std::size_t N>
constexpr auto operator>>=(Vector<T1, N> &lhs, const T2 &rhs) {
	return lhs = lhs >> rhs;
}

template<typename T>
constexpr T cross(const Vector<T, 2> &a, const Vector<T, 2> &b) {
	return a.x * b.y - a.y * b.x;
}
template<typename T>
constexpr Vector<T, 2> cross(T a, const Vector<T, 2> &b) {
	return {-a * b.y, a * b.x};
}
template<typename T>
constexpr Vector<T, 2> cross(const Vector<T, 2> &a, T b) {
	return {a.y * b, -a.x * b};
}
template<typename T>
constexpr Vector<T, 3> cross(const Vector<T, 3> &a, const Vector<T, 3> &b) {
	return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

template<typename T, std::size_t N>
constexpr T dot(const Vector<T, N> &a, const Vector<T, N> &b) {
	T result = 0;
	for (std::size_t i = 0; i < N; i++)
		result += a[i] * b[i];
	return result;
}

template<typename T, std::size_t N>
constexpr T length2(const Vector<T, N> &a) {
	return dot(a, a);
}
template<typename T, std::size_t N>
auto length(const Vector<T, N> &a) {
	return std::sqrt(length2(a));
}

template<typename T, std::size_t N>
constexpr auto normalize(const Vector<T, N> &a) {
	return a / length(a);
}

template<typename T, std::size_t N>
constexpr T distance2(const Vector<T, N> &a, const Vector<T, N> &b) {
	return length2(b - a);
}
template<typename T, std::size_t N>
constexpr auto distance(const Vector<T, N> &a, const Vector<T, N> &b) {
	return length(b - a);
}

template<typename T, std::size_t N>
constexpr T uangle(const Vector<T, N> &a, const Vector<T, N> &b) {
	const T d = dot(a, b);
	return d > 1 ? 0 : std::acos(d < -1 ? -1 : d);
}
template<typename T, std::size_t N>
constexpr T angle(const Vector<T, N> &a, const Vector<T, N> &b) {
	return uangle(normalize(a), normalize(b));
}

template<typename T, std::size_t N>
constexpr auto lerp(const Vector<T, N> &a, const Vector<T, N> &b, T c) {
	return a * (1 - c) + b * c;
}
template<typename T, std::size_t N>
constexpr T nlerp(const Vector<T, N> &a, const Vector<T, N> &b, T t) {
	return normalize(lerp(a, b, t));
}
template<typename T, std::size_t N>
constexpr T slerp(const Vector<T, N> &a, const Vector<T, N> &b, T t) {
	T th = uangle(a, b);
	return th == 0 ? a : a * (std::sin(th * (1 - t)) / std::sin(th)) + b * (std::sin(th * t) / std::sin(th));
}

template<typename T>
constexpr Vector<T, 2> rot(T a, const Vector<T, 2> &v) {
	const T s = std::sin(a);
	const T c = std::cos(a);
	return {v.x * c - v.y * s, v.x * s + v.y * c};
}
}
