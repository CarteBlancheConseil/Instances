//----------------------------------------------------------------------------
// File : bXMapRotation.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, rotate selected geometries with angle
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
// 05/07/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapRotation.h"
#include "CocoaStuff.h"

#include <mox_intf/bEventLog.h>
#include <mox_intf/ext_utils.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapRotation	::bXMapRotation(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				:bStdXMap(elt,gapp,bndl){
	setclassname("rotation2");
               
char	name[FILENAME_MAX];
GetName(this,name);
(void)_gapp->menuMgr()->add_item(kMenuMgrMenuPalettesID,name,GetSignature(this));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapRotation::~bXMapRotation(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapRotation::create(bGenericXMLBaseElement* elt){
	return(new bXMapRotation(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapRotation::open(int* flags){	
	bStdXMap::open(flags);
    _prm.rad=0;
    _prm.x=0;
	_prm.y=0;
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapRotation::process(int msg, void* prm){
	switch(msg){
		case kExtProcessCallFromIntf:
			return(rotate());
			break;
		case kExtProcessCallWithParams:{
rotation_prm* p=(rotation_prm*)prm;
			return(rotate(p->x,p->y,p->rad));
			}break;
		case kExtProcessCallWithXMLTree:{
rotation_prm			p;
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
				p.rad=deg2rad(atof(val));
					
				ival=kXMapRotationDir;
				elt=getelement(4);
				if(elt){
					elt->getvalue(val);
					ival=atoi(val);
				}
                if(ival==kXMapRotationDir){
                    p.rad=-p.rad;
                }
            
				ival=kXMapRotationOnCoord;
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
            
				return(rotate(p.x,p.y,p.rad));
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
bool bXMapRotation::test(void* prm){
	return(_gapp->selMgr()->count()>0);
}

// ---------------------------------------------------------------------------
//
// ------------
bool bXMapRotation::edit(void* prm){
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
bool bXMapRotation::rotate(){
bEventLog	log(_gapp,this);
	(void)rotate(_prm.x,_prm.y,_prm.rad);
	log.close();
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapRotation::rotate(double x, double y, double rad){
d2dvertex			dvx={x,y};
i2dvertex			ivx;
ivertices*			vxs;
bGenericGeoElement*	o;
bArray				sel(*(_gapp->selMgr()->elements()));

	_gapp->layersMgr()->SetObjInvalidation(false);	
	_gapp->locConverter()->convert(&ivx,&dvx);
	for(long i=1;i<=sel.count();i++){
		sel.get(i,&o);
		o->inval(kOBJ_Vertices_);
		o->getVertices(&vxs);
		ivs_rotate_anchor(vxs,rad,&ivx);
		o->setVertices(vxs);
	}
	_gapp->layersMgr()->SetObjInvalidation(true);
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapRotation::center(i2dvertex* c){
bGenericGeoElement*	o;
ivx_rect			vr,bounds;
	_gapp->selMgr()->elements()->get(1,&o);
	o->getBounds(&bounds);
	for(long i=2;i<=_gapp->selMgr()->count();i++){
		_gapp->selMgr()->elements()->get(i,&o);
		o->getBounds(&vr);
		ivr_union(&vr,&bounds,&bounds);
	}
	ivr_mid(&bounds,c);
}
