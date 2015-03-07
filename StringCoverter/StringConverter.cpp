#include "StringConverter.h"

namespace StringHelper {

	StringConverter::StringConverter() {}

	wstring StringConverter::toWString(string str) {
		return wstring(str.begin(), str.end());
	}

	LPCWSTR StringConverter::toLPCWSTR(string str) {
		return toWString(str).c_str();
	}

	StringConverter::~StringConverter() {}

}