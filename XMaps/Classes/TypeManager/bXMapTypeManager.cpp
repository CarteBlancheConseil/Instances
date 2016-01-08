//----------------------------------------------------------------------------
// File : bXMapTypeManager.cpp
// Project : MacMap
// Purpose : C++ source file : XMap type manager class
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
// 16/06/2011
//----------------------------------------------------------------------------

#include "bXMapTypeManager.h"
#include "CocoaStuff.h"
#include <mox_intf/ext_utils.h>
#include <mox_intf/bEventLog.h>
#include <mox_intf/mm_messages.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapTypeManager::bXMapTypeManager(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
					: bStdXMap(elt,gapp,bndl){
	setclassname("typemgr");
//char	name[FILENAME_MAX];
//GetName(this,name);
//(void)_gapp->menuMgr()->add_item(kMenuMgrMenuPalettesID,name,GetSignature(this));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapTypeManager::~bXMapTypeManager(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapTypeManager::create(bGenericXMLBaseElement* elt){
	return(new bXMapTypeManager(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapTypeManager::test(void* prm){
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapTypeManager::edit(void* prm){
_bTrace_("bXMapTypeManager::edit()",true);	
long		result=0;	
bEventLog	log(_gapp,
				getbundle(),
				"type manager",
				GetSignature(this));
	C_runTypeManagerCocoaAppModal(this,&result);
	if(result<=0){
	}
	log.close();
	return(process(kExtProcessCallFromIntf,prm));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapTypeManager::process(int msg, void* prm){
_bTrace_("bXMapTypeManager::process()",true);	
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
bool bXMapTypeManager::new_action(){	
bGenericExt*	ext=_gapp->xmapMgr()->find('Tnew');
	ext->process(kExtProcessCallFromIntf,NULL);
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapTypeManager::add_action(){
bGenericExt*	ext=_gapp->xmapMgr()->find('Tadd');
	ext->process(kExtProcessCallFromIntf,NULL);
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapTypeManager::rmv_action(long index){
bGenericType*	tp=_gapp->typesMgr()->get(index);
	if(tp==NULL){
		return(false);
	}
	_gapp->typesMgr()->rmv(index);
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapTypeManager::ren_action(long index,
								  char* name){
bGenericType*	tp=_gapp->typesMgr()->get(index);
	if(tp==NULL){
		return(false);
	}
	_gapp->typesMgr()->rename(index,name);
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapTypeManager::prot_action(long index){
bGenericType*	tp=_gapp->typesMgr()->get(index);
	if(tp==NULL){
		return(false);
	}
	tp->set_lock(true);
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapTypeManager::unprot_action(long index){
bGenericType*	tp=_gapp->typesMgr()->get(index);
	if(tp==NULL){
		return(false);
	}
	tp->set_lock(false);
	return(true);
}
