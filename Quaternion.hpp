#pragma once

#include "Matrix.hpp"

namespace MathsCPP {
template<typename T/*, typename = std::enable_if_t<std::is_arithmetic_v<T>>*/>
class Quaternion {
public:
	constexpr Quaternion() = default;
	constexpr Quaternion(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
	template<typename T1, typename = std::enable_if_t<std::is_arithmetic_v<T1>>>
	constexpr explicit Quaternion(T1 s) { std::fill(begin(), end(), static_cast<T>(s)); }
	template<typename T1>
	constexpr Quaternion(const Quaternion<T1> &q) { copy_cast(q.begin(), q.end(), begin()); }
	template<typename T1>
	constexpr explicit Quaternion(const Vector<T1, 3> &v) {
		auto sx = std::sin(v.x * 0.5f);
		auto cx = Maths::CosFromSin(sx, v.x * 0.5f);
		auto sy = std::sin(v.y * 0.5f);
		auto cy = Maths::CosFromSin(sy, v.y * 0.5f);
		auto sz = std::sin(v.z * 0.5f);
		auto cz = Maths::CosFromSin(sz, v.z * 0.5f);

		auto cycz = cy * cz;
		auto sysz = sy * sz;
		auto sycz = sy * cz;
		auto cysz = cy * sz;

		w = cx * cycz - sx * sysz;
		x = sx * cycz + cx * sysz;
		y = cx * sycz - sx * cysz;
		z = cx * cysz + sx * sycz;
	}
	template<typename T1>
	constexpr explicit Quaternion(const Vector<T1, 3> &ax, const Vector<T1, 3> &ay, const Vector<T1, 3> &az) {
		Matrix<T1, 4, 4> rotation;
		rotation[0][0] = ax.x;
		rotation[1][0] = ax.y;
		rotation[2][0] = ax.z;
		rotation[0][1] = ay.x;
		rotation[1][1] = ay.y;
		rotation[2][1] = ay.z;
		rotation[0][2] = az.x;
		rotation[1][2] = az.y;
		rotation[2][2] = az.z;
		*this = rotation;
	}
	template<typename T1>
	constexpr explicit Quaternion(const Matrix<T1, 4, 4> &m) {
		auto diagonal = m[0][0] + m[1][1] + m[2][2];

		if (diagonal > 0.0f) {
			auto w4 = std::sqrt(diagonal + 1.0f) * 2.0f;
			w = w4 / 4.0f;
			x = (m[2][1] - m[1][2]) / w4;
			y = (m[0][2] - m[2][0]) / w4;
			z = (m[1][0] - m[0][1]) / w4;
		} else if ((m[0][0] > m[1][1]) && (m[0][0] > m[2][2])) {
			auto x4 = std::sqrt(1.0f + m[0][0] - m[1][1] - m[2][2]) * 2.0f;
			w = (m[2][1] - m[1][2]) / x4;
			x = x4 / 4.0f;
			y = (m[0][1] + m[1][0]) / x4;
			z = (m[0][2] + m[2][0]) / x4;
		} else if (m[1][1] > m[2][2]) {
			auto y4 = std::sqrt(1.0f + m[1][1] - m[0][0] - m[2][2]) * 2.0f;
			w = (m[0][2] - m[2][0]) / y4;
			x = (m[0][1] + m[1][0]) / y4;
			y = y4 / 4.0f;
			z = (m[1][2] + m[2][1]) / y4;
		} else {
			auto z4 = std::sqrt(1.0f + m[2][2] - m[0][0] - m[1][1]) * 2.0f;
			w = (m[1][0] - m[0][1]) / z4;
			x = (m[0][2] + m[2][0]) / z4;
			y = (m[1][2] + m[2][1]) / z4;
			z = z4 / 4.0f;
		}
	}

	constexpr const T &operator[](std::size_t i) const { return at(i); }
	constexpr T &operator[](std::size_t i) { return at(i); }

	constexpr auto size() const { return 4; }

	auto begin() { return &at(0); }
	auto begin() const { return &at(0); }

	auto end() { return &at(0) + 4; }
	auto end() const { return &at(0) + 4; }

	constexpr const T &at(std::size_t i) const {
		assert(i < 4 && "Quaternion subscript out of range");
		return  i == 0 ? x : i == 1 ? y : i == 2 ? z : w;
	}
	constexpr T &at(std::size_t i) {
		assert(i < 4 && "Quaternion subscript out of range");
		return  i == 0 ? x : i == 1 ? y : i == 2 ? z : w;
	}

	constexpr const Vector<T, 2> &xy() const { return *reinterpret_cast<const Vector<T, 2> *>(this); }
	constexpr Vector<T, 2> &xy() { return *reinterpret_cast<Vector<T, 2> *>(this); }

	constexpr const Vector<T, 3> &xyz() const { return *reinterpret_cast<const Vector<T, 3> *>(this); }
	constexpr Vector<T, 3> &xyz() { return *reinterpret_cast<Vector<T, 3> *>(this); }

	constexpr const Vector<T, 4> &xyzw() const { return *reinterpret_cast<const Vector<T, 4> *>(this); }
	constexpr Vector<T, 4> &xyzw() { return *reinterpret_cast<Vector<T, 4> *>(this); }

	/**
	 * Calculates the dot product of the this vector and another vector.
	 * @param other The other vector.
	 * @return The dot product.
	 */
	constexpr T Dot(const Quaternion &other) const {
		T result = 0;
		for (std::size_t i = 0; i < 4; i++)
			result += at(i) * other[i];
		return result;
	}

	/**
	 * Gets the length squared of this vector.
	 * @return The length squared.
	 */
	constexpr T Length2() const {
		return Dot(*this);
	}

	/**
	 * Gets the length of this vector.
	 * @return The length.
	 */
	auto Length() const {
		return std::sqrt(Length2());
	}

	/**
	 * Gets the unit vector of this vector.
	 * @return The normalized vector.
	 */
	auto Normalize() const {
		return *this / Length();
	}

	/**
	 * Calculates the slerp between this quaternion and another quaternion, they must be normalized!
	 * @param other The other quaternion.
	 * @param t The progression.
	 * @return Left slerp right.
	 */
	template<typename T1, typename T2>
	auto Slerp(const Quaternion<T1> &other, T2 t) const {
		auto cosom = x * other.x + y * other.y + z * other.z + w * other.w;
		auto absCosom = std::abs(cosom);
		T2 scale0, scale1;

		if (1 - absCosom > 1E-6) {
			auto sinSqr = 1 - absCosom * absCosom;
			auto sinom = 1 / std::sqrt(sinSqr);
			auto omega = std::atan2(sinSqr * sinom, absCosom);
			scale0 = std::sin((1 - t) * omega) * sinom;
			scale1 = std::sin(t * omega) * sinom;
		} else {
			scale0 = 1 - t;
			scale1 = t;
		}

		scale1 = cosom >= 0.0f ? scale1 : -scale1;
	
		return (scale0 * *this) + (scale1 * other);
	}
	
	/**
	 * Converts this quaternion to a 4x4 matrix.
	 * @return The rotation matrix which represents the exact same rotation as this quaternion.
	 */
	auto ToMatrix() const {
		auto w2 = w * w;
		auto x2 = x * x;
		auto y2 = y * y;
		auto z2 = z * z;
		auto zw = z * w;
		auto xy = x * y;
		auto xz = x * z;
		auto yw = y * w;
		auto yz = y * z;
		auto xw = x * w;

		Matrix<T, 4, 4> result;
		result[0][0] = w2 + x2 - z2 - y2;
		result[0][1] = xy + zw + zw + xy;
		result[0][2] = xz - yw + xz - yw;
		result[1][0] = -zw + xy - zw + xy;
		result[1][1] = y2 - z2 + w2 - x2;
		result[1][2] = yz + yz + xw + xw;
		result[2][0] = yw + xz + xz + yw;
		result[2][1] = yz + yz - xw - xw;
		result[2][2] = z2 - y2 - x2 + w2;
		return result;
	}

	/**
	 * Converts this quaternion to a 3x3 matrix representing the exact same
	 * rotation as this quaternion.
	 * @return The rotation matrix which represents the exact same rotation as this quaternion.
	 */
	auto ToRotationMatrix() const {
		auto xy = x * y;
		auto xz = x * z;
		auto xw = x * w;
		auto yz = y * z;
		auto yw = y * w;
		auto zw = z * w;
		auto x2 = x * x;
		auto y2 = y * y;
		auto z2 = z * z;

		Matrix<T, 4, 4> result;
		result[0][0] = 1 - 2 * (y2 + z2);
		result[0][1] = 2 * (xy - zw);
		result[0][2] = 2 * (xz + yw);
		//result[0][3] = 0;
		result[1][0] = 2 * (xy + zw);
		result[1][1] = 1 - 2 * (x2 + z2);
		result[1][2] = 2 * (yz - xw);
		//result[1][3] = 0;
		result[2][0] = 2 * (xz - yw);
		result[2][1] = 2 * (yz + xw);
		result[2][2] = 1 - 2 * (x2 + y2);
		return result;
	}

	/**
	 * Converts this quaternion to euler angles.
	 * @return The euler angle representation of this quaternion.
	 */
	auto ToEuler() const {
		Vector3f result;
		result.x = std::atan2(2.0f * (x * w - y * z), 1.0f - 2.0f * (x * x + y * y));
		result.y = std::asin(2.0f * (x * z + y * w));
		result.z = std::atan2(2.0f * (z * w - x * y), 1.0f - 2.0f * (y * y + z * z));
		return result;
	}

	template<typename T1>
	constexpr friend auto operator==(const Quaternion &lhs, const Quaternion<T1> &rhs) {
		for (std::size_t i = 0; i < 4; i++) {
			if (std::abs(lhs[i] - rhs[i]) > 0.0001f)
				return false;
		}
		return true;
	}

	template<typename T1>
	constexpr friend auto operator!=(const Quaternion &lhs, const Quaternion<T1> &rhs) {
		for (std::size_t i = 0; i < 4; i++) {
			if (std::abs(lhs[i] - rhs[i]) <= 0.0001f)
				return true;
		}
		return false;
	}

	constexpr friend auto operator+(const Quaternion &lhs) {
		Quaternion result;
		for (std::size_t i = 0; i < 4; i++)
			result[i] = +lhs[i];
		return result;
	}

	constexpr friend auto operator-(const Quaternion &lhs) {
		Quaternion result;
		for (std::size_t i = 0; i < 4; i++)
			result[i] = -lhs[i];
		return result;
	}

	template<typename T1>
	constexpr friend auto operator+(const Quaternion &lhs, const Quaternion<T1> &rhs) {
		Quaternion<decltype(lhs[0] + rhs[0])> result;
		for (std::size_t i = 0; i < 4; i++)
			result[i] = lhs[i] + rhs[i];
		return result;
	}

	template<typename T1>
	constexpr friend auto operator-(const Quaternion &lhs, const Quaternion<T1> &rhs) {
		Quaternion<decltype(lhs[0] - rhs[0])> result;
		for (std::size_t i = 0; i < 4; i++)
			result[i] = lhs[i] - rhs[i];
		return result;
	}

	template<typename T1>
	constexpr friend auto operator*(const Quaternion &lhs, const Quaternion<T1> &rhs) {
		Quaternion<decltype(lhs[0] * rhs[0])> result;
		result.x = lhs.x * rhs.w + lhs.w * rhs.x + lhs.y * rhs.z - lhs.z * rhs.y;
		result.y = lhs.y * rhs.w + lhs.w * rhs.y + lhs.z * rhs.x - lhs.x * rhs.z;
		result.z = lhs.z * rhs.w + lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x;
		result.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
		return result;
	}

	template<typename T1>
	constexpr friend auto operator*(const Quaternion &lhs, Vector<T1, 3> rhs) {
		auto q = lhs.xyz();
		auto cross1 = q.Cross(rhs);
		auto cross2 = q.Cross(cross1);
		return rhs + 2.0f * (cross1 * lhs.w + cross2);
	}

	template<typename T1, typename = std::enable_if_t<std::is_arithmetic_v<T1>>>
	constexpr friend auto operator*(const Quaternion &lhs, T1 rhs) {
		Quaternion<decltype(lhs[0] * rhs)> result;
		for (std::size_t i = 0; i < 4; i++)
			result[i] = lhs[i] * rhs;
		return result;
	}

	template<typename T1, typename = std::enable_if_t<std::is_arithmetic_v<T1>>>
	constexpr friend auto operator/(const Quaternion &lhs, T1 rhs) {
		Quaternion<decltype(lhs[0] / rhs)> result;
		for (std::size_t i = 0; i < 4; i++)
			result[i] = lhs[i] / rhs;
		return result;
	}

	template<typename T1>
	constexpr friend auto operator*(Vector<T1, 3> lhs, const Quaternion &rhs) {
		return rhs * lhs;
	}

	template<typename T1, typename = std::enable_if_t<std::is_arithmetic_v<T1>>>
	constexpr friend auto operator*(T1 lhs, const Quaternion &rhs) {
		Quaternion<decltype(lhs *rhs[0])> result;
		for (std::size_t i = 0; i < 4; i++)
			result[i] = lhs * rhs[i];
		return result;
	}

	template<typename T1, typename = std::enable_if_t<std::is_arithmetic_v<T1>>>
	constexpr friend auto operator/(T1 lhs, const Quaternion &rhs) {
		Quaternion<decltype(lhs / rhs[0])> result;
		for (std::size_t i = 0; i < 4; i++)
			result[i] = lhs / rhs[i];
		return result;
	}

	template<typename T1>
	constexpr friend auto operator+=(Quaternion &lhs, const T1 &rhs) {
		return lhs = lhs + rhs;
	}

	template<typename T1>
	constexpr friend auto operator-=(Quaternion &lhs, const T1 &rhs) {
		return lhs = lhs - rhs;
	}

	template<typename T1>
	constexpr friend auto operator*=(Quaternion &lhs, const T1 &rhs) {
		return lhs = lhs * rhs;
	}

	template<typename T1>
	constexpr friend auto operator/=(Quaternion &lhs, const T1 &rhs) {
		return lhs = lhs / rhs;
	}

	friend std::ostream &operator<<(std::ostream &stream, const Quaternion &colour) {
		for (std::size_t i = 0; i < 4; i++)
			stream << colour[i] << (i != 4 - 1 ? ", " : "");
		return stream;
	}

	static const Quaternion Zero;
	static const Quaternion One;
	static const Quaternion Infinity;

	T x{}, y{}, z{}, w{1};
};

template<typename T>
const Quaternion<T> Quaternion<T>::Zero = Quaternion<T>(0);
template<typename T>
const Quaternion<T> Quaternion<T>::One = Quaternion<T>(1);
template<typename T>
const Quaternion<T> Quaternion<T>::Infinity = Quaternion<T>(std::numeric_limits<T>::infinity());

using Quaternionf = Quaternion<float>;
using Quaterniond = Quaternion<double>;
}
