//----------------------------------------------------------------------------
// File : bXMapDBDefVal.cpp
// Project : MacMap
// Purpose : C++ source file : XMap default values class, sets standard fields default values
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
// 16/03/2007 creation.
// 11/02/2016 coca intf.
//----------------------------------------------------------------------------

#include "bXMapDBDefVal.h"
#include "CocoaStuff.h"
#include <mox_intf/ext_utils.h>
#include <mox_intf/bEventLog.h>
#include <mox_intf/mm_messages.h>
#include <mox_intf/mm_errors.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapDBDefVal::bXMapDBDefVal(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
                : bStdXMap(elt,gapp,bndl){
	setclassname("dbdefval2");
		
char	name[FILENAME_MAX];
GetName(this,name);
(void)_gapp->menuMgr()->add_item(kMenuMgrMenuPalettesID,name,GetSignature(this));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapDBDefVal::~bXMapDBDefVal(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapDBDefVal::create(bGenericXMLBaseElement* elt){
	return(new bXMapDBDefVal(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapDBDefVal::test(void* prm){
	return(_gapp->typesMgr()->count()>0);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapDBDefVal::edit(void* prm){
_bTrace_("bXMapDBDefVal::edit()",true);
long        result=0;
bEventLog	log(_gapp,this);
    runCocoaAppModal(this,&result);
    if(result>0){
        process(kExtProcessCallFromIntf,prm);
    }
    log.close();
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapDBDefVal::process(int msg, void* prm){
_bTrace_("bXMapDBDefVal::process()",true);	
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
int bXMapDBDefVal::modify(	bGenericType* tp,
                            long field,
                            long cidx,
                            const char* value){
_bTrace_("bXMapDBDefVal::modify",true);
char	def[__MESSAGE_STRING_LENGTH_MAX__];
int		n=tp->fields()->count_constraints(field);

    if(n>0){
        tp->fields()->get_constraint(field,cidx,def);
        tp->fields()->set_default_value(field,def);
    }
    else{
        tp->fields()->set_default_value(field,(void*)value);

    }
    return noErr;
}
