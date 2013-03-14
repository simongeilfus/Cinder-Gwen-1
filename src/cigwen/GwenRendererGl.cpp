// Part of Cinder-Gwen, a block for cinder (www.libcinder.org)
// Created by Richard Eakin

#include "cigwen/GwenRendererGl.h"
#include "cinder/CinderMath.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/app/App.h"
#include "cinder/Utilities.h"

#include "Gwen/Gwen.h"
#include "Gwen/Utility.h"
#include "Gwen/Font.h"
#include "Gwen/Texture.h"

#define LOG_V std::cout << __PRETTY_FUNCTION__ << " | "

using namespace ci;

namespace  {
	Rectf fromGwen( const Gwen::Rect &r )	{ return Rectf( r.x, r.y, r.x + r.w, r.y + r.h ); }
}

namespace cigwen {

	GwenRendererGl::GwenRendererGl()
	{

	}

	GwenRendererGl::~GwenRendererGl()
	{

	}

	void GwenRendererGl::Init()
	{
	}

	void GwenRendererGl::Begin()
	{
		gl::enableAlphaBlending();
//		gl::enableAlphaTest( 1.0f ); // this matched the gwen gl renderer...
	}

	void GwenRendererGl::End()
	{
		glFlush();
	}

	void GwenRendererGl::DrawFilledRect( Gwen::Rect rect )
	{
		// dont think this is necessary..
		GLboolean texturesOn;
		glGetBooleanv( GL_TEXTURE_2D, &texturesOn );

		if ( texturesOn ) {
			glFlush();
			glDisable( GL_TEXTURE_2D );
		}
		// ..

		Translate( rect );
		gl::drawSolidRect( fromGwen( rect ) );
	}

	void GwenRendererGl::SetDrawColor( Gwen::Color color )
	{
		glColor4ubv( ( GLubyte* ) &color );
	}

	void GwenRendererGl::StartClip()
	{
		Gwen::Rect rect = ClipRegion();
		// OpenGL's coords are from the bottom left, so we need to translate them here.
		GLint view[4];
		glGetIntegerv( GL_VIEWPORT, &view[0] );
		rect.y = view[3] - ( rect.y + rect.h );

		glScissor( rect.x * Scale(), rect.y * Scale(), rect.w * Scale(), rect.h * Scale() );
		glEnable( GL_SCISSOR_TEST );
	};

	void GwenRendererGl::EndClip()
	{
		glDisable( GL_SCISSOR_TEST );
	}

	void GwenRendererGl::DrawTexturedRect( Gwen::Texture* tex, Gwen::Rect rect, float u1, float v1, float u2, float v2 )
	{
		gl::Texture& texture = mTextureMap[tex->name.Get()];
		if( ! texture ) {
			DrawMissingImage( rect );
			return;
		}

		Translate( rect );
		gl::draw( texture, Area( u1 * tex->width, v1 * tex->width, u2 * tex->height, v2 * tex->height ), fromGwen( rect ) );
	}

	void GwenRendererGl::LoadTexture( Gwen::Texture* tex )
	{
		const std::string& name = tex->name.Get();
		auto it = mTextureMap.find( name );
		if( it == mTextureMap.end() ) {
			DataSourceRef dataSource;
			if ( fs::exists( name ) )
				dataSource = loadFile( name );
			else if( ! app::getAssetPath( name ).empty() )
				dataSource = app::loadAsset( name );
			else {
				LOG_V << "failed to load: " << name << std::endl;
				tex->failed = true;
				return;
			}
			gl::Texture& texture = mTextureMap[name] = gl::Texture( loadImage( dataSource ) );
			tex->width = texture.getWidth();
			tex->height = texture.getHeight();
		} else {
			tex->width = it->second.getWidth();
			tex->height = it->second.getHeight();
		}
	}

	void GwenRendererGl::FreeTexture( Gwen::Texture* tex )
	{
		mTextureMap.erase( tex->name.Get() );
	}

