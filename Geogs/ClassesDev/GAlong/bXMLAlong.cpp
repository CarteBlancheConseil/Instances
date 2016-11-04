//----------------------------------------------------------------------------
// File : bXMLAlong.cpp
// Project : MacMap
// Purpose : C++ source file : Along Geog formula class
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
// 07/11/2006 creation.
//----------------------------------------------------------------------------

#include "bXMLAlong.h"
#include <MacMapSuite/vx_lib.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
enum{
	kAlongFully		=0x00000001,
	kAlongStrictly	=0x00000002,
};

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bAlongElement	::bAlongElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
					: bStdXMLGeog(elt,gapp,bndl){
	setclassname("along");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bAlongElement::~bAlongElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bAlongElement::create(bGenericXMLBaseElement* elt){
	return(new bAlongElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bAlongElement::init(void* ctx){
	_ctx=(bSelectSolver*)ctx;
	bStdXMLGeog::init(ctx);
	
char val[256];
bGenericXMLBaseElement* elt1=getelement(1);
bGenericXMLBaseElement* elt2=getelement(2);
bGenericXMLBaseElement* elt3=getelement(3);
	if((elt1)&&(elt2)&&(elt3)){
		elt1->getvalue(val);
		_full=atoi(val);
		elt2->getvalue(val);
		_strict=atoi(val);
		elt3->getvalue(val);
		_dst=atof(val);
	}
	else if((elt1)&&(elt2)){
		elt1->getvalue(val);
		_full=atoi(val);
		elt2->getvalue(val);
		_strict=atoi(val);
		elt3->getvalue(val);
		_dst=_strict?0:__FUZZY_DIST__;
	}
	else if(elt1){
		elt1->getvalue(val);
int		k=atoi(val);
		_full=((k&kAlongFully)==kAlongFully);
		_strict=((k&kAlongStrictly)==kAlongStrictly);
	}
	else{
		getvalue(val);
int		k=atoi(val);
		_full=((k&kAlongFully)==kAlongFully);
		_strict=((k&kAlongStrictly)==kAlongStrictly);
		_dst=_strict?0:__FUZZY_DIST__;
	}

	_ctx->set_preprocess();
	
bArray*					src=_ctx->get_source();
bGenericGeoIterator*	it=_ctx->get_type()->iterator();	

	for(int i=1;i<=src->count();i++){
		src->get(i,&_ref);
		_ref->getBounds(&_vxr);
		it->iterate(&_vxr,this,process);
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
int bAlongElement::process(void* o, void* prm){
//_bTrace_("bAlongElement::process",false);
bAlongElement*		gg=(bAlongElement*)prm;
bGenericGeoElement* geo=(bGenericGeoElement*)o;
ivertices*			vsa;
ivertices*			vsb;
double				dk;
int					k=0;
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

//_tm_("---------------------------------------------------------------------------");
//_tm_(geo->getID());
    
	for(long i=0;i<vsb->nv;i++){
        if(i>0&&eq_ivx2(&vsb->vx.vx2[i],&vsb->vx.vx2[i-1])){
//_tm_("case 1 on "+(int)i);
            continue;
        }
		dk=ivx2ivs_dist(&vsb->vx.vx2[i],vsa);
		if(dk>gg->_dst){
			if(gg->_full){
				break;
			}
			else{
				k=0;
			}
		}
		else{
//_tm_("case 1 : i "+(int)i+" ok");
			k++;
			if(k==2){
				gg->_ctx->valid_object(geo);
				return(0);
			}
		}
	}
	
    k=0;
	for(long i=0;i<vsa->nv;i++){
        if(i>0&&eq_ivx2(&vsa->vx.vx2[i],&vsa->vx.vx2[i-1])){
//_tm_("case 2 on "+(int)i);
            continue;
        }
		dk=ivx2ivs_dist(&vsa->vx.vx2[i],vsb);
		if(dk>gg->_dst){
			if(gg->_full){
				break;
			}
			else{
				k=0;
			}
		}
		else{
//_tm_("case 2 : i "+(int)i+" ok");
			k++;
			if(k==2){
				gg->_ctx->valid_object(geo);
				return(0);
			}
		}
	}
	return(0);
}
