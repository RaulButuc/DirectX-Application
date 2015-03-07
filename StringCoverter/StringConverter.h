/**
 *  StringConverter.h
 *  Purpose: Enable easy conversion from string to wstring and LPCWSTR formats.
 *
 *  @author Raul Butuc
 *  @version 1.0.0 06/03/2015
 */

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>

using std::string;
using std::wstring;

namespace StringHelper {

	template <typename _StrS, typename _StrT>
	class StringConverter {

	public:
		StringConverter();
		static _StrS convert(_StrT);
		~StringConverter();

	};

	template <typename _StrS, typename _StrT>
	StringConverter<_StrS, _StrT>::StringConverter() {}

	template <typename _StrS, typename _StrT>
	_StrS StringConverter<_StrS, _StrT>::convert(_StrT str) {
		wchar_t* wString = new wchar_t[2 * strlen(str.c_str())];
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wString, 2 * strlen(str.c_str()));

		return wString;
	}

	template <typename _StrS, typename _StrT>
	StringConverter<_StrS, _StrT>::~StringConverter() {}

}