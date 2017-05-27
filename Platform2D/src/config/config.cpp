/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#include "platform2d/config.h"

int platform2d::config::CreateNewUserConfig(const os_char_t *filename) {
	platform2d::config::ConfigT config;
	return config.SaveFile(filename);
}