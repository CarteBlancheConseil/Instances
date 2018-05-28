//----------------------------------------------------------------------------
// File : bToolZoom.cpp
// Project : MacMap
// Purpose : C++ source file : Zoom tool class
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
// 05/01/2005 creation.
// 02/03/2017 cocoa intf.
//----------------------------------------------------------------------------

#include "bToolZoom.h"
#include "CocoaStuff.h"
#include <mox_intf/ext_utils.h>
#include <mox_intf/NSContextualMenuWrappers.h>
#include <MacMapSuite/bTrace.h>
#include <MacMapSuite/C_Utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bToolZoom	::bToolZoom(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
			: bStdToolNav(elt,gapp,bndl)
			,_scales(sizeof(scale)){
	setclassname("zoomtool");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bToolZoom::~bToolZoom(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bToolZoom::create(bGenericXMLBaseElement* elt){
	return(new bToolZoom(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolZoom::open(int* flags){	
	set_use_trace(true);
	bStdToolNav::open(flags);
	_cminus=load_curs("OutCursor.png");
	set_mnu_cmd(1);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolZoom::close(){
	bStdToolNav::close();
	if(_cminus){
		ReleaseCocoaCursor(_cminus);
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolZoom::pop(cocoaMenuPrm prm){
int				cmd,x;
bGenericUnit*	u;
long			nb=_gapp->scaleMgr()->count();
menuitem_desc*	desc=new menuitem_desc[nb];
	
	x=_gapp->scaleMgr()->get_current();
	for(int i=1;i<=nb;i++){
		u=_gapp->scaleMgr()->get(i);
		u->long_name(desc[i-1].name);
		if(strlen(desc[i-1].name)<=0){
			sprintf(desc[i-1].name,"1/%.0f",u->coef());
		}
		desc[i-1].checked=(i==x);
        desc[i-1].disabled=false;
        desc[i-1].index=0;
	}
	if(prm.wdIsCocoa){
		cmd=popUpContextMenuWithCGPointAndNSWindow(prm.location,
												   prm.inWindow,
												   desc,
												   nb);		
	}
	else{
		cmd=popUpContextMenuWithCGPointAndWindowRef(prm.location,
													(WindowRef)prm.inWindow,
													desc,
													nb);		
	}
	delete[] desc;
	if((cmd>0)&&(cmd!=x)){
i2dvertex	vx;
		Convert(&vx,&prm.location);
		if(_gapp->scaleMgr()->set_current(cmd)){
			_gapp->mapIntf()->setScreenCenter(vx);
		}
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolZoom::clic(CGPoint pt, int count){
//_bTrace_("bToolZoom::clic(CGPoint, int)",true);
	bStdToolNav::clic(pt,count);
i2dvertex	vx;
	get_clic(&vx);
	if(is_modifiers(shiftKey)||is_modifiers(optionKey)){
		if(_gapp->scaleMgr()->set_current(_gapp->scaleMgr()->get_current()+1)){
		}
	}
	else{
		if(_gapp->scaleMgr()->set_current(_gapp->scaleMgr()->get_current()-1)){
		}
	}
	_gapp->mapIntf()->setScreenCenter(vx);
	set_cur(&pt);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolZoom::update(bool global){
	if(get_active()&&get_use_track()){
		if(!global){
			clearTempPathContext(false);
		}
CGPoint	a;
		get_cur(&a);
		if((a.x!=SHRT_MIN)&&(_gapp->scaleMgr()->get_current()>1)){
bGenericUnit*	scl=_gapp->scaleMgr()->get();
bGenericUnit*	scl2=_gapp->scaleMgr()->get(_gapp->scaleMgr()->get_current()-1);		
double			d=scl2->coef()/scl->coef();
CGRect			cgr=getTempPathContextRect();
			cgr.size.width*=d;
			cgr.size.height*=d;	
			hilite_rect(getTempPathContext(),CGRectOffset(cgr,a.x-CGRectGetMidX(cgr),a.y-CGRectGetMidY(cgr)),true,true);
		}
		if(!global){
			validTempPathContext();
		}
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolZoom::set_modifiers(int k){
	bStdToolNav::set_modifiers(k);
	if(!get_active()){
		return;
	}
	if(is_modifiers(shiftKey)||is_modifiers(optionKey)){
		set_curs(_cminus);
		set_use_track(false);
		clearTempPathContext(true);
	}
	else{
		set_curs();
		set_use_track(true);
		clearTempPathContext(true);
		update(false);
	}
	validTempPathContext();
}

// ---------------------------------------------------------------------------
//
// -----------
bool bToolZoom::edit(void* prm){
_bTrace_("bToolZoom::edit",true);
long            result=0;
bGenericUnit*	u;
scale			scl;
    
    for(int i=1;i<=_gapp->scaleMgr()->count();i++){
        u=_gapp->scaleMgr()->get(i);
        scl.idx=i;
        scl.modified=false;
        scl.created=false;
        scl.deleted=false;
        scl.value=u->coef();
        u->long_name(scl.name);
        scl.u=u;
        _scales.add(&scl);
    }

    set_on_edit(true);
    runCocoaAppModal(this,&result);
    if(result>0){
        dump();
    }
    set_on_edit(false);
    _scales.reset();
    
    return(true);
}

// ---------------------------------------------------------------------------
// Contextual menu for tool choice
// -----------
void bToolZoom::pop_tools(CGPoint location,
						  WindowRef inWindow){
	if(is_modifiers(controlKey)){
cocoaMenuPrm prm;
		prm.location=location;
		prm.inWindow=inWindow;
		prm.wdIsCocoa=false;
		pop(prm);
	}
	else{
		bStdToolNav::pop_tools(location,inWindow);
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolZoom::dump(){
int		i,k;
scale	scl;
	
// Modified	
	for(i=_scales.count();i>0;i--){
		_scales.get(i,&scl);
		if(scl.modified){
			k=RecoverScale(_gapp,scl.u);
			_gapp->scaleMgr()->set(k,scl.name,scl.value);
		}
	}
	
// Created	
	for(i=_scales.count();i>0;i--){
		_scales.get(i,&scl);
		if(scl.created){
			_gapp->scaleMgr()->add(scl.name,scl.value);
		}
	}

// Deleted	
	for(i=_scales.count();i>0;i--){
		_scales.get(i,&scl);
		if(scl.deleted){
			k=RecoverScale(_gapp,scl.u);
			_gapp->scaleMgr()->rmv(k);
		}
	}
}

