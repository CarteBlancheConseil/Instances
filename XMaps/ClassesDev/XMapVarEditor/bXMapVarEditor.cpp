//----------------------------------------------------------------------------
// File : bXMapVarEditor.cpp
// Project : MacMap
// Purpose : C++ source file : Constants editor class
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
// 16/05/2007 creation.
// 04/02/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapVarEditor.h"
#include "CocoaStuff.h"
#include <mox_intf/ext_utils.h>
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/bEventLog.h>
#include <mox_intf/mm_messages.h>
#include <mox_intf/mm_errors.h>
#include <mox_intf/bStdAlert.h>
#include <mox_intf/endian.h>
#include <mox_intf/NSCursorWrappers.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapVarEditor::bXMapVarEditor(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
                : bStdXMap(elt,gapp,bndl){
	setclassname("vareditor2");
		
char	name[FILENAME_MAX];
GetName(this,name);
(void)_gapp->menuMgr()->add_item(kMenuMgrMenuPalettesID,name,GetSignature(this));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapVarEditor::~bXMapVarEditor(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapVarEditor::create(bGenericXMLBaseElement* elt){
	return(new bXMapVarEditor(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapVarEditor::edit(void* prm){
_bTrace_("bXMapVarEditor::edit()",true);
    _new=true;
    _name[0]=0;
    _value[0]=0;
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
        process(kExtProcessCallFromIntf,prm);
    }
	return(true);
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXMapVarEditor::process(int msg, void* prm){
_bTrace_("bXMapVarEditor::process()",true);
    switch(msg){
        case kExtProcessCallFromIntf:
            save_action();
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
void bXMapVarEditor::get_infos(char* name,
                               char* value,
                               UInt32* kind){
    strcpy(name,_name);
    strcpy(value,_value);
    *kind=_fknd;
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapVarEditor::set_infos(const char* name,
                               const char* value,
                               UInt32 kind){
    strcpy(_name,name);
    strcpy(_value,value);
    kind=_fknd=kind;
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXMapVarEditor::save_action(){
//ControlRef	c=get_control(kXMapVarEditorSignature,kXMapVarEditorNameID);
//    GetTextControlValue(c,_name,FILENAME_MAX);
    if(strlen(_name)==0){
        MMBeep();
        return(false);
    }
    
//    c=get_control(kXMapVarEditorSignature,kXMapVarEditorValueID);
//    GetTextControlValue(c,_value,_values_length_max_);
    if(strlen(_value)==0){
        MMBeep();
        return(false);
    }
    
    if(_gapp->varMgr()->find(_name)){
        if(_new){
            MMBeep();
            return(false);
        }
    }
    
    if(_new){
        _fsgn=UniqueSignature(_gapp);
    }
    
//    c=get_control(kXMapVarEditorSignature,kXMapVarEditorPopupKindID);
//    switch(GetControl32BitValue(c)){
//        case 1:
//            _fknd=_char;
//            break;
//        case 2:
//            _fknd=_bool;
//            break;
//        case 3:
//            _fknd=_int;
//            break;
//        case 4:
//            _fknd=_double;
//            break;
//        case 5:
//            _fknd=_date;
//            break;
//        case 6:
//            _fknd=_time;
//            break;
//    }
    
    
bArray	arr(sizeof(xmlelt));
char	csgn[10];
    add_cdesc(arr,0,"uvar","");
    add_cdesc(arr,1,"version","3.0.0");
    add_cdesc(arr,1,"name",_name);
    sprintf(csgn,"%.4s",&_fsgn);
    add_cdesc(arr,1,"sign",csgn);
    sprintf(csgn,"%.4s",&_fknd);
    add_cdesc(arr,1,"sign",csgn);
    add_idesc(arr,1,"bool",0);
    add_cdesc(arr,1,"formula","");
    switch(_fknd){
        case _char:
            add_cdesc(arr,2,"dbchar",_value);
            break;
        case _bool:
            add_cdesc(arr,2,"dbbool",_value);
            break;
        case _int:
            add_cdesc(arr,2,"dbint",_value);
            break;
        case _double:
            add_cdesc(arr,2,"dbfloat",_value);
            break;
        case _date:
            add_cdesc(arr,2,"dbdate",_value);
            break;
        case _time:
            add_cdesc(arr,2,"dbtime",_value);
            break;
    }
    
bGenericXMLBaseElement*	root=_gapp->classMgr()->ParseXMLDescriptors(&arr);
    free_descs(arr);
    if(!root){
        MMBeep();
        return(true);
    }
bEventLog	log(_gapp,this);
    if(_new){
        if(!_gapp->varMgr()->add(root)){
            MMBeep();
            return(true);
        }
    }
    else{
        if(!_gapp->varMgr()->modify(_idx,root)){
            MMBeep();
            return(true);
        }
    }
    log.close();
    return(true);
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXMapVarEditor::parse(bGenericXMLBaseElement* root){
_bTrace_("bXMapVarEditor::parse",true);
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
    _idx=RecoverVar(_gapp,sgn);
    
    elt=_gapp->classMgr()->NthElement(root,2,"sign");
    if(elt){
        elt->getvalue(sgn);
        _fknd=*((UInt32*)sgn);
#ifdef __LITTLE_ENDIAN__
        LBSwapWord(&_fknd,sizeof(UInt32));
#endif
_tm_("sgn="+sgn+" to "+&_fknd);
    }
    else{
_te_("no sign 2");
        return(false);
    }
    
    elt=_gapp->classMgr()->NthElement(root,1,"bool");
    if(elt){
        elt->getvalue(sgn);
        if(atoi(sgn)==1){
_te_("protected var");
            return(false);
        }
    }
    
    elt=_gapp->classMgr()->NthElement(root,1,"formula");
    if(!elt){
_te_("no formula");
        return(false);
    }
    elt=elt->getelement(1);
    if(!elt){
_te_("no element 1");
        return(false);
    }
    elt->getvalue(_value);
    
    
    _new=false;
    return(true);
}

