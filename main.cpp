#include <iostream>

#include "Logger.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"

int main(int argc, char *argv[]) {
	using namespace acid;

	Vector2f a(0.5f, -0.5f);
	a.x() = 0.5f;
	Vector2f b(10.0f, 2.0f);
	Vector3f c(a, 1.0f);

	//WRITE_DEBUG("Hello World!");
	return 0;
}
