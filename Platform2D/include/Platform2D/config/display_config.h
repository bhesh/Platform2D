/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#ifndef PLATFORM2D_CONFIG_DISPLAY_CONFIG_H
#define PLATFORM2D_CONFIG_DISPLAY_CONFIG_H

#include "stdafx.h"

#include <SFML/Graphics.hpp>

namespace platform2d {

	namespace config {

		/**
			Gets the available fullscreen video modes

			@return VideoMode vector of the available fullscreen video modes
		*/
		std::vector<sf::VideoMode> GetFullscreenVideoModes();

		/**
			Gets the current desktop video mode

			@return the current desktop video mode
		*/
		sf::VideoMode GetDesktopVideoMode();

		/**
			Gets the video mode defined in the INI configuration file. The
			configuration file should specify the following under the @c Video
			section:
				@li @b lVideoWidth = @c width (defaults to 800)
				@li @b lVideoHeight = @c height (defaults to 600)
				@li @b lVideoBitsPerPixel = @c bpp (defaults to 32)

			@param config the ConfigT object to read from

			@return the video mode specified in the INI configuration file
		*/
		sf::VideoMode GetConfigVideoMode(ConfigT &configObj);

		/**
			Sets @c lVideoWidth, @c lVideoHeight, @c lVideoBitsPerPixel in the
			@c Video section to the values specified in the @c VideoMode object.
				@li @b lVideoWidth = @c width (defaults to 800)
				@li @b lVideoHeight = @c height (defaults to 600)
				@li @b lVideoBitsPerPixel = @c bpp (defaults to 32)

			@param config the ConfigT object to write to
			@param vmode the VideoMode object to get the values from
		*/
		void SetConfigVideoMode(ConfigT &configObj, sf::VideoMode vmode);

		/**
			Gets whether fullscreen is specified in the INI configuration file.
			This value will default to false if the option is invalid or 
			missing. The INI file should specify the following under the 
			@c Video section:
				@li @b bVideoFullscreen = @c 0 or @c 1 (defaults to 0)

			@param config the ConfigT object to read from

			@return whether fullscreen is specified in the INI configuration
			file. Defaults to false
		*/
		bool IsConfigVideoFullscreen(ConfigT &configObj);

		/**
			Sets the @c bVideoFullscreen in the @c Video section to the value of
			@c isFullscreen.
				@li @b bVideoFullscreen = @c 0 or @c 1 (defaults to 0)

			@b NOTE: This does not write it to disk. You must save the
			configuration.

			@param config the ConfigT object to write to
			@param isFullscreen set fullscreen to true or false in the
			configuration file
		*/
		void SetConfigVideoFullscreen(ConfigT &configObj, bool isFullscreen);

		/**
			Gets whether the window should be bordered from the INI
			configuration file. This option is ignored if fullscreen mode is
			enabled. This value will default to true if the option is invalid or
			missing. This INI file should specify the following under the
			@c Video section:
				@li @b bVideoBordered = @c 0 or @c 1 (defaults to 1)

			@param config the ConfigT object to read from

			@return whether the window should be bordered from the INI from the
			configuration file. Defaults to true
		*/
		bool IsConfigVideoBordered(ConfigT &configObj);

		/**
			Sets the @c bVideoBordered in the @c Video section to the value of
			@c isBordered.
				@li @b bVideoBordered = @c 0 or @c 1 (defaults to 1)

			@b NOTE: This does not write it to disk. You must save the
			configuration.

			@param config the ConfigT object to write to
			@param isBordered set bordered to true or false in the configuration
			file
		*/
		void SetConfigVideoBordered(ConfigT &configObj, bool isBordered);
	}
}

#endif // PLATFORM2D_CONFIG_DISPLAY_CONFIG_H