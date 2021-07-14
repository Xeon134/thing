#include "logger.h"

Logger::Logger(std::string fileName) {
	std::filesystem::path log = std::filesystem::current_path() / fileName;
	logFile = CreateFileW(log.wstring().c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
}

Logger::~Logger() {
	CloseHandle(logFile);
}

void Logger::Log(const char* format, ...) {
	SYSTEMTIME rawtime;
	GetSystemTime(&rawtime);
	char buf[MAX_PATH];
	auto size = GetTimeFormatA(LOCALE_CUSTOM_DEFAULT, 0, &rawtime, "[HH':'mm':'ss] ", buf, MAX_PATH) - 1;
	size += snprintf(buf + size, sizeof(buf) - size, "[TID: 0x%X] ", GetCurrentThreadId());
	va_list argptr;
	va_start(argptr, format);
	size += vsnprintf(buf + size, sizeof(buf) - size, format, argptr);
	WriteFile(logFile, buf, size, NULL, NULL);
	va_end(argptr);
}