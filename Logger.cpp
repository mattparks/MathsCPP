#ifdef __cpp_lib_source_location

#include <ctime>
#include <iomanip>
#include <iostream>
#include <experimental/source_location>

export module MathsCPP;

namespace MathsCPP {
constexpr auto TimestampFormat = "%Y-%m-%d %H:%M:%S GMT%z";

template<typename... Args>
void WriteDebug(const std::experimental::source_location &location = std::experimental::source_location::current(), Args ... args) {
	auto time = std::time(nullptr);
	auto tm = *std::localtime(&time);

	std::cout << "[DEBUG] " << std::put_time(&tm, TimestampFormat) << " - (" << location.file_name() << "::" << location.function_name() << "#" << location.line() << ") ";
	((std::cout << std::forward<Args>(args)), ...);
	std::cout << "\n";
}
}

#endif
