#include <Platform2D/config.h>
#include <Platform2D/debug.h>
#include <Platform2D/graphics.h>

#include <SFML/Graphics.hpp>

#define USER_CONFIG_FILE STRING("C:/Users/bhession/Desktop/Platform2D.ini")

int main(int argc, char **argv) {

	// Turn all debugging on
	platform2d::debug::SetDebugFlags(platform2d::debug::DB_ALL);

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

	// Make squares
	sf::RectangleShape rect1;
	rect1.setFillColor(sf::Color::Red);
	rect1.setSize(sf::Vector2f(100, 100));
	sf::RectangleShape rect2;
	rect2.setFillColor(sf::Color::Green);
	rect2.setSize(sf::Vector2f(100, 100));
	sf::RectangleShape rect3;
	rect3.setFillColor(sf::Color::Blue);
	rect3.setSize(sf::Vector2f(100, 100));

	// Make the window
	int FRAMES_PER_SECOND = 60;
	sf::RenderWindow window(vmode, STRING("2D Engine"), style);
	window.setFramerateLimit(FRAMES_PER_SECOND); // TEMPORARY
	window.setActive(false);
	platform2d::graphics::RenderThread render(&window);
	render.SetBackgroundColor(sf::Color::Black);
	render.Start();

	float x = -300.0;
	float r = 0.0;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				render.Stop();
				window.close();
			}
		}
		if (!window.isOpen())
			return 0;

		// Update position and draw
		sf::Transform transform1;
		transform1.translate(x, 150);
		transform1.rotate(r, sf::Vector2f(50, 150));
		render.Draw(rect1, sf::RenderStates(transform1));
		sf::Transform transform2;
		transform2.translate(x, 250);
		transform2.rotate(r, sf::Vector2f(50, 50));
		render.Draw(rect2, sf::RenderStates(transform2));
		sf::Transform transform3;
		transform3.translate(x, 350);
		transform3.rotate(r, sf::Vector2f(50, -50));
		render.Draw(rect3, sf::RenderStates(transform3));
		x += (4 * 60) / FRAMES_PER_SECOND;
		if (x >= 1480)
			x = -300;
		r += (3 * 60) / FRAMES_PER_SECOND;
		if (r >= 360)
			r = 0;

		// Update window
		render.Update();
	}
	return 0;
}