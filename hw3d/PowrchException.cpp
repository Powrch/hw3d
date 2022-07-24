#include "PowrchException.h"
#include <sstream>

PowrchException::PowrchException(int line, const char* file) noexcept
	:
	line(line),
	file(file)
{
}

const char* PowrchException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* PowrchException::GetType() const noexcept
{
	return "Powrch Exception";
}

int PowrchException::GetLine() const noexcept
{
	return line;
}

const std::string& PowrchException::GetFile() const noexcept
{
	return file;
}

std::string PowrchException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File]" << file << std::endl
		<< "[Line]" << line;
	return oss.str();
}
