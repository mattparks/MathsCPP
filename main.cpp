#include <iostream>

#include "Logger.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Colour.hpp"
#include "Quaternion.hpp"
#include "Rectangle.hpp"
#include "Duration.hpp"

int main(int argc, char *argv[]) {
	using namespace MathsCPP;

	{
		Vector2f a(6.0f);
		WRITE_DEBUG(a);
	}
	{
		Vector4f a(1.0f, 2.0f, 3.0f, 4.0f);
	//	Vector3f b(a);
	//	WRITE_DEBUG(b);
	//	Vector<float, 8> c(a);
	//	WRITE_DEBUG(c);
	}
	{
		Vector2f a(1.0f, 2.0f), b(3.0f, 4.0f);
		Vector4f c(a, b);
		WRITE_DEBUG(c);

		Vector<float, 5> d(c, 5.0f);
		WRITE_DEBUG(d);

		auto right = Vector<double, 3>::Right;
	}
	/*{
		Rectanglef ten(0, 0, 10, 10);
	}
	{
		Colourf red(std::string("#ff0000"));
		WRITE_DEBUG(red);
		auto asVec = red.xyzw();
		WRITE_DEBUG(asVec);
	}
	{
		Quaternionf l;
		Quaternionf l2;
		auto c2 = l * l2;
		auto sl = l.Slerp(l2, 0.5);
		Vector3f r;
		auto c = l * r;
	}
	{
		auto now = Duration<Microseconds>::Now();
		Duration<Seconds> future = now + 10s;
		if (future - 10s == now) {
			
		}
		auto futureFp = future.Cast<Seconds, float>();
		WRITE_DEBUG(futureFp);
	}
	{
		Vector<float, 3> a(1.0f, 2.0f, 3.0f);
		Vector3f b(4.0f, -5.0f, 6.0f);

		auto back = Vector<float, 3>::Back;

		auto dot = a.Dot(b); // = 12.0f
		auto sum = a.Swizzle<0, 1>() + b.Swizzle<0, 1>(); // = {5.0f, -3.0f}
		WRITE_DEBUG(dot);
		WRITE_DEBUG(sum);

		//Vector2f a(1.0f, 2.0f), b(3.0f, 4.0f);
		//Vector4f ab(a, b);
		//Vector4f vb(1.0f, 2.0f, b);
		//Vector4f av(a, 3.0f, 4.0f);
		//Vector<float, 5> avb(a, 5.0f, b);

		//Vector1d a1(1.0), b1(2.0), c1(3.0);
		//Vector3d abc1(a1, b1, c1);
	}
	{
		for (auto m : Matrix4x4f()) {
			for (auto n : m) {
				//	std::cout << n << ", ";
			}
			//std::cout << "\n";
		}
	}*/
	/*{
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
			{1, 1, 2, 1},
			{4, 7, 1, 0},
			{3, 3, 6, 8},
			{0, 2, 2, 4}
		);
		Vector<int32_t, 4> r(6, 2, 1, 0);
		WRITE_DEBUG("\n", l * r); // = {10, 39, 30, 6}
	}
	{
		auto perspective = Matrix4x4f::PerspectiveMatrix(90.0f, 1.0f, 0.0f, 1.0f, ForwardAxis::NegZ);
		WRITE_DEBUG("\n", perspective);
	}*/
	
	return 0;
}
