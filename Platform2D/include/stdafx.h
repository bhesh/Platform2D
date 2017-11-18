// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <string>
#include <condition_variable>
#include <mutex>
#include <set>
#include <thread>
#include <iostream>
#include <stdint.h>

#include "platform2d/config/SimpleIni.h"

#ifndef PLATFORM2D_H
#define PLATFORM2D_H

#ifdef _MSC_VER
typedef wchar_t os_char_t;
typedef std::wstring os_string_t;
typedef std::wostream os_ostream_t;
#define os_cout std::wcout
#define os_cerr std::wcerr
#define STRING(str) L ## str
#define CHAR(c) L ## c
#else
typedef char os_char_t;
typedef std::string os_string_t;
typedef std::ostream os_ostream_t;
#define os_cout std::cout;
#define os_cerr std::cerr;
#define STRING(str) str
#define CHAR(c) c
#endif

#endif // PLATFORM2D_H