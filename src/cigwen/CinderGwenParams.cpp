//
//  CinderGwenParams.cpp
//  CustomControlWindow
//
//  Created by Simon Geilfus on 19/03/13.
//
//

#include "CinderGwenParams.h"

#include "Gwen/Controls/CheckBox.h"
#include "Gwen/Controls/NumericUpDown.h"
#include "Gwen/Controls/ScrollControl.h"

namespace cigwen {
    
    
    
    GWEN_CONTROL_CONSTRUCTOR( Param ){
        
        mLabel = new Gwen::Controls::Label( this );
        mLabel->SetPos( 15, 0 );
        mLabel->SetSize( 80, 15 );
        
        SetMargin( Gwen::Margin( 0, 1.5f, 0, 1.5f ) );
    }
    
    void Param::setLabel( std::string text ){
        mLabel->SetText( text );
        //mLabel->SizeToContents();
    }
    void Param::setControl( Gwen::Controls::Base* control ){
        mControl = control;
        //mControl->SetPos( 80, mControl->GetPos().y );
        
        //SizeToChildren();
        //GetParent()->SizeToChildren();
        //GetParent()->GetParent()->SizeToChildren();
        //Invalidate();
        //GetParent()->Invalidate();
        //GetParent()->GetParent()->Invalidate();
        //ci::app::console() << "their size  : " << ChildrenSize().x << " " << ChildrenSize().y << std::endl;
        //ci::app::console() << "my size     : " << GetSize().x << " " << GetSize().y << std::endl;
        //ci::app::console() << "my dad size : " << GetParent()->GetSize().x << " " << GetParent()->GetSize().y << std::endl;
        //ci::app::console() << "his dad size : " << GetParent()->GetParent()->GetSize().x << " " << GetParent()->GetParent()->GetSize().y << std::endl << std::endl << std::endl;
        //Gwen::Point size = ChildrenSize() + Gwen::Point( 10.0f, 10.0f );
        //SetSize( size.x, size.y );
    }
    
    void Param::Render( Gwen::Skin::Base* skin ){
        // BaseClass::Render( skin );
        
        std::string typeName = mControl->GetTypeName();
        
        if( typeName == "CheckBox" ){
            Gwen::Controls::CheckBox* base = gwen_cast< Gwen::Controls::CheckBox >( mControl );
            if( *mData->cast<bool>() != base->IsChecked() ){
                base->SetChecked( *mData->cast<bool>() );
            }
        }
       /* else if( typeName == "NumericStepper" ){
            NumericStepper* base = gwen_cast< NumericStepper >( mControl );
            if( *mData->cast<float>() != base->getValue() ){
                if( base->getUseIntegers() )
                    base->setValue( *mData->cast<int32_t>() );
                else
                    base->setValue( *mData->cast<float>() );
            }
        }
        else if( typeName == "VectorStepper2f" ){
            VectorStepper2f* base = gwen_cast< VectorStepper2f >( mControl );
            ci::Vec2f v = *mData->cast<ci::Vec2f>();
            if( v != base->getValue() ){
                base->setValue( v );
            }
        }
        else if( typeName == "VectorStepper3f" ){
            VectorStepper3f* base = gwen_cast< VectorStepper3f >( mControl );
            ci::Vec3f v = *mData->cast<ci::Vec3f>();
            if( v != base->getValue() ){
                base->setValue( v );
            }
        }
        else if( typeName == "ColorPicker" ){
            ColorPicker* base = gwen_cast< ColorPicker >( mControl );
            if( base->useAlpha() ){
                ci::ColorA c = *mData->cast<ci::ColorA>();
                if( c != toCinder( base->GetColor() ) ){
                    base->SetColor( toGwen( c ) );
                }
            }
            else {
                ci::Color c = *mData->cast<ci::Color>();
                if( c != toCinder( base->GetColor() ) ){
                    base->SetColor( toGwen( c ) );
                }
            }
        }*/
    }
    
