/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#include "stdafx.h"

#include "platform2d/graphics/Render.h"

namespace platform2d {
	namespace graphics {

		void RenderBase::ClearBackground(sf::Color bgColor) {
			window->clear(bgColor);
		}

		void RenderBase::Draw(const sf::Drawable &drawable,
			const sf::RenderStates states) {
			window->draw(drawable, states);
		}

		void RenderBase::Update() {
			window->display();
		}

		RenderThread::RenderThread(sf::RenderWindow *window) :
			RenderBase(window) {
			is_running = false;
			is_rendering = false;
			thread = nullptr;
			drawBgColor = sf::Color::Black;
			renderBgColor = sf::Color::Black;
			drawQueue = &queue1;
			renderQueue = &queue2;
		}

		void RenderThread::Start() {
			if (thread != nullptr)
				throw "Rendering thread is already running.";
			is_running = true;
			thread = new std::thread(&RenderThread::RenderLoop, this);
		}

		void RenderThread::Stop() {
			if (thread == nullptr || !is_running)
				throw "Rendering thread is not running.";

			// Stop the thread
			{
				std::unique_lock<std::mutex> lock(mutex);
				while (is_rendering) cv.wait(lock);
				is_running = false;
				is_rendering = true;
			}
			cv.notify_one();

			// Clean up the child
			thread->join();
			delete thread;

			// Clean up the queues
			while (!queue1.empty()) {
				RenderItem *item = queue1.front();
				queue1.pop();
				delete item;
			}
			while (!queue2.empty()) {
				RenderItem *item = queue2.front();
				queue2.pop();
				delete item;
			}

			// Important to set this back to a clean state
			is_running = false;
			is_rendering = false;
			thread = nullptr;
			drawBgColor = sf::Color::Black;
			renderBgColor = sf::Color::Black;
			drawQueue = &queue1;
			renderQueue = &queue2;
		}

		void RenderThread::SetBackgroundColor(const sf::Color bgColor) {
			this->drawBgColor = bgColor;
		}

		void RenderThread::Draw(const sf::Drawable &drawable,
			const sf::RenderStates states) {
			RenderItem *item = new RenderItem();
			item->item = &drawable;
			item->states = states;
			this->drawQueue->push(item);
		}

		void RenderThread::Swap() {
			if (drawQueue == &queue1) {
				drawQueue = &queue2;
				renderQueue = &queue1;
			}
			else {
				drawQueue = &queue1;
				renderQueue = &queue2;
			}
			renderBgColor = drawBgColor;
		}

		void RenderThread::Update() {
			if (thread == nullptr || !is_running)
				throw "Rendering thread is not running.";
			{
				std::unique_lock<std::mutex> lock(mutex);
				while (is_rendering) cv.wait(lock);
				Swap();
				is_rendering = true;
			}
			cv.notify_one();
		}

		void RenderThread::RenderLoop() {
			window->setActive();
			while (is_running) {
				{
					std::unique_lock<std::mutex> lock(mutex);
					while (!is_rendering) cv.wait(lock);
					if (!is_running)
						break;
					RenderBase::ClearBackground(renderBgColor);
					while (!renderQueue->empty()) {
						RenderItem *item = renderQueue->front();
						RenderBase::Draw(*item->item, item->states);
						renderQueue->pop();
						delete item;
					}
					window->display();
					is_rendering = false;
				}
				cv.notify_one();
			}
		}
	}
}