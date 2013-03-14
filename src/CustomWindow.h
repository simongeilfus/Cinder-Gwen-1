#pragma once

#include "Gwen/Controls/WindowControl.h"
#include "cinder/Matrix44.h"
#include "cinder/Camera.h"

class CustomWindow : public Gwen::Controls::WindowControl {

	GWEN_CONTROL( CustomWindow, WindowControl );

	virtual void Render( Gwen::Skin::Base* skin );
	virtual void RenderUnder( Gwen::Skin::Base* skin );

private:
	ci::Matrix44f		mCubeRotation;
	ci::CameraPersp mCamera;
};