//----------------------------------------------------------------------------
// File : bXMapCalcEditor.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, MapCalculator editor
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
// 03/05/2007 creation.
// 16/03/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapCalcEditor.h"
#include "CocoaStuff.h"

#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/ext_utils.h>
#include <mox_intf/bEventLog.h>
#include <mox_intf/endian.h>
#include <mox_intf/NSCursorWrappers.h>

#include <MacMapSuite/bTrace.h>
#include <MacMapSuite/valconv.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapCalcEditor	::bXMapCalcEditor(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				:bStdXMap(elt,gapp,bndl){
	setclassname("calceditor2");
                    
char	name[FILENAME_MAX];
GetName(this,name);
(void)_gapp->menuMgr()->add_item(kMenuMgrMenuPalettesID,name,GetSignature(this));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapCalcEditor::~bXMapCalcEditor(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapCalcEditor::create(bGenericXMLBaseElement* elt){
	return(new bXMapCalcEditor(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapCalcEditor::process(int msg, void* prm){
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapCalcEditor::edit(void* prm){
	_new=true;
	_root=NULL;
	_name[0]=0;
	_fknd=0;
	_fsgn=0;
	if(prm){
		if(!parse((bGenericXMLBaseElement*)prm)){
			MMBeep();
			return(true);
		}
	}
long    result=0;
    runCocoaAppModal(this,&result);
    if(result>0){
        if(!save_action()){
        }
    }
    return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapCalcEditor::save_action(){
	if(!_root){
		return(true);
	}
	if(_gapp->calcMgr()->find(_name)){
		if(_new){
            MMBeep();
			return(false);
		}
	}

    if(_new){
		_fsgn=UniqueSignature(_gapp);
	}

bArray	arr(sizeof(xmlelt));
char	csgn[10];
	add_cdesc(arr,0,"ucalc","");
	add_cdesc(arr,1,"version","3.0.0");
	add_cdesc(arr,1,"name",_name);
	sprintf(csgn,"%.4s",&_fsgn);
	add_cdesc(arr,1,"sign",csgn);
	sprintf(csgn,"%.4s",&_fknd);
	add_cdesc(arr,1,"sign",csgn);
	add_idesc(arr,1,"bool",0);
	add_cdesc(arr,1,"formula","");
	
	_root->write(arr,2);
	
bGenericXMLBaseElement*	root=_gapp->classMgr()->ParseXMLDescriptors(&arr);
	free_descs(arr);
	if(!root){
        MMBeep();
		return(true);
	}
bEventLog	log(_gapp,this);
	if(_new){
		if(!_gapp->calcMgr()->add(root)){
            MMBeep();
            delete _root;
            _root=NULL;
			return(true);
		}
	}
	else{
		if(!_gapp->calcMgr()->modify(_idx,root)){
            MMBeep();
            delete _root;
            _root=NULL;
			return(true);
		}
	}
    delete _root;
    _root=NULL;

	log.close();
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapCalcEditor::parse(bGenericXMLBaseElement* root){
_bTrace_("bXMapCalcEditor::parse",true);
bGenericXMLBaseElement*	elt;
char					sgn[10];


	elt=_gapp->classMgr()->NthElement(root,1,"name");
	if(elt){
		elt->getvalue(_name);
	}
	else{
_te_("no name");
		return(false);
	}

	elt=_gapp->classMgr()->NthElement(root,1,"sign");
	if(elt){
		elt->getvalue(sgn);
		_fsgn=*((UInt32*)sgn);
	}
	else{
_te_("no sign 1");
		return(false);
	}
	_idx=RecoverCalc(_gapp,sgn);

	elt=_gapp->classMgr()->NthElement(root,2,"sign");
	if(elt){
		elt->getvalue(sgn);
		_fknd=*((UInt32*)sgn);
#ifdef __LITTLE_ENDIAN__
		LBSwapWord(&_fknd,sizeof(UInt32));
#endif
	}
	else{
_te_("no sign 2");
		return(false);
	}
	
	elt=_gapp->classMgr()->NthElement(root,1,"bool");
	if(elt){
		elt->getvalue(sgn);
		if(atoi(sgn)==1){
_te_("protected calc");	
			return(false);
		}
	}

bArray		arr(sizeof(bXMapCalcCell*));
parse_prm	prm;
	prm.stack=&arr;
	prm.cur=0;
	prm.root=NULL;
	
	elt=_gapp->classMgr()->NthElement(root,1,"formula");
	if(elt){
		elt->dotoall(&prm,0,bXMapCalcCell::parse);
	}
	if(prm.stack->count()>0){
		prm.stack->get(1,&_root);
	}
	
	_new=false;
	return(true);
}
