/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#ifndef PLATFORM2D_DEBUG_H
#define PLATFORM2D_DEBUG_H

#include "stdafx.h"

namespace platform2d {

	namespace debug {

		/**
			Video debugging flag
		*/
		PLATFORM2D_API const uint32_t DB_VIDEO = 0x1;

		/**
			Graphics debugging flag
		*/
		PLATFORM2D_API const uint32_t DB_GRAPHICS = 0x2;

		/**
			All debugging
		*/
		PLATFORM2D_API const uint32_t DB_ALL = 0xFFFFFFFF;

		/**
			This function sets the debug flag that supresses or verboses
			the output of @c Debug and @c DebugW commands.

			An example to set the video debugging flag:

			@code{.cpp}
				SetDebugFlags(DB_VIDEO | DB_GRAPHICS);
			@endcode

			@param the flags to set
		*/
		PLATFORM2D_API void SetDebugFlags(uint32_t flags);

		/**
			Returns the current debug flags.

			@return the current debug flags
		*/
		PLATFORM2D_API void SetDebugFlags(uint32_t flags);

#ifdef _MSC_VER
		/**
			Sets a new @c wostream to direct debugging to
		*/
		PLATFORM2D_API void SetDebugStream(std::wostream &newstream);
		
		/**
			The command to direct debugging messages to. For example:
			@code{.cpp}
				DebugW(DB_VIDEO) << L"Video debugging message" << std::endl;
			@endcode

			@param flag the flag used to filter debugging messages

			@return a reference to the current @c wostream object
		*/
		PLATFORM2D_API std::wostream& Debug(uint32_t flag);
#else
		/**
			Sets a new @c ostream to direct debugging to
		*/
		void SetDebugStream(std::ostream &newstream);

		/**
			The command to direct debugging messages to. For example:
			@code{.cpp}
				Debug(DB_VIDEO) << "Video debugging message" << std::endl;
			@endcode

			@param flag the flag used to filter debugging messages

			@return a reference to the current @c ostream object
		*/
		std::ostream& Debug(uint32_t flag);
#endif
	}
}

#endif // PLATFORM2D_DEBUG_H