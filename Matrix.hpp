#pragma once

#include "Vector.hpp"
#include "Maths.hpp"

namespace MathsCPP {
/// Should projection matrices be generated assuming forward is {0,0,-1} or {0,0,1}
enum class ForwardAxis { NegZ, PosZ };
/// Should projection matrices map z into the range of [-1,1] or [0,1]?
enum class ZRange { NegOneToOne, ZeroToOne };

/**
 * @brief Holds a row major MxN matrix.
 */
template<typename T, std::size_t N, std::size_t M/*, typename = std::enable_if_t<std::is_arithmetic_v<T>>*/>
class Matrix {
public:
	constexpr Matrix() = default;
	template<typename ...Args, typename = std::enable_if_t<sizeof...(Args) == M && std::conjunction_v<std::is_convertible<Args, Vector<T, N>>...>>>
	constexpr Matrix(Args... args) : data{args...} {}
	template<typename T1, typename = std::enable_if_t<std::is_arithmetic_v<T1> && M == N>>
	constexpr explicit Matrix(T1 s) {
		for (std::size_t j = 0; j < M; j++)
			at(j)[j] = static_cast<T>(s);
	}
	template<typename T1>
	constexpr explicit Matrix(const Matrix<T1, N, M> &m) { copy_cast(m.begin(), m.end(), begin()); }

	template<typename T1>
	constexpr Matrix &operator=(const Matrix<T1, N, M> &m) {
		copy_cast(m.begin(), m.end(), begin());
		return *this;
	}

	constexpr const auto &at(std::size_t i) const { return ((const Vector<T, N> *)this)[i]; }
	constexpr auto &at(std::size_t i) { return ((Vector<T, N> *)this)[i]; }
	
	constexpr const auto &operator[](std::size_t i) const { return at(i); }
	constexpr auto &operator[](std::size_t i) { return at(i); }
	
	auto begin() { return &at(0); }
	auto begin() const { return &at(0); }

	auto end() { return &at(0) + M; }
	auto end() const { return &at(0) + M; }

	/**
	 * Gets the submatrix of this matrix.
	 * @return The submatrix.
	 */
	constexpr auto GetSubmatrix(uint32_t row, uint32_t col) const {
		Matrix<T, N - 1, M - 1> result;
		uint32_t colCount = 0, rowCount = 0;

		for (uint32_t j = 0; j < M; j++) {
			if (j != row) {
				colCount = 0;

				for (uint32_t i = 0; i < N; i++) {
					if (i != col) {
						result[rowCount][colCount] = at(j)[i];
						colCount++;
					}
				}

				rowCount++;
			}
		}

		return result;
	}

	/**
	 * Takes the determinant of this matrix.
	 * @return The determinant.
	 */
	constexpr auto Determinant() const {
		if constexpr (M == 1 && N == 1) {
			return at(0)[0];
		} else if constexpr (M == 2 && N == 2) {
			return at(0)[0] * at(1)[1] - at(0)[1] * at(1)[0];
		} else {
			T result = 0;

			for (uint32_t i = 0; i < N; i++) {
				// Get minor of element [0][i].
				auto minor = GetSubmatrix(0, i).Determinant();

				// If this is an odd-numbered row, negate the value.
				auto factor = (i % 2 == 1) ? T(-1) : T(1);

				result += factor * at(0)[i] * minor;
			}

			return result;
		}
	}

	/**
	 * Inverses this matrix.
	 * @return The inversed matrix.
	 */
	constexpr auto Inverse() const {
		Matrix result;
		auto det = Determinant();

		for (uint32_t j = 0; j < M; j++) {
			for (uint32_t i = 0; i < N; i++) {
				// Get minor of element [j][i] - not [i][j], this is where the transpose happens.
				auto minorSubmatrix = GetSubmatrix(i, j);
				auto minor = minorSubmatrix.Determinant();

				// Multiply by (−1)^{i+j}.
				auto factor = ((j + i) % 2 == 1) ? T(-1) : T(1);
				auto cofactor = minor * factor;

				result[j][i] = cofactor / det;
			}
		}

		return result;
	}

	/**
	 * Transposes this matrix.
	 * @return The transposed matrix.
	 */
	constexpr auto Transpose() const {
		Matrix result;

		for (uint32_t j = 0; j < M; j++) {
			for (uint32_t i = 0; i < N; i++)
				result[i][j] = at(j)[i];
		}

		return result;
	}

