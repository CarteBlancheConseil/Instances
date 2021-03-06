//----------------------------------------------------------------------------
// File : bXMapCloneDetector.cpp
// Project : MacMap
// Purpose : C++ source file : XMap clone detector class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2016 Carte Blanche Conseil.
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
// 09/02/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapCloneDetector.h"
#include "CocoaStuff.h"

#include <mox_intf/ext_utils.h>
#include <mox_intf/mm_messages.h>
#include <mox_intf/bStdAlert.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapCloneDetector::bXMapCloneDetector(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
                : bStdXMap(elt,gapp,bndl){
	setclassname("clonedetector");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapCloneDetector::~bXMapCloneDetector(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapCloneDetector::create(bGenericXMLBaseElement* elt){
	return(new bXMapCloneDetector(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
//
// ------------
void bXMapCloneDetector::open(int* flags){
    bStdXMap::open(flags);
    _prm.name=1;
    _prm.subtype=1;
    _prm.color=1;
    _prm.direction=1;
    _prm.reversegeom=1;
    _prm.userfields=1;
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXMapCloneDetector::edit(void* prm){
_bTrace_("bXMapCloneDetector::edit()",true);
long    result=0;
    runCocoaAppModal(this,&result);
    if(result>0){
        return(process(kExtProcessCallFromIntf,prm));
    }
    return false;
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapCloneDetector::process(int msg, void* prm){
_bTrace_("bXMapCloneDetector::process()",true);	
	switch(msg){
        case kExtProcessCallFromIntf:
            return(detect(&_prm));
            break;
        case kExtProcessCallWithParams:
            return(detect((clonedetector_prm*)prm));
            break;
        default:
            break;
	}
	return(true);
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXMapCloneDetector::test(void* prm){
    return(_gapp->selMgr()->count()>0);
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapCloneDetector::set_infos(clonedetector_prm prm){
    _prm=prm;
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapCloneDetector::get_infos(clonedetector_prm* prm){
    (*prm)=_prm;
}

// ---------------------------------------------------------------------------
//
// ------------
bool bXMapCloneDetector::detect(clonedetector_prm* prm){
bArray				sel(*(_gapp->selMgr()->elements()));
bArray*				arr;
char				msg[__MESSAGE_STRING_LENGTH_MAX__];
    message_string(kMsgProgress,msg,1);
bProgressWait wt("",msg,true,sel.count());
    _gapp->cntMgr()->flush();
    
bGenericGeoElement	*oa,*ob;
bGenericType*		tp;
ivx_rect			vxr;
int					i,j;
bool				flg=false;
    
    for(i=1;i<=sel.count();i++){
        if(!wt.set_progress(i)){
            break;
        }
        sel.get(i,&oa);
        if(oa->contrasted()){
            continue;
        }
        tp=_gapp->typesMgr()->get(oa->getType());
        oa->getBounds(&vxr);
        tp->iterator()->objs_in_rect(&arr,&vxr);
        if(!arr){
            continue;
        }
        for(j=1;j<=arr->count();j++){
            arr->get(j,&ob);
            if(oa==ob){
                continue;
            }
            if(ob->contrasted()){
                continue;
            }
            if(obj_comp(oa,ob,prm)){
                flg=true;
                if(ob->masked()){
                    ob->setmasked(false,true);
                }
                ob->setcontrast(true,true);
            }
        }
        delete arr;
    }
    if(flg){
        b_message_string(kXMapCloneFoundMessageID,msg,getbundle(),0);
    }
    else{
        b_message_string(kXMapNoCloneFoundMessageID,msg,getbundle(),0);
    }
bAlertStop	alrt(msg,"");
    return(true);
}

// ---------------------------------------------------------------------------
//
// ------------
bool bXMapCloneDetector::obj_comp(	bGenericGeoElement* oa,
                                  bGenericGeoElement* ob,
                                  clonedetector_prm* prm){
//_bTrace_("bXMapCloneDetector::obj_comp",false);
char	ac[1024],bc[1024];
    
    if(prm->name){
        oa->getName(ac);
        ob->getName(bc);
        if(strcmp(ac,bc)!=0){
//_tm_("getName %s->%s",ac,bc);
            return(false);
        }
    }
    if(prm->subtype){
        if(oa->getSubType()!=ob->getSubType()){
//_tm_("getSubType %d->%d",oa->getSubType(),ob->getSubType());
            return(false);
        }
    }
    if(prm->color){
        if(oa->getColor()!=ob->getColor()){
//_tm_("getColor %d->%d",oa->getColor(),ob->getColor());
            return(false);
        }
    }
    if(prm->direction){
        if(oa->getDirection()!=oa->getDirection()){
//_tm_("getDirection %d->%d",oa->getDirection(),ob->getDirection());
            return(false);
        }
    }
    
ivertices	*vsa,*vsb;
    oa->getVertices(&vsa);
    ob->getVertices(&vsb);
    
    if(vsa->nv!=vsb->nv){
//_tm_("nv %d->%d",vsa->nv,vsb->nv);
        return(false);
    }
    if(vsa->no!=vsb->no){
//_tm_("no %d->%d",vsa->no,vsb->no);
        return(false);
    }
bool	gdr=true;
    for(int i=0;i<vsa->nv;i++){
        if(!eq_ivx2(&vsa->vx.vx2[i],&vsb->vx.vx2[i])){
//_tm_("vx[%d]",i);
            gdr=false;
            break;
        }
    }
    if(!gdr&&!prm->reversegeom){
        return(false);
    }
    if(!gdr&&prm->reversegeom){
        for(int i=0;i<vsa->nv;i++){
            if(!eq_ivx2(&vsa->vx.vx2[i],&vsb->vx.vx2[(vsb->nv-1)-i])){
//_tm_("rev vx[%d]",i);
                return(false);
            }
        }
    }
    
    if(prm->userfields){
        bGenericType* tp=_gapp->typesMgr()->get(oa->getType());
        for(int i=kOBJ_Dir_+1;i<=tp->fields()->count();i++){
            oa->getValue(i,ac);
            ob->getValue(i,bc);
            if(strcmp(ac,bc)!=0){
//_tm_("field %d",i);
                return(false);
            }
        }
    }
    return(true);
}


