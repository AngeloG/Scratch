/*  libscratch - Multipurpose objective C++ library.
    Copyright (C) 2012 - 2013  Angelo Geels

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef SCRATCH_CSTRING_H_INCLUDED
#define SCRATCH_CSTRING_H_INCLUDED

#include "CStackArray.h"

#ifndef CSTRING_FORMAT_BUFFER_SIZE
#define CSTRING_FORMAT_BUFFER_SIZE 1024
#endif

SCRATCH_NAMESPACE_BEGIN;

class SCRATCH_EXPORT CString
{
private:
  char* str_szBuffer;

  void CopyToBuffer(const char* szSrc);
  void AppendToBuffer(const char* szSrc);
  void AppendToBuffer(const char* szSrc, int iCount);
  void AppendToBuffer(const char cSrc);

public:
  static char* str_szEmpty;
  static int str_iInstances;

  CString();
  CString(const char* szValue);
  CString(const CString &strCopy);
  ~CString();

  void SetF(const char* szFormat, ...);
  void AppendF(const char* szFormat, ...);

  void Split(const CString &strNeedle, CStackArray<CString> &astrResult) const;
  void Split(const CString &strNeedle, CStackArray<CString> &astrResult, BOOL bTrimAll) const ;
  void Split(const CString &strNeedle, CStackArray<CString> &astrResult, BOOL bTrimAll, int iMax) const;
  CString Trim();
  CString Replace(const CString &strNeedle, const CString &strReplace) const;
  CString SubString(int iStart, int iLen) const;
  CString ToLower() const;
  CString ToUpper() const;

  bool Contains(const CString &strNeedle);
  bool Contains(char c) const;
  bool StartsWith(const CString &strNeedle);
  bool EndsWith(const CString &strNeedle);

  operator const char*();
  operator const char*() const;

  CString& operator=(char* szSrc);
  CString& operator=(const char* szSrc);
  CString& operator=(const CString &strSrc);

  CString& operator+=(const char* szSrc);
  CString& operator+=(const char cSrc);

  bool operator==(const char* szSrc) const;
  bool operator!=(const char* szSrc) const;

  char& operator[](int iIndex);
};

CString SCRATCH_EXPORT operator+(const CString &strLHS, const char* szRHS);
CString SCRATCH_EXPORT operator+(const CString &strLHS, const char cRHS);

CString SCRATCH_EXPORT operator+(const char* szLHS, CString &strRHS);
CString SCRATCH_EXPORT operator+(const char cLHS, CString &strRHS);

CString SCRATCH_EXPORT strPrintF(const char* szFormat, ...);

SCRATCH_NAMESPACE_END;

#endif // include once check
