//----------------------------------------------------------------------------
// File : bXMapTransType.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, type transfert (i.e. transfering selected objects from one type to another)
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
// 20/10/2005 creation.
// 15/02/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapTransType.h"
#include "CocoaStuff.h"

#include <mox_intf/ext_utils.h>
#include <mox_intf/bEventLog.h>
#include <mox_intf/mm_messages.h>
#include <mox_intf/mm_errors.h>
#include <mox_intf/MacMapCWrappers.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapTransType::bXMapTransType(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
                : bStdXMap(elt,gapp,bndl){
	setclassname("transtype");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapTransType::~bXMapTransType(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapTransType::create(bGenericXMLBaseElement* elt){
	return(new bXMapTransType(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
//
// ------------
void bXMapTransType::open(int* flags){
    bStdXMap::open(flags);
    _prm.type_dest=1;
    _prm.keep_objects=true;
    _prm.create_fields=true;
    _prm.objects=NULL;
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapTransType::edit(void* prm){
_bTrace_("bXMapTransType::edit()",true);	
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
bool bXMapTransType::process(int msg, void* prm){
_bTrace_("bXMapTransType::process()",true);	
	switch(msg){
        case kExtProcessCallFromIntf:
            transtype();
            break;
        case kExtProcessCallWithParams:
            transtype((transtype_prm*)prm);
            break;
        case kExtProcessCallWithXMLTree:
            transtype(true);
            break;
        default:
            break;
	}
	return(true);
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXMapTransType::test(void* prm){
    if(_gapp->typesMgr()->count()<=0){
        return(false);
    }
    return(_gapp->selMgr()->type_unique());
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapTransType::set_infos(transtype_prm prm){
    _prm=prm;
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapTransType::get_infos(transtype_prm* prm){
    (*prm)=_prm;
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapTransType::transtype(){
bArray      sel(*(_gapp->selMgr()->elements()));
bEventLog	log(_gapp,this);
    _prm.objects=&sel;
    transtype(&_prm);
    _prm.objects=NULL;
    log.close();
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapTransType::transtype(bool dummy){
transtype_prm			p;
bGenericXMLBaseElement*	elt;
char					val[_values_length_max_];
    
    elt=getelement(1);
    if(!elt){
        return;
    }
    elt->getvalue(val);
    p.type_dest=_gapp->typesMgr()->index(val);
    if(p.type_dest<=0){
        return;
    }
    
    elt=getelement(2);
    if(!elt){
        return;
    }
    elt->getvalue(val);
    p.keep_objects=atoi(val);
    
    elt=getelement(3);
    if(!elt){
        return;
    }
    elt->getvalue(val);
    p.create_fields=atoi(val);
    
bArray	sel((*(_gapp->selMgr()->elements())));
    if(sel.count()<=0){
        return;
    }
    p.objects=&sel;
    
    transtype(&p);
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapTransType::transtype(transtype_prm* p){
_bTrace_("bXMapTransType::transtype",false);
bGenericGeoElement* fo=NULL;
bGenericGeoElement* to=NULL;
bGenericType*		ft;
bGenericType*		tt;
fieldindex*			fidx;
ivertices*			vxs;
    
    p->objects->get(1,&fo);
    ft=_gapp->typesMgr()->get(fo->getType());
    tt=_gapp->typesMgr()->get(p->type_dest);
    
    if(p->create_fields){
        field_create(p,ft);
    }
    
    fidx=field_index(p,ft);
    
ivx_rect			bnds={-(__BOUNDS_MAX__-1),-(__BOUNDS_MAX__-1),(__BOUNDS_MAX__-1),(__BOUNDS_MAX__-1)};
    
    tt->iterator()->set_bounds(&bnds);
    
    if(!fidx){
_te_("fidx==NULL");
    }
    
int     nj=ft->fields()->count()-kOBJ_Dir_;
char	ttl[__MESSAGE_STRING_LENGTH_MAX__];
char	msg[__MESSAGE_STRING_LENGTH_MAX__];
    GetName(this,ttl);
    message_string(kMsgProgress,msg,1);

bProgressWait wt(ttl,msg,true,p->objects->count());
    
    _gapp->layersMgr()->SetObjInvalidation(false);
    for(int i=1;i<=p->objects->count();i++){
        if(!wt.set_progress(i)){
            return;
        }
        p->objects->get(i,&fo);
        if(!tt->new_object(&to)){
            continue;
        }
        fo->getVertices(&vxs);
        //_tm_("getvxs");
        to->setVertices(vxs);
        
        fo->getName(msg);
        to->setName(msg);
        to->setSubType(fo->getSubType());
        to->setColor(fo->getColor());
        to->setDirection(fo->getDirection());
        
        //_tm_("settvxs");
        for(int j=0;j<nj;j++){
            //_tm_("%d-> %d",i,j);
            if(!fidx[j].idx){
                continue;
            }
            //_tm_("%d-> %d to %d",i,j+kOBJ_Dir_+1,fidx[j].idx);
            fo->getValue(j+kOBJ_Dir_+1,fidx[j].val);
            to->setValue(fidx[j].idx,fidx[j].val);
        }
    }
    if(!p->keep_objects){
        kill_objects(p->objects);
    }
    _gapp->layersMgr()->SetObjInvalidation(true);
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapTransType::field_create(transtype_prm* p, bGenericType* from_type){
_bTrace_("bXMapTransType::field_create",false);
    
bGenericType*		to_type=_gapp->typesMgr()->get(p->type_dest);
bStdBaseAccessor*	dbf=from_type->fields();
bStdBaseAccessor*	dbt=to_type->fields();
int					x,k,fk,l,d;
char				name[256],to_name[256];
    
    
    for(int i=kOBJ_Dir_+1;i<=dbf->count();i++){
        dbf->get_name(i,name);
        dbf->get_kind(i,&k);
        dbf->get_len(i,&l);
        dbf->get_decs(i,&d);
        
        x=dbt->get_index(name);
        if(!x){
            if(dbt->add(k,l,d,name)){
_te_("dbt->add failed for "+name+" with "+x);
            }
            else{
                x=dbt->get_index(name);
            }
        }
        else{
            dbt->get_kind(x,&fk);
            if(fk!=k){
                sprintf(to_name,"%s:%.4s",name,&k);
                x=dbt->get_index(name);
                if(!x){
                    if(dbt->add(k,l,d,to_name)){
_te_("dbt->add failed for "+to_name+" with "+x);
                    }
                    else{
                        x=dbt->get_index(to_name);
                    }
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------
//
// -----------
fieldindex* bXMapTransType::field_index(transtype_prm* p, bGenericType* from_type){
bGenericType*		to_type=_gapp->typesMgr()->get(p->type_dest);
bStdBaseAccessor*	dbf=from_type->fields();
bStdBaseAccessor*	dbt=to_type->fields();
fieldindex*			fidx=(fieldindex*)malloc((dbf->count()-kOBJ_Dir_)*sizeof(fieldindex));
    
    if(!fidx){
        return(NULL);
    }
int					fk,k,x,s;
char				name[256];
    
    for(int i=kOBJ_Dir_+1;i<=dbf->count();i++){
        dbf->get_name(i,name);
        dbf->get_size(i,&s);
        x=dbt->get_index(name);
        if(x){
            dbf->get_kind(i,&fk);
            dbt->get_kind(x,&k);
            if(k!=fk){
                x=0;
            }
        }
        fidx[i-(kOBJ_Dir_+1)].idx=x;
        if(x){
            fidx[i-(kOBJ_Dir_+1)].val=malloc(s);
        }
        else{
            fidx[i-(kOBJ_Dir_+1)].val=NULL;
        }
    }
    return(fidx);
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapTransType::kill_objects(bArray* a){
    if(_gapp->selMgr()->elements()==a){
        FlushSelection(_gapp);
    }
bGenericGeoElement*	o;
bGenericType*		tp;
    a->get(1,&o);
    tp=_gapp->typesMgr()->get(o->getType());
    for(int i=a->count();i>0;i--){
        a->get(i,&o);
        tp->kill_object(o);
    }
}


