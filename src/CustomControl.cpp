
#include "CustomControl.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h"

#include "cigwen/CinderGwen.h"

using namespace Gwen;
using namespace ci;

CustomControl::CustomControl( Gwen::Controls::Base *parent )
: Controls::Base( parent, "cigwen sample CustomControl" )
{}

void CustomControl::Render( Skin::Base* skin )
{
	Vec2f pos( cigwen::fromGwen( LocalPosToCanvas() ) );
	ci::Rectf bounds( cigwen::fromGwen( GetBounds() ) );
	float aspect = (float)m_InnerBounds.w / (float)m_InnerBounds.h;

	mCubeRotation.rotate( Vec3f( 1, 1, 1 ), 0.03f );

	gl::pushMatrices();

	gl::translate( pos );
	float yOffset = 10;
	float yHeight = 20;
	gl::drawString( std::string( "pos: " ) + ci::toString( pos ), Vec2f( 10, yOffset ), ci::Color::black() );		yOffset += yHeight;
	gl::drawString( std::string( "bounds: " ) + ci::toString( bounds ), Vec2f( 10, yOffset ), ci::Color::black() );		yOffset += yHeight;
	gl::drawString( std::string( "aspect: " ) + ci::toString( aspect ), Vec2f( 10, yOffset ), ci::Color::black() );		yOffset += yHeight;

	//----------------------

	gl::pushMatrices();

	gl::color( ci::Color( 0, 1, 0 ) );
	gl::drawSolidCircle( bounds.getCenter(), 20 );

//	gl::enableDepthRead();

//	mCamera.lookAt( Vec3f( 1, 1, -5 ), Vec3f::zero() );
//	mCamera.setPerspective( 60, aspect, 1, 1000 );
//
//	//	gl::setMatrices( mCamera );
//	//	setProjection( cam );
//	//	setModelView( cam );
//	gl::multProjection( mCamera.getProjectionMatrix() );
//	gl::multModelView( mCamera.getModelViewMatrix() );
//	gl::multModelView( mCubeRotation );
//
//	gl::color( ci::Color::white() );
//	gl::drawColorCube( Vec3f::zero(), Vec3f( 1.0f, 1.0f, 1.0f ) );
//
//	gl::disableDepthRead();

	gl::popMatrices();

	//-------------------------------

	gl::popMatrices();

	//	m_Render->SetDrawColor( Gwen::Color( 0, 200, 0, 255 ) );
	//	m_Render->DrawFilledRect( Gwen::Rect( 1, 1, 20, 40 ) );
	
}

//void CustomWindow::Render( Skin::Base* skin )
//{
//	BaseClass::Render( skin );
//
//	ci::Area frame( m_Bounds.x + m_InnerBounds.x, m_Bounds.y + m_InnerBounds.y, m_InnerBounds.w, m_InnerBounds.h );
//	float aspect = (float)m_InnerBounds.w / (float)m_InnerBounds.h;
//
//	mCubeRotation.rotate( Vec3f( 1, 1, 1 ), 0.03f );
//
//	gl::pushMatrices();
//	gl::enableDepthRead();
//
//	gl::translate( frame.x1, frame.y1 );
////	gl::drawSolidCircle( Vec2f( 30, 30 ), 20 );
//
//	gl::drawString( std::string( "aspect: " ) + ci::toString( aspect ), Vec2f( 10, 10 ), ci::Color::black() );
//
//	mCamera.lookAt( Vec3f( 1, 1, -5 ), Vec3f::zero() );
//	mCamera.setPerspective( 60, aspect, 1, 1000 );
//
//	gl::setMatrices( mCamera );
//	gl::multModelView( mCubeRotation );
//
//	gl::color( ci::Color::white() );
//	gl::drawColorCube( Vec3f::zero(), Vec3f( 1.0f, 1.0f, 1.0f ) );
//
//	gl::disableDepthRead();
//	gl::popMatrices();
//
//}

void CustomControl::RenderUnder( Skin::Base* skin )
{
}