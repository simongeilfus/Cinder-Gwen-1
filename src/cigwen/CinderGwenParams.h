//
//  CinderGwenParams.h
//  CustomControlWindow
//
//  Created by Simon Geilfus on 19/03/13.
//
//

#pragma once


#include "Gwen/Gwen.h"
//#include "Gwen/Skins/Simple.h"
//#include "Gwen/Skins/TexturedBase.h"

//#include "Gwen/BaseRender.h"
#include "Gwen/Controls/Base.h"
//#include "Gwen/Controls/Text.h"
//#include "Gwen/Controls.h"
#include "Gwen/Controls/WindowControl.h"

#include <boost/assign/list_of.hpp>

namespace cigwen {
    
    enum { TypeId_float, TypeId_double, TypeId_int, TypeId_bool, TypeId_Vec2f, TypeId_Vec3f, TypeId_Color, TypeId_ColorA, TypeId_Cue, TypeId_string, TypeId_path };
    
    
    static std::map<std::string, int> TypeIds = boost::assign::map_list_of
    ( []{ return typeid(float).name(); }(), TypeId_float )
    ( []{ return typeid(double).name(); }(), TypeId_double )
    ( []{ return typeid(int).name(); }(), TypeId_int )
    ( []{ return typeid(bool).name(); }(), TypeId_bool )
    ( []{ return typeid(ci::Vec2f).name(); }(), TypeId_Vec2f )
    ( []{ return typeid(ci::Vec3f).name(); }(), TypeId_Vec3f )
    ( []{ return typeid(ci::Color).name(); }(), TypeId_Color )
    ( []{ return typeid(ci::ColorA).name(); }(), TypeId_ColorA )
    ( []{ return typeid(std::function<void()>).name(); }(), TypeId_Cue )
    ( []{ return typeid(std::string).name(); }(), TypeId_string )
    ( []{ return typeid(ci::fs::path).name(); }(), TypeId_path );
    
    class TypeInfo {
    public:
        
        TypeInfo() : mUndefined( true ) {}
        TypeInfo( const std::type_info& info ) : mTypeInfo( &info ), mTypeInfoName( info.name() ), mTypeId( TypeIds[ info.name() ] ), mUndefined( false ) {}
        const std::type_info& get() const { return *mTypeInfo; }
        const std::string& getName() { return mTypeInfoName; }
        int getId(){ return mTypeId; }
        
    private:
        const std::type_info*   mTypeInfo;
        std::string             mTypeInfoName;
        int                     mTypeId;
        bool                    mUndefined;
    };
    
    template<typename T> class ParamData;
    
    class ParamAbstractData {
    public:
        virtual ~ParamAbstractData(){};
        
        template<typename T> ParamData<T>* cast(){ return static_cast< ParamData<T>* >( this ); }
        
        TypeInfo& getType(){ return mType; }
        
    protected:
        TypeInfo        mType;
    };
    
    typedef std::shared_ptr< ParamAbstractData > ParamAbstractDataRef;
    
    template<typename T>
    class ParamData : public ParamAbstractData {
    public:
        
        ParamData(){}
        ParamData( T* value ) : mValue( value ) {}
        ParamData( const ParamData<T> &rhs ) : mValue( rhs.mValue ) {}
        
        operator const T&() const { return *mValue; }
        
        ParamData<T>& operator=( const ParamData &rhs ) { if( this != &rhs ) { mValue = rhs.mValue; } return *this; }
        ParamData<T>& operator=( T* value ) { mValue = value; return *this; }
        
        T* ptr(){ return mValue; }
        const T& value(){ return *mValue; }
        
        
    private:
        T* mValue;
    };
    
    class Param : public Gwen::Controls::Base {
    public:
        
        GWEN_CONTROL( Param, Gwen::Controls::Base );
        
        void setLabel( std::string text );
        void setControl( Gwen::Controls::Base* control );
    private:
        
        
        void PostLayout( Gwen::Skin::Base* skin )
        {
            SizeToChildren( true, true );
        }
        
        void Render( Gwen::Skin::Base* skin );
        
        void valueChanged( Gwen::Controls::Base* control );
        void onNewKeyFrame( Gwen::Controls::Base* control );
        
        Gwen::Controls::Label*          mLabel;
        Gwen::Controls::Base*           mControl;
        
