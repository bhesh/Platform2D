/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#include "stdafx.h"

#include "platform2d/debug.h"

namespace platform2d {
	namespace debug {

		uint32_t kDbFlags = 0;

#ifdef _MSC_VER
		static std::wostream wnullstream(NULL);
		static std::wostream *wout = &std::wcerr;

		void SetDebugStream(std::wostream &newstream) {
			wout = &newstream;
		}

		std::wostream& Debug(uint32_t flag) {
			return (kDbFlags & flag) ? *wout : wnullstream;
		}
#else
		static std::ostream nullstream(NULL);
		static std::ostream *out = &std::cerr;

		void SetDebugStream(std::ostream &newstream) {
			out = &newstream;
		}

		std::ostream& Debug(uint32_t flag) {
			return (kDbFlags & flag) ? *out : nullstream;
		}
#endif
	}
}