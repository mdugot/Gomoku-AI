#include "utils.h"

void success(std::string message)
{
	OUT << DEFAULT_COLOR << message << "\n";
	exit(EXIT_SUCCESS);
}

void failure(std::string message)
{
	ERROR << RED << message << DEFAULT_COLOR << "\n";
	exit(EXIT_FAILURE);
}
