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

		static GwenInputRef create( Gwen::Controls::Canvas *canvas ) { return GwenInputRef( new GwenInput( canvas ) ); }

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

		Gwen::Controls::Canvas *mCanvas;
		ci::Vec2i mMousePos;
	};
	
} // namespace cigwen