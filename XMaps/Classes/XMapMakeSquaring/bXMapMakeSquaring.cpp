//----------------------------------------------------------------------------
// File : bXMapMakeSquaring.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, create new squaring (graticule)
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
// 21/06/2007 creation.
// 05/07/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapMakeSquaring.h"
#include "CocoaStuff.h"

#include <mox_intf/bEventLog.h>
#include <mox_intf/Carb_Utils.h>
#include <mox_intf/ext_Utils.h>
#include <mox_intf/MacMapCWrappers.h>
#include <mox_intf/NSCursorWrappers.h>
#include <mox_intf/mm_messages.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapMakeSquaring   ::bXMapMakeSquaring(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl)
                    :bStdXMap(elt,gapp,bndl){
	setclassname("makesquaring");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapMakeSquaring::~bXMapMakeSquaring(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapMakeSquaring::create(bGenericXMLBaseElement* elt){
	return(new bXMapMakeSquaring(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapMakeSquaring::open(int* flags){	
	bStdXMap::open(flags);
	_prm.justo=0;
	_prm.o.x=0;
	_prm.o.y=0;
	_prm.nh=1;
	_prm.nv=1;
	_prm.sz=1;
	_prm.kind=kMakeSquaringSqr;
	_prm.tp=NULL;
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapMakeSquaring::process(int msg, void* prm){
	switch(msg){
		case kExtProcessCallFromIntf:
			if(_prm.sz<=0){
				return(false);
			}
			return(make());
			break;
		case kExtProcessCallWithParams:{
makesquaring_prm* p=(makesquaring_prm*)prm;
				if(p->sz<=0){
					return(false);
				}
				if(p->kind==kMakeSquaringSqr){
					return(make_sqr(p->tp,&p->o,p->nh,p->nv,p->sz));
				}
				else{
					return(make_hex(p->tp,&p->o,p->nh,p->nv,p->sz));
				}
			}break;
		case kExtProcessCallWithXMLTree:{
makesquaring_prm		p;
char					val[_values_length_max_];
bGenericXMLBaseElement*	elt;
				elt=getelement(1);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				p.tp=_gapp->typesMgr()->get(_gapp->typesMgr()->index(val));
				if(!p.tp){
					return(false);
				}
				
				elt=getelement(2);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				p.kind=atoi(val);
				
				elt=getelement(3);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				p.o.x=atof(val);
				
				elt=getelement(4);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				p.o.y=atof(val);
				
				elt=getelement(5);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				p.nh=atof(val);
				
				elt=getelement(6);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				p.nv=atoi(val);

				elt=getelement(7);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				p.sz=atof(val);
				
				if(p.kind==kMakeSquaringSqr){
					return(make_sqr(p.tp,&p.o,p.nh,p.nv,p.sz));
				}
				else{
					return(make_hex(p.tp,&p.o,p.nh,p.nv,p.sz));
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
bool bXMapMakeSquaring::test(void* prm){
	_prm.tp=(bGenericType*)CurType(_gapp);
	if(!_prm.tp){
		return(false);
	}
	if(	(_prm.tp->kind()!=kBaseKindPolyline)	&&
		(_prm.tp->kind()!=kBaseKindPolygon)		&&
		(_prm.tp->kind()!=kBaseKindRaster)		){
		return(false);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapMakeSquaring::edit(void* prm){
makesquaring_prm p=_prm;
	if(prm){
		_prm=(*(makesquaring_prm*)prm);			
	}
long    result=0;
    runCocoaAppModal(this,&result);
    if(result>0){
        process(kExtProcessCallFromIntf,prm);
    }
	if(prm){
		_prm=p;
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapMakeSquaring::make(){
	if(!_prm.tp){
		return(true);
	}
bEventLog	log(_gapp,this);
	if(_prm.kind==kMakeSquaringSqr){
		make_sqr(_prm.tp,&_prm.o,_prm.nh,_prm.nv,_prm.sz);
	}
	else{
		make_hex(_prm.tp,&_prm.o,_prm.nh,_prm.nv,_prm.sz);
	}
	log.close();
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapMakeSquaring::make_sqr(bGenericType* tp, d2dvertex* dvx, int nh, int nv, double sz){
_bTrace_("bXMapMakeSquaring::make_sqr",false);
ivertices*			vxs=ivs_new(_2D_VX,5,0);
	if(!vxs){
_te_("ivs_new");
		return(false);
	}
bGenericGeoElement*	o;
d2dvertex			co=*dvx,c;
int					i,j;
char				msg[__MESSAGE_STRING_LENGTH_MAX__];
	message_string(kMsgProgress,msg,1);
bProgressWait wt("",msg,true,true,(nh*nv));
   
	_gapp->layersMgr()->SetObjInvalidation(false);
	co.y+=sz;
	for(i=1;i<=nv;i++){
		co.x=dvx->x;
		co.y-=sz;
		for(j=1;j<=nh;j++){
			if(!wt.set_progress(((i-1)*nh+j))){
				break;
			}
			c.x=co.x+sz*(j-1);
			c.y=co.y;
			Convert(&vxs->vx.vx2[0],&c);
			c.y-=sz;
			Convert(&vxs->vx.vx2[1],&c);
			c.x+=sz;
			Convert(&vxs->vx.vx2[2],&c);
			c.y+=sz;
			Convert(&vxs->vx.vx2[3],&c);
			vxs->vx.vx2[4]=vxs->vx.vx2[0];
			if(!tp->new_object(&o)){
_te_("new_object");
				ivs_free(vxs);
                _gapp->layersMgr()->SetObjInvalidation(true);
                return(false);
			}
            if(!InitWithStyle(_gapp,_gapp->layersAccessCtx()->get_current(),o)){
                MMBeep();
            }
			if(!o->setVertices(vxs)){
_te_("setVertices");
				tp->kill_object(o);
				ivs_free(vxs);
                _gapp->layersMgr()->SetObjInvalidation(true);
                return(false);
			}
		}
		if(!wt.get_progress()){
			break;
		}
	}
	ivs_free(vxs);
	_gapp->layersMgr()->SetObjInvalidation(true);

	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapMakeSquaring::make_hex(bGenericType* tp, d2dvertex* dvx, int nh, int nv, double sz){
_bTrace_("bXMapMakeSquaring::make_sqr",false);
ivertices*			vxs=ivs_new(_2D_VX,7,0);
	if(!vxs){
_te_("ivs_new");
		return(false);
	}
bGenericGeoElement*	o;
d2dvertex			co=*dvx,c;
int					i,j;
double				d=(sz/sin(M_PI/3.0))/2.0;
char				msg[__MESSAGE_STRING_LENGTH_MAX__];
	message_string(kMsgProgress,msg,1);
bProgressWait wt("",msg,true,true,(nh*nv));

	_gapp->layersMgr()->SetObjInvalidation(false);
	co.y-=d;
	for(i=1;i<=nv;i++){
		co.x=(i&1)?(dvx->x+sz):(dvx->x+(sz/2.0));
		for(j=1;j<=nh;j++){
			if(!wt.set_progress(((i-1)*nh+j))){
				break;
			}
			
			c.x=co.x+d*cos(M_PI*(5.0/6.0));
			c.y=co.y+d*sin(M_PI*(5.0/6.0));
			Convert(&vxs->vx.vx2[0],&c);
			
			c.x=co.x+d*cos(M_PI/2.0);
			c.y=co.y+d*sin(M_PI/2.0);
			Convert(&vxs->vx.vx2[1],&c);
			
			c.x=co.x+d*cos(M_PI/6.0);
			c.y=co.y+d*sin(M_PI/6.0);
			Convert(&vxs->vx.vx2[2],&c);
			
			c.x=co.x+d*cos(M_PI*(11.0/6.0));
			c.y=co.y+d*sin(M_PI*(11.0/6.0));
			Convert(&vxs->vx.vx2[3],&c);
			
			c.x=co.x+d*cos(M_PI*(3.0/2.0));
			c.y=co.y+d*sin(M_PI*(3.0/2.0));
			Convert(&vxs->vx.vx2[4],&c);

			c.x=co.x+d*cos(M_PI*(7.0/6.0));
			c.y=co.y+d*sin(M_PI*(7.0/6.0));
			Convert(&vxs->vx.vx2[5],&c);

			vxs->vx.vx2[6]=vxs->vx.vx2[0];

			co.x+=sz;

			if(!tp->new_object(&o)){
_te_("new_object");
				ivs_free(vxs);
                _gapp->layersMgr()->SetObjInvalidation(true);
                return(false);
			}
            if(!InitWithStyle(_gapp,_gapp->layersAccessCtx()->get_current(),o)){
                MMBeep();
			}
			if(!o->setVertices(vxs)){
_te_("setVertices");
				tp->kill_object(o);
				ivs_free(vxs);
                _gapp->layersMgr()->SetObjInvalidation(true);
                return(false);
			}
		}
		co.y-=(d*2.0*0.75);
	}
	ivs_free(vxs);
	_gapp->layersMgr()->SetObjInvalidation(true);

	return(true);
}

