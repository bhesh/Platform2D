/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#ifndef PLATFORM2D_DEBUG_H
#define PLATFORM2D_DEBUG_H

#include "platform2d/config/types.h"
#include <iostream>
#include <stdint.h>

namespace platform2d {

	namespace debug {

		/**
			Masks for setting the different debugging flags.
		*/
		enum {
			/**
				Video debugging flag
			*/
			DB_VIDEO = 0x1,

			/**
				Graphics debugging flag
			*/
			DB_GRAPHICS = 0x2,

			/**
				All debugging
			*/
			DB_ALL = 0xFFFFFFFF
		};

		/**
			The variable that keeps track of which debugging flags are set. Both
			@c Debug and @c DebugW commands will reference this variable to
			decide whether to print the message or not. The variable is
			initially set to 0.

			An example to set the video debugging flag:

			@code{.cpp}
				kDbFlags |= DB_VIDEO;
			@endcode

			An example to clear the graphics flag:

			@code{.cpp}
				kDbFlags &= ~DB_GRAPHICS;
			@endcode
		*/
		extern uint32_t kDbFlags;

#ifdef _MSC_VER
		/**
			Sets a new @c wostream to direct debugging to
		*/
		void SetDebugStream(std::wostream &newstream);
		
		/**
			The command to direct debugging messages to. For example:
			@code{.cpp}
				DebugW(DB_VIDEO) << L"Video debugging message" << std::endl;
			@endcode

			@param flag the flag used to filter debugging messages

			@return a reference to the current @c wostream object
		*/
		std::wostream& Debug(uint32_t flag);
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