//----------------------------------------------------------------------------
// File : bXMapDBStructure.cpp
// Project : MacMap
// Purpose : C++ source file : XMap database structure class
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
// 28/04/2005 creation.
// 02/09/2015 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapDBStructure.h"
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
bXMapDBStructure::bXMapDBStructure(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
                : bStdXMap(elt,gapp,bndl){
	setclassname("dbstructure");
		
char	name[FILENAME_MAX];
GetName(this,name);
(void)_gapp->menuMgr()->add_item(kMenuMgrMenuPalettesID,name,GetSignature(this));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapDBStructure::~bXMapDBStructure(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapDBStructure::create(bGenericXMLBaseElement* elt){
	return(new bXMapDBStructure(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapDBStructure::test(void* prm){
	return(_gapp->typesMgr()->count()>0);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapDBStructure::edit(void* prm){
_bTrace_("bXMapDBStructure::edit()",true);	
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
bool bXMapDBStructure::process(int msg, void* prm){
_bTrace_("bXMapDBStructure::process()",true);	
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
int bXMapDBStructure::remove(	bGenericType* tp,
                                long field){
_bTrace_("bXMapDBStructure::remove",true);
    if(tp->fields()->remove(field)){
        return _bDataBaseRemoveFieldErr_;
    }
    return noErr;
}

// ---------------------------------------------------------------------------
// 
// -----------
int bXMapDBStructure::add(	bGenericType* tp,
                            long kind,
                            long len,
                            long decs,
                            const char* name){
_bTrace_("bXMapDBStructure::add",true);
    if(tp->fields()->add(kind,len,decs,name)){
        return _bDataBaseAddFieldErr_;
    }
    return noErr;
}

// ---------------------------------------------------------------------------
// 
// -----------
int bXMapDBStructure::modify(	bGenericType* tp,
                                long field,
                                long kind,
                                long len,
                                long decs,
                                const char* name){
_bTrace_("bXMapDBStructure::modify",true);
    if(tp->fields()->modify(field,kind,len,decs,name)){
        return _bDataBaseModifyFieldErr_;
    }
    return noErr;
}


// ---------------------------------------------------------------------------
//
// -----------
int bXMapDBStructure::set_default_value(	bGenericType* tp,
                                            long field,
                                            void* value,
                                            bool init){
_bTrace_("bXMapDBStructure::set_default_value",true);
char	msg[__MESSAGE_STRING_LENGTH_MAX__];
char	exp[__MESSAGE_STRING_LENGTH_MAX__];
   
    if(init&&tp->nb_live()>0){
b_message_string("init existing",msg,getbundle(),1);
b_message_string("init existing exp",exp,getbundle(),1);
bAlertWarningYes	alrt(msg,exp);
        if(alrt.result()){
            for(long i=1;i<=tp->fields()->count_records();i++){
                if(tp->fields()->write(i,field,value)){
                    return _bDataBaseSetDefaultValueErr_;
                }
            }
        }
    }
    if(!tp->fields()->set_default_value(field,value)){
        return _bDataBaseSetDefaultValueErr_;
    }
    return noErr;
}

// ---------------------------------------------------------------------------
//
// -----------
int bXMapDBStructure::set_masked(	bGenericType* tp,
                                    long field,
                                    bool value){
_bTrace_("bXMapDBStructure::set_masked",true);
    if(!tp->fields()->set_hidden(field,value)){
        return _bDataBaseSetHiddenErr_;
    }
    return noErr;
}

// ---------------------------------------------------------------------------
//
// -----------
int bXMapDBStructure::set_delete_protected(	bGenericType* tp,
                                            long field,
                                            bool value){
_bTrace_("bXMapDBStructure::set_delete_protected",true);
    if(!tp->fields()->set_delprotected(field,value)){
        return _bDataBaseSetDeleteProtectedErr_;
    }
    return noErr;
}

// ---------------------------------------------------------------------------
//
// -----------
int bXMapDBStructure::set_write_protected(	bGenericType* tp,
                                            long field,
                                            bool value){
_bTrace_("bXMapDBStructure::set_write_protected",true);
    if(!tp->fields()->set_writeprotected(field,value)){
        return _bDataBaseSetWriteProtectedErr_;
    }
    return noErr;
}


