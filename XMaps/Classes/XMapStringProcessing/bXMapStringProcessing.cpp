//----------------------------------------------------------------------------
// File : bXMapStringProcessing.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, string formating utility
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
// 28/05/2009 creation.
// 19/02/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapStringProcessing.h"
#include "CocoaStuff.h"

#include <mox_intf/ext_utils.h>
#include <mox_intf/Type_Utils.h>
#include <mox_intf/bEventLog.h>
#include <mox_intf/mm_messages.h>
#include <mox_intf/mm_errors.h>
#include <mox_intf/bStdAlert.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
//
// ------------
static int formatinfo(char* fmt, int* pos){
char	*p=strchr(fmt,'#');
    if(p==NULL){
        return(0);
    }
int		l=0;
    *pos=p-fmt;
    while(p[0]=='#'){
        p++;
        l++;
    }
    return(l);
}

// ---------------------------------------------------------------------------
//
// ------------
static void strformat(char* fmt, char* str, int pos, int len){
int		i,n=len-strlen(str);
char	buff1[__MESSAGE_STRING_LENGTH_MAX__*3];
char	buff2[__MESSAGE_STRING_LENGTH_MAX__*3];
    
    strcpy(buff1,fmt);
    strcpy(buff2,str);
    
    for(i=1;i<=n;i++){
        strinsert(buff2,"0",0);
    }
    strrep(buff1,"#","");
    strinsert(buff1,buff2,pos);
    strcpy(str,buff1);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapStringProcessing   ::bXMapStringProcessing(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl)
                        : bStdXMap(elt,gapp,bndl)
                        ,_arr(sizeof(int)){
	setclassname("stringprocessing");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapStringProcessing::~bXMapStringProcessing(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapStringProcessing::create(bGenericXMLBaseElement* elt){
	return(new bXMapStringProcessing(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
//
// ------------
void bXMapStringProcessing::open(int* flags){
    bStdXMap::open(flags);
    _arr.reset();
    _prm.tp=0;
    _prm.sep[0]=0;
    _prm.cas=kStrProcessCaseDontChange;
    _prm.srch[0]=0;
    _prm.repl[0]=0;
    _prm.fmt[0]=0;
    _prm.target=kOBJ_Name_;
    _prm.arr=&_arr;
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapStringProcessing::edit(void* prm){
_bTrace_("bXMapStringProcessing::edit()",true);	
bGenericGeoElement* o;
long                result=0;
    
    _gapp->selMgr()->elements()->get(1,&o);
    _prm.tp=o->getType();
    runCocoaAppModal(this,&result);
    if(result>0){
        return(process(kExtProcessCallFromIntf,prm));
    }
    else{
        _arr.reset();
    }
    return false;
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapStringProcessing::process(int msg, void* prm){
_bTrace_("bXMapStringProcessing::process()",true);	
	switch(msg){
        case kExtProcessCallFromIntf:
            process_str();
            break;
        case kExtProcessCallWithParams:
            process_str((strprocess_prm*)prm,true);
            break;
        case kExtProcessCallWithXMLTree:
            process_str(true);
            break;
        default:
            break;
	}
	return(true);
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXMapStringProcessing::test(void* prm){
    return(SelectionIsMonoType(_gapp));
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapStringProcessing::set_params(strprocess_prm prm){
   _prm=prm;
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapStringProcessing::get_params(strprocess_prm *prm){
    *prm=_prm;
}

// ---------------------------------------------------------------------------
//
// -----------
bGenericType* bXMapStringProcessing::get_type(){
    return _gapp->typesMgr()->get(_prm.tp);
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXMapStringProcessing::process_str(){
bEventLog	log(_gapp,this);
    _gapp->layersMgr()->SetObjInvalidation(false);
    process_str(&_prm,false);
    _arr.reset();
    _gapp->layersMgr()->SetObjInvalidation(true);
    log.close();
    return(true);
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXMapStringProcessing::process_str(bool dummy){
_bTrace_("bXMapStringProcessing::process_str",true);
strprocess_prm			p;
bGenericXMLBaseElement*	elt;
bGenericXMLBaseElement*	cnt;
bGenericType*			tp;
int						idx;
char					value[_values_length_max_];
bArray					arr(sizeof(int));
    
    p.tp=SelectionIsMonoType(_gapp);
    if(p.tp==0){
_te_("bad selection");
        return(false);
    }
    
    tp=_gapp->typesMgr()->get(p.tp);
    p.arr=&arr;
    
// Fields
    cnt=getelement(1);
    if(!cnt){
_te_("no field container");
        return(false);
    }
    for(long i=1;i<=cnt->countelements();i++){
        elt=cnt->getelement(i);
        elt->getvalue(value);
        idx=tp->fields()->get_index(value);
        if(idx==0){
_te_("bad field "+value);
            return(false);
        }
        arr.add(&idx);
    }
    if(arr.count()==0){
_te_("no field");
        return(false);
    }
// Separator
    elt=getelement(2);
    if(!elt){
_te_("no separator");
        return(false);
    }
    elt->getvalue(p.sep);
// Case
    elt=getelement(3);
    if(!elt){
_te_("no case");
        return(false);
    }
    elt->getvalue(value);
    p.cas=atoi(value);
    if((p.cas<kStrProcessCaseDontChange)||(p.cas>kStrProcessCaseFWUpper)){
_te_("bad case "+p.cas);
        return(false);
    }
// Search
    elt=getelement(4);
    if(!elt){
_te_("no search");
        return(false);
    }
    elt->getvalue(p.srch);
char pat[4]={'<','>','&',0};
    
//    if(strcmp(pat,p.srch)==0){
//        strcpy(p.srch," ");
//    }
_tm_("tst :"+pat[0]+"="+(pat[0]/16)+(pat[0]%16));
_tm_("tst :"+pat[1]+"="+(pat[1]/16)+(pat[1]%16));
_tm_("tst :"+pat[2]+"="+(pat[2]/16)+(pat[2]%16));
    
_tm_("search string :"+p.srch);
// Replace
    elt=getelement(5);
    if(!elt){
_te_("no replacement");
        return(false);
    }
    elt->getvalue(p.repl);
//    if(strcmp(pat,p.repl)==0){
//        strcpy(p.repl," ");
//    }
_tm_("replacement string :"+p.repl);
// Format
    elt=getelement(6);
    if(!elt){
_te_("no format");
        return(false);
    }
    elt->getvalue(p.fmt);
// Fill field
    elt=getelement(7);
    if(!elt){
_te_("no target field");
        return(false);
    }
    elt->getvalue(value);
    p.target=tp->fields()->get_index(value);
    if(p.target==0){
_te_("bad target field "+value);
        return(false);
    }
    
    return(process_str(&p,true));
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXMapStringProcessing::process_str(strprocess_prm* prm, bool silent){
_bTrace_("bXMapStringProcessing::process_str(strprocess_prm*,bool)",true);
int					j,err=0,fidx;
char				val[__MESSAGE_STRING_LENGTH_MAX__];
char				buffer[__MESSAGE_STRING_LENGTH_MAX__*3+1];
bArray				sel(*(_gapp->selMgr()->elements()));
bGenericGeoElement*	o;
    
    b_message_string(kXMapStringProcessingProcessMessageID,val,getbundle(),1);
bProgressWait wt("",val,true,sel.count());
    
int	fpos=0;
int	flen=formatinfo(prm->fmt,&fpos);
    
    for(int i=1;i<=sel.count();i++){
        if(!wt.set_progress(i)){
            break;
        }
        sel.get(i,&o);
        buffer[0]=0;
        
// Concat
        for(j=1;j<=prm->arr->count()-1;j++){
            prm->arr->get(j,&fidx);
            val[0]=0;
            if(o->getValue(fidx,val)==false){
_te_("o->getValue for field "+fidx);
                err++;
                break;
            }
            if(strncat(buffer,val,__MESSAGE_STRING_LENGTH_MAX__*3)==NULL){
_te_("strncat "+buffer+"+"+val);
                err++;
                break;
            }
            if(strncat(buffer,prm->sep,__MESSAGE_STRING_LENGTH_MAX__*3)==NULL){
_te_("strncat "+buffer+"+"+prm->sep);
                err++;
                break;
            }
        }
        prm->arr->get(prm->arr->count(),&fidx);
        val[0]=0;
        if(o->getValue(fidx,val)==false){
_te_("o->getValue for field "+fidx);
            err++;
        }
        else if(strncat(buffer,val,__MESSAGE_STRING_LENGTH_MAX__*3)==NULL){
_te_("strncat "+buffer+"+"+val);
            err++;
        }
// Case
        switch(prm->cas){
            case kStrProcessCaseLower:
                strlower(buffer);
                break;
            case kStrProcessCaseUpper:
                strupper(buffer);
                break;
            case kStrProcessCaseFUpper:
                strlower(buffer);
                strupperfcs(buffer);
                break;
            case kStrProcessCaseFWUpper:
                strlower(buffer);
                strupperfcw(buffer);
                break;
        }
// Replace
        if(strlen(prm->srch)>0){
            strrep(buffer,prm->srch,prm->repl);
        }
// Format
        if(flen>0){
            strformat(prm->fmt,buffer,fpos,flen);
        }
// Affect
        if(o->setValue(prm->target,buffer)==false){
_te_("o->setValue "+buffer+" for field "+fidx);
            err++;
        }
    }
    
    if(err){
        b_message_string(kXMapStringProcessingErrorsOccursID,val,getbundle(),0);
        b_message_string(kXMapStringProcessingReadLogID,buffer,getbundle(),0);
bAlertStop	alrt(val,buffer,silent);
    }
    
    return(true);
}

