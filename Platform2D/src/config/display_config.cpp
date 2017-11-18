/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#include "stdafx.h"

#include "platform2d/config.h"

#define VIDEO_SECTION L"Video"
#define VIDEO_WIDTH L"lVideoWidth"
#define VIDEO_HEIGHT L"lVideoHeight"
#define VIDEO_BPP L"lVideoBitsPerPixel"
#define VIDEO_IS_FULLSCREEN L"bVideoFullscreen"
#define VIDEO_IS_BORDERED L"bVideoBordered"

namespace platform2d {
	namespace config {

		std::vector<sf::VideoMode> GetFullscreenVideoModes() {
			return sf::VideoMode::getFullscreenModes();
		}

		sf::VideoMode GetDesktopVideoMode() {
			return sf::VideoMode::getDesktopMode();
		}

		sf::VideoMode GetConfigVideoMode(
			ConfigT &configObj) {
			unsigned int width = (unsigned int)configObj.GetLongValue(VIDEO_SECTION,
				VIDEO_WIDTH, 800);
			unsigned int height = (unsigned int)configObj.GetLongValue(VIDEO_SECTION,
				VIDEO_HEIGHT, 600);
			unsigned int bpp = (unsigned int)configObj.GetLongValue(VIDEO_SECTION,
				VIDEO_BPP, 32);
			return sf::VideoMode(width, height, bpp);
		}

		void SetConfigVideoMode(ConfigT &configObj,
			sf::VideoMode vmode) {
			configObj.SetLongValue(VIDEO_SECTION, VIDEO_WIDTH, vmode.width);
			configObj.SetLongValue(VIDEO_SECTION, VIDEO_HEIGHT, vmode.height);
			configObj.SetLongValue(VIDEO_SECTION, VIDEO_BPP, vmode.bitsPerPixel);
		}

		bool IsConfigVideoFullscreen(
			ConfigT &configObj) {
			return configObj.GetBoolValue(VIDEO_SECTION, VIDEO_IS_FULLSCREEN);
		}

		void SetConfigVideoFullscreen(
			ConfigT &configObj, bool isFullscreen) {
			configObj.SetBoolValue(VIDEO_SECTION, VIDEO_IS_FULLSCREEN, isFullscreen);
		}

		bool IsConfigVideoBordered(
			ConfigT &configObj) {
			return configObj.GetBoolValue(VIDEO_SECTION, VIDEO_IS_BORDERED);
		}

		void SetConfigVideoBordered(
			ConfigT &configObj, bool isBordered) {
			configObj.SetBoolValue(VIDEO_SECTION, VIDEO_IS_BORDERED, isBordered);
		}
	}
}