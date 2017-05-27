/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#include "platform2d/config.h"
#include "platform2d/config/display_config.h"
#include "platform2d/config/SimpleIni.h"

#include <iostream>

#define VIDEO_SECTION L"Video"
#define VIDEO_WIDTH L"lVideoWidth"
#define VIDEO_HEIGHT L"lVideoHeight"
#define VIDEO_BPP L"lVideoBitsPerPixel"
#define VIDEO_IS_FULLSCREEN L"bVideoFullscreen"
#define VIDEO_IS_BORDERED L"bVideoBordered"

std::vector<sf::VideoMode> platform2d::config::GetFullscreenVideoModes() {
	return sf::VideoMode::getFullscreenModes();
}

sf::VideoMode platform2d::config::GetDesktopVideoMode() {
	return sf::VideoMode::getDesktopMode();
}

sf::VideoMode platform2d::config::GetConfigVideoMode(
	platform2d::config::ConfigT &configObj) {
	unsigned int width = (unsigned int)configObj.GetLongValue(VIDEO_SECTION,
		VIDEO_WIDTH, 800);
	unsigned int height = (unsigned int)configObj.GetLongValue(VIDEO_SECTION,
		VIDEO_HEIGHT, 600);
	unsigned int bpp = (unsigned int)configObj.GetLongValue(VIDEO_SECTION,
		VIDEO_BPP, 32);
	return sf::VideoMode(width, height, bpp);
}

void platform2d::config::SetConfigVideoMode(platform2d::config::ConfigT &configObj,
	sf::VideoMode vmode) {
	configObj.SetLongValue(VIDEO_SECTION, VIDEO_WIDTH, vmode.width);
	configObj.SetLongValue(VIDEO_SECTION, VIDEO_HEIGHT, vmode.height);
	configObj.SetLongValue(VIDEO_SECTION, VIDEO_BPP, vmode.bitsPerPixel);
}

bool platform2d::config::IsConfigVideoFullscreen(
	platform2d::config::ConfigT &configObj) {
	return configObj.GetBoolValue(VIDEO_SECTION, VIDEO_IS_FULLSCREEN);
}

void platform2d::config::SetConfigVideoFullscreen(
	platform2d::config::ConfigT &configObj, bool isFullscreen) {
	configObj.SetBoolValue(VIDEO_SECTION, VIDEO_IS_FULLSCREEN, isFullscreen);
}

bool platform2d::config::IsConfigVideoBordered(
	platform2d::config::ConfigT &configObj) {
	return configObj.GetBoolValue(VIDEO_SECTION, VIDEO_IS_BORDERED);
}

void platform2d::config::SetConfigVideoBordered(
	platform2d::config::ConfigT &configObj, bool isBordered) {
	configObj.SetBoolValue(VIDEO_SECTION, VIDEO_IS_BORDERED, isBordered);
}