    void Param::valueChanged( Gwen::Controls::Base* control ){
        std::string typeName = control->GetTypeName();
        //ci::app::console() << typeName <<std::endl;
        
        if( typeName == "CheckBox" ){
            Gwen::Controls::CheckBox* base = gwen_cast< Gwen::Controls::CheckBox >( control );
            mData = base->IsChecked();
        }
        /*else if( typeName == "NumericStepper" ){
            NumericStepper* base = gwen_cast< NumericStepper >( control );
            if( base->getUseIntegers() ){
                mAnimRef = (int32_t) base->getValue();
            }
            else{
                mAnimRef = base->getValue();
            }
        }
        else if( typeName == "VectorStepper2f" ){
            VectorStepper2f* base = gwen_cast< VectorStepper2f >( control );
            mAnimRef = base->getValue();
        }
        else if( typeName == "VectorStepper3f" ){
            VectorStepper3f* base = gwen_cast< VectorStepper3f >( control );
            mAnimRef = base->getValue();
        }*/
        else if( typeName == "ColorPicker" ){
            ColorPicker* base = gwen_cast< ColorPicker >( control );
            mAnimRef = toCinder( base->GetColor() );
        }
    }
    //------------------------------------------------------------------------------------------------------------------------
    
    GWEN_CONTROL_CONSTRUCTOR( ParamsWindow ){
        m_InnerPanel = new Gwen::Controls::ScrollControl( this );
        ( (Gwen::Controls::ScrollControl*) m_InnerPanel )->SetScroll( true, true );
        ( (Gwen::Controls::ScrollControl*) m_InnerPanel )->SetAutoHideBars( true );
        m_InnerPanel->Dock( Gwen::Pos::Fill );
        //new Gwen::Controls::Base( m_InnerPanel );
        m_InnerPanel->Show();
        //        SetPadding( Gwen::Padding( 0, 0, 10, 10 ) );
        //m_InnerPanel->SetPadding( Gwen::Padding( 0, 0, 10, 10 ) );
        //m_InnerPanel->SetMargin( Gwen::Margin( 0, 0, 10, 10 ) );
        
        mLayoutDone = false;
    }
    
    //------------------------------------------------------------------------------------------------------------------------
    
	Params::Params(){
        mControl = NULL;
    }
    
    Params::Params( const std::string &title, const ci::Vec2i &size ){
        mWindow = new ParamsWindow( CanvasSingleton::getCanvas() );
        mWindow->SetTitle( title );
        mWindow->SetSize( size.x, size.y );
        mWindow->SetClosable( false );
        
        //mScroll = new Gwen::Controls::ScrollControl( mWindow );
        //mScroll->Dock( Gwen::Pos::Fill );
        //mScroll->SetAutoHideBars( true );
        //mScroll->SetScroll( false, true );
        //mScroll->SetInnerSize( size.x, size.y );
        //mScroll->SetSize( size.x, size.y );
        
        //new Gwen::Controls::Base( mScroll );
        
        mControl            = mWindow;
    }
    Params::~Params(){
        if( mControl != NULL ) {
            mControl->RemoveAllChildren();
            delete mControl;
        }
    }
    
    void Params::clear()
    {
        mWindow->Inner()->Inner()->RemoveAllChildren();
    }
    
