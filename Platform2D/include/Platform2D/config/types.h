/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#ifndef PLATFORM2D_CONFIG_TYPES_H
#define PLATFORM2D_CONFIG_TYPES_H

#ifdef _MSC_VER
typedef wchar_t os_char_t;
#define STRING(str) L##str
#else
typedef char os_char_t;
#define STRING(str) str
#endif

#endif // PLATFORM2D_CONFIG_TYPES_H