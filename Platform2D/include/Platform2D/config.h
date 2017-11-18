/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#ifndef PLATFORM2D_CONFIG_H
#define PLATFORM2D_CONFIG_H

#include "stdafx.h"

#include "config/SimpleIni.h"

namespace platform2d {

	namespace config {

		/**
			Renames the CSimpleIni object to this library's namespace.

			Refer to @url https://github.com/brofield/simpleini for more
			information.
		*/
		typedef CSimpleIni ConfigT;

		/**
			Creates a new blank user configuration file.

			@param filename the file to create

			@return 0 on success, error code otherwise
		*/
		int CreateNewUserConfig(const os_char_t *filename);
	}
}

#include "platform2d/config/display_config.h"

#endif // PLATFORM2D_CONFIG_H