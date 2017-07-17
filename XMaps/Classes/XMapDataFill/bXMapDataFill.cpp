//----------------------------------------------------------------------------
// File : bXMapDataFill.cpp
// Project : MacMap
// Purpose : C++ source file : XMap classe, fills object's datas
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
// 16/03/2006 creation.
// 15/02/2016 coca intf.
//----------------------------------------------------------------------------

#include "bXMapDataFill.h"
#include "bXMapDataFillRun.h"
#include "CocoaStuff.h"

#include <mox_intf/ext_utils.h>
#include <mox_intf/Type_Utils.h>
#include <mox_intf/bEventLog.h>
#include <mox_intf/mm_messages.h>
#include <mox_intf/mm_errors.h>
#include <mox_intf/bStdAlert.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapDataFill   ::bXMapDataFill(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl)
                : bStdXMap(elt,gapp,bndl)
                ,_runs(sizeof(bXMapDataFillRun*)){
	setclassname("datafill");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapDataFill::~bXMapDataFill(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapDataFill::create(bGenericXMLBaseElement* elt){
	return(new bXMapDataFill(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
//
// ------------
void bXMapDataFill::open(int* flags){
    bStdXMap::open(flags);
    _tp=NULL;
    _fld=0;
    _run=0;
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapDataFill::edit(void* prm){
_bTrace_("bXMapDataFill::edit()",true);	
bGenericGeoElement* o;
long                result=0;
    
    _gapp->selMgr()->elements()->get(1,&o);
    _tp=_gapp->typesMgr()->get(o->getType());
    runCocoaAppModal(this,&result);
    if(result>0){
        return(process(kExtProcessCallFromIntf,prm));
    }
    else{
        reset();
    }
    return false;
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapDataFill::process(int msg, void* prm){
_bTrace_("bXMapDataFill::process()",true);	
	switch(msg){
        case kExtProcessCallFromIntf:
            fill_data();
            break;
        case kExtProcessCallWithParams:
            break;
        case kExtProcessCallWithXMLTree:
            if(parse_tree()){
                fill_data(true);
            }
            break;
        default:
            break;
	}
	return(true);
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXMapDataFill::test(void* prm){
    if(_gapp->typesMgr()->count()<=0){
        return(false);
    }
    return(_gapp->selMgr()->type_unique());
}

// ---------------------------------------------------------------------------
//
// -----------
bGenericType* bXMapDataFill::get_type(){
   return _tp;
}

// ---------------------------------------------------------------------------
//
// -----------
bArray& bXMapDataFill::get_runs(){
    return _runs;
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapDataFill::fill_data(){
bEventLog	log(_gapp,this);
    fill_data(false);
    log.close();
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapDataFill::fill_data(bool silent){
_bTrace_("bXMapDataFill::fill_data",true);
bArray				sel(*(_gapp->selMgr()->elements()));
long				j,err=0;
bGenericGeoElement*	o;
bXMapDataFillRun*	run;
char				msg[__MESSAGE_STRING_LENGTH_MAX__];
char				ttl[__MESSAGE_STRING_LENGTH_MAX__];
    GetName(this,ttl);
    
    _gapp->layersMgr()->SetObjInvalidation(false);

    _gapp->selMgr()->flush();
    
    message_string(kMsgProgress,msg,1);
bProgressWait wt(ttl,msg,true,true,sel.count());
    for(long i=1;i<=sel.count();i++){
        if(!wt.set_progress(i)){
            _tm_("user break");
            break;
        }
        sel.get(i,&o);
        if(o->getType()!=_tp->index()){
            continue;
        }
        o->setselect(true,false);
        for(j=1;j<=_runs.count();j++){
            _runs.get(j,&run);
            if(!run->apply(o)){
                err=-1;
_te_("run->apply failed at ("+i+":"+j+")");
            }
        }
        o->setselect(false,false);
    }
    
    _gapp->selMgr()->flush();
    _gapp->selMgr()->add(&sel);
    
    _gapp->layersMgr()->SetObjInvalidation(true);

    reset();
    if(err){
        b_error_string(kXMapDataFillErrorCode,msg,getbundle());
bAlertStop	alrt(msg,"",silent);
    }
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapDataFill::reset(){
bXMapDataFillRun*	run;
    for(long i=1;i<=_runs.count();i++){
        _runs.get(i,&run);
        delete run;
    }
    _runs.reset();
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXMapDataFill::parse_tree(){
    _tp=_gapp->typesMgr()->get(SelectionIsMonoType(_gapp));
    
bGenericXMLBaseElement*	elt;

char	name[_values_length_max_],value[_values_length_max_];
int		mode;
int		n=countelements();
int		r=n%3;
    if(r==1){
        elt=getelement(n);
        elt->getvalue(value);
        _tp=_gapp->typesMgr()->get(_gapp->typesMgr()->index(value));
        n--;
    }
    else{
        if(!test(NULL)){
            return(false);
        }
        _tp=_gapp->typesMgr()->get(SelectionIsMonoType(_gapp));
    }
    
    n/=3;
    for(int i=1;i<=n;i++){
        elt=getelement((i-1)*3+1);
        if(!elt){
            return(true);
        }
        elt->getvalue(name);
        
        elt=getelement((i-1)*3+2);
        if(!elt){
            return(true);
        }
        elt->getvalue(value);
        mode=atoi(value);
        
        elt=getelement((i-1)*3+3);
        if(!elt){
            return(true);
        }
        elt->getvalue(value);
        
        add_run(name,mode,value);
    }
    
    return(true);
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapDataFill::add_run(char* field, int mode, char* value){
_bTrace_("bXMapDataFill::add_run",false);
bXMapDataFillRun*	run;
int					k,sz,d;
char				runstr[256]="";
    
    _fld=_tp->fields()->get_index(field);
    _tp->fields()->get_kind(_fld,&k);
    _tp->fields()->get_size(_fld,&sz);
    _tp->fields()->get_decs(_fld,&d);
    switch(mode){
        case 1:{
            run=new bXMapDataFillRunValue(	runstr,
                                          _fld,sz,k,d,
                                          value);
        }break;
        case 2:{
bGenericCalc* clc=(bGenericCalc*)(void*)_gapp->calcMgr()->find(value);
            if(!clc){
_te_("calc "+value+" not found");
                return;
            }
            run=new bXMapDataFillRunCalc(	runstr,
                                         _fld,sz,k,d,
                                         clc);
        }break;
        case 3:{
int		f,fk,fsz,fd;
            f=_tp->fields()->get_index(value);
            if(!f){
                return;
            }
            _tp->fields()->get_kind(f,&fk);
            _tp->fields()->get_size(f,&fsz);
            _tp->fields()->get_decs(f,&fd);
            run=new bXMapDataFillRunField(	runstr,
                                          _fld,sz,k,d,
                                          f,fsz,fk,fd);
        }break;
        case 4:		
            run=new bXMapDataFillRunAskValue(value,
                                             _fld,sz,k,d,
                                             _tp);
            break;
            
        default:
            return;
            break;
    }
    if(!_runs.add(&run)){
        delete run;
        return;
    }
}
