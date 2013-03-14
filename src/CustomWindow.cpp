

#include "CustomWindow.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h"

using namespace Gwen;
using namespace ci;

GWEN_CONTROL_CONSTRUCTOR( CustomWindow )
{
}

void CustomWindow::Render( Skin::Base* skin )
{
	BaseClass::Render( skin );

	ci::Area frame( m_Bounds.x + m_InnerBounds.x, m_Bounds.y + m_InnerBounds.y, m_InnerBounds.w, m_InnerBounds.h );
	float aspect = (float)m_InnerBounds.w / (float)m_InnerBounds.h;

	mCubeRotation.rotate( Vec3f( 1, 1, 1 ), 0.03f );

	gl::pushMatrices();
	gl::enableDepthRead();

	gl::translate( frame.x1, frame.y1 );
//	gl::drawSolidCircle( Vec2f( 30, 30 ), 20 );

	gl::drawString( std::string( "aspect: " ) + ci::toString( aspect ), Vec2f( 10, 10 ), ci::Color::black() );

	mCamera.lookAt( Vec3f( 1, 1, -5 ), Vec3f::zero() );
	mCamera.setPerspective( 60, aspect, 1, 1000 );

	gl::setMatrices( mCamera );
	gl::multModelView( mCubeRotation );

	gl::color( ci::Color::white() );
	gl::drawColorCube( Vec3f::zero(), Vec3f( 1.0f, 1.0f, 1.0f ) );

	gl::disableDepthRead();
	gl::popMatrices();

//	m_Render->SetDrawColor( Gwen::Color( 0, 200, 0, 255 ) );
//	m_Render->DrawFilledRect( Gwen::Rect( 1, 1, 20, 40 ) );

}

void CustomWindow::RenderUnder( Skin::Base* skin )
{
	BaseClass::RenderUnder( skin );
}