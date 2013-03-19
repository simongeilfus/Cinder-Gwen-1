#pragma once

#include "Gwen/Controls/Base.h"
#include "cinder/Matrix44.h"
#include "cinder/Camera.h"

class CustomControl : public Gwen::Controls::Base {
public:
	CustomControl( Gwen::Controls::Base *parent );
	virtual ~CustomControl();

	virtual void Render( Gwen::Skin::Base* skin );
	virtual void RenderUnder( Gwen::Skin::Base* skin );

private:

	void draw2d();
	void draw3d();

	ci::Matrix44f		mCubeRotation;
	ci::CameraPersp		mCamera;
};