#pragma once

#include <cmath>
#include <type_traits>

#include "Vector.hpp"

namespace acid {
template<typename T, std::size_t N>
const Vector<T, N> Vector<T, N>::Zero = Vector<T, N>(0);
template<typename T, std::size_t N>
const Vector<T, N> Vector<T, N>::One = Vector<T, N>(1);
template<typename T, std::size_t N>
const Vector<T, N> Vector<T, N>::Infinity = Vector<T, N>(std::numeric_limits<T>::infinity());
template<typename T, std::size_t N> // typename = std::enable_if_t<N <= 2> 
const Vector<T, N> Vector<T, N>::Right = Vector<T, N>(1, 0);
template<typename T, std::size_t N> // typename = std::enable_if_t<N <= 2> 
const Vector<T, N> Vector<T, N>::Left = Vector<T, N>(-1, 0);
template<typename T, std::size_t N> // typename = std::enable_if_t<N <= 2> 
const Vector<T, N> Vector<T, N>::Up = Vector<T, N>(0, 1);
template<typename T, std::size_t N> // typename = std::enable_if_t<N <= 2> 
const Vector<T, N> Vector<T, N>::Down = Vector<T, N>(0, -1);
template<typename T, std::size_t N> // typename = std::enable_if_t<N <= 3> 
const Vector<T, N> Vector<T, N>::Front = Vector<T, N>(0, 0, 1);
template<typename T, std::size_t N> // typename = std::enable_if_t<N <= 3> 
const Vector<T, N> Vector<T, N>::Back = Vector<T, N>(0, 0, -1);

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
}
