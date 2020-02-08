#include <iostream>

#include "Logger.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"

int main(int argc, char *argv[]) {
	using namespace SpauldingCPP;
	Vec2f a(1.0f, 1.0f);
	Vec3f b(a, 1.0f);
	auto c = Vec3f(a, 0.0f) + b;

	Mat4x4f view;

	//WRITE_DEBUG("Hello World!");
	return 0;
}
