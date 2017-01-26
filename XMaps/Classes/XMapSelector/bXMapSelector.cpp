//----------------------------------------------------------------------------
// File : bXMapSelector.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, selector : selecting objects by database and/or geographic request
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2005 Carte Blanche Conseil.
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
// 20/01/2005 creation.
// 29/07/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapSelector.h"
#include "bXMapSelectorCriterion.h"
#include "CocoaStuff.h"

#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/ext_utils.h>
#include <mox_intf/Carb_Utils.h>
#include <mox_intf/Type_Utils.h>
#include <mox_intf/bSelectSolver.h>
#include <mox_intf/bGenericCalc.h>
#include <mox_intf/bEventLog.h>
#include <mox_intf/mm_messages.h>
#include <mox_intf/endian.h>

#include <mox_intf/NSCursorWrappers.h>

#include <std_ext/bStdUserExt.h>

#include <MacMapSuite/bTrace.h>
#include <MacMapSuite/valconv.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapSelector	::bXMapSelector(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				:bStdXMap(elt,gapp,bndl)
				,_critarr(sizeof(bXMapSelectorCriterion*)){
	setclassname("selector");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapSelector::~bXMapSelector(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapSelector::create(bGenericXMLBaseElement* elt){
	return(new bXMapSelector(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapSelector::open(int* flags){
	bStdXMap::open(flags);

	_tp=NULL;
	_selwhat=kSelReplace;
	_use_mask=false;
	
	_next=0;
	_add2cnt=false;
	_add2hdn=kAdd2HiddenNone;
	
	_geog=NULL;
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapSelector::process(int msg, void* prm){
_bTrace_("bXMapSelector::process",true);
bGenericXMLBaseElement* root=NULL;
    switch(msg){
		case kExtProcessCallFromIntf:
			root=make(NULL);
            DumpXMLTreeData(root,stderr);
			break;
		case kExtProcessCallWithXMLTree:
			root=getelement(1);
			break;
		default:
_tw_("message "+msg+" not handled");
			break;
	}
	if(!root){
_te_("root == NULL");
		return(false);
	}

bSelectSolver	solver(_gapp,true);
    solver.exec(root);
    
	if(msg==kExtProcessCallFromIntf){
		_gapp->classMgr()->ReleaseXMLInstance(root);
	}
	reset();
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapSelector::test(void* prm){
	return(_gapp->typesMgr()->count()>0);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapSelector::edit(void* prm){
_bTrace_("bXMapSelector::edit",true);
	_act=kXMapSelectorSelect;
	_root=NULL;
	_name[0]=0;
	_fsgn=0;
	_idx=0;
	if(prm){
		if((int)prm==kXMapSelectorCreateMacroCall){
			_act=kXMapSelectorCreateMacro;
		}
		else if(!parse((bGenericXMLBaseElement*)prm)){
			MMBeep();
			return(true);
		}
	}
    
long    result=0;
    runCocoaAppModal(this,&result);
    if(result>0){
        if(_act!=kXMapSelectorSelect){
_tm_("Ok for save");
           save_formula();
        }
        else{
_tm_("Ok for select");
            return(process(kExtProcessCallFromIntf,prm));
        }
    }
    else{
        reset();
    }
    return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bXMapSelector::reset(){
bXMapSelectorCriterion* crit;
	for(int i=1;i<_critarr.count();i++){
		if(!_critarr.get(i,&crit)){
			break;
		}
		delete crit; 
	}
	_critarr.reset();
    
    _tp=NULL;
    _selwhat=kSelReplace;
    _use_mask=false;
    
    _next=0;
    _add2cnt=false;
    _add2hdn=kAdd2HiddenNone;
    
    _geog=NULL;
}

// ---------------------------------------------------------------------------
// 
// ------------
bGenericXMLBaseElement* bXMapSelector::make(char* macro){
_bTrace_("bXMapSelector::make",true);
	if(_tp==NULL){
_te_("_tp==NULL");
		return(NULL);
	}

bArray						l(sizeof(xmlelt));
bGenericClassesMgr*			mgr=_gapp->classMgr();
char						name[256];
int							i,k;
bXMapSelectorCriterion*		c;
bool						b=false,encap=(macro!=NULL);
bGenericXMLBaseElement*		root=NULL;
int							ii=(encap)?1:0;
char						csgn[10];

	for(;;){
		if(encap){
			if(_act==kXMapSelectorCreateMacro){
				_fsgn=UniqueSignature(_gapp);
			}
			sprintf(csgn,"%.4s",&_fsgn);
			add_cdesc(l,0,"umacro","");
			add_cdesc(l,1,"version","3.0.0");
			add_cdesc(l,1,"name",macro);
			add_cdesc(l,1,"sign",csgn);
			add_idesc(l,1,"bool",0);
		}
		add_cdesc(l,0+ii,"formula","");
		_tp->name(name);
		add_cdesc(l,1+ii,"dbtype",name);
		add_idesc(l,1+ii,"dbselkind",_selwhat);
		add_idesc(l,1+ii,"dbusemasked",_use_mask);
		if(_add2cnt){
			add_idesc(l,1+ii,"dbaddtocontrast",_add2cnt);
		}
		if(_add2hdn){
			add_idesc(l,1+ii,"dbaddtomasked",_add2hdn);			
		}
		if(_next){
			sprintf(csgn,"%.4s",&_next);
			add_cdesc(l,1+ii,"dbsetnext",csgn);
		}
		if(_geog){
			_geog->get_params(&l,1+ii);
		}
		
        for(i=_critarr.count()-1;i>0;i--){
            _critarr.get(i,&c);
            switch(c->get_cntop()){
                case kAndElement:
                    add_cdesc(l,(_critarr.count()-i)+ii,"and","");
                    break;
                case kOrElement:
                    add_cdesc(l,(_critarr.count()-i)+ii,"or","");
                    break;
                case kXOrElement:
                    add_cdesc(l,(_critarr.count()-i)+ii,"xor","");
                    break;
                default:
                    add_cdesc(l,(_critarr.count()-i)+ii,"and","");
                    break;
            }
        }
        i=_critarr.count();
        
		if(b){
			break;
		}
		k=i;
		for(i=1;i<=_critarr.count();i++){
			if(!_critarr.get(i,&c)){
				b=true;
				break;
			}
			if(!c->make(&l,k+ii,_bndl)){
_te_("make criterion error");
				b=true;
				break;
			}
			if(i>1){
				k--;
			}
		}
		
		if(b){
			break;
		}
		root=mgr->ParseXMLDescriptors(&l);
		if(!root){
_te_("ParseXMLDescriptors failed");
		}
		
		break;
	}
	
	free_descs(l);
	
	return(root);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapSelector::parse(bGenericXMLBaseElement* root){
_bTrace_("bXMapSelector::parse",false);
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
	_idx=RecoverMacro(_gapp,sgn);

	elt=_gapp->classMgr()->NthElement(root,1,"bool");
	if(elt){
		elt->getvalue(sgn);
		if(atoi(sgn)==1){
_te_("protected macro");	
			return(false);
		}
	}

parse_prm	prm;
bArray		arr(sizeof(bXMapSelectorCriterion*));

    prm.stack=&arr;
	prm.tp=NULL;
	prm.selwhat=kSelReplace;
	prm.use_mask=false;
	prm.next=0;
	prm.add2cnt=false;
	prm.add2hdn=kAdd2HiddenNone;
	prm.geog=NULL;
	prm.targetsign=0;
	prm.targetvalue[0]=0;
	prm.targetkind=0;
    prm.opsgn=0;
    prm.cntop=kAndElement;
	prm.val[0]=0;

bArray		ops(sizeof(int));
    prm.stackop=&ops;

	elt=_gapp->classMgr()->NthElement(root,1,"formula");
	if(elt){
		if(!elt->dotoall(&prm,0,bXMapSelectorCriterion::parse)){
			return(false);
		}
	}
	
bool	b;

	if(	(prm.targetkind!=0)		&&
		(prm.targetvalue[0]!=0)	&&
		(prm.opsgn!=0)			){
bXMapSelectorCriterion*	crit=new bXMapSelectorCriterion(_gapp,
														prm.targetsign,
														prm.targetvalue,
														prm.targetkind,
														prm.opsgn,
														prm.val,
														&b,
                                                        prm.cntop/*kAndElement*/);
		arr.add(&crit);
	}
	
	_critarr.reset();
	_critarr+arr;
	
	_tp=prm.tp;
	_selwhat=prm.selwhat;
	_use_mask=prm.use_mask;
	_next=prm.next;
	_add2cnt=prm.add2cnt;
	_add2hdn=prm.add2hdn;

	_geog=prm.geog;
	if(_geog){
_tm_("with geog");
	}
	_act=kXMapSelectorEditMacro;
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapSelector::save_formula(){
_bTrace_("bXMapSelector::save_formula",true);
	if(strlen(_name)<=0){
_te_("strlen(_name)<=0");
		reset();
		return;
	}
bGenericXMLBaseElement* root=make(_name);
	if(!root){
_te_("!root");
		reset();
		return;
	}

    DumpXMLTreeData(root,stderr);
    
bEventLog	log(_gapp,this);
	if(_act==kXMapSelectorCreateMacro){
		if(!_gapp->macroMgr()->add(root)){
_te_("!add");
			reset();
			return;
		}
	}
	else{
		if(!_gapp->macroMgr()->modify(_idx,root)){
_te_("!modify");
			reset();
            return;
		}
	}
	reset();
	log.close();
}
