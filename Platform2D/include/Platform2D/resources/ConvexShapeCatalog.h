/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#include "platform2d/resources/Catalog.h"

#include <SFML/Graphics.hpp>

namespace platform2d {

	namespace resources {
		/**
			Defines the ShapeCatalog. This is a special Catalog used to store
			primitive shapes. The shapes are drawn by an ordered array of
			vertices.

			Refer to Catalog for more information.
		*/
		class ConvexShapeCatalog :
			public Catalog<sf::ConvexShape>,
			public IDrawableCatalog,
			public IShapeCatalog {
		public:

			/**
				Default constructor.
			*/
			ConvexShapeCatalog() : Catalog<sf::ConvexShape>(SHAPE) {};

			/**
				Gets the Drawable instance associated with the given Catalog
				key.

				@param key the ID used to retrieve the Drawable instance.

				@return a reference to the Drawable instance.
			*/
			const sf::Drawable& GetDrawable(const CatalogKey key) const {
				return at(key);
			}

			/**
				Gets the Shape instance associated with the given Catalog
				key.

				@param key the ID used to retrieve the Shape instance.

				@return a reference to the Shape instance.
			*/
			const sf::Shape& GetShape(const CatalogKey key) const {
				return at(key);
			}
		};
	}
}