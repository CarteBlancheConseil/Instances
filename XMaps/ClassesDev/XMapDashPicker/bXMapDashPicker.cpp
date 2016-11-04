//----------------------------------------------------------------------------
// File : bXMapDashPicker.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, dash picker (used by vDefs)
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
// 10/03/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapDashPicker.h"
#include "CocoaStuff.h"

#include <mox_intf/ext_utils.h>
#include <mox_intf/MacMapCWrappers.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapDashPicker::bXMapDashPicker(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
                : bStdXMap(elt,gapp,bndl){
	setclassname("dashpicker");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapDashPicker::~bXMapDashPicker(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapDashPicker::create(bGenericXMLBaseElement* elt){
	return(new bXMapDashPicker(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapDashPicker::edit(void* prm){
_bTrace_("bXMapDashPicker::edit()",true);	
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
bool bXMapDashPicker::process(int msg, void* prm){
_bTrace_("bXMapDashPicker::process()",true);	
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


