//----------------------------------------------------------------------------
// File : bToolCreate.cpp
// Project : MacMap
// Purpose : C++ source file : Object creation tool class
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
// 06/05/2005 creation.
// 18/03/2014 Ready for CG geometry	& drawing
// 28/03/2017 cocoa intf.
//----------------------------------------------------------------------------

#include "bToolCreate.h"
#include "CocoaStuff.h"

#include <mox_intf/bEventLog.h>
#include <mox_intf/xmldesc_utils.h>

#include <mox_intf/ext_utils.h>
#include <mox_intf/MacMapCWrappers.h>
#include <mox_intf/CGUtils.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bToolCreate	::bToolCreate(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
			:bToolNSGeomWithJoin(elt,gapp,bndl){
	setclassname("createtool");
	_opn=false;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bToolCreate::~bToolCreate(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bToolCreate::create(bGenericXMLBaseElement* elt){
	return(new bToolCreate(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolCreate::open(int* flags){	
	set_use_trace(true);
    _opn=false;
	bToolNSGeomWithJoin::open(flags);
	set_use_join(true);
	set_use_locs(false);
	set_use_sel(false);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolCreate::idle(void* prm){
CGPoint	t;
	_gapp->locConverter()->transform(&t,(CGPoint*)prm);	
	bToolNSGeomWithJoin::idle(&t);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolCreate::clic(CGPoint pt, int count){
CGPoint	t;
	
	_gapp->locConverter()->transform(&t,&pt);
	pt=t;
	
	if(!get_use_locs()){
		for(;;){
			_tp=(bGenericType*)CurType(_gapp);		
			if(_tp==NULL){
				break;
			}	
			switch(_tp->kind()){
				case kBaseKindPoint:
				case kBaseKindText:	
					set_use_locs(false);
					set_use_track(false);
					set_use_angle(false);
					break;
				case kBaseKindPolyline:
				case kBaseKindPolygon:
				case kBaseKindRaster:
					set_use_locs(true);
					set_use_track(true);
					set_use_angle(true);
					reset_clic();
					break;
			}
			break;
		}
	}

	if((count>1)&&(get_use_locs())){
		action(0);
//		clearTempPathContext(true);
		validTempPathContext();
	}

// JOIN
i2dvertex	br;
	if(get_join(&br)){
		bToolNSGeomWithJoin::clic(br,count);
	}
	else{
		bToolNSGeomWithJoin::clic(pt,count);
	}

	if((count==1)&&(!get_use_locs())){
		action(0);
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolCreate::drag(CGPoint pt){
CGPoint	t;

	Convert(&t,&pt);
	pt=t;
	bToolNSGeomWithJoin::drag(pt);
	
	if(get_use_locs()){
//		clearTempPathContext(true);
		bToolNSGeomWithJoin::track_join();
i2dvertex	va,vb;
		get_last(&va);
		get_cur(&vb);
CGPoint		cga,cgb;
		Convert(&cga,&va);
		Convert(&cgb,&vb);
		if((cga.x==cgb.x)&&(CGPointsDist(&cga,&cgb)<3)){
			update(true);
			validTempPathContext();
			return;
		}
		if((cga.y==cgb.y)&&(CGPointsDist(&cga,&cgb)<3)){
			update(true);
			validTempPathContext();
			return;
		}
		
		bToolNSGeomWithJoin::clic(vb,1);
		update(false);
		validTempPathContext();
	}	
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolCreate::update(bool global){
	/*if(!global){
		clearTempPathContext(false);
	}*/
	if(get_use_locs()){
		draw_poly(true,true);
	}
	bToolNSGeomWithJoin::update(global);
	if(!global){
		validTempPathContext();
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bToolCreate::set_key(int k){
bool	b=false;

	if(get_use_locs()){
		switch(k){
			case kEnterCharCode:
			case kReturnCharCode:			
				action(0);
				(void)bToolNSGeomWithJoin::set_key(k);
				validTempPathContext();
				k=0;
				b=true;
				break;
			case kEscapeCharCode:
				(void)bToolNSGeomWithJoin::set_key(k);
				//clearTempPathContext(true);
				validTempPathContext();
				k=0;
				_tp=NULL;
				set_use_locs(false);
				set_use_track(false);
				set_use_angle(false);
				b=true;
				break;
			case kBackspaceCharCode:
				if(get_locs()->count()<2){
					break;
				}
				(void)bToolNSGeomWithJoin::set_key(k);
				//clearTempPathContext(true);
				update(true);
				validTempPathContext();
				k=0;
				break;
		}
	}
	
	(void)bToolNSGeomWithJoin::set_key(k);
	
	return(b);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolCreate::action(int count){
	if(get_use_locs()){
		create_multi();
		
		set_use_locs(false);
		set_use_track(false);
		set_use_angle(false);
		
		get_locs()->reset();
	}
	else{
		create_single();
	}
	_tp=NULL;
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolCreate::create_multi(){
_bTrace_("bToolCreate::create_multi",false);
i2dvertex		first,last;
	if(_tp==NULL){
_te_("NULL type");
		return;
	}
	switch(_tp->kind()){
		case kBaseKindPoint:
		case kBaseKindText:	
_te_("bad type kind");
			return;
			break;
		case kBaseKindPolyline:
			if(get_locs()->count()<2){
_te_("get_locs()->count() < 2 for Polyline kind");
				return;
			}
			if(get_locs()->count()==2){
				get_locs()->get(1,&first);
				get_locs()->get(2,&last);
				if(eq_ivx2(&first,&last)){
_te_("doubled coordinate for Polyline kind");
					return;
				}
			}
			break;
		case kBaseKindPolygon:
		case kBaseKindRaster:
			if(get_locs()->count()<3){
_te_("get_locs()->count() < 3 for Polygon kind");
				return;
			}
			get_locs()->get(1,&first);
			get_locs()->get(get_locs()->count(),&last);
			if(eq_ivx2(&first,&last)){
				get_locs()->add(&first);
			}
			break;
	}


bEventLog	log(_gapp,this);

bGenericGeoElement*	o=NULL;
	if(!_tp->new_object(&o)){
_te_("new_object failed");
		return;
	}
ivertices*	vxs;

	switch(_tp->kind()){
		case kBaseKindPolyline:
			vxs=ivs_new(_2D_VX,get_locs()->count(),0);
			if(!vxs){
_te_("ivs_new failed");
				if(_tp->kill_object(o)){
				}
				return;
			}
			for(int i=0;i<get_locs()->count();i++){
				get_locs()->get(i+1,&vxs->vx.vx2[i]);
			}
			break;
		case kBaseKindPolygon:
		case kBaseKindRaster:
			vxs=ivs_new(_2D_VX,get_locs()->count()+1,0);
			if(!vxs){
_te_("ivs_new failed");
				if(_tp->kill_object(o)){
				}
				return;
			}
			for(int i=0;i<get_locs()->count();i++){
				get_locs()->get(i+1,&vxs->vx.vx2[i]);
			}
			vxs->vx.vx2[vxs->nv-1]=vxs->vx.vx2[0];
			break;
        default:
_te_("bad type kind");
            MMBeep();
            return;
	}
    if(!InitWithStyle(_gapp,_gapp->layersMgr()->get_current(),o)){
_te_("InitWithStyle failed");
		MMBeep();
	}
	if(!o->setVertices(vxs)){
		ivs_free(vxs);
_te_("setVertices failed");
		if(_tp->kill_object(o)){
		}
		return;
	}
	ivs_free(vxs);
	log.close();
	
	_gapp->selMgr()->flush();
	o->setselect(true,true);
	if(_opn){
		SendCommandToApplication('fich');
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolCreate::create_single(){
_bTrace_("bToolCreate::create_single",false);
	if(_tp==NULL){
_te_("NULL type");
		return;
	}
	switch(_tp->kind()){
		case kBaseKindPoint:
		case kBaseKindText:	
			break;
		case kBaseKindPolyline:
		case kBaseKindPolygon:
		case kBaseKindRaster:
_te_("bad type kind");
			return;
			break;
	}

bEventLog	log(_gapp,this);
	
bGenericGeoElement*	o=NULL;
	if(!_tp->new_object(&o)){
_te_("new_object failed");
		return;
	}
//_tm_("new_object ok");
ivertices*	vxs=ivs_new(_2D_VX,1,0);
	if(!vxs){
_te_("ivs_new failed");
		if(_tp->kill_object(o)){
		}
		return;
	}
//_tm_("ivs_new ok");
	get_clic(&vxs->vx.vx2[0]);
    if(!InitWithStyle(_gapp,_gapp->layersMgr()->get_current(),o)){
_te_("InitWithStyle failed");
		MMBeep();
	}
	if(!o->setVertices(vxs)){
_te_("setVertices failed");
		ivs_free(vxs);
		if(_tp->kill_object(o)){
		}
		return;
	}
//_tm_("setVertices ok");
	ivs_free(vxs);
//_tm_("ivs_free ok");

	log.close();
	
	_gapp->selMgr()->flush();
	o->setselect(true,true);
	if(_opn){
		SendCommandToApplication('fich');
	}
}

// ---------------------------------------------------------------------------
//
// -----------
bool bToolCreate::edit(void* prm){
_bTrace_("bToolCreate::edit",true);
long            result=0;
bGenericType*	tp=NULL;

// A GERER PAR UN MAP EVENT
    for(int i=_tp_use.count()+1;i<=_gapp->typesMgr()->count();i++){
        _tp_use.add(&tp);
    }
    for(int i=_tp_use.count();i>_gapp->typesMgr()->count();i--){
        _tp_use.rmv(i);
    }
// A GERER PAR UN MAP EVENT

    set_on_edit(true);
    runCocoaAppModal(this,&result);
    if(result>0){
        save();
    }
    else{
        load();
    }
    set_on_edit(false);
    
    return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bGenericXMLBaseElement* bToolCreate::load(){
bGenericXMLBaseElement* groot=bToolNSGeomWithJoin::load();
bGenericXMLBaseElement* elt=NULL;
	if(!groot){
		return(NULL);
	}
bGenericXMLBaseElement* root=get_param(groot,"private");
	if(!root){
		_gapp->classMgr()->ReleaseXMLInstance(groot);
		return(NULL);
	}
char					val[_values_length_max_];
	for(;;){
		elt=_gapp->classMgr()->NthElement(root,1,"bool");
		if(!elt){
			break;
		}
		elt->getvalue(val);
		_opn=atoi(val);
		break;
	}
	_gapp->classMgr()->ReleaseXMLInstance(groot);
	return(NULL);
}

// ---------------------------------------------------------------------------
// 
// -----------
bGenericXMLBaseElement* bToolCreate::make(bArray &arr){
	add_cdesc(arr,0,"param","");
	add_cdesc(arr,1,"version",kCurrentToolParamVers);
	add_cdesc(arr,1,"param","");
	add_cdesc(arr,2,"sign","private");
	add_idesc(arr,2,"bool",_opn);
	return(bToolNSGeomWithJoin::make(arr));
}