        Gwen::Event::Caller             mOnLayout;
        
        ParamAbstractDataRef            mData;
        friend class Params;
    };
    
    class ParamsWindow : public Gwen::Controls::WindowControl {
    public:
        
        GWEN_CONTROL( ParamsWindow, Gwen::Controls::WindowControl );
        
        void Invalidate(){
            BaseClass::Invalidate();
            mLayoutDone = false;
        }
        void PostLayout( Gwen::Skin::Base* skin )
        {
            if( !mLayoutDone ){
                bool resized = SizeToChildren( true, true );
                if(resized) {
                    SizeToChildren();
                }
                //mLayoutDone = true;
            }
        }
        
        bool mLayoutDone;
    };
    
    class Params : public Gwen::Event::Handler {
    public:
        Params();
        Params( const std::string &title, const ci::Vec2i &size );
        ~Params();
        
        void	show( bool visible = true );
        void	hide();
        bool	isVisible() const;
        
        void    clear();
        
        void	addParam( const std::string &name, bool *boolParam, int layout = Gwen::Pos::Top, float colWidth = 120.0f, const std::string& group = "none", const std::string& tab = "none" );
        void	addParam( const std::string &name, float *floatParam, float min = -1000.0f, float max = 1000.0f, float step = 0.1f, int floatPrecision = 3, int layout = Gwen::Pos::Top, float colWidth = 120.0f, const std::string& group = "none", const std::string& tab = "none" );
        void	addParam( const std::string &name, int *intParam, int min = -1000, int max = 1000, int step = 1, int layout = Gwen::Pos::Top, float colWidth = 120.0f, const std::string& group = "none", const std::string& tab = "none" );
        void	addParam( const std::string &name, ci::Vec2f *vectorParam, ci::Vec2f min = ci::Vec2f( -1000.0f, -1000.0f ), ci::Vec2f max = ci::Vec2f( 1000.0f, 1000.0f ), float step = 0.1f, int floatPrecision = 3, int layout = Gwen::Pos::Top, float colWidth = 120.0f, bool vertical = true, const std::string& group = "none", const std::string& tab = "none" );
        void	addParam( const std::string &name, ci::Vec3f *vectorParam, ci::Vec3f min = ci::Vec3f( -1000.0f, -1000.0f, -1000.0f ), ci::Vec3f max = ci::Vec3f( 1000.0f, 1000.0f, 1000.0f ), float step = 0.1f, int floatPrecision = 3, int layout = Gwen::Pos::Top, float colWidth = 120.0f, bool vertical = true, const std::string& group = "none", const std::string& tab = "none" );
        
        
        void	addParam( const std::string &name, ci::Color *colorParam, int layout = Gwen::Pos::Top, float colWidth = 120.0f, const std::string& group = "none", const std::string& tab = "none" );
        void	addParam( const std::string &name, ci::ColorA *colorParam, int layout = Gwen::Pos::Top, float colWidth = 120.0f, const std::string& group = "none", const std::string& tab = "none"  );
        void	addParam( const std::string &name, std::string *strParam, const std::string &optionsStr = "", bool readOnly = false );
        void    addParam( const std::string &name, const std::vector<std::string> &enumNames, int *param, const std::string &optionsStr = "", bool readOnly = false );
        
        void	addParam( const std::string &name, ci::DataSourceRef pathParam, int layout = Gwen::Pos::Top, float colWidth = 120.0f );
        
        
        void	addSeparator( const std::string &name = "" );
        void	addText( const std::string &name = "" );
        void	addButton( const std::string &name, const std::function<void()> &callback );
        
        void    setPosition( ci::Vec2f pos ){ mWindow->SetPos( pos.x, pos.y ); }
        void    setVisible( bool visible ){ mControl->SetHidden( !visible ); }
        bool    getVisible(){ return !mControl->Hidden(); }
        
        //void    removeAll(){ mControl->Inner()->Inner()->RemoveAllChildren(); mButtonCallbacks.clear();}
        
        Gwen::Controls::Base* getControl();
        
    private:
        
        void onLayout( Gwen::Controls::Base* control );
        void buttonCallback( Gwen::Controls::Base* control );
        
        
        Gwen::Controls::Base* mControl;
        ParamsWindow* mWindow;
        std::vector<std::shared_ptr<std::function<void()> > >	mButtonCallbacks;
        
    };
    
}