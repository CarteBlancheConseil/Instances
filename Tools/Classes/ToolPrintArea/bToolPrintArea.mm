//----------------------------------------------------------------------------
// File : bToolPrintArea.cpp
// Project : MacMap
// Purpose : Objective C++ source file : Print area tool class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2006-2018 Carte Blanche Conseil.
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
// 22/03/2006 creation.
// 18/03/2014 Ready for CG geometry	& drawing
// 09/11/2018 64Bits
//----------------------------------------------------------------------------

#include "bToolPrintArea.h"
#include "CocoaStuff.h"

#include <mox_intf/mm_messages.h>
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/ext_utils.h>

#include <MacMapSuite/bTrace.h>
#include <MacMapSuite/C_Utils.h>
#include <Cocoa/Cocoa.h>

// ---------------------------------------------------------------------------
// 
// ------------
paper ppr[]={
{"A4",21,29.7},
{"A3",29.7,42},
{"A5",14.85,21},
{"B5",17.60,25.01},
{"US Letter",21.59,27.94},
{"US Legal",21.59,35.56}
};

#define _d_(a,b,d) (((double)(labs(b-a)))*d)

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bToolPrintArea	::bToolPrintArea(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				: bStdToolPres(elt,gapp,bndl){
	setclassname("printareatool");
	_draw=true;
	_pprnat=1;
	_pprkind=1;
	_sizekind=kPrintAreaPopKindMenuGeo;
	ivrset(&_vxr,0,0,0,0);
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bToolPrintArea::~bToolPrintArea(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bToolPrintArea::create(bGenericXMLBaseElement* elt){
	return(new bToolPrintArea(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolPrintArea::open(int* flags){
	set_use_trace(true);
    _draw=true;
    _pprnat=1;
    _pprkind=1;
    _sizekind=kPrintAreaPopKindMenuGeo;

    bStdToolPres::open(flags);

	_cmove=load_curs("MoveCursor.png");
	_cxyresize=load_curs("XYResizeCursor.png");
	_cxresize=load_curs("XResizeCursor.png");
	_cyresize=load_curs("YResizeCursor.png");
	
	_vxr=*(_gapp->printMgr()->get_print_area());
	_startmove=false;
	_dragmode=kPrintAreaDragModeSet;

	set_use_drag(false);
	set_use_track(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolPrintArea::close(){
	bStdToolPres::close();
	if(_cmove){
		ReleaseCocoaCursor(_cmove);
	}
	if(_cxyresize){
		ReleaseCocoaCursor(_cxyresize);
	}
	if(_cxresize){
		ReleaseCocoaCursor(_cxresize);
	}
	if(_cyresize){
		ReleaseCocoaCursor(_cyresize);
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolPrintArea::pop(cocoaMenuPrm prm){
	set_mnu_cmd(0);
	bStdToolPres::pop(prm);
	clearTempPathContext(true);
	switch(get_mnu_cmd()){
		case kPrintAreaMenuCommandCenter:
			center_to_screen();
			break;
		case kPrintAreaMenuCommandWindow:
			fit_to_screen();
			break;
		case kPrintAreaMenuCommandSelection:
			fit_to_objs(_gapp->selMgr()->elements());
			break;
		case kPrintAreaMenuCommandContrasts:
			fit_to_objs(_gapp->cntMgr()->elements());
			break;
	}
	_gapp->printMgr()->set_print_area(&_vxr);
	update(true);
	validTempPathContext();
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolPrintArea::clic(i2dvertex loc, int count){
	bStdToolPres::clic(loc,count);

ivx_rect		vr=*(_gapp->printMgr()->get_print_area());
bGenericUnit*	u=_gapp->scaleMgr()->get();
i2dvertex		vxa={vr.left,vr.top};
	
	if(	(_d_(vr.bottom,loc.v,u->conv())<3)	&&
		(_d_(vr.right,loc.h,u->conv())<3)	){
		_dragmode=kPrintAreaDragModeFullResize;
		set_clic(&vxa);
		set_cur(&vxa);
	}
	else if(_d_(vr.bottom,loc.v,u->conv())<3){
		_dragmode=kPrintAreaDragModeBottomResize;
		set_clic(&vxa);
		set_cur(&vxa);
	}
	else if(_d_(vr.right,loc.h,u->conv())<3){
		_dragmode=kPrintAreaDragModeRightResize;
		set_clic(&vxa);
		set_cur(&vxa);
	}
	else if((_d_(vr.top,loc.v,u->conv())<3)	||
			(_d_(vr.left,loc.h,u->conv())<3)){
		_dragmode=kPrintAreaDragModeMove;
		_startmove=true;
	}
	else{
		_dragmode=kPrintAreaDragModeSet;
	}
	
	set_use_drag(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolPrintArea::end_clic(){
	bStdToolPres::end_clic();
	_dragmode=kPrintAreaDragModeSet;
	set_use_drag(false);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bToolPrintArea::nsevent(void* nsevt){
NSEvent* evt=(NSEvent*)nsevt;
    if( ([evt type]==NSEventTypeApplicationDefined) &&
        ([evt subtype]==NSEventSubtypeDrawMap)	){
        update(false);
        return(true);
    }
    return(bStdToolPres::nsevent(evt));
    
/*UInt32	clss=GetEventClass(evt);
	if(clss==kEventClassWindow){
UInt32	kind=GetEventKind(evt);
		switch(kind){
			case kEventWindowDrawContent:
			case kEventWindowUpdate:
				update(false);
				return(true);
				break;
		}
	}
	return(bStdToolPres::event(evt));*/
}


// ---------------------------------------------------------------------------
// 
// -----------
void bToolPrintArea::activate(){
	bStdToolPres::activate();
	switch(_dragmode){
		case kPrintAreaDragModeSet:
			break;
		case kPrintAreaDragModeMove:
			set_curs(_cmove);
			break;
		case kPrintAreaDragModeBottomResize:
			set_curs(_cyresize);
			break;
		case kPrintAreaDragModeRightResize:
			set_curs(_cxresize);
			break;
		case kPrintAreaDragModeFullResize:
			set_curs(_cxyresize);
			break;
		default:
			break;
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolPrintArea::update(bool global){
	if(!global){
		clearTempPathContext(false);
	}
	if(_draw||get_on_drag()){
ivx_rect	vxr=*(_gapp->printMgr()->get_print_area());
		if(ivr_ok(&vxr)){
CGContextRef	ctx=getTempPathContext();
			if(ctx){
CGFloat	dsh[2]={5,5};
				CGContextSaveGState(ctx);
				CGContextSetLineDash(ctx,0,dsh,2);
				hilite_rect(ctx,ivr2cgr(_gapp,vxr),false,true);
				CGContextRestoreGState(ctx);
			}
		}	
	}
	if(!global){
		validTempPathContext();
	}	
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolPrintArea::drag(CGPoint pt){
	set_use_drag(false);
	bStdToolPres::drag(pt);
	set_use_drag(true);
	
i2dvertex	a,b;
ivx_rect	vr=*(_gapp->printMgr()->get_print_area());
ivx_rect	scr;
	_gapp->mapIntf()->screenBounds(&scr);
	
/*	get_clic(&a);
	if(!ivx2_in_ivr(&scr,&a)){
		return;
	}*/
	get_last(&a);
	if(!ivx2_in_ivr(&scr,&a)){
		return;
	}
	get_cur(&a);
	if(!ivx2_in_ivr(&scr,&a)){
		return;
	}
	
	get_last(&a);
	get_cur(&b);
	
	switch(_dragmode){
		case kPrintAreaDragModeSet:
		case kPrintAreaDragModeFullResize:
			get_clic(&a);
			get_last(&b);
			vr.left=(a.h<b.h)?a.h:b.h;
			vr.top=(a.v<b.v)?a.v:b.v;
			vr.right=(a.h>b.h)?a.h:b.h;
			vr.bottom=(a.v>b.v)?a.v:b.v;
			
			break;
		case kPrintAreaDragModeMove:
			vr.left+=(b.h-a.h);
			vr.right+=(b.h-a.h);
			vr.top+=(b.v-a.v);
			vr.bottom+=(b.v-a.v);
			break;
		case kPrintAreaDragModeBottomResize:
			vr.bottom=b.v;
			break;
		case kPrintAreaDragModeRightResize:
			vr.right=b.h;
			break;
		default:
			break;
	}
	
	if(	(is_modifiers(shiftKey)							&&
		(	(_dragmode==kPrintAreaDragModeBottomResize)	||
			(_dragmode==kPrintAreaDragModeRightResize)	))){
			 
ivx_rect	bkvr=*(_gapp->printMgr()->get_print_area());
double		rh=(double)(vr.right-vr.left)/(double)(bkvr.right-bkvr.left);
double		rv=(double)(vr.bottom-vr.top)/(double)(bkvr.bottom-bkvr.top);

		  switch(_dragmode){
			  case kPrintAreaDragModeSet:
			  case kPrintAreaDragModeFullResize:
			  case kPrintAreaDragModeMove:
				  break;
			  case kPrintAreaDragModeBottomResize:
				  vr.right=vr.left+(vr.right-vr.left)*rv;
				  break;
			  case kPrintAreaDragModeRightResize:
				  vr.bottom=vr.top+(vr.bottom-vr.top)*rh;
				  break;
			  default:
				  break;
		  }
	}
	
	_gapp->printMgr()->set_print_area(&vr);
    _vxr=vr;
    
	clearTempPathContext(true);
	update(true);
	validTempPathContext();
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolPrintArea::track_draw(){
	if(!get_active()){
		return;
	}
i2dvertex	b;
ivx_rect	vr=*(_gapp->printMgr()->get_print_area());
	get_cur(&b);

	if(!get_on_drag()){
bGenericUnit*	u=_gapp->scaleMgr()->get();
		
		if(	(_d_(vr.bottom,b.v,u->conv())<3)&&
			(_d_(vr.right,b.h,u->conv())<3)	){
			set_curs(_cxyresize);
		}
		else if((_d_(vr.bottom,b.v,u->conv())<3)&&((vr.left<b.h)&&(b.h<vr.right))){
			set_curs(_cyresize);
		}
		else if((_d_(vr.right,b.h,u->conv())<3)&&((vr.top<b.v)&&(b.v<vr.bottom))){
			set_curs(_cxresize);
		}
		else if((_d_(vr.top,b.v,u->conv())<3)	||
				(_d_(vr.left,b.h,u->conv())<3)	){
			set_curs(_cmove);
		}
		else{
			set_curs();
		}
		return;
	}
}

// ---------------------------------------------------------------------------
//
// -----------
bool bToolPrintArea::edit(void* prm){
_bTrace_("bToolPrintArea::edit",true);
long    result=0;
    
    _vxr=*(_gapp->printMgr()->get_print_area());
    set_on_edit(true);
    runCocoaAppModal(this,&result);
    if(result>0){
        clearTempPathContext(true);
        _gapp->printMgr()->set_print_area(&_vxr);
        update(true);
        validTempPathContext();
        save();
    }
    else{
        load();
        _vxr=*(_gapp->printMgr()->get_print_area());
    }
    set_on_edit(false);
    
    return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolPrintArea::center_to_screen(){
i2dvertex	svx,avx;

	_vxr=*(_gapp->printMgr()->get_print_area());
	ivr_mid(&_vxr,&avx);
	_gapp->mapIntf()->screenCenter(&svx);
	
	_vxr.left+=(svx.h-avx.h);
	_vxr.right+=(svx.h-avx.h);
	_vxr.top+=(svx.v-avx.v);
	_vxr.bottom+=(svx.v-avx.v);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolPrintArea::fit_to_screen(){
	_gapp->mapIntf()->screenBounds(&_vxr);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolPrintArea::fit_to_objs(bArray* arr){	
bGenericGeoElement*	o;
bGenericStyle*		style;
long				j;
CGRect				ro,rg=CGRectZero;
	
	for(long i=1;i<=arr->count();i++){
		arr->get(i,&o);
        for(j=1;j<=_gapp->layersMgr()->count();j++){
            style=_gapp->layersMgr()->get(j);
			if(!style->visible()){
				continue;
			}
			if(style->gettype()==NULL){
				continue;
			}
			if(style->gettype()->index()!=o->getType()){
				continue;
			}
			style->rect(o,&ro);
			if(CGRectIsEmpty(ro)){
				continue;
			}
			if(CGRectIsEmpty(rg)){
				rg=ro;
			}
			else{
				rg=CGRectUnion(rg,ro);
			}
		}
	}
	if(CGRectIsEmpty(rg)){
		return;
	}
	_vxr=cgr2ivr(_gapp,rg);
}

// ---------------------------------------------------------------------------
// 
// -----------
bGenericXMLBaseElement* bToolPrintArea::load(){
bGenericXMLBaseElement* groot=bStdToolPres::load();
bGenericXMLBaseElement* elt=NULL;
	if(!groot){
		if(_gprm){
			delete _gprm;
			_gprm=NULL;
		}
		_gprm=new bToolPrintAreaParams(NULL,_gapp,getbundle());
		return(NULL);
	}
bGenericXMLBaseElement* root=get_param(groot,"private");
	if(!root){
		_gapp->classMgr()->ReleaseXMLInstance(groot);
		if(_gprm){
			delete _gprm;
			_gprm=NULL;
		}
		_gprm=new bToolPrintAreaParams(NULL,_gapp,getbundle());
		return(NULL);
	}
char					val[_values_length_max_];
	for(;;){
		elt=_gapp->classMgr()->NthElement(root,1,"bool");
		if(!elt){
			break;
		}
		elt->getvalue(val);
		_draw=atoi(val);
		
		elt=_gapp->classMgr()->NthElement(root,1,"int");
		if(!elt){
			break;
		}
		elt->getvalue(val);
		_pprnat=atoi(val);
		if((_pprnat<1)||(_pprnat>2)){
			_pprnat=1;
			if(_pprkind==kPrintAreaPopKindMenuStandard){
				_pprkind=kPrintAreaPopKindMenuCustom;
			}
		}
		
		elt=_gapp->classMgr()->NthElement(root,2,"int");
		if(!elt){
			break;
		}
		elt->getvalue(val);
		_pprkind=atoi(val);
		
		
		elt=_gapp->classMgr()->NthElement(root,3,"int");
		if(!elt){
			break;
		}
		elt->getvalue(val);
		_sizekind=atoi(val);
		break;
	}
	
	if(	(_sizekind<kPrintAreaPopKindMenuGeo)		||
		(_sizekind>kPrintAreaPopKindMenuStandard)	){
		_sizekind=1;
	}

	if(	(_pprkind<1)	||
		(_pprkind>_nppr)){
		_pprkind=1;
		if(_sizekind==kPrintAreaPopKindMenuStandard){
			_sizekind=kPrintAreaPopKindMenuCustom;
		}
	}
	
	if((_pprnat<1)||(_pprnat>2)){
		_pprnat=1;
		if(_sizekind==kPrintAreaPopKindMenuStandard){
			_sizekind=kPrintAreaPopKindMenuCustom;
		}
	}
	
	
	root=get_param(groot,"graphic");
	if(_gprm){
		delete _gprm;
		_gprm=NULL;
	}
	_gprm=new bToolPrintAreaParams(root,_gapp,getbundle());

	_gapp->classMgr()->ReleaseXMLInstance(groot);

	
	return(NULL);
}

// ---------------------------------------------------------------------------
// 
// -----------
bGenericXMLBaseElement* bToolPrintArea::make(bArray &arr){
	add_cdesc(arr,0,"param","");
	add_cdesc(arr,1,"version",kCurrentToolParamVers);
	add_cdesc(arr,1,"param","");
	add_cdesc(arr,2,"sign","private");
	add_idesc(arr,2,"bool",_draw);
	add_idesc(arr,2,"int",_pprnat);
	add_idesc(arr,2,"int",_pprkind);
	add_idesc(arr,2,"int",_sizekind);
	return(bStdToolPres::make(arr));
}

#pragma mark =>Graphic params
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bToolPrintAreaParams::bToolPrintAreaParams(bGenericXMLBaseElement* root,
										   bGenericMacMapApp* gapp,
										   CFBundleRef bndl)
					:bGraphicParams(root,gapp){
	if(_status==-1){
		_width=1;
		_stroke[0]=0;
		_stroke[1]=0;
		_stroke[2]=0;
		_stroke[3]=1;
		_fill[0]=0;
		_fill[1]=0;
		_fill[2]=0;
		_fill[3]=0;
	}
	_status=-1;
	_ndash=0;
	_dash=NULL;
	if(root!=NULL){
		parse(root,gapp);
	}
	else{
		root=GetXMLParamFromBundle(gapp,bndl,kStdGraphicParamsToolTraceName);
		if(root!=NULL){
			parse(root,gapp);
			gapp->classMgr()->ReleaseXMLInstance(root);
		}
		else{
			_dash=new CGFloat[2];
			_dash[0]=4;
			_dash[1]=4;
			_ndash=2;
		}
	}
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bToolPrintAreaParams::~bToolPrintAreaParams(){
	if(_dash){
		delete _dash;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bToolPrintAreaParams::update(bArray& arr, 
								  long indent){
	bGraphicParams::update(arr,indent);
	for(long i=0;i<_ndash;i++){
		add_ddesc(arr,indent+1,"float",_dash[i],2);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bToolPrintAreaParams::apply(CGContextRef ctx){
	if(_dash){
		CGContextSetLineDash(ctx,0,_dash,_ndash);
	}
	bGraphicParams::apply(ctx);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bToolPrintAreaParams::setDash(const float* dash, long ndash){
	if(_dash){
		delete _dash;
	}
	_dash=new CGFloat[ndash];
	_ndash=ndash;
}

// ---------------------------------------------------------------------------
// 
// ------------
void bToolPrintAreaParams::parse(bGenericXMLBaseElement* root, bGenericMacMapApp* gapp){
bGenericXMLBaseElement* elt=NULL;
char					val[_values_length_max_];
long					i;
	
	for(i=0;;i++){
		elt=gapp->classMgr()->NthElement(root,i+10,"float");
		if(!elt){
			break;
		}
	}
	_ndash=i;
	_dash=new CGFloat[_ndash];
	for(i=0;i<_ndash;i++){
		elt=gapp->classMgr()->NthElement(root,i+10,"float");
		elt->getvalue(val);
		_dash[i]=matof(val);
	}
	_status=0;
}


