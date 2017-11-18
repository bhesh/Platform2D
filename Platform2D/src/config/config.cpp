/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#include "stdafx.h"

#include "platform2d/config.h"

namespace platform2d {
	namespace config {

		int CreateNewUserConfig(const os_char_t *filename) {
			platform2d::config::ConfigT config;
			return config.SaveFile(filename);
		}
	}
}