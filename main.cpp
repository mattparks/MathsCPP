#include <iostream>

#include "Logger.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"

int main(int argc, char *argv[]) {
	using namespace acid;

	Vector2f a(0.5f, -0.5f);
	Vector2i b(10, 2);
	Vector3f c(a, 1.0f);
	Vector3f d(0.7f, -0.1f, 0.9f);

	auto nInf3f = -Vector4f::Infinity.xyz();

	auto cd = c.Cross(d);
	auto ang1 = c.Angle(d);

	auto ab = -a + b;

	//auto perspective = Matrix4x4f::PerspectiveMatrix(90.0f, 1.0f, 0.0f, 1.0f, ForwardAxis::NegZ);

	//WRITE_DEBUG("Hello World!");
	return 0;
}
