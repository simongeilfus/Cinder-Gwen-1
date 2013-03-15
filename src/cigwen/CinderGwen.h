// Part of Cinder-Gwen, a block for cinder (www.libcinder.org)
// Created by Richard Eakin

#pragma once

#include "cinder/Rect.h"
#include "Gwen/Structures.h"

namespace cigwen {

	inline ci::Rectf fromGwen( const Gwen::Rect &r )	{ return ci::Rectf( r.x, r.y, r.x + r.w, r.y + r.h ); }

} // namespace cigwen
