#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>

using std::string;
using std::wstring;

namespace StringHelper {

	class StringConverter {

	public:
		StringConverter();
		static wstring toWString(string);
		static LPCWSTR toLPCWSTR(string);
		~StringConverter();

	};

}