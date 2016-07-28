//----------------------------------------------------------------------------
// File : bXMapToolMenuConfig.cpp
// Project : MacMap
// Purpose : C++ source file : XMap classe, contextual tool menu configuration
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
// 08/06/2007 creation.
// 24/02/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapToolMenuConfig.h"
#include "CocoaStuff.h"

#include <mox_intf/ext_utils.h>
//#include <mox_intf/Type_Utils.h>
//#include <mox_intf/xmldesc_utils.h>
//#include <mox_intf/bEventLog.h>
//#include <mox_intf/mm_messages.h>
//#include <mox_intf/mm_errors.h>
//#include <mox_intf/bStdAlert.h>
//#include <mox_intf/MacMapCWrappers.h>

#include <std_ext/bStdTool.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapToolMenuConfig ::bXMapToolMenuConfig(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl)
                    : bStdXMap(elt,gapp,bndl){
	setclassname("toolmenuconfig2");
		
char	name[FILENAME_MAX];
GetName(this,name);
(void)_gapp->menuMgr()->add_item(kMenuMgrMenuPalettesID,name,GetSignature(this));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapToolMenuConfig::~bXMapToolMenuConfig(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapToolMenuConfig::create(bGenericXMLBaseElement* elt){
	return(new bXMapToolMenuConfig(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapToolMenuConfig::edit(void* prm){
_bTrace_("bXMapToolMenuConfig::edit()",true);	
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
bool bXMapToolMenuConfig::process(int msg, void* prm){
_bTrace_("bXMapToolMenuConfig::process()",true);	
    switch(msg){
        case kExtProcessCallFromIntf:
            break;
        case kExtProcessCallWithParams:
            break;
        case kExtProcessCallGetData:
            break;
        case kExtProcessCallSetData:
            break;
        case kExtProcessCallWithXMLTree:
            break;
        default:
            break;
    }
	return(true);
}

