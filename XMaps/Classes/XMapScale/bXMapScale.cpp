//----------------------------------------------------------------------------
// File : bXMapScale.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, scale selected geometries by factor
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
// 07/11/2005 creation.
// 21/07/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapScale.h"
#include "CocoaStuff.h"

#include <mox_intf/bEventLog.h>
#include <mox_intf/ext_utils.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapScale	::bXMapScale(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
            :bStdXMap(elt,gapp,bndl){
	setclassname("scale");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapScale::~bXMapScale(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapScale::create(bGenericXMLBaseElement* elt){
	return(new bXMapScale(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapScale::open(int* flags){	
	bStdXMap::open(flags);
	_prm.x=0;
	_prm.y=0;
	_prm.cx=1;
	_prm.cy=1;
//	_kind=kXMapScaleOnSelf;
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapScale::process(int msg, void* prm){
	switch(msg){
		case kExtProcessCallFromIntf:
			return(scale());
			break;
		case kExtProcessCallWithParams:{
scale_prm* p=(scale_prm*)prm;
			return(scale(p->x,p->y,p->cx,p->cy));
			}break;
		case kExtProcessCallWithXMLTree:{
scale_prm				p;
char					val[_values_length_max_];
int                     ival;
bGenericXMLBaseElement*	elt;
				elt=getelement(1);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				p.x=atof(val);

				elt=getelement(2);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				p.y=atof(val);

				elt=getelement(3);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				p.cx=atof(val);
					
				elt=getelement(4);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				p.cy=atof(val);
					
				ival=kXMapScaleOnCoord;
				elt=getelement(5);
				if(elt){
					elt->getvalue(val);
					ival=atoi(val);
				}
                if(ival==kXMapRotationOnSelf){
i2dvertex			ivx;
d2dvertex			dvx;
                    center(&ivx);
                    _gapp->locConverter()->convert(&dvx,&ivx);
                    p.x=dvx.x;
                    p.y=dvx.y;
                }

				return(scale(p.x,p.y,p.cx,p.cy));
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
bool bXMapScale::test(void* prm){
	return(_gapp->selMgr()->count()>0);
}

// ---------------------------------------------------------------------------
//
// ------------
bool bXMapScale::edit(void* prm){
long    result=0;
    runCocoaAppModal(this,&result);
    if(result>0){
        return(process(kExtProcessCallFromIntf,prm));
    }
    return(false);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapScale::scale(){
bEventLog	log(_gapp,this);
	(void)scale(_prm.x,_prm.y,_prm.cx,_prm.cy);
	log.close();
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapScale::scale(double x, double y, double cx, double cy){
d2dvertex			dvx={x,y};
i2dvertex			ivx;
ivertices*			vxs;
bGenericGeoElement*	o;
bArray				sel(*(_gapp->selMgr()->elements()));

	_gapp->locConverter()->convert(&ivx,&dvx);
	_gapp->layersMgr()->SetObjInvalidation(false);
	for(int i=1;i<=sel.count();i++){
		sel.get(i,&o);
		o->inval(kOBJ_Vertices_);
		o->getVertices(&vxs);
		ivs_scale_anchor(vxs,cx,cy,&ivx);
		o->setVertices(vxs);
	}
	_gapp->layersMgr()->SetObjInvalidation(true);
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapScale::center(i2dvertex* c){
bGenericGeoElement*	o;
ivx_rect			vr,bounds;
	_gapp->selMgr()->elements()->get(1,&o);
	o->getBounds(&bounds);
	for(int i=2;i<=_gapp->selMgr()->count();i++){
		_gapp->selMgr()->elements()->get(i,&o);
		o->getBounds(&vr);
		ivr_union(&vr,&bounds,&bounds);
	}
	ivr_mid(&bounds,c);
}

