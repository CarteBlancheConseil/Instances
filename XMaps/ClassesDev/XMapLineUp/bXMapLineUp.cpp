//----------------------------------------------------------------------------
// File : bXMapLineUp.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, order selected points into columns and lines
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
// 16/11/2006 creation.
// 04/07/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapLineUp.h"
#include "CocoaStuff.h"

#include <mox_intf/bEventLog.h>
#include <mox_intf/ext_utils.h>
#include <mox_intf/Type_Utils.h>
#include <mox_intf/bEventLog.h>
#include <mox_intf/mm_messages.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------

typedef int (*insidePtr)	(i2dvertex*,ivertices*,int);

// ---------------------------------------------------------------------------
// Constructeur
// ------------
static int dummy_ivx_in_ivs(i2dvertex* vx, ivertices* vxs, int limit){
	return(1);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapLineUp	::bXMapLineUp(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
			:bStdXMap(elt,gapp,bndl){
	setclassname("lineup2");
char	name[FILENAME_MAX];
GetName(this,name);
(void)_gapp->menuMgr()->add_item(kMenuMgrMenuPalettesID,name,GetSignature(this));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapLineUp::~bXMapLineUp(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapLineUp::create(bGenericXMLBaseElement* elt){
	return(new bXMapLineUp(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapLineUp::open(int* flags){	
	bStdXMap::open(flags);
	_kind=kXMapLineUpKindLine;
	_nb=1;
	_hd=1;
	_vd=1;
	_use_surf=false;
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXMapLineUp::edit(void* prm){
_bTrace_("bXMapLineUp::edit()",true);
long    result=0;
    
    runCocoaAppModal(this,&result);
    if(result>0){
        return(process(kExtProcessCallFromIntf,prm));
    }
    return false;
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapLineUp::process(int msg, void* prm){
	switch(msg){
		case kExtProcessCallFromIntf:
			make();
			break;
		case kExtProcessCallWithParams:
			break;
		default:
			break;
	}
	return(false);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapLineUp::test(void* prm){
	return(SelectionIsMonoGender(_gapp)==kBaseKindPoint);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapLineUp::make(){
bGenericGeoElement* o;
ivx_rect			vr,vrb,bnd;
bArray				arr(*_gapp->selMgr()->elements());
int					i,j,ko,kv;
int					imax,jmax,n=0;
insidePtr			inside;
ivertices			*ref,*vxs;
i2dvertex			p,lp;
bool				end=false;
int					hd=round(Measure_d2i(_gapp,_hd));
int					vd=round(Measure_d2i(_gapp,_vd));

	if(_use_surf){
		inside=ivx_in_ivs;
		_gapp->cntMgr()->elements()->get(1,&o);
		o->getBounds(&bnd);
		o->getVertices(&ref);
		imax=1+(bnd.bottom-bnd.top)/vd;
		jmax=1+(bnd.right-bnd.left)/hd;
	}
	else{
		inside=dummy_ivx_in_ivs;
		arr.get(1,&o);
		o->getBounds(&bnd);
		vr=bnd;
		o->getVertices(&vxs);
		n+=vxs->nv;
		for(i=2;i<arr.count();i++){
			arr.get(i,&o);
			o->getBounds(&vrb);
			ivr_union(&vrb,&vr,&bnd);
			vr=bnd;
			o->getVertices(&vxs);
			n+=vxs->nv;
		}
		ref=NULL;
		if(_kind==kXMapLineUpKindLine){
			imax=ceil((double)n/_nb);
			jmax=_nb;
		}
		else{
			imax=_nb;
			jmax=ceil((double)n/_nb);	
		}
	}
		
	_gapp->layersMgr()->SetObjInvalidation(false);	
	
char			msg[__MESSAGE_STRING_LENGTH_MAX__];
char			ttl[__MESSAGE_STRING_LENGTH_MAX__];
    get_localized_name(ttl,getbundle());
	message_string(kMsgProgress,msg,1);
bProgressWait	wt(ttl,msg,true,true,arr.count());	

bEventLog	log(_gapp,this);
	
	ko=1;
	kv=0;
	arr.get(ko,&o);
	o->getVertices(&vxs);
	lp.h=bnd.left;
	lp.v=bnd.top;
	for(i=0;i<imax;i++){
		for(j=0;j<jmax;j++){
			p.h=bnd.left+j*hd;
			p.v=bnd.top+i*vd;
			if(!inside(&p,ref,1)){
				continue;
			}
			lp=p;
			vxs->vx.vx2[kv]=p;
			kv++;
			if(kv==vxs->nv){
				kv=0;
				ko++;
				o->setVertices(vxs);
				if(!wt.set_progress(ko)){
					end=true;
					break;
				}
				if(!arr.get(ko,&o)){
					end=true;
					break;
				}
				o->getVertices(&vxs);
			}
		}
		if(end){
			break;
		}
	}
	
	if(!end){
		if(kv<vxs->nv){
			for(i=kv;i<vxs->nv;i++){
				vxs->vx.vx2[kv]=lp;
			}
			o->setVertices(vxs);
			ko++;
		}
		for(i=ko;i<=arr.count();i++){
			if(!wt.set_progress(i)){
				break;
			}	
			arr.get(i,&o);
			o->getVertices(&vxs);
			for(j=0;j<vxs->nv;j++){
				vxs->vx.vx2[j]=lp;
			}
			o->setVertices(vxs);
		}
	}
	_gapp->layersMgr()->SetObjInvalidation(true);	
	log.close();
}

