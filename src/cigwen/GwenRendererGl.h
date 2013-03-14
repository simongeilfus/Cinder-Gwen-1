// Part of Cinder-Gwen, a block for cinder (www.libcinder.org)
// Created by Richard Eakin

#pragma once

#include "Gwen/BaseRender.h"
#include "cinder/gl/TextureFont.h"

#include <map>

namespace cigwen {

class GwenRendererGl : public Gwen::Renderer::Base {
public:
	GwenRendererGl();
	virtual ~GwenRendererGl();

	virtual void Init()		override;
	virtual void Begin()	override;
	virtual void End()		override;

	virtual void SetDrawColor( Gwen::Color color )	override;
	virtual void DrawFilledRect( Gwen::Rect rect )	override;

	virtual void StartClip()	override;
	virtual void EndClip()		override;

	// Textures
	virtual void LoadTexture( Gwen::Texture* pTexture )	override;
	virtual void FreeTexture( Gwen::Texture* pTexture )	override;
	virtual void DrawTexturedRect( Gwen::Texture* pTexture, Gwen::Rect pTargetRect, float u1 = 0.0f, float v1 = 0.0f, float u2 = 1.0f, float v2 = 1.0f )	override;
	virtual Gwen::Color PixelColour( Gwen::Texture* pTexture, unsigned int x, unsigned int y, const Gwen::Color & col_default )	override;

	// Text
	virtual void RenderText( Gwen::Font* pFont, Gwen::Point pos, const Gwen::UnicodeString & text )	override;
	virtual Gwen::Point MeasureText( Gwen::Font* pFont, const Gwen::UnicodeString & text )	override;


	// Context stuff... hopefully just need to return true
	virtual bool InitializeContext( Gwen::WindowProvider* pWindow )				override { return true; }
	virtual bool ShutdownContext( Gwen::WindowProvider* pWindow )				override { return true; }
	virtual bool ResizedContext( Gwen::WindowProvider* pWindow, int w, int h )	override { return true; }

	virtual bool BeginContext( Gwen::WindowProvider* pWindow )					override { return true; }
	virtual bool EndContext( Gwen::WindowProvider* pWindow )					override { return true; }
	virtual bool PresentContext( Gwen::WindowProvider* pWindow )				override { return true; }


private:

	ci::gl::TextureFontRef getTextureFont( Gwen::Font* font );

//	FIXME: this'd be nice, but it's not always working
//	typedef std::pair<std::wstring, int> FontType;
//	typedef std::pair<std::string, int> FontType;
//    struct FontCompare {
//        bool operator() ( const FontType &type1, const FontType &type2 ) const	{ return ( (type1.second < type2.second) || (type1.first < type2.first) ); }
//    };
//	std::map<FontType, ci::gl::TextureFontRef, FontCompare> mFontMap;

	std::map<std::string, ci::gl::TextureFontRef> mFontMap;
	std::map<std::string,ci::gl::Texture> mTextureMap;
};

} // namespace cigwen