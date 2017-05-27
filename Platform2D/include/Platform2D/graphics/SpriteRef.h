/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#ifndef PLATFORM2D_GRAPHICS_SPRITE_REF_H
#define PLATFORM2D_GRAPHICS_SPRITE_REF_H

#include "platform2d/resources/Catalog.h"
#include "platform2d/resources/Database.h"

namespace platform2d {

	namespace graphics {

		/**
			Defines a SpriteRef.
		*/
		typedef struct _SpriteRef {

			/**
				A reference to which catalog the Sprite is in.
			*/
			mutable platform2d::resources::IDrawableCatalog *catalog;

			/**
				The key to find the Sprite in the catalog.
			*/
			mutable platform2d::resources::CatalogKey key;

			/**
				Describes how to transform this Sprite instance.
			*/
			mutable sf::Transform transformation;

			/**
				Describes color transformations.
			*/
			mutable sf::Color color;

			/**
				Which layer to draw this to. The higher the layer is, the later
				it is draw. This is important to set appropriately so a
				foreground Sprite is not hidden behind the background.
			*/
			unsigned int layer;
		} SpriteRef;

		/**
			Overloads < operator to sort SpriteRefs by layer.
		*/
		bool operator < (const SpriteRef &left, const SpriteRef &right);

		/**
			Overloads > operator to sort SpriteRefs by layer.
		*/
		bool operator > (const SpriteRef &left, const SpriteRef &right);

		/**
			Overloads <= operator to sort SpriteRefs by layer.
		*/
		bool operator <= (const SpriteRef &left, const SpriteRef &right);

		/**
			Overloads >= operator to sort SpriteRefs by layer.
		*/
		bool operator >= (const SpriteRef &left, const SpriteRef &right);

		/**
			Overloads == operator to sort SpriteRefs by layer.
		*/
		bool operator == (const SpriteRef &left, const SpriteRef &right);
	}
}

#endif // PLATFORM2D_GRAPHICS_SPRITE_REF_H
