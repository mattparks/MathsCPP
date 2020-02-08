#pragma once

#include <array>
#include <cassert>

namespace SpauldingCPP {
template<std::size_t N, typename T>
class Vector {
public:
	Vector() = default;
	Vector(const T &value) {
		for (std::size_t i = 0; i < N; i++) {
			data[i] = value;
		}
	}
	template<typename ...Args>
	Vector(Args... args) : data{args...} {
	}
	template<typename T1>
	Vector(const Vector<N, T1> &other) {
		for (std::size_t i = 0; i < N; i++) {
			data[i] = static_cast<T>(other[i]);
		}
	}
	Vector(const Vector<N - 1, T> &other, T scalar) {
		std::memcpy(data.data(), other.ptr(), sizeof(other));
		data[N - 1] = scalar;
	}
	template<std::size_t N1>
	Vector(const Vector<N1, T> &v1, const Vector<N - N1, T> &v2) {
		std::memcpy(data.data(), v1.ptr(), sizeof(v1));
		std::memcpy(data.data() + N1, v2.ptr(), sizeof(v2));
	}

	template<typename T1>
	Vector operator+(const Vector<N, T1> &rhs) const {
		Vector result = *this;
		for (std::size_t i = 0; i < N; i++)
			result[i] += rhs.at(i);
		return result;
	}

	template<typename T1>
	Vector operator-(const Vector<N, T1> &rhs) const {
		Vector result = *this;
		for (std::size_t i = 0; i < N; i++)
			result[i] -= rhs.at(i);
		return result;
	}

	template<typename T1>
	Vector operator*(const Vector<N, T1> &rhs) const {
		Vector result = *this;
		for (std::size_t i = 0; i < N; i++)
			result[i] *= rhs.at(i);
		return result;
	}

	template<typename T1>
	Vector operator/(const Vector<N, T1> &rhs) const {
		Vector result = *this;
		for (std::size_t i = 0; i < N; i++)
			result[i] /= rhs.at(i);
		return result;
	}

	template<typename T1>
	auto Angle(const Vector<N, T1> &other) {
		auto dls = Dot(other) / (Length() * other.Length());

		if (dls < -1) {
			dls = -1;
		} else if (dls > 1) {
			dls = 1;
		}

		return std::acos(dls);
	}

	template<typename T1>
	T Dot(const Vector<N, T1> &other) {
		T result = 0;
		for (std::size_t i = 0; i < N; i++)
			result += at(i) * other.at(i);
		return result;
	}

	template<typename T1, typename = std::enable_if_t<N == 3>>
	Vector Cross(const Vector<N, T1> &other) {
		return {
			at<1>() * other.template at<2>() - at<2>() * other.template at<1>(),
			other.template at<0>() * at<2>() - other.template at<2>() * at<0>(),
			at<0>() * other.template at<1>() - at<1>() * other.template at<0>()
		};
	}

	auto Length() const {
		return std::sqrt(Length2());
	}
	auto Length2() const {
		return Dot(*this);
	}

	template<typename = std::enable_if_t<N >= 1>>
	const auto &x() const {
		return at<0>();
	}
	template<typename = std::enable_if_t<N >= 2>>
	const T &y() const {
		return at<1>();
	}
	template<typename = std::enable_if_t<N >= 3>>
	const T &z() const {
		return at<2>();
	}
	template<typename = std::enable_if_t<N >= 4>>
	const T &w() const {
		return at<3>();
	}
	template<typename = std::enable_if_t<N >= 2>>
	Vector<2, T> xy() const {
		return {at<0>(), at<1>()};
	}
	template<typename = std::enable_if_t<N >= 2>>
	Vector<2, T> xz() const {
		return {at<0>(), at<2>()};
	}
	template<typename = std::enable_if_t<N >= 3>>
	Vector<3, T> xyz() const {
		return {at<0>(), at<1>(), at<2>()};
	}
	template<typename = std::enable_if_t<N >= 4>>
	Vector<4, T> xyzw() const {
		return {at<0>(), at<1>(), at<2>(), at<3>()};
	}
	
	const auto *ptr() const {
		return data.data();
	}
	
	auto begin() { return data.begin(); }
	constexpr auto begin() const { return cbegin(); }
	constexpr auto cbegin() const { return data.cbegin(); }
	auto end() { return data.end(); }
	constexpr auto end() const { return cend(); }
	constexpr auto cend() const { return data.end(); }

	template<std::size_t Idx>
	constexpr T at() const {
		static_assert(Idx < N, "Invalid component index in vector");
		return std::get<Idx>(data);
	}
	template<std::size_t Idx>
	T &at() {
		static_assert(Idx < N, "Invalid component index in vector");
		return std::get<Idx>(data);
	}

	T at(std::size_t idx) const {
		assert(idx < N);
		return data[idx];
	}
	T &at(std::size_t idx) {
		assert(idx < N);
		return data[idx];
	}

	constexpr auto operator[](std::size_t idx) const {
		assert(idx < N);
		return data[idx];
	}
	auto &operator[](std::size_t idx) {
		assert(idx < N);
		return data[idx];
	}

	template<unsigned N1>
	operator Vector<N1, T>() const {
		Vector<N1, T> ret;
		std::memcpy(&ret[0], ptr(), std::min(sizeof(ret), sizeof(*this)));
		return ret;
	}
private:
	std::array<T, N> data{};
};

// float2, double2, int2, uint2
using Vec2f = Vector<2, float>;
using Vec2d = Vector<2, double>;
using Vec2i = Vector<2, int32_t>;
using Vec2u = Vector<2, uint32_t>;

using Vec3f = Vector<3, float>;
using Vec3d = Vector<3, double>;
using Vec3i = Vector<3, int32_t>;
using Vec3u = Vector<3, uint32_t>;

using Vec4f = Vector<4, float>;
using Vec4d = Vector<4, double>;
using Vec4i = Vector<4, int32_t>;
using Vec4u = Vector<4, uint32_t>;
}

#include "Vector.inl"