    void Params::setInspectable( Inspectable* inspectable )
    {
        clear();
        addInspectable( inspectable );
    }
    void Params::addInspectable( Inspectable* inspectable )
    {
        std::vector< std::pair< std::string, std::vector< Inspectable::ParameterRef > > > groups;
        for( int i = 0; i < inspectable->getNumParameters(); i++ ){
            Inspectable::ParameterRef param = inspectable->getParameter( i );
            
            bool found = false;
            int j = 0;
            for( ; j < groups.size(); j++ ){
                if( groups[j].first == param->mGroup ){
                    found = true;
                    break;
                }
            }
            if( !found ){
                j = groups.size();
                groups.push_back( std::pair<std::string, std::vector< Inspectable::ParameterRef > >( param->mGroup, std::vector< Inspectable::ParameterRef >() ) );
            }
            
            groups[j].second.push_back( param );
        }
        
        for( int i = 0; i < groups.size(); i++ ){
            if( !groups[i].first.empty() ) addText( groups[i].first );
            for( int j = 0; j < groups[i].second.size(); j++ ){
                Inspectable::ParameterRef param = groups[i].second[j];
                if( param->mEditable ){
                    if( param->mValue.type() == typeid( ci::Anim<float>* ) ) addInspectableParam<float>( param );
                    else if( param->mValue.type() == typeid( ci::Anim<int>* ) ) addInspectableParam<int>( param );
                    else if( param->mValue.type() == typeid( ci::Anim<bool>* ) ) addInspectableParam<bool>( param );
                    else if( param->mValue.type() == typeid( ci::Anim<ci::Vec2f>* ) ) addInspectableParam<ci::Vec2f>( param );
                    else if( param->mValue.type() == typeid( ci::Anim<ci::Vec3f>* ) ) addInspectableParam<ci::Vec3f>( param );
                    else if( param->mValue.type() == typeid( ci::Anim<ci::Color>* ) ) addInspectableParam<ci::Color>( param );
                    else if( param->mValue.type() == typeid( ci::Anim<ci::ColorA>* ) ) addInspectableParam<ci::ColorA>( param );
                }
            }
        }
    }
    
    void Params::addParam( const std::string &name, ci::Anim<bool> *boolParam, int layout, float colWidth, const std::string& group, const std::string& tab ){
        Param* param = new Param( mControl );
        param->Dock( layout );
        param->setLabel( name );
        assert( Inspectable::ParametersMap.count( boolParam ) > 0 );
        param->mAnimRef = Inspectable::ParametersMap[ boolParam ]->mAnimRef;
        //std::cout << name << " " << *boolParam << " " << *param->mData->cast<bool>() << std::endl;
        Gwen::Controls::CheckBox* control = new Gwen::Controls::CheckBox( param );
        control->onCheckChanged.Add( param, &Param::valueChanged );
        control->SetSize( 15, 15 );
        control->SetPos( colWidth, 2.5f );
        param->setControl( control );
        
        mWindow->mLayoutDone = false;
    }
    
