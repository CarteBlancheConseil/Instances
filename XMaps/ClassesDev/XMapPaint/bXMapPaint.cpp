//----------------------------------------------------------------------------
// File : bXMapPaint.cpp
// Project : MacMap
// Purpose : C++ source file : XMap paint class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2015 Carte Blanche Conseil.
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
// 08/11/2005 creation.
// 20/08/2015 cocoa intf (palette).
//----------------------------------------------------------------------------
// SCRIPT_COMPATIBLE
//----------------------------------------------------------------------------

#include "bXMapPaint.h"
#include "CocoaStuff.h"

#include <mox_intf/bEventLog.h>
#include <mox_intf/mm_messages.h>
#include <mox_intf/ext_utils.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapPaint	::bXMapPaint(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
			: bStdNSXMap(elt,gapp,bndl){
	setclassname("paint");
	set_flags(kXMapNeedIdle);
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapPaint::~bXMapPaint(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapPaint::create(bGenericXMLBaseElement* elt){
	return(new bXMapPaint(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void* bXMapPaint::ccinit(){
	return(initializeCocoa(getapp(),this));
}

// ---------------------------------------------------------------------------
//
// ------------
bool bXMapPaint::process(int msg, void* prm){
    switch(msg){
        case kExtProcessCallFromIntf:
            break;
        case kExtProcessCallWithParams:{
            paint_prm* p=(paint_prm*)prm;
            return(paint(*p));
        }break;
        case kExtProcessCallWithXMLTree:{
char					val[_values_length_max_];
bGenericXMLBaseElement*	elt;
            elt=getelement(1);
            if(!elt){
                return(false);
            }
            elt->getvalue(val);
            paint(atoi(val));
        }break;
        default:
            break;
    }
    return(true);
}

// ---------------------------------------------------------------------------
//
// ------------
bool bXMapPaint::test(void* prm){
    return((!_wd_open)&&(_gapp->document()!=NULL));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapPaint::edit(void* prm){
//_bTrace_("bXMapPaint::edit",true);
	if(!_controller){
//_tm_("null controller");
        _controller=ccinit();
        if(_controller){
//_tm_("ccinit succeed");
            _wd_open=true;
        }
	}
	return(true);
}

// ---------------------------------------------------------------------------
//
// ------------
bool bXMapPaint::paint(int c, bool dummy){
bEventLog	log(_gapp,this);
    _gapp->layersMgr()->SetObjInvalidation(false);
    (void)paint(c);
    _gapp->layersMgr()->SetObjInvalidation(true);
    log.close();
    return(true);
}

// ---------------------------------------------------------------------------
//
// ------------
bool bXMapPaint::paint(int c){
char	msg[__MESSAGE_STRING_LENGTH_MAX__];
bArray	sel(*(_gapp->selMgr()->elements()));
    message_string(kMsgProgress,msg,1);
bProgressWait       wt("",msg,true,true,sel.count());
bGenericGeoElement*	o;
    for(int i=1;i<=sel.count();i++){
        if(!wt.set_progress(i)){
            break;
        }
        sel.get(i,&o);
        o->setColor(c);
    }
    return(true);
}

