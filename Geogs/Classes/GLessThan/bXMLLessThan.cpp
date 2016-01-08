//----------------------------------------------------------------------------
// File : bXMLLessThan.cpp
// Project : MacMap
// Purpose : C++ source file : Less than Geog formula class
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
// 26/01/2005 creation.
//----------------------------------------------------------------------------

#include "bXMLLessThan.h"
#include <MacMapSuite/vx_lib.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bLessThanElement	::bLessThanElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
					: bStdXMLGeog(elt,gapp,bndl){
	setclassname("lessthan");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bLessThanElement::~bLessThanElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bLessThanElement::create(bGenericXMLBaseElement* elt){
	return(new bLessThanElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bLessThanElement::init(void* ctx){
	_ctx=(bSelectSolver*)ctx;
	bStdXMLGeog::init(ctx);	
char					val[_values_length_max_];
bGenericXMLBaseElement* elt=getelement(1);
	if(elt){
		elt->getvalue(val);
	}
	else{
		getvalue(val);
	}
	_dst=atof(val);
	_ctx->set_preprocess();
bArray*					src=_ctx->get_source();
bGenericGeoIterator*	it=_ctx->get_type()->iterator();	
	for(int i=1;i<=src->count();i++){
		src->get(i,&_ref);
		_ref->getBounds(&_vxr);
		_vxr.top-=round(_dst);
		_vxr.left-=round(_dst);
		_vxr.bottom+=round(_dst);
		_vxr.right+=round(_dst);
		it->iterate(&_vxr,this,process);
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
int bLessThanElement::process(void* o, void* prm){
bLessThanElement*	gg=(bLessThanElement*)prm;
bGenericGeoElement* geo=(bGenericGeoElement*)o;
ivertices*			vsa;
ivertices*			vsb;
ivx_rect			vxr;

//time_t	t1=time(NULL);
//fprintf(stderr,"%d\n",t1);
	
	if(geo->flag1()){
		return(0);
	}
	if(gg->_ctx->get_source_kind()==kSrcObj){
		if(geo==gg->_ctx->get_object()){
			return(0);
		}
	}
	if(geo->selected()){
		if(gg->_ctx->get_source_kind()==kSrcSel){
			return(0);
		}
	}
	if(geo->contrasted()){
		if(gg->_ctx->get_source_kind()==kSrcCnt){
			return(0);
		}
	}
	geo->getBounds(&vxr);
	if(!ivr_sect(&vxr,&gg->_vxr,&vxr)){
		return(0);
	}
	gg->_ref->getVertices(&vsa);
	geo->getVertices(&vsb);
	if(vxs_dist(vsa,vsb)<gg->_dst){
		gg->_ctx->valid_object(geo);
	}

	return(0);
}
