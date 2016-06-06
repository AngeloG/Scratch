/*  libscratch - Multipurpose objective C++ library.
    
    Copyright (c) 2013 - 2016 Angelo Geels <spansjh@gmail.com>
    
    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:
    
    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "Common.h"
#include "Stream.hpp"

#ifdef SCRATCH_IMPL
#if WINDOWS
#pragma comment(lib, "wsock32.lib")
#endif

static BOOL _bWinsockInitialized = FALSE;
#endif

#if !WINDOWS
	#include <sys/socket.h>
	#include <unistd.h>
	#include <netdb.h>
#endif

SCRATCH_NAMESPACE_BEGIN;

class SCRATCH_EXPORT NetworkStream : public Stream
{
public:
#if WINDOWS
  WSADATA* ns_pWSAData;
  SOCKET ns_socket;
#else
  int ns_socket;
#endif
  sockaddr_in* ns_psin;

  BOOL ns_bEOF;

public:
	NetworkStream(void);
	~NetworkStream(void);

  ULONG Size();
  ULONG Location();
  void Seek(ULONG ulPos, INDEX iOrigin);
  BOOL AtEOF();

  BOOL Connect(const char* szAddress, USHORT iPort);
  void Close();
  void Write(const void* p, ULONG iLen);
  int Read(void* pDest, ULONG iLen);

  BOOL IsConnected();

  static void Cleanup(void);
};

#ifdef SCRATCH_IMPL

NetworkStream::NetworkStream(void)
{
#if WINDOWS
	ns_pWSAData = new WSADATA;
	ns_socket = NULL;
#else
	ns_socket = 0;
#endif
	ns_psin = new sockaddr_in;

	ns_bEOF = FALSE;

#if WINDOWS
	if (!_bWinsockInitialized) {
		if (WSAStartup(MAKEWORD(2, 2), ns_pWSAData) != 0) {
#ifdef SCRATCH_NO_EXCEPTIONS
			return;
#else
			throw "Couldn't initialize winsock";
#endif
		}
		_bWinsockInitialized = TRUE;
	}
#endif
}

NetworkStream::~NetworkStream(void)
{
	if (ns_socket != 0) {
#if WINDOWS
		closesocket(ns_socket);
#else
		close(ns_socket);
#endif
	}

#if WINDOWS
	delete ns_pWSAData;
#endif
	delete ns_psin;
}

ULONG NetworkStream::Size()
{
#ifdef SCRATCH_NO_EXCEPTIONS
	return 0;
#else
	throw "Function not supported in Network Stream";
#endif
}

ULONG NetworkStream::Location()
{
#ifdef SCRATCH_NO_EXCEPTIONS
	return 0;
#else
	throw "Function not supported in Network Stream";
#endif
}

void NetworkStream::Seek(ULONG ulPos, INDEX iOrigin)
{
#ifndef SCRATCH_NO_EXCEPTIONS
	throw "Function not supported in Network Stream";
#endif
}

BOOL NetworkStream::AtEOF()
{
	return ns_bEOF;
}

BOOL NetworkStream::Connect(const char* szAddress, USHORT iPort)
{
	hostent* phe = gethostbyname(szAddress);
	if (phe == NULL) {
		return FALSE;
	}

	ns_psin->sin_family = AF_INET;
	ns_psin->sin_addr.s_addr = *(ULONG*)phe->h_addr_list[0];
	ns_psin->sin_port = htons(iPort);

	ns_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ns_socket, (sockaddr*)ns_psin, sizeof(sockaddr_in)) == 0) {
		return TRUE;
	}

	return FALSE;
}

void NetworkStream::Close()
{
#if WINDOWS
	closesocket(ns_socket);
#else
	close(ns_socket);
#endif
	ns_socket = 0;
}

void NetworkStream::Write(const void* p, ULONG iLen)
{
	send(ns_socket, (const char*)p, iLen, 0);
}

int NetworkStream::Read(void* pDest, ULONG iLen)
{
	int iRet = recv(ns_socket, (char*)pDest, iLen, 0);
	ns_bEOF = (iRet <= 0) || ((ULONG)iRet < iLen);
	return iRet;
}

BOOL NetworkStream::IsConnected()
{
#if WINDOWS
	fd_set fds;
	fds.fd_array[0] = ns_socket;
	fds.fd_count = 1;
	return select(0, &fds, &fds, &fds, NULL) == 1;
#else
	return TRUE; //TODO: FIXME
#endif
}

void NetworkStream::Cleanup(void)
{
#if WINDOWS
	if (_bWinsockInitialized) {
		WSACleanup();
		_bWinsockInitialized = false;
	}
#endif
}

#endif

SCRATCH_NAMESPACE_END;
