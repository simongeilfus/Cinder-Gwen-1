#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "cigwen/GwenRendererGl.h"
#include "cigwen/GwenInput.h"

#include "Gwen/Skins/Simple.h"
#include "Gwen/Skins/TexturedBase.h"
#include "Gwen/UnitTest/UnitTest.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class GwenUnitTestApp : public AppNative {
  public:

	void prepareSettings( Settings *settings );
	void setup();
	void draw();

private:
	cigwen::GwenRendererGl *mRenderer;
	cigwen::GwenInputRef mGwenInput;
	Gwen::Controls::Canvas *mCanvas;
};

void GwenUnitTestApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 1004, 650 );
}

void GwenUnitTestApp::setup()
{
	getWindow()->setTitle( "Gwen UnitTest" );

	// TODO: map this to other systems or find a better way..
	fs::path gwenBinPath = getAppPath().parent_path().parent_path().parent_path().parent_path().parent_path().parent_path() / "lib" / "gwen" / "gwen" / "bin";
	addAssetDirectory( gwenBinPath );

	mRenderer = new cigwen::GwenRendererGl();
	mRenderer->Init();

	Gwen::Skin::TexturedBase* skin = new Gwen::Skin::TexturedBase( mRenderer );
	skin->Init( "DefaultSkin.png" );

	mCanvas = new Gwen::Controls::Canvas( skin );
	mCanvas->SetSize( 998, 650 - 24 );
	mCanvas->SetDrawBackground( true );
	mCanvas->SetBackgroundColor( Gwen::Color( 150, 170, 170, 255 ) );

	mGwenInput = cigwen::GwenInput::create( mCanvas );

	UnitTest* unit = new UnitTest( mCanvas );
	unit->SetPos( 10, 10 );
}

void GwenUnitTestApp::draw()
{
	gl::clear();
	mCanvas->RenderCanvas();
}

CINDER_APP_NATIVE( GwenUnitTestApp, RendererGl )
