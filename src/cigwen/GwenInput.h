// Part of Cinder-Gwen, a block for cinder (www.libcinder.org)
// Created by Richard Eakin

#pragma once

#include "cinder/app/Window.h"
#include "Gwen/Controls/Canvas.h"
#include <memory>

namespace cigwen {

	typedef std::shared_ptr<class GwenInput> GwenInputRef;

	class GwenInput {
	public:
		static GwenInputRef create( Gwen::Controls::Canvas *canvas )	{ return GwenInputRef( new GwenInput( canvas ) ); }
		//! set the ammount to multiply the 'mouse wheel increment' by (default: 10)
		void	setMouseWheelMultiplier( int m )	{ mMouseWheelMultiplier = m; }
		int		getMouseWheelMultiplier() const		{ return mMouseWheelMultiplier; }

	protected:
		// signal callbacks for ci::app events:
		void mouseDown( ci::app::MouseEvent &event );
		void mouseDrag( ci::app::MouseEvent &event );
		void mouseUp( ci::app::MouseEvent &event );
		void mouseMove( ci::app::MouseEvent &event );
		void mouseWheel( ci::app::MouseEvent &event );
		void keyDown( ci::app::KeyEvent &event );
		void keyUp( ci::app::KeyEvent &event );
		void resize();

	protected:
		GwenInput( Gwen::Controls::Canvas *canvas );

		int mapToGwen( const ci::app::KeyEvent &event ) const;

		Gwen::Controls::Canvas *mCanvas;
		ci::Vec2i mMousePos;
		int mMouseWheelMultiplier;
	};
	
} // namespace cigwen