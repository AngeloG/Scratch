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

#ifndef SCRATCH_CMEMORYSTREAM_H_INCLUDED
#define SCRATCH_CMEMORYSTREAM_H_INCLUDED 1

#ifdef USE_PRAGMAONCE
  #pragma once
#endif

#include "Common.h"
#include "CStream.h"

class CMemoryStream : public CStream
{
public:
  UBYTE* strm_pubBuffer;
  ULONG strm_ulPosition;
  ULONG strm_ulSize;
  ULONG strm_ulUsed;

public:
  CMemoryStream(void);
  ~CMemoryStream(void);

  ULONG Size();
  ULONG Location();
  void Seek(ULONG ulPos, INDEX iOrigin);

  void Write(const void* p, ULONG iLen);
  void* Read(ULONG iLen);
  const void* ReadToEnd(void);

private:
  void AllocateMoreMemory(INDEX ctBytes);
};

#endif