    void Params::addParam( const std::string &name, ci::Anim<float> *floatParam, float min, float max, float step, int floatPrecision, int layout, float colWidth, const std::string& group, const std::string& tab ){
        Param* param = new Param( mControl );
        param->Dock( layout );
        param->setLabel( name );
        assert( Inspectable::ParametersMap.count( floatParam ) > 0 );
        param->mAnimRef = Inspectable::ParametersMap[ floatParam ]->mAnimRef;
        param->mOnLayout.Add( this, &Params::onLayout );
        //std::cout << name << " " << *floatParam << " " << *Inspectable::ParametersMap[ floatParam ]->mData->cast<float>() << std::endl;
        // std::cout << name << " " << *floatParam << " " << *param->mData->cast<float>() << std::endl;
        
        NumericStepper* control = new NumericStepper( param );
        control->onChanged.Add( param, &Param::valueChanged );
        control->SetPos( colWidth, 0.0f );
        control->setMin( min );
        control->setMax( max );
        control->setStep( step );
        control->setFloatPrecision( floatPrecision );
        param->setControl( control );
        
        mWindow->mLayoutDone = false;
    }
    void Params::addParam( const std::string &name, ci::Anim<int> *intParam, int min, int max, int step, int layout, float colWidth, const std::string& group, const std::string& tab ){
        Param* param = new Param( mControl );
        param->Dock( layout );
        param->setLabel( name );
        assert( Inspectable::ParametersMap.count( intParam ) > 0 );
        param->mAnimRef = Inspectable::ParametersMap[ intParam ]->mAnimRef;
        param->mOnLayout.Add( this, &Params::onLayout );
        
        NumericStepper* control = new NumericStepper( param );
        control->setUseIntegers( true );
        control->SetPos( colWidth, 0.0f );
        control->onChanged.Add( param, &Param::valueChanged );
        control->setMin( min );
        control->setMax( max );
        control->setStep( step );
        param->setControl( control );
        
        mWindow->mLayoutDone = false;
    }
    void Params::addParam( const std::string &name, ci::Anim<ci::Vec2f> *vectorParam, ci::Vec2f min, ci::Vec2f max, float step, int floatPrecision, int layout, float colWidth, bool vertical, const std::string& group, const std::string& tab ){
        Param* param = new Param( mControl );
        param->Dock( layout );
        param->setLabel( name );
        assert( Inspectable::ParametersMap.count( vectorParam ) > 0 );
        param->mAnimRef = Inspectable::ParametersMap[ vectorParam ]->mAnimRef;
        param->mOnLayout.Add( this, &Params::onLayout );
        
        VectorStepper2f* control = new VectorStepper2f( param );
        control->onChanged.Add( param, &Param::valueChanged );
        control->SetPos( colWidth, 0.0f );
        control->setMin( min );
        control->setMax( max );
        control->setStep( step );
        control->setFloatPrecision( floatPrecision );
        if( vertical ) control->setVertical();
        param->setControl( control );
        
        mWindow->mLayoutDone = false;
    }
    void Params::addParam( const std::string &name, ci::Anim<ci::Vec3f> *vectorParam, ci::Vec3f min, ci::Vec3f max, float step, int floatPrecision, int layout, float colWidth, bool vertical, const std::string& group, const std::string& tab ){
        Param* param = new Param( mControl );
        param->Dock( layout );
        param->setLabel( name );
        assert( Inspectable::ParametersMap.count( vectorParam ) > 0 );
        param->mAnimRef = Inspectable::ParametersMap[ vectorParam ]->mAnimRef;
        param->mOnLayout.Add( this, &Params::onLayout );
        
        VectorStepper3f* control = new VectorStepper3f( param );
        control->onChanged.Add( param, &Param::valueChanged );
        control->SetPos( colWidth, 0.0f );
        control->setMin( min );
        control->setMax( max );
        control->setStep( step );
        control->setFloatPrecision( floatPrecision );
        if( vertical ) control->setVertical();
        param->setControl( control );
        
        mWindow->mLayoutDone = false;
    }
    void Params::addParam( const std::string &name, ci::Anim<ci::Color> *colorParam, int layout, float colWidth, const std::string& group, const std::string& tab ){
        Param* param = new Param( mControl );
        param->setLabel( name );
        param->Dock( layout );
        assert( Inspectable::ParametersMap.count( colorParam ) > 0 );
        param->mAnimRef = Inspectable::ParametersMap[ colorParam ]->mAnimRef;
        param->mOnLayout.Add( this, &Params::onLayout );
        
        ColorPicker* control = new ColorPicker( param );
        control->onChanged.Add( param, &Param::valueChanged );
        control->SetPos( colWidth, 0.0f );
        param->setControl( control );
        
        mWindow->mLayoutDone = false;
    }
    void Params::addParam( const std::string &name, ci::Anim<ci::ColorA> *colorParam, int layout, float colWidth, const std::string& group, const std::string& tab ){
        Param* param = new Param( mControl );
        param->setLabel( name );
        param->Dock( layout );
        assert( Inspectable::ParametersMap.count( colorParam ) > 0 );
        param->mAnimRef = Inspectable::ParametersMap[ colorParam ]->mAnimRef;
        param->mOnLayout.Add( this, &Params::onLayout );
        
        ColorPicker* control = new ColorPicker( param );
        control->onChanged.Add( param, &Param::valueChanged );
        control->setUseAlpha();
        control->SetPos( colWidth, 0.0f );
        param->setControl( control );
        
        mWindow->mLayoutDone = false;
    }
    void Params::addParam( const std::string &name, std::string *strParam, const std::string &optionsStr, bool readOnly ){
        
    }
    void Params::addParam( const std::string &name, const std::vector<std::string> &enumNames, ci::Anim<int> *param, const std::string &optionsStr, bool readOnly ){
        
    }
    
