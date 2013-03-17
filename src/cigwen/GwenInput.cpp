// Part of Cinder-Gwen, a block for cinder (www.libcinder.org)
// Created by Richard Eakin

#include "cigwen/GwenInput.h"
#include "cinder/app/App.h"

using namespace ci;

namespace cigwen {

	GwenInput::GwenInput( Gwen::Controls::Canvas *canvas )
	: mCanvas( canvas ), mMouseWheelMultiplier( 10 )
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
		if( mCanvas->InputMouseButton( 0, true ) )
			event.setHandled();
	}

	void GwenInput::mouseDrag( app::MouseEvent &event )
	{
		if( mCanvas->InputMouseMoved( event.getX(), event.getY(), event.getX() - mMousePos.x, event.getY() - mMousePos.y ) )
			event.setHandled();
		mMousePos = event.getPos();
	}

	void GwenInput::mouseUp( app::MouseEvent &event )
	{
		if( mCanvas->InputMouseButton( 0, false ) )
			event.setHandled();
	}

	void GwenInput::mouseMove( app::MouseEvent &event )
	{
		if( mCanvas->InputMouseMoved( event.getX(), event.getY(), event.getX() - mMousePos.x, event.getY() - mMousePos.y ) )
			event.setHandled();
		mMousePos = event.getPos();
	}

	void GwenInput::mouseWheel( app::MouseEvent &event )
	{
		if( mCanvas->InputMouseWheel( event.getWheelIncrement() * mMouseWheelMultiplier ) )
			event.setHandled();
	}

	void GwenInput::keyDown( app::KeyEvent &event )
	{
		int key = mapToGwen( event );
		if( key != -1 && mCanvas->InputKey( key, true ) ) {
			event.setHandled();
			return;
		}

		// key must be a char..
		if( mCanvas->InputCharacter( event.getChar() ) )
			event.setHandled();
	}

	void GwenInput::keyUp( app::KeyEvent &event )
	{
		int key = mapToGwen( event );
		if( key != -1 && mCanvas->InputKey( key, false ) ) {
			event.setHandled();
			return;
		}
	}

	void GwenInput::resize()
	{
		mCanvas->SetSize( app::getWindowWidth(), app::getWindowHeight() );
	}

	int GwenInput::mapToGwen( const app::KeyEvent &event ) const
	{
		switch( event.getCode() ) {
			case app::KeyEvent::KEY_RETURN:		return Gwen::Key::Return;
			case app::KeyEvent::KEY_BACKSPACE:	return Gwen::Key::Backspace;
			case app::KeyEvent::KEY_DELETE:		return Gwen::Key::Delete;
			case app::KeyEvent::KEY_LEFT:		return Gwen::Key::Left;
			case app::KeyEvent::KEY_RIGHT:		return Gwen::Key::Right;
			case app::KeyEvent::KEY_LSHIFT:		return Gwen::Key::Shift;
			case app::KeyEvent::KEY_RSHIFT:		return Gwen::Key::Shift;
			case app::KeyEvent::KEY_TAB:		return Gwen::Key::Tab;
			case app::KeyEvent::KEY_SPACE:		return Gwen::Key::Space;
			case app::KeyEvent::KEY_HOME:		return Gwen::Key::Home;
			case app::KeyEvent::KEY_END:		return Gwen::Key::End;
			case app::KeyEvent::KEY_LCTRL:		return Gwen::Key::Control;
			case app::KeyEvent::KEY_RCTRL:		return Gwen::Key::Control;
			case app::KeyEvent::KEY_UP:			return Gwen::Key::Up;
			case app::KeyEvent::KEY_DOWN:		return Gwen::Key::Down;
			case app::KeyEvent::KEY_ESCAPE:		return Gwen::Key::Escape;
			case app::KeyEvent::KEY_LALT:		return Gwen::Key::Alt;
			case app::KeyEvent::KEY_RALT:		return Gwen::Key::Alt;
			default:							return -1;
		}
	}

} // namespace cigwen