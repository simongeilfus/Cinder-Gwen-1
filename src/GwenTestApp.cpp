//#include "Gwen/Renderers/OpenGL_DebugFont.h"

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "Gwen/Gwen.h"
#include "Gwen/Skins/Simple.h"
#include "Gwen/Skins/TexturedBase.h"
#include "Gwen/UnitTest/UnitTest.h"
#include "Gwen/Controls.h"

#if 1
#include "cigwen/GwenRendererGl.h"
#define RendererType cigwen::GwenRendererGl
#else
#include "cigwen/GwenRenderer.h"
#define RendererType cigwen::GwenRenderer
#endif

#include "cigwen/GwenInput.h"
#include "CustomControl.h"

#define SKIN_ASSET "DefaultSkin.png"
//#define SKIN_ASSET "obscureskin.png"

using namespace ci;
using namespace ci::app;
using namespace std;

class GwenTestApp : public AppNative, public Gwen::Event::Handler {
  public:
	void prepareSettings( Settings *settings );
	void setup();
	

	void addUnitTest();
	void addControls();
	void openWindow();


	void update();
	void draw();

  private:
	RendererType* mRenderer;

	Gwen::Controls::Canvas* mCanvas;
	cigwen::GwenInputRef mGwenInput;

	Vec2i mLastMousePos;
	gl::Texture mTestTex;
};

void GwenTestApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 1004, 650 );
}

void GwenTestApp::setup()
{
	getWindow()->setTitle( "Cinder + Gwen" );
	
	mRenderer = new RendererType();

	mRenderer->Init();

	Gwen::Skin::TexturedBase* skin = new Gwen::Skin::TexturedBase( mRenderer );
	skin->Init( getAssetPath( SKIN_ASSET ).c_str() );

	mCanvas = new Gwen::Controls::Canvas( skin );
	mCanvas->SetSize( 998, 650 - 24 );
	mCanvas->SetDrawBackground( true );
	mCanvas->SetBackgroundColor( Gwen::Color( 150, 170, 170, 255 ) );

	mGwenInput = cigwen::GwenInput::create( mCanvas );

	addControls();
//	addUnitTest();

	gl::enableAlphaBlending();
}

void GwenTestApp::addUnitTest()
{
	UnitTest* pUnit = new UnitTest( mCanvas );
	pUnit->SetPos( 10, 10 );
}

void GwenTestApp::addControls()
{
	Gwen::Controls::Label *label = new Gwen::Controls::Label( mCanvas );
	label->SetText( "First label" );
	label->SizeToContents();
	label->SetPos( 50, 50 );

	Gwen::Controls::Button *btn = new Gwen::Controls::Button( mCanvas );
	btn->SetBounds( 200, 30, 80, 60 );
	btn->SetText( "Click Me" );
	btn->onPress.Add( this, &GwenTestApp::openWindow );


	Gwen::Controls::Button *btn2 = new Gwen::Controls::Button( mCanvas );
	btn2->SetBounds( 300, 30, 68, 68 );
	btn2->SetImage( getAssetPath( "gwen64.png" ).c_str() );
}

void GwenTestApp::openWindow()
{
	auto window = new Gwen::Controls::WindowControl( mCanvas );
	window->SetTitle( "This is CustomControl" );
	window->SetSize( 400, 400 );
	window->SetPos( 200, 200 );
	window->SetDeleteOnClose( true );
	window->SetClampMovement( false );

	auto control = new CustomControl( window );
	control->SetPos( 0, 0 );
	control->Dock( Gwen::Pos::Fill );
}

void GwenTestApp::update()
{
}

void GwenTestApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );

	mCanvas->RenderCanvas();
}

CINDER_APP_NATIVE( GwenTestApp, RendererGl( RendererGl::AA_MSAA_4 ) )