    void Params::addParam( const std::string &name, ci::DataSourceRef pathParam, int layout, float colWidth )
    {
        
        Gwen::Controls::Base* container = new Gwen::Controls::Base( mControl );
        container->Dock( Gwen::Pos::Top );
        container->SetSize( 80, 25 );
        
        //param->setControl( label );
        
        Gwen::Controls::Label* label = new Gwen::Controls::Label( container );
        label->SetSize( 80, 15 );
        label->SetText( name );
        
        Gwen::Controls::FilePicker* filePicker = new Gwen::Controls::FilePicker( container );
        filePicker->SetPos( 85, 0 );
        //filePicker->
    }
    
    void Params::addSeparator( const std::string &name ){
        Gwen::Controls::Base* base = new Gwen::Controls::Base( mControl );
        base->Dock( Gwen::Pos::Top );
        base->SetSize( 200, 30 );
        
        //Gwen::Controls::SplitterBar* splitter = new Gwen::Controls::SplitterBar( base );
        //splitter->SetSize( 200, 5 );
        
    }
    void Params::addText( const std::string &name ){
        //Param* param = new Param( mControl );
        //param->setLabel( name );
        //param->Dock( Gwen::Pos::Top );
        
        Gwen::Controls::Base* labelContainer = new Gwen::Controls::Base( mControl );
        labelContainer->Dock( Gwen::Pos::Top );
        labelContainer->SetSize( 80, 25 );
        
        Gwen::Controls::Label* label = new Gwen::Controls::Label( labelContainer );
        label->SetSize( 80, 15 );
        label->SetText( name );
        label->MakeColorDark();
        label->SetMargin( Gwen::Margin( 2, 2, 0, 10 ) );
        
        //param->setControl( label );
        
        // Gwen::Controls::FilePicker* filePicker = new Gwen::Controls::FilePicker( mControl );
    }
    void Params::addButton( const std::string &name, const std::function<void()> &callback ){
        std::shared_ptr<std::function<void ()> > callbackPtr( new std::function<void ()>( callback ) );
        mButtonCallbacks.push_back( callbackPtr );
        
        Gwen::Controls::Base* buttonContainer = new Gwen::Controls::Base( mControl );
        buttonContainer->Dock( Gwen::Pos::Top );
        buttonContainer->SetSize( 200, 20 );
        
        Gwen::Controls::Button* button = new Gwen::Controls::Button( buttonContainer );
        button->SetSize( 180, 20 );
        button->SetText( name );
        button->UserData.Set( "fn shared_ptr", callbackPtr );
        button->onPress.Add( this, &Params::buttonCallback );
        //button->SetSize( 80, 15 );
    }
    
    void Params::buttonCallback( Gwen::Controls::Base* control )
    {
        std::shared_ptr<std::function<void ()> > callbackPtr = control->UserData.Get< std::shared_ptr<std::function<void ()> > >( "fn shared_ptr" );
        callbackPtr->operator()();
    }
    
    Gwen::Controls::Base* Params::getControl(){
        return mControl;
    }
    
    
    void Params::onLayout( Gwen::Controls::Base* control ){
        //mWindow->GetChild( 0 )->SizeToChildren(false, true);
        // mWindow->SizeToChildren(false, true);
        // mWindow->Invalidate();
        //mScroll->SizeToChildren();
        //ci::app::console() << "Params sizetochilds" << std::endl;
    }
}