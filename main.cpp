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

	auto cd = c.Cross(d);

	auto ab = -a + b;

	//WRITE_DEBUG("Hello World!");
	return 0;
}
