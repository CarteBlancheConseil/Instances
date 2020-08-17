//----------------------------------------------------------------------------
// File : bXMLTo.cpp
// Project : MacMap
// Purpose : C++ source file : To Geog formula class
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
// 30/05/2008 creation.
//----------------------------------------------------------------------------

#include "bXMLTo.h"
#include <MacMapSuite/vx_lib.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bToElement	::bToElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				: bStdXMLGeog(elt,gapp,bndl){
	setclassname("to");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bToElement::~bToElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bToElement::create(bGenericXMLBaseElement* elt){
	return(new bToElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bToElement::init(void* ctx){
	_ctx=(bSelectSolver*)ctx;
	bStdXMLGeog::init(ctx);
	
	_ctx->set_preprocess();
	
bArray*					src=_ctx->get_source();
bGenericGeoIterator*	it=_ctx->get_type()->iterator();	
bGenericGeoElement*		o;	
ivertices*				vxs;
i2dvertex*				vxp;
int						i,j,k,np,nv;

	for(i=1;i<=src->count();i++){
		src->get(i,&o);
		o->getVertices(&vxs);
		np=ivs_n_parts(vxs);
		for(j=0;j<np;j++){
			vxp=ivs2_part(vxs,j,&nv);
			for(k=0;k<nv;k++){
				_vx=vxp[k];
				it->iterate(&_vx,this,process);
			}
		}
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
int bToElement::process(void* o, void* prm){
bToElement*		    gg=(bToElement*)prm;
bGenericGeoElement* geo=(bGenericGeoElement*)o;
ivertices*			vsb;
i2dvertex*			vxp;
int					i,np,nv;
	
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

	np=ivs_n_parts(vsb);
	for(i=0;i<np;i++){
		vxp=ivs2_part(vsb,i,&nv);
		if(eq_ivx2(&(gg->_vx),&vxp[nv-1])){
			gg->_ctx->valid_object(geo);
		}
	}
		
	return(0);
}
