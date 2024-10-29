#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdarg.h>

#define LOG(...) Log(__VA_ARGS__)

void Log(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);

	std::ostringstream oss;

	char buffer[512];
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	oss << buffer;

	va_end(args);

	std::cout << oss.str() << std::endl;
}

std::string read_f(std::string path) {
	std::ifstream file(path, std::ios::binary);

	if (!file.is_open())
		throw std::runtime_error("Unable to open file:");

	std::string buffer;
	unsigned char byte;

	while (file.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
		buffer.push_back(byte);
	}

	file.close();

	return buffer;
}

std::vector<std::string> read_l(std::string path) {
	std::vector<std::string> buffer;
	std::string line;

	std::ifstream fd(path, std::ios::binary);
	if (fd.is_open()) {
		while (std::getline(fd, line)) {
			buffer.push_back(line);
		}
		fd.close();
	}

	return buffer;
}

ssize_t fetch_size_s(std::string path) {
	std::ifstream fd;
	fd.open(path, std::ios::binary);
	fd.seekg(0, std::ios_base::end);
	ssize_t size = fd.tellg();
	return size;
}

inline std::string hexify(long val) {
	std::stringstream stream;
	stream << std::hex << val;
	return stream.str();
}
