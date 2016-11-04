//----------------------------------------------------------------------------
// File : bXMLFarthest.cpp
// Project : MacMap
// Purpose : C++ source file : Farthest Geog formula class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2008 Carte Blanche Conseil.
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
// 03/12/2008 creation.
//----------------------------------------------------------------------------

#include "bXMLFarthest.h"
#include <MacMapSuite/bTrace.h>
#include <MacMapSuite/vx_lib.h>

// ---------------------------------------------------------------------------

typedef struct odist{
	bGenericGeoElement*	o;
	int					dmin;
}odist;

// ---------------------------------------------------------------------------
// Constructeur
// ------------
static int odist_comp(const void* a, const void* b){
	if(((odist*)a)->dmin<((odist*)b)->dmin){
		return(1);
	}
	if(((odist*)b)->dmin<((odist*)a)->dmin){
		return(-1);
	}
	return(0);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bFarthestElement	::bFarthestElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				:bStdXMLGeog(elt,gapp,bndl){
	setclassname("farthest");
	_nb=0;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bFarthestElement::~bFarthestElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bFarthestElement::create(bGenericXMLBaseElement* elt){
	return(new bFarthestElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bFarthestElement::init(void* ctx){
	bStdXMLGeog::init(ctx);	
char					val[_values_length_max_];
bGenericXMLBaseElement* elt=getelement(1);
	if(elt){
		elt->getvalue(val);
	}
	else{
		getvalue(val);
	}
	_nb=atoi(val);
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bFarthestElement::reset(bStdSolver* ctx){
bSelectSolver*			_ctx=(bSelectSolver*)(void*)ctx;
bArray*					src=_ctx->get_source();
bArray*					prc=_ctx->get_processed();
bArray					arr(sizeof(odist));
bGenericGeoElement*		ref;
bGenericGeoElement*		geo;
ivertices*				vsa;
ivertices*				vsb;
odist					od;
double					d;

	for(int i=prc->count();i>0;i--){
		prc->get(i,&geo);
		if(_ctx->get_source_kind()==kSrcObj){
			if(geo==_ctx->get_object()){
				_ctx->inval_object(i);
				continue;
			}
		}
		if(geo->selected()){
			if(_ctx->get_source_kind()==kSrcSel){
				_ctx->inval_object(i);
				continue;
			}
		}
		if(geo->contrasted()){
			if(_ctx->get_source_kind()==kSrcCnt){
				_ctx->inval_object(i);
				continue;
			}
		}		
		geo->getVertices(&vsa);
		od.o=geo;
		od.dmin=LONG_MAX;
		for(int j=1;j<=src->count();j++){
			src->get(j,&ref);
			ref->getVertices(&vsb);
			d=vxs_dist(vsa,vsb);
			if(d<=od.dmin){
				od.dmin=d;
				break;
			}
		}
		arr.add(&od);
	}
	arr.sort(odist_comp);
	for(int i=arr.count();i>0;i--){
		_ctx->inval_object(i);
	}
	for(int i=1;i<=_nb;i++){
		arr.get(i,&od);
		_ctx->valid_object(od.o);
	}
	bStdXMLGeog::reset(ctx);
}

