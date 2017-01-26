//----------------------------------------------------------------------------
// File : bXMLInclude.cpp
// Project : MacMap
// Purpose : C++ source file : Include Geog formula class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2006 Carte Blanche Conseil.
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
//----------------------------------------------------------------------------

#include "bXMLInclude.h"

// ---------------------------------------------------------------------------
// 
// ------------
enum{
	kIncludeFully		=0x00000001,
	kIncludeStrictly	=0x00000002,
};

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bIncludeElement	::bIncludeElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				: bStdXMLGeog(elt,gapp,bndl){
	setclassname("include");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bIncludeElement::~bIncludeElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bIncludeElement::create(bGenericXMLBaseElement* elt){
	return(new bIncludeElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bIncludeElement::init(void* ctx){
	_ctx=(bSelectSolver*)ctx;
	bStdXMLGeog::init(ctx);

char val[256];
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
		_full=((k&kIncludeFully)==kIncludeFully);
		_strict=((k&kIncludeStrictly)==kIncludeStrictly);
	}
	else{
		getvalue(val);
int		k=atoi(val);
		_full=((k&kIncludeFully)==kIncludeFully);
		_strict=((k&kIncludeStrictly)==kIncludeStrictly);
	}
	
	_ctx->set_preprocess();
	
bArray*					src=_ctx->get_source();
bGenericGeoIterator*	it=_ctx->get_type()->iterator();	
//bGenericType*			tp;

	for(int i=1;i<=src->count();i++){
		src->get(i,&_ref);
		_ref->getBounds(&_vxr);
		/*tp=_gapp->typesMgr()->get(_ref->getType());
		switch(tp->kind()){
			case kBaseKindPolygon:
			case kBaseKindRaster:*/
				it->iterate(&_vxr,this,process_for_surf);
				/*break;
			case kBaseKindPolyline:
				it->iterate(&_vxr,this,process_for_line);
				break;
		}*/
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
int bIncludeElement::process_for_surf(void* o, void* prm){
bIncludeElement*	gg=(bIncludeElement*)prm;
bGenericGeoElement* geo=(bGenericGeoElement*)o;
ivertices*			vsa;
ivertices*			vsb;
ivx_rect			vr;

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
	geo->getBounds(&vr);
	if(!ivr_sect(&gg->_vxr,&vr,&vr)){
		return(0);
	}
	
	gg->_ref->getVertices(&vsa);
	
	if(gg->_full){
		for(int i=0;i<vsa->nv;i++){
			if(!ivx_in_ivs(&vsa->vx.vx2[i],vsb,!gg->_strict)){
				return(0);
			}
		}
		gg->_ctx->valid_object(geo);
	}
	else{
		for(int i=0;i<vsa->nv;i++){
			if(ivx_in_ivs(&vsa->vx.vx2[i],vsb,!gg->_strict)){
				gg->_ctx->valid_object(geo);
				return(0);
			}
		}
	}
	return(0);
}

// ---------------------------------------------------------------------------
// 
// -----------
int bIncludeElement::process_for_line(void* o, void* prm){
bIncludeElement*	gg=(bIncludeElement*)prm;
bGenericGeoElement* geo=(bGenericGeoElement*)o;
ivertices*			vsa;
ivertices*			vsb;
ivx_rect			vr;
int					idx1,idx2;

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
	geo->getBounds(&vr);
	if(!ivr_sect(&gg->_vxr,&vr,&vr)){
		return(0);
	}
	
	gg->_ref->getVertices(&vsa);
	
	if(gg->_full){
		for(int i=0;i<vsa->nv;i++){
			idx2=ivx2_exists(vsb,&vsa->vx.vx2[i]);
			if(!idx2){
				return(0);
			}
			if(gg->_strict){
				if(i==0){
					idx1=idx2;
				}
				else if(idx1>idx2){
					return(0);
				}
			}
		}
		gg->_ctx->valid_object(geo);
	}
	else{
		idx1=0;
		for(int i=0;i<vsa->nv;i++){
			idx2=ivx2_exists(vsb,&vsa->vx.vx2[i]);
			if(idx1==0){
				idx1=idx2;
			}
			if(idx1&&idx2){
				if(gg->_strict){
					if(idx1>idx2){
						return(0);
					}
					if(idx1<idx2){
						gg->_ctx->valid_object(geo);
						return(0);
					}	
				}
				else{
					if(idx1!=idx2){
						gg->_ctx->valid_object(geo);
						return(0);
					}
				}
			}
		}
	}
	return(0);
}
