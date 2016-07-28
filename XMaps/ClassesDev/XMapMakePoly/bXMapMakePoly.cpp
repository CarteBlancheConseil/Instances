//----------------------------------------------------------------------------
// File : bXMapMakePoly.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, create new polygon
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
// 04/07/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapMakePoly.h"
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
bXMapMakePoly	::bXMapMakePoly(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				:bStdXMap(elt,gapp,bndl){
	setclassname("makepoly2");
                    
char	name[FILENAME_MAX];
GetName(this,name);
(void)_gapp->menuMgr()->add_item(kMenuMgrMenuPalettesID,name,GetSignature(this));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapMakePoly::~bXMapMakePoly(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapMakePoly::create(bGenericXMLBaseElement* elt){
	return(new bXMapMakePoly(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapMakePoly::open(int* flags){	
	bStdXMap::open(flags);
	_prm.justo=0;
	_prm.o.x=0;
	_prm.o.y=0;
	_prm.nb=5;
	_prm.sz=100;
	_prm.tp=NULL;
	_prm.sui=0;
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapMakePoly::process(int msg, void* prm){
	switch(msg){
		case kExtProcessCallFromIntf:
			return(make());
			break;
		case kExtProcessCallWithParams:{
makepoly_prm* p=(makepoly_prm*)prm;
				return(make(p->tp,&p->o,p->sz,p->nb,p->sui,p->justo));
			}
			break;
		case kExtProcessCallWithXMLTree:{
makepoly_prm			p;
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
				p.sz=atof(val);
				
				elt=getelement(5);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				p.nb=atoi(val);

				elt=getelement(6);
				if(elt){
					elt->getvalue(val);
					p.sui=atoi(val);
				}
				else{
					p.sui=0;
				}
			
				return(make(p.tp,&p.o,p.sz,p.nb,p.sui,p.justo));
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
bool bXMapMakePoly::test(void* prm){
	_prm.tp=(bGenericType*)CurType(_gapp);
	if(!_prm.tp){
		return(false);
	}
	if(	(_prm.tp->kind()!=kBaseKindPolyline)	&&
		(_prm.tp->kind()!=kBaseKindPolygon)		){
		return(false);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapMakePoly::edit(void* prm){
_bTrace_("bXMapMakePoly::edit()",true);
makepoly_prm p=_prm;
	if(prm){
		_prm=(*(makepoly_prm*)prm);			
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
bool bXMapMakePoly::make(){
	if(!_prm.tp){
		return(true);
	}
bEventLog	log(_gapp,this);
	(void)make(_prm.tp,&_prm.o,_prm.sz,_prm.nb,_prm.sui,_prm.justo);
	log.close();
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapMakePoly::make(bGenericType* tp, d2dvertex* o, double r, int n, int sui, int justo){
_bTrace_("bXMapMakePoly::make",false);
double		a,a0;
	
	if(n&0x00000001){
		a0=M_PI/2.0;
	}
	else{
		a0=M_PI/2.0+M_PI/n;
	}

	if(sui==1){
bGenericUnit*	scl=_gapp->scaleMgr()->get();
double			c=0.01/GetRawPrecisionCoef(_gapp)*scl->coef();
		c*=GetPrecisionCoef(_gapp);
		r*=c;
	}
	
	if(justo==2){
		o->x+=r;
		o->y-=r;
	}
	
ivertices*	vxs=ivs_new(_2D_VX,0,0);
i2dvertex	ivx;
d2dvertex	dvx;

	for(int i=0;i<n;i++){
		a=a0-i*2.0*M_PI/(double)n;
		dvx.x=o->x+r*cos(a);
		dvx.y=o->y+r*sin(a);
		_gapp->locConverter()->convert(&ivx,&dvx);
		if((vxs->nv>0)&&(eq_ivx2(&vxs->vx.vx2[vxs->nv-1],&ivx))){
			continue;
		}
		vxs=ivx2_add(vxs,&ivx);
		if(!vxs){
			return(false);
		}
	}
	if(!eq_ivx2(&vxs->vx.vx2[0],&vxs->vx.vx2[vxs->nv-1])){
		ivx=vxs->vx.vx2[0];
		vxs=ivx2_add(vxs,&ivx);
	}
	if(!vxs){
		return(false);
	}
	if(vxs->nv<4){
		ivs_free(vxs);
		return(false);
	}
bGenericGeoElement*	go;
	if(!tp->new_object(&go)){
_te_("new_object");
		ivs_free(vxs);
		return(false);
	}
	if(!InitWithStyle(_gapp,_gapp->layersAccessCtx()->get_current(),go)){
		MMBeep();
	}
	if(!go->setVertices(vxs)){
_te_("setVertices");
		tp->kill_object(go);
		ivs_free(vxs);
		return(false);
	}
	ivs_free(vxs);
	return(true);
}
