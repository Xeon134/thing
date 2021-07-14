#pragma once
#include <Windows.h>
#include <filesystem>

class Logger {
private:
	HANDLE logFile;
public:
	Logger(std::string);
	~Logger();
	void Log(const char*, ...);
};
