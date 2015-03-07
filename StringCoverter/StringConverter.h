#pragma once

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