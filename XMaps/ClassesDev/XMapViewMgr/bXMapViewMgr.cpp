//----------------------------------------------------------------------------
// File : bXMapViewMgr.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, views management
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2016 Carte Blanche Conseil.
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
// 29/05/2007 creation.
// 19/02/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapViewMgr.h"
#include "CocoaStuff.h"
#include <mox_intf/ext_utils.h>
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/bEventLog.h>
#include <mox_intf/mm_messages.h>
#include <mox_intf/mm_errors.h>
#include <mox_intf/bStdAlert.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapViewMgr::bXMapViewMgr(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
                : bStdXMap(elt,gapp,bndl){
	setclassname("viewmgr2");
		
char	name[FILENAME_MAX];
GetName(this,name);
(void)_gapp->menuMgr()->add_item(kMenuMgrMenuPalettesID,name,GetSignature(this));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapViewMgr::~bXMapViewMgr(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapViewMgr::create(bGenericXMLBaseElement* elt){
	return(new bXMapViewMgr(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapViewMgr::edit(void* prm){
_bTrace_("bXMapViewMgr::edit()",true);	
long    result=0;
    runCocoaAppModal(this,&result);
    if(result>0){
        process(kExtProcessCallFromIntf,prm);
    }
	return true;
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapViewMgr::process(int msg, void* prm){
_bTrace_("bXMapViewMgr::process()",true);	
	switch(msg){
        case kExtProcessCallFromIntf:
            break;
		case kExtProcessCallWithParams:
			break;
		case kExtProcessCallWithXMLTree:
			break;
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
int bXMapViewMgr::add(){
_bTrace_("bXMapViewMgr::add",true);
    if(!_gapp->viewMgr()->append()){
        return -1;
    }
    return noErr;
}

// ---------------------------------------------------------------------------
//
// -----------
int bXMapViewMgr::remove(long idx){
_bTrace_("bXMapViewMgr::remove",true);
    if(_gapp->viewMgr()->remove(idx)){
        return -1;
    }
    return noErr;
}

// ---------------------------------------------------------------------------
//
// -----------
int bXMapViewMgr::rename(long idx, const char* name){
_bTrace_("bXMapViewMgr::rename",true);
    if(!_gapp->viewMgr()->set_name(idx,name)){
    }
    return noErr;
}

// ---------------------------------------------------------------------------
//
// -----------
int bXMapViewMgr::duplicate(long idx){
_bTrace_("bXMapViewMgr::duplicate",true);
    if(_gapp->viewMgr()->duplicate(idx)){
        return -1;
    }
    return noErr;
}



