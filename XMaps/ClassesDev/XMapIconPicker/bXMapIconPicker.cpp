//----------------------------------------------------------------------------
// File : bXMapIconPicker.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, icon picker (used by vDefs)
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
// 28/04/2005 creation.
// 08/03/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapIconPicker.h"
#include "CocoaStuff.h"
#include <mox_intf/ext_utils.h>
#include <mox_intf/MacMapCWrappers.h>
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/bEventLog.h>
#include <mox_intf/mm_messages.h>
#include <mox_intf/mm_errors.h>
#include <mox_intf/bStdAlert.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapIconPicker::bXMapIconPicker(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
                : bStdXMap(elt,gapp,bndl){
	setclassname("iconpicker2");
		
char	name[FILENAME_MAX];
GetName(this,name);
(void)_gapp->menuMgr()->add_item(kMenuMgrMenuPalettesID,name,GetSignature(this));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapIconPicker::~bXMapIconPicker(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapIconPicker::create(bGenericXMLBaseElement* elt){
	return(new bXMapIconPicker(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapIconPicker::edit(void* prm){
_bTrace_("bXMapIconPicker::edit()",true);	
    if(prm){
        _prm=*((picker_prm*)prm);
    }
    else{
        _prm.tp=(bGenericType*)CurType(_gapp);
        strcpy(_prm.name,"");
    }
long    result=0;
    runCocoaAppModal(this,&result);
    if(prm){
        *((picker_prm*)prm)=_prm;
    }
    
if(result){
_tm_(_prm.name);
}
    
    return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapIconPicker::process(int msg, void* prm){
_bTrace_("bXMapIconPicker::process()",true);	
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


