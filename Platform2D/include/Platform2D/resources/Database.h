/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#ifndef PLATFORM2D_RESOURCES_DATABASE_H
#define PLATFORM2D_RESOURCES_DATABASE_H

#include "platform2d/resources/Catalog.h"

#include <stdint.h>
#include <unordered_map>

namespace platform2d {

	namespace resources {

		/**
			Restricting the CatalogId to 32 bits.
		*/
		typedef uint32_t CatalogId;
	}
}

#endif // PLATFORM2D_RESOURCES_DATABASE_H