//----------------------------------------------------------------------------
// File : bXMLOutside.cpp
// Project : MacMap
// Purpose : C++ source file : Outside Geog formula class
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

#include "bXMLOutside.h"
#include <MacMapSuite/vx_lib.h>

// ---------------------------------------------------------------------------
// 
// ------------
enum{
	kOutsideFully		=0x00000001,
	kOutsideStrictly	=0x00000002,
};

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bOutsideElement	::bOutsideElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
					: bStdXMLGeog(elt,gapp,bndl){
	setclassname("outside");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bOutsideElement::~bOutsideElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bOutsideElement::create(bGenericXMLBaseElement* elt){
	return(new bOutsideElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bOutsideElement::init(void* ctx){
	bStdXMLGeog::init(ctx);
char					val[_values_length_max_];	
bGenericXMLBaseElement* elt1=getelement(1);
bGenericXMLBaseElement* elt2=getelement(2);
	if((elt1)&&(elt1)){
		elt1->getvalue(val);
		_full=atoi(val);
		elt2->getvalue(val);
		_strict=atoi(val);
	}
	else if(elt1){
		elt1->getvalue(val);
int		k=atoi(val);
		_full=((k&kOutsideFully)==kOutsideFully);
		_strict=((k&kOutsideStrictly)==kOutsideStrictly);
	}
	else{
		getvalue(val);
int		k=atoi(val);
		_full=((k&kOutsideFully)==kOutsideFully);
		_strict=((k&kOutsideStrictly)==kOutsideStrictly);
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bOutsideElement::reset(bStdSolver* ctx){
bSelectSolver*			_ctx=(bSelectSolver*)(void*)ctx;
bArray*					src=_ctx->get_source();
bArray*					prc=_ctx->get_processed();
bGenericGeoElement*		ref;
bGenericGeoElement*		geo;
ivertices*				vsa;
ivertices*				vsb;
	
	if(_full){
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
			for(int j=1;j<=src->count();j++){
				src->get(j,&ref);
				ref->getVertices(&vsb);
				for(int k=0;k<vsa->nv;k++){
					if(ivx_in_ivs(&vsa->vx.vx2[k],vsb,!_strict)){
						_ctx->inval_object(i);
						break;
					}
				}
			}
		}		
	}
	else{
bool	keep;
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
			for(int j=1;j<=src->count();j++){
				keep=false;
				src->get(j,&ref);
				ref->getVertices(&vsb);
				for(int k=0;k<vsa->nv;k++){
					if(!ivx_in_ivs(&vsa->vx.vx2[k],vsb,!_strict)){
						keep=true;
						break;
					}
				}
				if(!keep){
					_ctx->inval_object(i);
				}
			}
		}	
	}
	bStdXMLGeog::reset(ctx);
}

