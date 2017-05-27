/** @mainpage
	<table>
		<tr><th>Library     <td>Platform2D
		<tr><th>Author      <td>Brian Hession
		<tr><th>Email		<td><a href="mailto:hessionb@gmail.com">hessionb@gmail.com</a>
		<tr><th>Version     <td>0.0.1
	</table>

	@section intro INTRODUCTION

	Platform2D is an engine with the idea of abstracting  a lot of the nuances
	that come with implementing a 2D platform game. It handles a lot of the
	behind-the-scenes work so the developer can focus solely on the game. It is
	designed to be fast and flexible. It utilizes SFML libraries for both
	graphics and sound and is written in native C++ code.


	@section design DESIGN

	TODO: Design


	@section license LICENSE

	Copyright 2017 Brian Hession, all rights reserved.
 */

 //#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

/*
#include "platform2d/config/types.h"

#include "platform2d/config.h"
#include "platform2d/debug.h"
#include "platform2d/graphics.h"
#include "platform2d/resources.h"

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
	render.Start();

	// Make a square square
	sf::ConvexShape square;
	square.setPointCount(4);
	square.setPoint(0, sf::Vector2f(0, 0));
	square.setPoint(1, sf::Vector2f(300, 0));
	square.setPoint(2, sf::Vector2f(300, 300));
	square.setPoint(3, sf::Vector2f(0, 300));

	// Add to Catalog
	platform2d::resources::ConvexShapeCatalog shapeCatalog;
	shapeCatalog[0u] = (const sf::ConvexShape)square;

	// Make set
	int layers = 32;
	int num = 3;
	std::set<platform2d::graphics::SpriteRef> sprites;
	{
		for (int i = 0; i < layers; ++i) {
			for (int j = 0; j < num; ++j) {
				platform2d::graphics::SpriteRef sprite;
				sprite.catalog = &shapeCatalog;
				sprite.key = 0u;
				sprite.transformation.translate((float)((vmode.width / 2) - 150), (float)((vmode.height / 2) - 150));
				sprite.transformation.rotate(((90.0f / num) * j) + ((45.0f / num) * i), 150.0f, 150.0f);
				float scale = 4.0f - ((1.0f / (4 * (num - 1))) * i);
				sprite.transformation.scale(scale, scale, 150.0f, 150.f);
				sprite.layer = (i * num) + j;
				sprite.color += sf::Color(0x05000001);
				sprites.insert(sprite);
			}
		}
	}

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				render.Stop();
				window.close();
			}
		}

		for (auto& sprite : sprites) {
			switch (sprite.layer % 4) {
			case 0:
				sprite.transformation.rotate(0.25f, 150.0f, 150.0f);
			case 1:
				sprite.transformation.rotate(0.25f, 150.0f, 150.0f);
			case 2:
				sprite.transformation.rotate(0.25f, 150.0f, 150.0f);
			case 3:
				sprite.transformation.rotate(0.25f, 150.0f, 150.0f);
			}
		}
		render.Update(sprites);
	}

	return 0;
}
*/

#include "ResourceDB/Database.h"

#include <iostream>

int main(int argc, char **argv) {
	std::vector<ResourceDB::DBItem> items;
	std::cout << "Test: " << sizeof(items) << std::endl;
	char c;
	std::cin >> c;
	return 0;
}