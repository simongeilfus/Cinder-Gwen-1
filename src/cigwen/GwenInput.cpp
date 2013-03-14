// Part of Cinder-Gwen, a block for cinder (www.libcinder.org)
// Created by Richard Eakin

#include "cigwen/GwenInput.h"
#include "cinder/app/App.h"

using namespace ci;

namespace cigwen {

	GwenInput::GwenInput( Gwen::Controls::Canvas *canvas )
	: mCanvas( canvas )
	{
		app::WindowRef window = app::getWindow();
		window->connectMouseDown( &GwenInput::mouseDown, this );
		window->connectMouseDrag( &GwenInput::mouseDrag, this );
		window->connectMouseUp( &GwenInput::mouseUp, this );
		window->connectMouseMove( &GwenInput::mouseMove, this );
		window->connectMouseWheel( &GwenInput::mouseWheel, this );
		window->connectKeyDown( &GwenInput::keyDown, this );
		window->connectKeyUp( &GwenInput::keyUp, this );
		window->connectResize( &GwenInput::resize, this );
	}

	void GwenInput::mouseDown( app::MouseEvent &event )
	{
		mCanvas->InputMouseButton( 0, true );

	}

	void GwenInput::mouseDrag( app::MouseEvent &event )
	{
		mCanvas->InputMouseMoved( event.getX(), event.getY(), event.getX() - mMousePos.x, event.getY() - mMousePos.y );
		mMousePos = event.getPos();

	}

	void GwenInput::mouseUp( app::MouseEvent &event )
	{
		mCanvas->InputMouseButton( 0, false );

	}

	void GwenInput::mouseMove( app::MouseEvent &event )
	{
		mCanvas->InputMouseMoved( event.getX(), event.getY(), event.getX() - mMousePos.x, event.getY() - mMousePos.y );
		mMousePos = event.getPos();

	}

	void GwenInput::mouseWheel( app::MouseEvent &event )
	{
		mCanvas->InputMouseWheel( event.getWheelIncrement() * 5 );

	}

	void GwenInput::keyDown( app::KeyEvent &event )
	{

	}

	void GwenInput::keyUp( app::KeyEvent &event )
	{
		// TODO: get this working proper, will require sorting between keys and chars
		mCanvas->InputCharacter( event.getChar() );
	}

	void GwenInput::resize()
	{
		mCanvas->SetSize( app::getWindowWidth(), app::getWindowHeight() );
	}


} // namespace cigwen