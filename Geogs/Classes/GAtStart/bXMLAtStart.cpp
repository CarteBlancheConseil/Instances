//----------------------------------------------------------------------------
// File : bXMLAtStart.cpp
// Project : MacMap
// Purpose : C++ source file : At start Geog formula class
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
// 28/02/2007 creation.
//----------------------------------------------------------------------------

#include "bXMLAtStart.h"
#include <MacMapSuite/vx_lib.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bAtStartElement	::bAtStartElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				: bStdXMLGeog(elt,gapp,bndl){
	setclassname("atstart");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bAtStartElement::~bAtStartElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bAtStartElement::create(bGenericXMLBaseElement* elt){
	return(new bAtStartElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bAtStartElement::init(void* ctx){
	_ctx=(bSelectSolver*)ctx;
	bStdXMLGeog::init(ctx);
	
	_ctx->set_preprocess();
	
bArray*					src=_ctx->get_source();
bGenericGeoIterator*	it=_ctx->get_type()->iterator();	
bGenericGeoElement*		o;	
ivertices*				vxs;
i2dvertex*				vxp;
int						i,j,np,nv;

	for(i=1;i<=src->count();i++){
		src->get(i,&o);
		o->getVertices(&vxs);
		np=ivs_n_parts(vxs);
		for(j=0;j<np;j++){
			vxp=ivs2_part(vxs,j,&nv);
			_vx=vxp[0];
			it->iterate(&_vx,this,process);
		}
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
int bAtStartElement::process(void* o, void* prm){
bAtStartElement*	gg=(bAtStartElement*)prm;
bGenericGeoElement* geo=(bGenericGeoElement*)o;
ivertices*			vsb;
	
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

	geo->getVertices(&vsb);
	
	for(int i=0;i<vsb->nv;i++){
		if(ivx2_exists(vsb,&gg->_vx)){
			gg->_ctx->valid_object(geo);
		}
	}
	
	return(0);
}
