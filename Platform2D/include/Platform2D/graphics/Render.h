/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#ifndef PLATFORM2D_GRAPHICS_RENDER_H
#define PLATFORM2D_GRAPHICS_RENDER_H

#include "stdafx.h"

#include "platform2d/graphics/SpriteRef.h"

#include <SFML/Graphics.hpp>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

namespace platform2d {

	namespace graphics {

		class RenderBase {
		public:
			RenderBase(sf::RenderWindow *window) { this->window = window; }
			~RenderBase() {};
			//void SetMap();
		protected:
			void ClearBackground(const sf::Color color);
			void Draw();
			sf::RenderWindow *window;
		};

		class RenderThread : public RenderBase {
		public:
			RenderThread(sf::RenderWindow *window);
			~RenderThread() { if (IsRunning()) Stop(); };
			void Start();
			void Stop();
			//void SetMap();
			bool IsRunning() const { return thread != nullptr; };
			void SetBackgroundColor(const sf::Color bgColor);
			void Draw(const sf::Drawable &drawable);
			void Update();
			void RenderLoop();

		private:
			void Swap();
			sf::Color leftBgColor;
			std::queue<const sf::Drawable&> leftQueue;
			sf::Color rightBgColor;
			std::queue<const sf::Drawable&> rightQueue;
			sf::Color *drawBgColor;
			std::queue<const sf::Drawable&> *drawQueue;
			sf::Color *renderBgColor;
			std::queue<const sf::Drawable&> *renderQueue;
			std::thread *thread;
			std::mutex mutex;
			std::condition_variable cv;
			bool can_update;
			bool is_running;
		};
	}
}

#endif // PLATFORM2D_GRAPHICS_RENDER_H