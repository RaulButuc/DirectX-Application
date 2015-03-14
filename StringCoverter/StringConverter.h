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

  template <typename StrT, typename StrS>
  class StringConverter {

    public:
      static StrT convert(StrS);

  };

  /**
   *  Convert a string of type StrS to a string of type StrT.
   *
   *  @param str The string of type StrS that is to be converted.
   *  @return The converted string into the desired format (long pointer constant type assumed).
   *         
   */
  template <typename StrT, typename StrS>
  StrT StringConverter<StrT, StrS>::convert(StrS str) {
    wchar_t* wString = new wchar_t[2 * strlen(str.c_str())];
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wString, 2 * strlen(str.c_str()));

    return wString;
  }

}
