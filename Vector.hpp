#pragma once

#include <array>
#include <cassert>

namespace acid {
template<typename T, std::size_t N>
class Vector {
public:
	Vector() = default;
	Vector(const T &s) { data.fill(s); }
	template<typename ...Args>
	Vector(Args... args) : data{args...} {}
	template<typename T1>
	Vector(const Vector<T1, N> &other) {
		for (std::size_t i = 0; i < N; i++) {
			data[i] = static_cast<T>(other[i]);
		}
	}
	Vector(const Vector<T, N - 1> &other, T scalar) {
		std::memcpy(data.data(), other.ptr(), sizeof(other));
		data[N - 1] = scalar;
	}
	template<std::size_t N1>
	Vector(const Vector<T, N1> &v1, const Vector<T, N - N1> &v2) {
		std::memcpy(data.data(), v1.ptr(), sizeof(v1));
		std::memcpy(data.data() + N1, v2.ptr(), sizeof(v2));
	}

	template<typename T1>
	constexpr bool operator==(const Vector<T1, N> &rhs) const {
		for (std::size_t i = 0; i < N; i++) {
			if (at(i) != rhs.at(i))
				return false;
		}
		return true;
	}
	template<typename T1>
	constexpr bool operator!=(const Vector<T1, N> &rhs) const {
		for (std::size_t i = 0; i < N; i++) {
			if (at(i) != rhs.at(i))
				return true;
		}
		return false;
	}

	Vector operator-() const {
		Vector result;
		for (std::size_t i = 0; i < N; i++)
			result[i] = -at(i);
		return result;
	}

	template<typename T1>
	Vector operator+(const Vector<T1, N> &rhs) const {
		Vector result = *this;
		for (std::size_t i = 0; i < N; i++)
			result[i] += rhs.at(i);
		return result;
	}

	template<typename T1>
	Vector operator-(const Vector<T1, N> &rhs) const {
		Vector result = *this;
		for (std::size_t i = 0; i < N; i++)
			result[i] -= rhs.at(i);
		return result;
	}

	template<typename T1>
	Vector operator*(const Vector<T1, N> &rhs) const {
		Vector result = *this;
		for (std::size_t i = 0; i < N; i++)
			result[i] *= rhs.at(i);
		return result;
	}

	template<typename T1>
	Vector operator/(const Vector<T1, N> &rhs) const {
		Vector result = *this;
		for (std::size_t i = 0; i < N; i++)
			result[i] /= rhs.at(i);
		return result;
	}

	auto Angle(const Vector &other) {
		auto dls = Dot(other) / (Length() * other.Length());

		if (dls < -1) {
			dls = -1;
		} else if (dls > 1) {
			dls = 1;
		}

		return std::acos(dls);
	}

	T Dot(const Vector &other) const {
		T result = 0;
		for (std::size_t i = 0; i < N; i++)
			result += at(i) * other.at(i);
		return result;
	}

	template<typename = std::enable_if_t<N == 3>>
	Vector Cross(const Vector &other) const {
		return {
			at<1>() * other.at<2>() - at<2>() * other.at<1>(),
			other.at<0>() * at<2>() - other.at<2>() * at<0>(),
			at<0>() * other.at<1>() - at<1>() * other.at<0>()
		};
	}

	auto Length() const {
		return std::sqrt(Length2());
	}
	auto Length2() const {
		return Dot(*this);
	}

	void Normalize() {
		
	}

	Vector Normalized() const {
		
	}

	T x() const { return at<0>(); }
	template<typename = std::enable_if_t<N >= 2>>
	T y() const { return at<1>(); }
	template<typename = std::enable_if_t<N >= 3>>
	T z() const { return at<2>(); }
	template<typename = std::enable_if_t<N >= 4>>
	T w() const { return at<3>(); }

	T &x() { return at<0>(); }
	template<typename = std::enable_if_t<N >= 2>>
	T &y() { return at<1>(); }
	template<typename = std::enable_if_t<N >= 3>>
	T &z() { return at<2>(); }
	template<typename = std::enable_if_t<N >= 4>>
	T &w() { return at<3>(); }

	template<typename = std::enable_if_t<N >= 3>>
	Vector<T, 2> xy() const { return {at<0>(), at<1>()}; }
	template<typename = std::enable_if_t<N >= 3>>
	Vector<T, 2> xz() const { return {at<0>(), at<2>()}; }
	template<typename = std::enable_if_t<N >= 4>>
	Vector<T, 3> xyz() const { return {at<0>(), at<1>(), at<2>()}; }

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
	operator Vector<T, N1>() const {
		Vector<T, N1> ret;
		std::memcpy(&ret[0], ptr(), std::min(sizeof(ret), sizeof(*this)));
		return ret;
	}
private:
	std::array<T, N> data{};
};

using Vector2f = Vector<float, 2>;
using Vector2d = Vector<double, 2>;
using Vector2i = Vector<int32_t, 2>;
using Vector2u = Vector<uint32_t, 2>;

using Vector3f = Vector<float, 3>;
using Vector3d = Vector<double, 3>;
using Vector3i = Vector<int32_t, 3>;
using Vector3u = Vector<uint32_t, 3>;

using Vector4f = Vector<float, 4>;
using Vector4d = Vector<double, 4>;
using Vector4i = Vector<int32_t, 4>;
using Vector4u = Vector<uint32_t, 4>;
}

#include "Vector.inl"
