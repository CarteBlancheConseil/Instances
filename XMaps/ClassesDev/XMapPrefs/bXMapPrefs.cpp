//----------------------------------------------------------------------------
// File : bXMapPrefs.cpp
// Project : MacMap
// Purpose : C++ source file : XMap classe, preferences
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
// 18/06/2007 creation.
// 25/02/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapPrefs.h"
#include "CocoaStuff.h"

#include <mox_intf/ext_utils.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapPrefs   ::bXMapPrefs(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl)
                : bStdXMap(elt,gapp,bndl){
	setclassname("prefs2");
		
char	name[FILENAME_MAX];
GetName(this,name);
(void)_gapp->menuMgr()->add_item(kMenuMgrMenuPalettesID,name,GetSignature(this));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapPrefs::~bXMapPrefs(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapPrefs::create(bGenericXMLBaseElement* elt){
	return(new bXMapPrefs(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapPrefs::edit(void* prm){
_bTrace_("bXMapPrefs::edit()",true);	
long    result=0;
    
    runCocoaAppModal(this,&result);
    if(result>0){
        return(process(kExtProcessCallFromIntf,prm));
    }
    return false;
}


// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapPrefs::process(int msg, void* prm){
_bTrace_("bXMapPrefs::process()",true);	
	switch(msg){
        case kExtProcessCallFromIntf:
            break;
        case kExtProcessCallWithParams:
            break;
        case kExtProcessCallWithXMLTree:
            break;
        default:
            break;
	}
	return(true);
}


