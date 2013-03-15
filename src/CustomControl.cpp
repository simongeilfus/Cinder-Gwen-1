
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

	static float rot = 0;
	rot += 0.5f;

	float w = 40;
	Rectf r( -w, -w, w, w );

	gl::translate( bounds.getCenter() );
	gl::rotate( rot );
	gl::color( ci::Color( 0, 0.8, 0 ) );
	gl::drawSolidRect( r );
	gl::color( ci::Color( 0, 0, 0.8 ) );
	gl::drawStrokedRect( r );

	//----------------------
	// TODO: draw cube

//	gl::pushMatrices();

//	gl::enableDepthRead();
//
//	mCamera.lookAt( Vec3f( 1, 1, -5 ), Vec3f::zero() );
//	mCamera.setPerspective( 60, aspect, 1, 1000 );
//
//	gl::setMatrices( mCamera );
//	gl::multProjection( mCamera.getProjectionMatrix() );
//	gl::multModelView( mCamera.getModelViewMatrix() );
//	gl::multModelView( mCubeRotation );
//
//	gl::color( ci::Color::white() );
//	gl::drawColorCube( Vec3f::zero(), Vec3f( 1.0f, 1.0f, 1.0f ) );
//
//	gl::disableDepthRead();
//
//	gl::popMatrices();

	//-------------------------------

	gl::popMatrices();
}


void CustomControl::RenderUnder( Skin::Base* skin )
{
}