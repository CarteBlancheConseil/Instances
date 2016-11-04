//----------------------------------------------------------------------------
// File : bXMapMakeRect.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, create new rectangle
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
// 15/03/2006 creation.
// 05/07/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapMakeRect.h"
#include "CocoaStuff.h"

#include <mox_intf/bEventLog.h>
#include <mox_intf/Carb_Utils.h>
#include <mox_intf/ext_Utils.h>
#include <mox_intf/MacMapCWrappers.h>
#include <mox_intf/NSCursorWrappers.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapMakeRect	::bXMapMakeRect(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				:bStdXMap(elt,gapp,bndl){
	setclassname("makerect");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapMakeRect::~bXMapMakeRect(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapMakeRect::create(bGenericXMLBaseElement* elt){
	return(new bXMapMakeRect(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapMakeRect::open(int* flags){	
	bStdXMap::open(flags);
	_prm.justo=0;
	_prm.o.x=0;
	_prm.o.y=0;
	_prm.w=100;
	_prm.h=100;
	_prm.tp=NULL;
	_prm.sui=0;
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapMakeRect::process(int msg, void* prm){
	switch(msg){
		case kExtProcessCallFromIntf:
			return(make());
			break;
		case kExtProcessCallWithParams:{
makerect_prm* p=(makerect_prm*)prm;
			return(make(p->tp,&p->o,p->w,p->h,p->sui,p->justo));
			}break;
		case kExtProcessCallWithXMLTree:{
makerect_prm			p;
char					val[_values_length_max_];
bGenericXMLBaseElement*	elt;
				p.justo=0;
				elt=getelement(1);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				p.tp=_gapp->typesMgr()->get(_gapp->typesMgr()->index(val));
				if(!p.tp){
					return(false);
				}
				elt=getelement(2);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				p.o.x=atof(val);
				
				elt=getelement(3);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				p.o.y=atof(val);
				
				elt=getelement(4);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				p.w=atof(val);
				
				elt=getelement(5);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				p.h=atoi(val);

				elt=getelement(6);
				if(elt){
					elt->getvalue(val);
					p.sui=atoi(val);
				}
				else{
					p.sui=0;
				}
			
				return(make(p.tp,&p.o,p.w,p.h,p.sui,p.justo));
			}	
			break;
		default:
			break;
	}
	return(false);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapMakeRect::test(void* prm){
	_prm.tp=(bGenericType*)CurType(_gapp);
	if(!_prm.tp){
		return(false);
	}
	if(	(_prm.tp->kind()!=kBaseKindPolyline)	&&
		(_prm.tp->kind()!=kBaseKindPolygon)		&&
		(_prm.tp->kind()!=kBaseKindRaster)		){
		return(false);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapMakeRect::edit(void* prm){
makerect_prm p=_prm;
	if(prm){
		_prm=(*(makerect_prm*)prm);			
	}
long    result=0;
    runCocoaAppModal(this,&result);
    if(result>0){
        process(kExtProcessCallFromIntf,prm);
    }
	if(prm){
		_prm=p;
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapMakeRect::make(){
	if(!_prm.tp){
		return(true);
	}
bEventLog	log(_gapp,this);
	(void)make(_prm.tp,&_prm.o,_prm.w,_prm.h,_prm.sui,_prm.justo);
	log.close();
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapMakeRect::make(bGenericType* tp, d2dvertex* dvx, double w, double h, int sui, int justo){
_bTrace_("bXMapMakeRect::make",false);
ivertices*	vxs=ivs_new(_2D_VX,5,0);
	if(!vxs){
_te_("ivs_new");
		return(false);
	}
	
_tm_("sui="+sui+" w="+w+" h="+h);
	if(sui==1){
bGenericUnit*	scl=_gapp->scaleMgr()->get();
double			c=0.01/GetRawPrecisionCoef(_gapp)*scl->coef();
		c*=GetPrecisionCoef(_gapp);
		w*=c;
		h*=c;
	}
	
	if(justo==2){
		dvx->x+=(w/2.0);
		dvx->y-=(h/2.0);
	}
	
	dvx->x-=(w/2);
	dvx->y-=(h/2);
	_gapp->locConverter()->convert(&(vxs->vx.vx2[0]),dvx);
	dvx->y+=h;
	_gapp->locConverter()->convert(&(vxs->vx.vx2[1]),dvx);
	dvx->x+=w;
	_gapp->locConverter()->convert(&(vxs->vx.vx2[2]),dvx);
	dvx->y-=h;
	_gapp->locConverter()->convert(&(vxs->vx.vx2[3]),dvx);
	vxs->vx.vx2[4]=vxs->vx.vx2[0];

bGenericGeoElement*	o;
	if(!tp->new_object(&o)){
_te_("new_object");
		ivs_free(vxs);
		return(false);
	}
	if(!InitWithStyle(_gapp,_gapp->layersAccessCtx()->get_current(),o)){
		MMBeep();
	}
	if(!o->setVertices(vxs)){
_te_("setVertices");
		tp->kill_object(o);
		ivs_free(vxs);
		return(false);
	}
	ivs_free(vxs);
	return(true);
}