	// TODO: glGetTexImage is unsupported on gl es, will have to keep a shadow Surface during init for that to work
	Gwen::Color GwenRendererGl::PixelColour( Gwen::Texture* tex, unsigned int x, unsigned int y, const Gwen::Color & col_default )
	{
		gl::Texture& texture = mTextureMap[tex->name.Get()];
		if( ! texture )
			return col_default;

		unsigned int iPixelSize = sizeof( unsigned char ) * 4;
		texture.bind();
		unsigned char* data = ( unsigned char* ) malloc( iPixelSize * tex->width * tex->height );
		glGetTexImage( GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
		unsigned int iOffset = ( y * tex->width + x ) * 4;
		Gwen::Color c;
		c.r = data[0 + iOffset];
		c.g = data[1 + iOffset];
		c.b = data[2 + iOffset];
		c.a = data[3 + iOffset];
		//
		// Retrieving the entire texture for a single pixel read
		// is kind of a waste - maybe cache this pointer in the texture
		// data and then release later on? It's never called during runtime
		// - only during initialization.
		//
		free( data );
		texture.unbind();
		return c;
	}

	void GwenRendererGl::RenderText( Gwen::Font* font, Gwen::Point pos, const Gwen::UnicodeString & text )
	{
		if ( !text.length() )
			return;

		std::string str = static_cast<std::string>( Gwen::Utility::UnicodeToString( text ) );
		gl::TextureFontRef texFont = getTextureFont( font );
		float scale = Scale();

		// TODO: account for scale

		Translate( pos.x, pos.y );
		texFont->drawString( str, Vec2f( pos.x, pos.y + texFont->getFont().getSize() - texFont->getDescent() ) );
	}

	Gwen::Point GwenRendererGl::MeasureText( Gwen::Font* font, const Gwen::UnicodeString & text )
	{
		std::string str = static_cast<std::string>( Gwen::Utility::UnicodeToString( text ) );
		Vec2f size = getTextureFont( font )->measureString( str );

		return Gwen::Point( size.x, size.y );
	}

//	gl::TextureFontRef GwenRendererGl::getTextureFont( Gwen::Font* font )
//	{
//		FontType fontType( Gwen::Utility::UnicodeToString( font->facename ), static_cast<int>( roundf( font->size ) ) );
//		LOG_V << "name: " << fontType.first << ", size: " << fontType.second << std::endl << " (count=" << mFontMap.size() << ")" << std::endl;
//		auto fontIt = mFontMap.find( fontType );
//		if( fontIt == mFontMap.end() ) {
//			LOG_V << "\tcreating font" << std::endl;
//			// TODO: check fontface exists first, or use system default and print error
//			mFontMap.insert( std::make_pair( fontType, gl::TextureFont::create( ci::Font( fontType.first, fontType.second ) ) ) );
//		} else {
//			LOG_V << "\talready exists." << std::endl;
//		}
//		return mFontMap[fontType];
//	}

	gl::TextureFontRef GwenRendererGl::getTextureFont( Gwen::Font* font )
	{
		std::string name = Gwen::Utility::UnicodeToString( font->facename );
		int size = static_cast<int>( roundf( font->size ) );
		std::string fontKey =  name + std::string( "-" ) + ci::toString( size );
		auto fontIt = mFontMap.find( fontKey );
		if( fontIt == mFontMap.end() ) {
			try {
				ci::Font cinderFont( name, size );
				LOG_V << "creating font, fontKey: " << fontKey << " (count=" << mFontMap.size() << ")" << std::endl;
				mFontMap.insert( std::make_pair( fontKey, gl::TextureFont::create( cinderFont ) ) );
			}
			catch( FontInvalidNameExc& exc ) {
				app::console() << __PRETTY_FUNCTION__ << " | error, cannot find font named: " << name << ". replacing with system default." << std::endl;
				mFontMap.insert( std::make_pair( fontKey, gl::TextureFont::create( ci::Font::getDefault() ) ) );
			}
		}
		return mFontMap[fontKey];
	}

} // namespace cigwen
