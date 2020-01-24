//----------------------------------------------------------------------------
// File : bXBoxPresentation.cpp
// Project : MacMap
// Purpose : C++ source file : Presentation XMapBox class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 1997-2015 Carte Blanche Conseil.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// See the LICENSE.txt file for more information.
//
//----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------
// 01/04/2015 creation.
//----------------------------------------------------------------------------

#include "bXBoxPresentation.h"
#include "CocoaStuff.h"
#include <MacMapSuite/bTrace.h>
#include <mox_intf/bGenericTool.h>
#include <mox_intf/MacMapCWrappers.h>
#include <Cocoa/Cocoa.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXBoxPresentation	::bXBoxPresentation(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
                    : bStdNSXBox(elt,gapp,bndl){
	setclassname("xboxpresentation");
    set_flags(kXMapNeedEvents);
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXBoxPresentation::~bXBoxPresentation(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXBoxPresentation::create(bGenericXMLBaseElement* elt){
	return(new bXBoxPresentation(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXBoxPresentation::nsevent(void* nsevt){
    if(!_controller){
        return(false);
    }
/*UInt32			clss=GetEventClass(evt);
UInt32			kind=GetEventKind(evt);*/
NSEvent*        evt=(NSEvent*)nsevt;
CGPoint         loc;
bGenericTool*	tool=(bGenericTool*)CurTool(_gapp);
    
    switch([evt type]){
        case NSEventTypeLeftMouseDown:
            tool->get_cur(&loc);
            clickCocoa(_controller,loc);// return true ?
            break;
        case NSEventTypeApplicationDefined:
            if([evt subtype]==NSEventSubtypeMacMapDataBase){
bArray*			arr=_gapp->eventMgr()->events();
bGenericEvent*	mevt;
                
                for(long i=1;i<=arr->count();i++){
                    arr->get(i,&mevt);
                    switch(mevt->kind()){
                        case kEventKindTypeElement:{
                            refreshCocoa(_controller);
                        }
                    }
                }
               
            }
            break;
    }
    
/*    if((clss==kEventClassMouse)&&(kind==kEventMouseDown)*//*&&(_on_get)*//*){
        tool->get_cur(&loc);
        clickCocoa(_controller,loc);// return true ?
    }
    else if(clss==kEventClassMacMap){
bArray*			arr=_gapp->eventMgr()->events();
bGenericEvent*	mevt;
        
        for(long i=1;i<=arr->count();i++){
            arr->get(i,&mevt);
            switch(mevt->kind()){
                case kEventKindTypeElement:{
                    refreshCocoa(_controller);
                }
            }
        }
    }*/
    return false;
}

// ---------------------------------------------------------------------------
// 
// -----------
void* bXBoxPresentation::ccinit(){
	return(initializeCocoa(getapp(),this));
}
