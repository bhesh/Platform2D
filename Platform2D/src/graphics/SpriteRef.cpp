/**
	Copyright 2017, Brian Hession, All rights reserved.
*/

#include "platform2d/graphics/SpriteRef.h"

bool platform2d::graphics::operator < (const SpriteRef &left, const SpriteRef &right) {
	return left.layer < right.layer;
}

bool platform2d::graphics::operator > (const SpriteRef &left, const SpriteRef &right) {
	return left.layer > right.layer;
}

bool platform2d::graphics::operator <= (const SpriteRef &left, const SpriteRef &right) {
	return left.layer <= right.layer;
}

bool platform2d::graphics::operator >= (const SpriteRef &left, const SpriteRef &right) {
	return left.layer >= right.layer;
}

bool platform2d::graphics::operator == (const SpriteRef &left, const SpriteRef &right) {
	return left.layer == right.layer;
}
