#include "platform2d/config.h"
#include "platform2d/debug.h"
#include "platform2d/graphics.h"

#include <SFML/Graphics.hpp>

#define USER_CONFIG_FILE STRING("C:/Users/brian/Desktop/Platform2D.ini")

int main(int argc, char **argv) {

	// Turn all debugging on
	platform2d::debug::kDbFlags = platform2d::debug::DB_ALL;

	// Load configuration file
	platform2d::config::ConfigT userConfig;
	if (userConfig.LoadFile(USER_CONFIG_FILE) < 0) {
		platform2d::debug::Debug(platform2d::debug::DB_VIDEO) <<
			STRING("Error loading configuration file") << std::endl;
		platform2d::debug::Debug(platform2d::debug::DB_VIDEO) <<
			STRING("Creating a new configuration file") << std::endl;
		platform2d::config::CreateNewUserConfig(USER_CONFIG_FILE);
	}

	// Get the video mode from configuration
	sf::VideoMode vmode = platform2d::config::GetConfigVideoMode(userConfig);
	bool fullscreen = platform2d::config::IsConfigVideoFullscreen(userConfig);
	bool hasBorder = platform2d::config::IsConfigVideoBordered(userConfig);

	// Set the window style
	sf::Uint32 style;
	if (fullscreen)
		style = sf::Style::Fullscreen;
	else if (hasBorder)
		style = sf::Style::Titlebar | sf::Style::Close;
	else
		style = sf::Style::None;

	// Output debugging details
	platform2d::debug::Debug(platform2d::debug::DB_VIDEO)
		<< STRING("Resolution: ") << vmode.width
		<< STRING("x") << vmode.height
		<< STRING(" at ") << vmode.bitsPerPixel
		<< STRING("bpp") << std::endl;
	platform2d::debug::Debug(platform2d::debug::DB_VIDEO)
		<< STRING("Fullscreen: ") << fullscreen << std::endl;
	platform2d::debug::Debug(platform2d::debug::DB_VIDEO)
		<< STRING("Border: ") << hasBorder << std::endl;

	// Make the window
	sf::RenderWindow window(vmode, STRING("2D Engine"), style);
	window.setFramerateLimit(60); // TEMPORARY
	window.setActive(false);
	platform2d::graphics::RenderThread render(&window);
	render.SetBackgroundColor(sf::Color::Cyan);
	render.Start();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				render.Stop();
				window.close();
			}
		}
		render.Update();
	}

	return 0;
}