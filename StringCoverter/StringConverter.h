/**
 *  StringConverter.h
 *  Purpose: Enable easy conversion from string to lpConstWideStr and other string types.
 *
 *  @author Raul Butuc
 *  @version 1.0.1 07/03/2015
 */

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>

using std::string;

namespace StringHelper {

  template <typename _StrS, typename _StrT>
  class StringConverter {

    public:
      static _StrS convert(_StrT);

  };

  /**
   *  Convert a string of type _StrT to a string of type _StrS.
   *
   *  @param _str The string of type _StrT that is to be converted.
   *  @return The converted string into the desired format (assuming long pointer constant type).
   */
  template <typename _StrS, typename _StrT>
  _StrS StringConverter<_StrS, _StrT>::convert(_StrT _str) {
    wchar_t* wString = new wchar_t[2 * strlen(_str.c_str())];
    MultiByteToWideChar(CP_ACP, 0, _str.c_str(), -1, wString, 2 * strlen(_str.c_str()));

    return wString;
  }

}