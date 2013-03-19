// Part of Cinder-Gwen, a block for cinder (www.libcinder.org)
// Created by Richard Eakin

#pragma once

#include "cinder/Rect.h"
#include "Gwen/Structures.h"

namespace cigwen {

	inline Gwen::Color toGwen( const ci::ColorA &c )	{ return Gwen::Color( c.r * 255, c.g * 255, c.b * 255, c.a * 255 ); }
	inline ci::ColorA fromGwen( const Gwen::Color &c )	{ return ci::ColorA( c.r / 255.0f, c.g / 255.0f, c.b / 255.0f, c.a / 255.0f ); }
    
    
	inline Gwen::Point toGwen( const ci::Vec2f& v )     { return Gwen::Point( v.x, v.y ); }
	inline ci::Vec2f fromGwen( const Gwen::Point &p )	{ return ci::Vec2f( p.x, p.y ); }
    
	inline Gwen::Rect toGwen( const ci::Rectf& r )      { return Gwen::Rect( r.x1, r.y1, r.getWidth(), r.getHeight() ); }
	inline ci::Rectf fromGwen( const Gwen::Rect &r )	{ return ci::Rectf( r.x, r.y, r.x + r.w, r.y + r.h ); }

} // namespace cigwen
