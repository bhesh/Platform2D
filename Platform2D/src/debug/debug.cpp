/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#include "platform2d/debug.h"

uint32_t platform2d::debug::kDbFlags = 0;

#ifdef _MSC_VER
static std::wostream wnullstream(NULL);
static std::wostream *wout = &std::wcerr;

void platform2d::debug::SetDebugStream(std::wostream &newstream) {
	wout = &newstream;
}

std::wostream& platform2d::debug::Debug(uint32_t flag) {
	return (platform2d::debug::kDbFlags & flag) ? *wout : wnullstream;
}
#else
static std::ostream nullstream(NULL);
static std::ostream *out = &std::cerr;

void platform2d::debug::SetDebugStream(std::ostream &newstream) {
	out = &newstream;
}

std::ostream& platform2d::debug::Debug(uint32_t flag) {
	return (platform2d::debug::kDbFlags & flag) ? *out : nullstream;
}
#endif