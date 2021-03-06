//----------------------------------------------------------------------------
// File : bXMapTranslation.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, translate selected geometries in x and y
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
// 19/10/2005 creation.
// 22/07/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapTranslation.h"
#include "CocoaStuff.h"

#include <mox_intf/bEventLog.h>
#include <mox_intf/ext_utils.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapTranslation	::bXMapTranslation(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
					:bStdXMap(elt,gapp,bndl){
	setclassname("translation");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapTranslation::~bXMapTranslation(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapTranslation::create(bGenericXMLBaseElement* elt){
	return(new bXMapTranslation(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapTranslation::open(int* flags){	
	bStdXMap::open(flags);
	_prm.x=0;
	_prm.y=0;
	_prm.kind=kXMapTranslationWithOffset;
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapTranslation::process(int msg, void* prm){
	switch(msg){
		case kExtProcessCallFromIntf:
			switch(_prm.kind){
				case kXMapTranslationWithOffset:
					return(translation_with_offset());
					break;
				case kXMapTranslationToCoord:
					return(translation_to_coord());
					break;
			}
			break;
		case kExtProcessCallWithParams:{
translation_prm* p=(translation_prm*)prm;
				switch(p->kind){
					case kXMapTranslationWithOffset:
						return(translation_with_offset(p->x,p->y));
						break;
					case kXMapTranslationToCoord:
						return(translation_to_coord(p->x,p->y));
						break;
				}
			}
			break;
		case kExtProcessCallWithXMLTree:{
translation_prm			p;
char					val[_values_length_max_];
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
				p.kind=atoi(val);
					
				switch(p.kind){
					case kXMapTranslationWithOffset:
						return(translation_with_offset(p.x,p.y));
						break;
					case kXMapTranslationToCoord:
						return(translation_to_coord(p.x,p.y));
						break;
					}			
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
bool bXMapTranslation::test(void* prm){
	return(_gapp->selMgr()->count()>0);
}

// ---------------------------------------------------------------------------
//
// ------------
bool bXMapTranslation::edit(void* prm){
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
bool bXMapTranslation::translation_with_offset(){
bEventLog	log(_gapp,this);
	translation_with_offset(_prm.x,_prm.y);
	log.close();
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapTranslation::translation_with_offset(double dx, double dy){
d2dvertex			dvx={dx,dy};
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
		ivs_move(vxs,ivx.h,ivx.v);
		o->setVertices(vxs);
	}
	_gapp->layersMgr()->SetObjInvalidation(true);
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapTranslation::translation_to_coord(){
bEventLog	log(_gapp,this);
	(void)translation_to_coord(_prm.x,_prm.y);
	log.close();
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapTranslation::translation_to_coord(double dx, double dy){
d2dvertex			dvx={dx,dy};
i2dvertex			ivx;
ivertices*			vxs;
bGenericGeoElement*	o;
int					dh,dv;

	_gapp->locConverter()->convert(&ivx,&dvx);
	for(int i=1;i<=_gapp->selMgr()->count();i++){
		_gapp->selMgr()->elements()->get(i,&o);
		o->inval(kOBJ_Vertices_);
		o->getVertices(&vxs);
		dh=ivx.h-vxs->vx.vx2[0].h;
		dv=ivx.v-vxs->vx.vx2[0].v;
		ivs_move(vxs,dh,dv);
		o->setVertices(vxs);
	}
	return(true);
}
