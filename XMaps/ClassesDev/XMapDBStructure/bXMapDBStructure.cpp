//----------------------------------------------------------------------------
// File : bXMapDBStructure.cpp
// Project : MacMap
// Purpose : C++ source file : XMap database structure class
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
// 02/09/2015 creation.
//----------------------------------------------------------------------------

#include "bXMapDBStructure.h"
#include "CocoaStuff.h"
#include <mox_intf/ext_utils.h>
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/bEventLog.h>
#include <mox_intf/mm_messages.h>
#include <mox_intf/mm_errors.h>
#include <mox_intf/bStdAlert.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapDBStructure::bXMapDBStructure(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
                : bStdXMap(elt,gapp,bndl){
	setclassname("dbstructure");
		
char	name[FILENAME_MAX];
GetName(this,name);
(void)_gapp->menuMgr()->add_item(kMenuMgrMenuPalettesID,name,GetSignature(this));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapDBStructure::~bXMapDBStructure(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapDBStructure::create(bGenericXMLBaseElement* elt){
	return(new bXMapDBStructure(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapDBStructure::test(void* prm){
	return(_gapp->typesMgr()->count()>0);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapDBStructure::edit(void* prm){
_bTrace_("bXMapDBStructure::edit()",true);	
	return(process(kExtProcessCallFromIntf,prm));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapDBStructure::process(int msg, void* prm){
_bTrace_("bXMapDBStructure::process()",true);	
	switch(msg){
        case kExtProcessCallFromIntf:{
long        result=0;
bEventLog	log(_gapp,this);
            runCocoaAppModal(this,&result);
            if(result<=0){
            }
            log.close();
        }break;
		case kExtProcessCallWithParams:
			break;
		case kExtProcessCallWithXMLTree:
			break;
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
int bXMapDBStructure::remove(	bGenericType* tp,
                                long field){
_bTrace_("bXMapDBStructure::remove",true);
    if(tp->fields()->remove(field)){
        return _bDataBaseRemoveFieldErr_;
    }
    return noErr;
}

// ---------------------------------------------------------------------------
// 
// -----------
int bXMapDBStructure::add(	bGenericType* tp,
                            long kind,
                            long len,
                            long decs,
                            const char* name){
_bTrace_("bXMapDBStructure::add",true);
    if(tp->fields()->add(kind,len,decs,name)){
        return _bDataBaseAddFieldErr_;
    }
    return noErr;
}

// ---------------------------------------------------------------------------
// 
// -----------
int bXMapDBStructure::modify(	bGenericType* tp,
                                long field,
                                long kind,
                                long len,
                                long decs,
                                const char* name){
_bTrace_("bXMapDBStructure::modify",true);
    if(tp->fields()->modify(field,kind,len,decs,name)){
        return _bDataBaseModifyFieldErr_;
    }
    return noErr;
}


// ---------------------------------------------------------------------------
//
// -----------
int bXMapDBStructure::set_default_value(	bGenericType* tp,
                                            long field,
                                            void* value,
                                            bool init){
_bTrace_("bXMapDBStructure::set_default_value",true);
char	msg[__MESSAGE_STRING_LENGTH_MAX__];
char	exp[__MESSAGE_STRING_LENGTH_MAX__];
   
    if(init&&tp->nb_live()>0){
b_message_string("init existing",msg,getbundle(),1);
b_message_string("init existing exp",exp,getbundle(),1);
bAlertWarningYes	alrt(msg,exp);
        if(alrt.result()){
            for(long i=1;i<=tp->fields()->count_records();i++){
                if(tp->fields()->write(i,field,value)){
                    return _bDataBaseSetDefaultValueErr_;
                }
            }
        }
    }
    if(!tp->fields()->set_default_value(field,value)){
        return _bDataBaseSetDefaultValueErr_;
    }
    return noErr;
}

// ---------------------------------------------------------------------------
//
// -----------
int bXMapDBStructure::set_masked(	bGenericType* tp,
                                    long field,
                                    bool value){
_bTrace_("bXMapDBStructure::set_masked",true);
    if(!tp->fields()->set_hidden(field,value)){
        return _bDataBaseSetHiddenErr_;
    }
    return noErr;
}

// ---------------------------------------------------------------------------
//
// -----------
int bXMapDBStructure::set_delete_protected(	bGenericType* tp,
                                            long field,
                                            bool value){
_bTrace_("bXMapDBStructure::set_delete_protected",true);
    if(!tp->fields()->set_delprotected(field,value)){
        return _bDataBaseSetDeleteProtectedErr_;
    }
    return noErr;
}

// ---------------------------------------------------------------------------
//
// -----------
int bXMapDBStructure::set_write_protected(	bGenericType* tp,
                                            long field,
                                            bool value){
_bTrace_("bXMapDBStructure::set_write_protected",true);
    if(!tp->fields()->set_writeprotected(field,value)){
        return _bDataBaseSetWriteProtectedErr_;
    }
    return noErr;
}

//// ---------------------------------------------------------------------------
//// 
//// -----------
//bool bXMapDBStructure::do_make_from_field(bGenericType* tp,
//											  long field,
//											  long srcfield,
//											  bool usevalue){
//_bTrace_("bXMapDBStructure::do_make_from_field",true);
//int						k;
//DBStructure_prm		prm;
//MCITp					pp;
//
//	prm.tp=tp;
//	prm.field=field;
//	prm.srcfield=srcfield;
//	prm.srcuse=usevalue?kDBStructureUseValue:kDBStructureUseLabel;
//
//	pp.prm=&prm;
//	pp.init=0;
//	
//char	mess[__MESSAGE_STRING_LENGTH_MAX__];
//
//	tp->fields()->get_name(srcfield,mess);
////_tm_("source="+mess);
//	tp->fields()->get_name(field,mess);
////_tm_("dest="+mess);
//	
//	get_localized_name(mess,getbundle());
//bProgressWait	wt(mess,NULL,true,true,prm.tp->nb_live()*2);
//	pp.wt=&wt;
//	pp.wtn=0;
// 	
//	if(prm.tp->fields()->count_constraints(prm.field)==0){
//		if(prm.srcuse==kDBStructureUseValue){
//_tm_("nouvelle contrainte par valeur");
//			prm.tp->fields()->get_kind(prm.field,&k);
//			switch(k){
//				case _char:{
//					char	buff[1024];
//					pp.val=buff;
//					prm.tp->iterator()->iterate(&pp,fill_char);
//				}break;
//				case _bool:
//				case _int:{
//					int	buff;
//					pp.val=&buff;
//					prm.tp->iterator()->iterate(&pp,fill_int);
//				}break;
//				case _double:
//				case _date:
//				case _time:{
//					double	buff;
//					pp.val=&buff;
//					prm.tp->iterator()->iterate(&pp,fill_double);
//				}break;
//			}
//		}
//		else{
//_tm_("nouvelle contrainte par intitulé");
//			int	buff=1;
//			pp.val=&buff;
//			pp.init=1;
//			prm.tp->iterator()->iterate(&pp,fill_int);
//		}
//	}
//	
//	if(prm.srcuse==kDBStructureUseValue){
//		prm.tp->fields()->get_kind(prm.field,&k);
//		switch(k){
//			case _char:
//				prm.tp->iterator()->iterate(&pp,analyse_char);
//				break;
//			case _bool:
//			case _int:
//				prm.tp->iterator()->iterate(&pp,analyse_int);
//				break;
//			case _double:
//			case _date:
//			case _time:
//				prm.tp->iterator()->iterate(&pp,analyse_double);
//				break;
//		}
//	}
//	else{
//		prm.tp->iterator()->iterate(&pp,analyse_char);
//	}
//	
//	return(false);
//}

/*// ---------------------------------------------------------------------------
// 
// -----------
void bXMapDBStructure::do_beep(){
_bTrace_("bXMapDBStructure::do_beep",true);
	SysBeep(5);
}*/

//// ---------------------------------------------------------------------------
//// 
//// ------------
//int bXMapDBStructure::analyse_char(void *o, void *prm){
//_bTrace_("bXMapDBStructure::analyse_char*",false);
//bGenericGeoElement*	geo=(bGenericGeoElement*)o;
//MCITp*				p=(MCITp*)prm;
//char				val[1024];
//int					index;
//
//	p->wtn++;
//	if(!p->wt->set_progress(p->wtn)){
//		return(-1);
//	}
///*	if(!p->wt->get_progress()){
//		return(-1);
//	}*/
//	geo->getValue(p->prm->srcfield,val);
//	index=p->prm->tp->fields()->get_constraint_index(p->prm->field,val);
//	if(index==0){
//		if(!p->prm->tp->fields()->add_constraint(p->prm->field,_char,val)){
//_te_("echec ajout contrainte "+val);
//		}
//		else{
//		}
//	}
//	if(p->prm->srcuse==kDBStructureUseValue){
//		geo->setValue(p->prm->field,val);
//	}
//	else{
//		if(index==0){
//			index=p->prm->tp->fields()->get_constraint_index(p->prm->field,val);
//		}
//		geo->setValue(p->prm->field,&index);
//	}
//	return(0);
//}
//
//// ---------------------------------------------------------------------------
//// 
//// ------------
//int bXMapDBStructure::analyse_int(void *o, void *prm){
//bGenericGeoElement*	geo=(bGenericGeoElement*)o;
//MCITp*				p=(MCITp*)prm;
//int					val;
//	
//	p->wtn++;
//	if(!p->wt->set_progress(p->wtn)){
//		return(-1);
//	}
//	geo->getValue(p->prm->srcfield,&val);
//	if(p->prm->tp->fields()->get_constraint_index(p->prm->field,&val)==0){
//		if(!p->prm->tp->fields()->add_constraint(p->prm->field,_int,&val)){
//		}
//		else{
//		}
//	}
//	geo->setValue(p->prm->field,val);
//	return(0);
//}
//
//// ---------------------------------------------------------------------------
//// 
//// ------------
//int bXMapDBStructure::analyse_double(void *o, void *prm){
//bGenericGeoElement*	geo=(bGenericGeoElement*)o;
//MCITp*				p=(MCITp*)prm;
//double				val;
//	
//	p->wtn++;
//	if(!p->wt->set_progress(p->wtn)){
//		return(-1);
//	}
//	geo->getValue(p->prm->srcfield,&val);
//	if(p->prm->tp->fields()->get_constraint_index(p->prm->field,&val)==0){
//		if(!p->prm->tp->fields()->add_constraint(p->prm->field,_double,&val)){
//		}
//		else{
//		}
//	}
//	geo->setValue(p->prm->field,val);
//	return(0);
//}
//
//// ---------------------------------------------------------------------------
//// 
//// ------------
//int bXMapDBStructure::fill_char(void *o, void *prm){
//bGenericGeoElement*	geo=(bGenericGeoElement*)o;
//MCITp*				p=(MCITp*)prm;
//	
//	p->wtn++;
//	if(!p->wt->set_progress(p->wtn)){
//		return(-1);
//	}
//	if(p->init==0){
//		geo->getValue(p->prm->srcfield,(char*)p->val);
//		p->init=1;
//	}
//	geo->setValue(p->prm->field,(char*)p->val);
//	return(0);
//}
//
//// ---------------------------------------------------------------------------
//// 
//// ------------
//int bXMapDBStructure::fill_int(void *o, void *prm){
//bGenericGeoElement*	geo=(bGenericGeoElement*)o;
//MCITp*				p=(MCITp*)prm;
//	
//	p->wtn++;
//	if(!p->wt->set_progress(p->wtn)){
//		return(-1);
//	}
//	if(p->init==0){
//		geo->getValue(p->prm->srcfield,(int*)p->val);
//		p->init=1;
//	}
//	geo->setValue(p->prm->field,(*((int*)p->val)));
//	return(0);
//}
//
//// ---------------------------------------------------------------------------
//// 
//// ------------
//int bXMapDBStructure::fill_double(void *o, void *prm){
//bGenericGeoElement*	geo=(bGenericGeoElement*)o;
//MCITp*				p=(MCITp*)prm;
//	
//	p->wtn++;
//	if(!p->wt->set_progress(p->wtn)){
//		return(-1);
//	}
//	if(p->init==0){
//		geo->getValue(p->prm->srcfield,(double*)p->val);
//		p->init=1;
//	}
//	geo->setValue(p->prm->field,(*((double*)p->val)));
//	return(0);
//}
