#pragma once

#include <ctime>
#include <iomanip>
#include <iostream>

namespace SpauldingCPP {
class Logger {
public:
	static constexpr auto TimestampFormat = "%Y-%m-%d %H:%M:%S GMT%z";
	
	template<typename... Args>
	static void WriteDebug(const char *function, int line, const char *fileName, Args ... args) {
		auto time = std::time(nullptr);
		auto tm = *std::localtime(&time);

		std::cout << "[DEBUG] " << std::put_time(&tm, TimestampFormat) << " - (" << fileName << "::" << function << "#" << line << ") ";
		((std::cout << std::forward<Args>(args)), ...);
		std::cout << "\n";
	}
};

#define WRITE_DEBUG(...) SpauldingCPP::Logger::WriteDebug(__FUNCTION__,__LINE__, __FILE__, __VA_ARGS__)
}