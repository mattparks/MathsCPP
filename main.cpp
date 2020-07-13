#include <iostream>

#include "Logger.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"

int main(int argc, char *argv[]) {
	using namespace acid;

	{
		Vector2f a(0.5f, -0.5f);
		Vector2i b(10, 2);
		Vector3f c(10, 2, 1.0f);
		Vector3f d(0.7f, -0.1f, 0.9f);
		Vector4d kk(-1.0);

		auto dp = d.CartesianToPolar();
		Vector3f dc = dp.PolarToCartesian();
		auto dsame = d == dc;

		auto nInf3f = -Vector4f::Infinity.xyz();

		for (auto m : Matrix4x4f()) {
			for (auto n : m) {
			//	std::cout << n << ", ";
			}
			//std::cout << "\n";
		}

		auto cd = c.Cross(d);
		auto ang1 = c.Angle(d);

		auto ab = -a + b;
	}
	{
		auto i = Matrix4x4f::Identity;
		auto iTran = i.Transpose();
		auto iDet= i.Determinant();
		auto iInv = i.Inverse();
	}
	{
		Matrix<int32_t, 3, 2> l(
			Vector3i(1, 2, 3),
			Vector3i(4, 5, 6)
		);
		Matrix<int32_t, 2, 3> r(
			Vector2i(7, 8),
			Vector2i(9, 10),
			Vector2i(11, 12)
		);
		WRITE_DEBUG("\n", l * r);
	}
	{
		Matrix<int32_t, 2, 2> l(
			Vector2i(4, 0),
			Vector2i(1, -9)
		);
		WRITE_DEBUG("\n", 2 * l);
	}
	{
		Matrix<int32_t, 2, 2> l(
			Vector2i(11, 3),
			Vector2i(7, 11)
		);
		Matrix<int32_t, 3, 2> r(
			Vector3i(8, 0, 1),
			Vector3i(0, 3, 5)
		);
		WRITE_DEBUG("\n", l * r);
	}
	{
		Matrix<int32_t, 2, 2> l(
			Vector2i(1, 2),
			Vector2i(3, 4)
		);
		WRITE_DEBUG("\n", l * l * l);
	}
	{
		Matrix<int32_t, 3, 3> l(
			Vector3i(1, 3, 3),
			Vector3i(1, 4, 3),
			Vector3i(1, 3, 4)
		);
		WRITE_DEBUG("\n", l.Inverse());
		WRITE_DEBUG("\n", l * l.Inverse());
	}
	{
		Matrix<int32_t, 2, 2> l(
			Vector2i(4, 2),
			Vector2i(0, -2)
		);
		Vector<int32_t, 2> r(5, 0);
		WRITE_DEBUG("\n", l * r);
	}
	{
		Matrix<int32_t, 4, 4> l(
			Vector4i(1, 1, 2, 1),
			Vector4i(4, 7, 1, 0),
			Vector4i(3, 3, 6, 8),
			Vector4i(0, 2, 2, 4)
		);
		Vector<int32_t, 4> r(6, 2, 1, 0);
		WRITE_DEBUG("\n", l * r); // = {10, 39, 30, 6}
	}
	{
		auto perspective = Matrix4x4f::PerspectiveMatrix(90.0f, 1.0f, 0.0f, 1.0f, ForwardAxis::NegZ);
		WRITE_DEBUG("\n", perspective);
	}
	
	return 0;
}
