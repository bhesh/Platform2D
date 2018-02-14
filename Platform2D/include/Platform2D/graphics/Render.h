/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#ifndef PLATFORM2D_GRAPHICS_RENDER_H
#define PLATFORM2D_GRAPHICS_RENDER_H

#include "stdafx.h"

#include <SFML/Graphics.hpp>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

namespace platform2d {

	namespace graphics {

		class PLATFORM2D_API RenderBase {
		public:
			RenderBase(sf::RenderWindow *window) { this->window = window; }
			~RenderBase() {};
			void ClearBackground(const sf::Color bgColor);
			void Draw(const sf::Drawable &item, const sf::RenderStates states);
			void Update();
		protected:
			sf::RenderWindow *window;
		};

		class PLATFORM2D_API RenderThread : public RenderBase {
		public:
			RenderThread(sf::RenderWindow *window);
			~RenderThread() { if (IsRunning()) Stop(); };
			void Start();
			void Stop();
			bool IsRunning() const { return thread != nullptr; };
			void SetBackgroundColor(const sf::Color bgColor);
			void Draw(const sf::Drawable &drawable, const sf::RenderStates states);
			void Update();

		private:
			void RenderLoop();
			std::thread *thread;
			std::mutex mutex;
			std::condition_variable cv;
			bool is_running;
			bool is_rendering;

			// Acts as a double buffer
			typedef struct _RenderItem {
				const sf::Drawable *item;
				sf::RenderStates states;
			} RenderItem;
			sf::Color drawBgColor;
			sf::Color renderBgColor;
			std::queue<RenderItem*> queue1;
			std::queue<RenderItem*> queue2;
			std::queue<RenderItem*> *drawQueue;
			std::queue<RenderItem*> *renderQueue;
			void Swap();
		};
	}
}

#endif // PLATFORM2D_GRAPHICS_RENDER_H