	template<typename = std::enable_if_t<N == 4 && M == 4>>
	static Matrix<T, 4, 4> FrustumMatrix(T x0, T x1, T y0, T y1, T n, T f, ForwardAxis a = ForwardAxis::NegZ, ZRange z = ZRange::NegOneToOne) {
		const T s = a == ForwardAxis::PosZ ? T(1) : T(-1);
		const T o = z == ZRange::NegOneToOne ? n : T(0);
		return {
			Vector<T, 4>(2 * n / (x1 - x0), 0, 0, 0),
			Vector<T, 4>(0, 2 * n / (y1 - y0), 0, 0),
			Vector<T, 4>(-s * (x0 + x1) / (x1 - x0), -s * (y0 + y1) / (y1 - y0), s * (f + o) / (f - n), s),
			Vector<T, 4>(0, 0, -(n + o) * f / (f - n), 0)
		};
	}

	template<typename = std::enable_if_t<N == 4 && M == 4>>
	static Matrix<T, 4, 4> PerspectiveMatrix(T fovy, T aspect, T n, T f, ForwardAxis a = ForwardAxis::NegZ, ZRange z = ZRange::NegOneToOne) {
		T y = n * std::tan(fovy / 2);
		T x = y * aspect;
		return FrustumMatrix(-x, x, -y, y, n, f, a, z);
	}

	// TODO: Rotate, Translate, OrthographicMatrix, ViewMatrix, Project, Unproject, LookAt

	template<typename T1>
	constexpr friend auto operator==(const Matrix &lhs, const Matrix<T1, N, M> &rhs) {
		for (std::size_t j = 0; j < M; j++) {
			if (lhs[j] != rhs[j])
				return false;
		}
		return true;
	}

	template<typename T1>
	constexpr friend auto operator!=(const Matrix &lhs, const Matrix<T1, N, M> &rhs) {
		for (std::size_t j = 0; j < M; j++) {
			if (lhs[j] != rhs[j])
				return true;
		}
		return false;
	}

	constexpr friend auto operator+(const Matrix &lhs) {
		Matrix result;
		for (std::size_t j = 0; j < M; j++)
			result[j] = +lhs[j];
		return result;
	}

	constexpr friend auto operator-(const Matrix &lhs) {
		Matrix result;
		for (std::size_t i = 0; i < M; i++)
			result[i] = -lhs[i];
		return result;
	}

	template<typename T1>
	constexpr friend auto operator+(const Matrix &lhs, const Matrix<T1, N, M> &rhs) {
		Matrix<decltype(lhs[0][0] + rhs[0][0]), N, M> result;
		for (std::size_t j = 0; j < M; j++)
			result[j] = lhs[j] + rhs[j];
		return result;
	}

	template<typename T1>
	constexpr friend auto operator-(const Matrix &lhs, const Matrix<T1, N, M> &rhs) {
		Matrix<decltype(lhs[0][0] - rhs[0][0]), N, M> result;
		for (std::size_t j = 0; j < M; j++)
			result[j] = lhs[j] - rhs[j];
		return result;
	}

	template<typename T1, std::size_t N1, std::size_t M1>
	constexpr friend auto operator*(const Matrix &lhs, const Matrix<T1, N1, M1> &rhs) {
		Matrix<decltype(lhs[0][0] * rhs[0][0]), N1, M> result;
		for (std::size_t j = 0; j < M; j++) {
			for (std::size_t i = 0; i < N1; i++) {
				for (std::size_t p = 0; p < M1; p++) {
					result[j][i] += lhs[j][p] * rhs[p][i];
				}
			}
		}
		return result;
	}

	template<typename T1, std::size_t N1, std::size_t M1>
	constexpr friend auto operator/(const Matrix &lhs, const Matrix<T1, N1, M1> &rhs) {
		Matrix<decltype(lhs[0][0] * rhs[0][0]), N1, M> result;
		for (std::size_t j = 0; j < M; j++) {
			for (std::size_t i = 0; i < N1; i++) {
				for (std::size_t p = 0; p < M1; p++) {
					result[j][i] += lhs[j][p] / rhs[p][i];
				}
			}
		}
		return result;
	}

