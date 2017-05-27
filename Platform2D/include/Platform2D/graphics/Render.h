/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#ifndef PLATFORM2D_GRAPHICS_RENDER_H
#define PLATFORM2D_GRAPHICS_RENDER_H

#include "platform2d/graphics/SpriteRef.h"

#include <SFML/Graphics.hpp>

#include <condition_variable>
#include <mutex>
#include <set>
#include <thread>

namespace platform2d {

	namespace graphics {

		class RenderBase {
		public:
			RenderBase(sf::RenderWindow *window) { this->window = window; }
			~RenderBase() {};
			//void SetMap();
			void Update(std::set<SpriteRef> &sprites);
		protected:
			void DrawBackground(const sf::Color color);
			void DrawForeground(const std::set<SpriteRef> &sprites);
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
			void Update(std::set<SpriteRef> &sprites);
			void RenderLoop();

		private:
			std::set<SpriteRef> sprites;
			std::thread *thread;
			std::mutex mutex;
			std::condition_variable cv;
			bool can_update;
			bool is_running;
		};
	}
}

#endif // PLATFORM2D_GRAPHICS_RENDER_H