#pragma once

#include <string>
#include <iomanip>
#include <sstream>

#include "bakkesmod\wrappers\wrapperstructs.h"

template <typename T>
std::string to_string_decimals(const T a_value, int n)
{
	std::ostringstream out;
	out << std::fixed << std::setprecision(n) << a_value;
	return out.str();
}

std::string to_string(float f, int prec = 2) {
	return to_string_decimals(f, prec);
}