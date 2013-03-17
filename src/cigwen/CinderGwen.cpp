#include "Gwen/Platform.h"

#include "cinder/app/App.h"
#include "cinder/app/Window.h"
#include "cinder/Utilities.h"

//! Implement platform-specific methods declared in the Gwen::Platform namespace
namespace Gwen { namespace Platform {

	void Sleep( unsigned int iMS )
	{
		ci::sleep( static_cast<float>( iMS ) );
	}

	void SetCursor( unsigned char iCursor )
	{
		// TODO: NSCursor for mac, look at Gwen/Platform/Windows.cpp for win
	}

	void GetCursorPos( Gwen::Point & p )
	{
		// TODO: is there a cinder specific way to get this, without tying into GwenInput?
	}

	void GetDesktopSize( int & w, int & h )
	{
		ci::DisplayRef display = ci::app::getWindow()->getDisplay();
		w = display->getWidth();
		h = display->getHeight();
	}

	UnicodeString GetClipboardText()
	{
		return L""; // TODO
	}

	bool SetClipboardText( const UnicodeString & str )
	{
		return false; // TODO
	}

	float GetTimeInSeconds()
	{
		return ci::app::getElapsedSeconds();
	}

	bool FileOpen( const String & Name, const String & StartPath, const String & Extension, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback )
	{
//		ci::app::getOpenFilePath();
		return false; // TODO
	}

	bool FileSave( const String & Name, const String & StartPath, const String & Extension, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback )
	{
		return false; // TODO
	}

	bool FolderOpen( const String & Name, const String & StartPath, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback )
	{
		return false; // TODO
	}

	void *CreatePlatformWindow( int x, int y, int w, int h, const Gwen::String & strWindowTitle )
	{
		return NULL; // TODO
	}

	void DestroyPlatformWindow( void* pPtr )
	{
		// TODO
	}

	void SetBoundsPlatformWindow( void* pPtr, int x, int y, int w, int h )
	{
		// TODO
	}

	void MessagePump( void* pWindow, Gwen::Controls::Canvas* ptarget )
	{
		 // TODO
	}

	bool HasFocusPlatformWindow( void* pPtr )
	{
		return false; // TODO
	}

	void SetWindowMaximized( void* pPtr, bool bMaximized, Gwen::Point & pNewPos, Gwen::Point & pNewSize )
	{
		 // TODO
	}

	void SetWindowMinimized( void* pPtr, bool bMinimized )
	{
		 // TODO
	}

} } // namespace Gwen::Platform