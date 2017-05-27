/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#include "platform2d/graphics/SpriteRef.h"
#include "platform2d/graphics/Render.h"
#include "platform2d/resources/Catalog.h"

#include <SFML/Graphics.hpp>

#include <set>

void platform2d::graphics::RenderBase::DrawBackground(sf::Color color) {
	window->clear(color);
}

void platform2d::graphics::RenderBase::DrawForeground(
	const std::set<SpriteRef> &sprites) {
	for (auto &sprite : sprites) {
		const platform2d::resources::Catalog *catalog = sprite.catalog;
		switch (catalog->)
		const sf::Drawable &drawable = catalog->GetDrawable(sprite.key);
		const sf::Transform &transform = sprite.transformation;
		window->draw(drawable, sf::RenderStates(transform));
	}
}

void platform2d::graphics::RenderBase::Update(std::set<SpriteRef> &sprites) {
	DrawBackground(sf::Color::Black);
	DrawForeground(sprites);
	window->display();
}

platform2d::graphics::RenderThread::RenderThread(sf::RenderWindow *window) :
	RenderBase(window) {
	is_running = false;
	can_update = true;
	thread = nullptr;
}

void platform2d::graphics::RenderThread::Start() {
	if (thread != nullptr)
		throw "Rendering thread is already running.";
	is_running = true;
	can_update = false;
	thread = new std::thread(&platform2d::graphics::RenderThread::RenderLoop, this);
}

void platform2d::graphics::RenderThread::Stop() {
	if (thread == nullptr)
		throw "Rendering thread is not running.";

	// Stop the thread
	{
		std::unique_lock<std::mutex> lock(mutex);
		while (!can_update) cv.wait(lock);
		is_running = false;
		can_update = false;
	}
	cv.notify_one();
	thread->join();
	delete thread;

	// Important to set these back to a clean state
	can_update = true;
	thread = nullptr;
}

void platform2d::graphics::RenderThread::Update(std::set<SpriteRef> &sprites) {
	{
		std::unique_lock<std::mutex> lock(mutex);
		while (!can_update) cv.wait(lock);
		this->sprites = sprites;
		can_update = false;
	}
	cv.notify_one();
}

void platform2d::graphics::RenderThread::RenderLoop() {
	window->setActive();
	while (is_running) {
		{
			std::unique_lock<std::mutex> lock(mutex);
			while (can_update) cv.wait(lock);
			if (!is_running)
				break;
			DrawBackground(sf::Color::Black);
			DrawForeground(sprites);
			window->display();
			can_update = true;
		}
		cv.notify_one();
	}
}