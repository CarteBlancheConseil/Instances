//----------------------------------------------------------------------------
// File : bXMapFExp.cpp
// Project : MacMap
// Purpose : C++ source file : XMap classe, export format and projection
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
// 23/02/2016 creation.
// 23/02/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapFExp.h"
#include "CocoaStuff.h"

#include <mox_intf/ext_utils.h>
#include <mox_intf/Type_Utils.h>
#include <mox_intf/xmldesc_utils.h>

#include <MacMapSuite/bTrace.h>


// ---------------------------------------------------------------------------
// Constructeur
// ------------
type_p	::type_p(bGenericType* tp)
        :_flds(sizeof(fexp_field)){
    _tp=tp;
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
type_p	::~type_p(){
    
}

// ---------------------------------------------------------------------------
//
// ------------
bool type_p::load(bGenericMacMapApp* gapp){
_bTrace_("type_p::load",true);
bGenericXMLBaseElement*	root=GetXMLParamFromType(gapp,_tp,kXMapFExpMessageID,kXMapFExpStdParamID);
fexp_field				fld;
    if(!root){
_te_("root==NULL");
//int		fid;
        for(long i=kOBJ_Name_;i<=_tp->fields()->count();i++){
            _tm_(i);
            fld.fid=_tp->fields()->get_id(i);
            //_tp->fields()->get_name(i,fld.fname);
            fld.fname[0]=0;
            _flds.add(&fld);
        }
        return(true);
    }

    root->dotoall(this,0,read_proc);

    for(long i=_flds.count();i>0;i--){
        _flds.get(i,&fld);
        if(fld.fid==0){
            _flds.rmv(i);
        }
    }

    gapp->classMgr()->ReleaseXMLInstance(root);
    return(true);
}

// ---------------------------------------------------------------------------
//
// ------------
bool type_p::dump(bGenericMacMapApp* gapp){
_bTrace_("type_p::dump",false);
bArray		arr(sizeof(xmlelt));
fexp_field	fld;
    
    add_cdesc(arr,0,"param","");
    add_cdesc(arr,1,"version","3.0.0");
    for(long i=1;i<=_flds.count();i++){
        _flds.get(i,&fld);
        add_idesc(arr,1,"int",fld.fid);
        add_cdesc(arr,1,"name",fld.fname);
    }
bGenericXMLBaseElement*			root=gapp->classMgr()->ParseXMLDescriptors(&arr);
    free_descs(arr);
    if(!root){
_te_("root == NULL");
        return(false);
    }
    if(!SetXMLParamToType(_tp,kXMapFExpMessageID,kXMapFExpStdParamID,root)){
_te_("SetXMLParamToType failed");
    }
    gapp->classMgr()->ReleaseXMLInstance(root);
    return(true);
}

// ---------------------------------------------------------------------------
//
// ------------
bool type_p::read_proc(	bGenericXMLBaseElement* elt,
                       void* prm,
                       int indent){
type_p*		p=(type_p*)prm;
char		name[_names_length_max_];
char        value[_values_length_max_];
fexp_field	fld;
    
    elt->getclassname(name);
    if(!strcmp(name,"int")){
        elt->getvalue(value);
        fld.fid=atoi(value);
        p->_flds.add(&fld);
    }
    else if(!strcmp(name,"name")){
        p->_flds.get(p->_flds.count(),&fld);
        elt->getvalue(fld.fname);
        p->_flds.put(p->_flds.count(),&fld);
    }
    return(true);
}


// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapFExp   ::bXMapFExp(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl)
                        : bStdXMap(elt,gapp,bndl){
	setclassname("fexp2");
		
char	name[FILENAME_MAX];
GetName(this,name);
(void)_gapp->menuMgr()->add_item(kMenuMgrMenuPalettesID,name,GetSignature(this));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapFExp::~bXMapFExp(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapFExp::create(bGenericXMLBaseElement* elt){
	return(new bXMapFExp(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapFExp::edit(void* prm){
_bTrace_("bXMapFExp::edit()",true);	
long    result=0;
    
    runCocoaAppModal(this,&result);
    if(result>0){
        return(process(kExtProcessCallFromIntf,prm));
    }
    return(true);
}

// ---------------------------------------------------------------------------
//
// ------------
void bXMapFExp::open(int* flags){
    bStdXMap::open(flags);
    _srid=-1;
    read_p();
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapFExp::process(int msg, void* prm){
_bTrace_("bXMapFExp::process()",true);	
fexp_prm* p=(fexp_prm*)prm;
    switch(msg){
        case kExtProcessCallFromIntf:
            break;
        case kExtProcessCallWithParams:
            break;
        case kExtProcessCallGetData:
            get(p->tidx,p->flds,&p->srid);
            break;
        case kExtProcessCallSetData:
            set(p->tidx,p->flds,p->srid);
            break;
        case kExtProcessCallWithXMLTree:
            return(parse());
            break;
        default:
            break;
    }
	return(true);
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXMapFExp::test(void* prm){
    return(_gapp->typesMgr()->count()>0);
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapFExp::get(int tidx, bArray* arr, int* srid){
bGenericType*	tp=_gapp->typesMgr()->get(tidx);
    if(tp){
type_p	p(tp);
        p.load(_gapp);
        arr->reset();
        *arr+p._flds;
    }
    *srid=_srid;
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapFExp::set(int tidx, bArray* arr, int srid){
bGenericType*	tp=_gapp->typesMgr()->get(tidx);
    if(tp){
type_p	p(tp);
        p._flds+(*arr);
        p.dump(_gapp);
    }
    if(_gapp->document()->srid()!=-1){
        _srid=srid;
        write_p();
    }
}

// ---------------------------------------------------------------------------
//
// ------------
void bXMapFExp::read_p(){
_bTrace_("bXMapFExp::read_p",false);
char	name[_names_length_max_];
    getclassname(name);
bGenericXMLBaseElement* root=NULL;
bGenericXMLBaseElement* elt=NULL;
bool					b=_gapp->document()->readTree(&root,GetSignature(this),name);
char					val[_values_length_max_];
    
    _srid=-1;
    
    if((!b)||(!root)){
        write_p();
        (void)_gapp->document()->readTree(&root,GetSignature(this),name);
        return;
    }
    if((!b)||(!root)){
_te_("((!b)||(!root)) for "+name);
        return;
    }
    elt=_gapp->classMgr()->NthElement(root,1,"int");
    if(!elt){
        return;
    }
    elt->getvalue(val);
    _srid=atoi(val);
    
    _gapp->classMgr()->ReleaseXMLInstance(root);
}

// ---------------------------------------------------------------------------
//
// ------------
void bXMapFExp::write_p(){
bGenericXMLBaseElement* root=make_p();
    if(!root){
        return;
    }
char	name[_names_length_max_];
    getclassname(name);
    
    if(!_gapp->document()->writeTree(root,GetSignature(this),name)){
        return;
    }
    _gapp->classMgr()->ReleaseXMLInstance(root);
}

// ---------------------------------------------------------------------------
//
// ------------
bGenericXMLBaseElement* bXMapFExp::make_p(){
bArray	arr(sizeof(xmlelt));
    add_cdesc(arr,0,"param","");
    add_cdesc(arr,1,"version","3.0.0");
    
    add_idesc(arr,1,"int",_srid);
    
bGenericXMLBaseElement*	root=_gapp->classMgr()->ParseXMLDescriptors(&arr);
    free_descs(arr);
    return(root);
}

// ---------------------------------------------------------------------------
//
// ------------
bool bXMapFExp::parse(){
bGenericXMLBaseElement*	elt;
bGenericXMLBaseElement*	chld;
char					val[_values_length_max_];
bGenericType*			tp;
bArray					arr(sizeof(int));
int						nb;
fexp_field				fld;
    
    elt=_gapp->classMgr()->NthElement(this,1,"int");
    if(elt){
        elt->getvalue(val);
        _srid=atoi(val);
        write_p();
    }
    
    for(long i=1;;i++){
        elt=_gapp->classMgr()->NthElement(this,i,"container");
        if(!elt){
            break;
        }
        
        chld=_gapp->classMgr()->NthElement(elt,1,"int");
        if(!chld){
            return(false);
        }
        chld->getvalue(val);
        tp=_gapp->typesMgr()->get(_gapp->typesMgr()->index(val));
        if(!tp){
            return(false);
        }
        
        nb=_gapp->classMgr()->CountElements(elt,"name");
        arr.reset();
        for(long j=1;j<=nb;j++){
            chld=_gapp->classMgr()->NthElement(elt,j,"name");
            chld->getvalue(val);
            fld.fid=tp->fields()->get_id(tp->fields()->get_index(val));
            if(fld.fid==0){
                return(false);
            }
            fld.fname[0]=0;
            chld=_gapp->classMgr()->NthElement(elt,j,"string");
            if(chld){
                chld->getvalue(fld.fname);
            }
            arr.add(&fld);
        }
        
        set(tp->index(),&arr,_srid);
    }
    return(true);
}



