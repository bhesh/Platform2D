/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#ifndef PLATFORM2D_RESOURCES_ICATALOG_H
#define PLATFORM2D_RESOURCES_ICATALOG_H

#include <SFML/Graphics.hpp>

#include <stdint.h>
#include <unordered_map>

namespace platform2d {

	namespace resources {

		enum CATALOG_TYPE {
			TEXTURE,
			SPRITE,
			SHAPE,
		};

		/**
			Restricting the key to 32 bits.
		*/
		typedef uint32_t CatalogKey;

		/**

		*/
		typedef struct _CatalogEntry {
			CATALOG_TYPE type;
			void *data;
		} CatalogEntry;

		/**
			Defines a Catalog. A Catalog is a category in the Database. The
			database Categories implemented are:
				@li DrawableCatalog

			@b NOTE: A catalog should be initialized once at the start of the
			program. Many threads may be reading from the Catalogs. There are
			no locks in place at the moment since the data is considered atomic
			and read only.
		*/
		template<class T>
		class Catalog : public std::unordered_map<CatalogKey, T> {
		public:

			/**
				Sets the type of Catalog this is.
			*/
			Catalog(CATALOG_TYPE t) { type = t; }

			/**
				Returns what type of Catalog this is.
			*/
			CATALOG_TYPE GetType() { return type; }
		private:
			CATALOG_TYPE type;
		};

		/**
			Defines the IDrawableCatalog interface. This interface defines the
			function required to retrieve the Drawable instance. It is used by
			the rendering functions/threads to locate the
			Sprites/Shapes/Textures that are needed to render the frame
			properly.
		*/
		class IDrawableCatalog {
		public:

			/**
				A virtual function unique to DrawableCatalogs and is called to
				retrieve the @c Drawable instance.

				@param key the ID used to retrieve the Drawable instance.

				@return a reference to the Drawable instance.
			*/
			virtual const sf::Drawable& GetDrawable(const CatalogKey key) const = 0;
		};

		/**
			Defines the IShapeCatalog interface. This interface defines the
			function required to retrieve the Shape instance. It is used by
			the rendering functions/threads to locate the shapes that are needed
			to draw.
		*/
		class IShapeCatalog {
		public:

			/**
				A virtual function unique to IShapeCatalogs and is called to
				retrieve the @c Shape instance.

				@param key the ID used to retrieve the Shape instance.

				@return a reference to the Shape instance.
			*/
			virtual const sf::Shape& GetShape(const CatalogKey key) const = 0;
		};
	}
}

#include "platform2d/resources/ConvexShapeCatalog.h"

#endif // PLATFORM2D_RESOURCES_ICATALOG_H