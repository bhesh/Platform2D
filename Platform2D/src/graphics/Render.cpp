/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#include "stdafx.h"

#include "platform2d/graphics/Render.h"

namespace platform2d {
	namespace graphics {

		void RenderBase::ClearBackground(sf::Color color) {
			window->clear(color);
		}

		void RenderBase::Draw() {
			/*
			for (auto &sprite : sprites) {
				const platform2d::resources::Catalog *catalog = sprite.catalog;
				switch (catalog->)
				const sf::Drawable &drawable = catalog->GetDrawable(sprite.key);
				const sf::Transform &transform = sprite.transformation;
				window->draw(drawable, sf::RenderStates(transform));
			}
			*/
		}

		RenderThread::RenderThread(sf::RenderWindow *window) :
			RenderBase(window) {
			is_running = false;
			can_update = true;
			thread = nullptr;
			leftBgColor = sf::Color::Black;
			rightBgColor = sf::Color::Black;
			drawBgColor = &leftBgColor;
			drawQueue = &leftQueue;
			renderBgColor = &rightBgColor;
			renderQueue = &rightQueue;
		}

		void RenderThread::Start() {
			if (thread != nullptr)
				throw "Rendering thread is already running.";
			is_running = true;
			can_update = false;
			thread = new std::thread(&RenderThread::RenderLoop, this);
		}

		void RenderThread::Stop() {
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

		void RenderThread::SetBackgroundColor(const sf::Color bgColor) {
			*this->drawBgColor = bgColor;
		}

		void RenderThread::Draw(const sf::Drawable &drawable) {
			this->drawQueue->push(drawable);
		}

		void RenderThread::Swap() {
			if (drawBgColor == &leftBgColor) {
				drawBgColor = &rightBgColor;
				drawQueue = &rightQueue;
				renderBgColor = &leftBgColor;
				renderQueue = &leftQueue;
			}
			else {
				drawBgColor = &leftBgColor;
				drawQueue = &leftQueue;
				renderBgColor = &rightBgColor;
				renderQueue = &rightQueue;
			}
		}

		void RenderThread::Update() {
			{
				std::unique_lock<std::mutex> lock(mutex);
				while (!can_update) cv.wait(lock);
				Swap();
				can_update = false;
			}
			cv.notify_one();
		}

		void RenderThread::RenderLoop() {
			window->setActive();
			while (is_running) {
				{
					std::unique_lock<std::mutex> lock(mutex);
					while (can_update) cv.wait(lock);
					if (!is_running)
						break;
					ClearBackground(*this->renderBgColor);
					while (!renderQueue->empty()) {
						const sf::Drawable &drawable = renderQueue->front();
						window->draw(drawable);
						renderQueue->pop();
					}
					window->display();
					can_update = true;
				}
				cv.notify_one();
			}
		}
	}
}