	/// Transform column vector by matrix ( vec = matrix * vec )
	template<typename T1>
	constexpr friend auto operator*(const Matrix &lhs, Vector<T1, N> rhs) {
		Vector<decltype(lhs[0][0] * rhs[0]), M> result;
		for (std::size_t j = 0; j < M; j++) {
			for (std::size_t i = 0; i < N; i++)
				result[j] += lhs[j][i] * rhs[i];
		}
		return result;
	}

	/// Transform column vector by matrix ( vec = matrix * vec ),
	/// assume homogenous coords, e.g. vec3 = mat4x4 * vec3, with w = 1.0
	template<typename T1, std::size_t N1>
	constexpr friend auto operator*(const Matrix &lhs, Vector<T1, N1> rhs) {
		Vector<decltype(lhs[0][0] * rhs[0]), N1> result;
		T tmp;
		for (std::size_t j = 0; j < M; j++) {
			tmp = 0;
			for (std::size_t i = 0; i < N - 1; i++)
				tmp += rhs[i] * lhs[j][i];
			if (j < N - 1) {
				result[j] = tmp + lhs[j][N - 1]; // * 1.0 -> homogeneous vec4
			} else {
				tmp += lhs[j][N - 1];
				for (std::size_t i = 0; i < N - 1; i++)
					result[i] /= tmp;
			}
		}
		return result;
	}

	template<typename T1, typename = std::enable_if_t<std::is_arithmetic_v<T1>>>
	constexpr friend auto operator*(const Matrix &lhs, T1 rhs) {
		Matrix<decltype(lhs[0][0] * rhs), N, M> result;
		for (std::size_t j = 0; j < M; j++)
			result[j] = lhs[j] * rhs;
		return result;
	}

	template<typename T1, typename = std::enable_if_t<std::is_arithmetic_v<T1>>>
	constexpr friend auto operator/(const Matrix &lhs, T1 rhs) {
		Matrix<decltype(lhs[0][0] / rhs), N, M> result;
		for (std::size_t j = 0; j < M; j++)
			result[j] = lhs[j] / rhs;
		return result;
	}

	template<typename T1, typename = std::enable_if_t<std::is_arithmetic_v<T1>>>
	constexpr friend auto operator*(T1 lhs, const Matrix &rhs) {
		Matrix<decltype(lhs * rhs[0][0]), N, M> result;
		for (std::size_t j = 0; j < M; j++)
			result[j] = lhs * rhs[j];
		return result;
	}

	template<typename T1, typename = std::enable_if_t<std::is_arithmetic_v<T1>>>
	constexpr friend auto operator/(T1 lhs, const Matrix &rhs) {
		Matrix<decltype(lhs / rhs[0][0]), N, M> result;
		for (std::size_t j = 0; j < M; j++)
			result[j] = lhs / rhs[j];
		return result;
	}

	template<typename T1>
	constexpr friend auto operator+=(Matrix &lhs, const T1 &rhs) {
		return lhs = lhs + rhs;
	}

	template<typename T1>
	constexpr friend auto operator-=(Matrix &lhs, const T1 &rhs) {
		return lhs = lhs - rhs;
	}

	template<typename T1>
	constexpr friend auto operator*=(Matrix &lhs, const T1 &rhs) {
		return lhs = lhs * rhs;
	}

	template<typename T1>
	constexpr friend auto operator/=(Matrix &lhs, const T1 &rhs) {
		return lhs = lhs / rhs;
	}

	friend std::ostream &operator<<(std::ostream &stream, const Matrix &matrix) {
		for (std::size_t j = 0; j < M; j++)
			stream << matrix[j] << (j != M - 1 ? "\n" : "");
		return stream;
	}

	static const Matrix Identity;

	Vector<T, N> data[M]{};
};

template<typename T, std::size_t N, std::size_t M>
const Matrix<T, N, M> Matrix<T, N, M>::Identity = Matrix<T, N, M>(1);

using Matrix1x1f = Matrix<float, 1, 1>;
using Matrix2x2f = Matrix<float, 2, 2>;
using Matrix3x3f = Matrix<float, 3, 3>;
using Matrix4x4f = Matrix<float, 4, 4>;
}

namespace std {
template<typename T, size_t N, size_t M>
struct hash<MathsCPP::Matrix<T, N, M>> {
	size_t operator()(const MathsCPP::Matrix<T, N, M> &matrix) const noexcept {
		size_t seed = 0;
		for (size_t i = 0; i < M; i++)
			MathsCPP::Maths::HashCombine(seed, matrix[i]);
		return seed;
	}
};
}
