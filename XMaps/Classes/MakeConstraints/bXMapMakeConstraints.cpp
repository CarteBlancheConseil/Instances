//----------------------------------------------------------------------------
// File : bXMapMakeConstraints.cpp
// Project : MacMap
// Purpose : C++ source file : XMap make constraints class
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
// 19/06/2008 creation.
//----------------------------------------------------------------------------

#include "bXMapMakeConstraints.h"
#include "CocoaStuff.h"
#include <mox_intf/ext_utils.h>
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/bEventLog.h>
#include <mox_intf/mm_messages.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
typedef struct MCITp{
	MakeConstraints_prm*	prm;
	void*					val;
	int						init;
	int						wtn;
	bStdWait*				wt;
}MCITp;

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapMakeConstraints::bXMapMakeConstraints(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
					: bStdXMap(elt,gapp,bndl){
	setclassname("makeconstraints");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapMakeConstraints::~bXMapMakeConstraints(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapMakeConstraints::create(bGenericXMLBaseElement* elt){
	return(new bXMapMakeConstraints(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapMakeConstraints::test(void* prm){
	return(_gapp->typesMgr()->count()>0);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapMakeConstraints::edit(void* prm){
_bTrace_("bXMapMakeConstraints::edit()",true);	
long	result=0;	
	if(prm){
		set_prm(prm);
	}
	else{
		_prm.tp=_gapp->typesMgr()->get(1);
		_prm.field=kOBJ_Dir_+1;
		_prm.srcfield=1;
		_prm.srcuse=kMakeConstraintsUseValue;
	}

bEventLog	log(_gapp,this);
	runCocoaAppModal(this,&result);
	if(result<=0){
	}
	log.close();
	
	return(process(kExtProcessCallFromIntf,prm));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapMakeConstraints::process(int msg, void* prm){
_bTrace_("bXMapMakeConstraints::process()",true);	
	switch(msg){
		case kExtProcessCallFromIntf:
			break;
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
void* bXMapMakeConstraints::get_prm(){
	return(&_prm);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bXMapMakeConstraints::set_prm(const void* prm){
_bTrace_("bXMapMakeConstraints::set_prm()",true);	
MakeConstraints_prm*	tmp=(MakeConstraints_prm*)prm;
	_prm=*tmp;
_tm_("srcfield="+_prm.srcfield);
_tm_("srcuse="+_prm.srcuse);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapMakeConstraints::do_remove(bGenericType* tp,
									 long field,
									 long constraint){
_bTrace_("bXMapMakeConstraints::do_remove",true);
	 if(!tp->fields()->rmv_constraint(field,constraint)){
_te_("remove_constraint failed for "+constraint);
		 return(false);
	 }	
	 return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapMakeConstraints::do_add	(bGenericType* tp,
									 long field,
									 long kind,
									 void* value){
_bTrace_("bXMapMakeConstraints::do_add",true);
	if(!tp->fields()->add_constraint(field,kind,value)){
_te_("add_constraint failed");
		return(false);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapMakeConstraints::do_modify(bGenericType* tp,
									 long field,
									 long constraint,
									 void* value){
_bTrace_("bXMapMakeConstraints::do_modify",true);
	if(!tp->fields()->set_constraint(field,constraint,value)){
_te_("set_constraint failed for "+constraint);
		return(false);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapMakeConstraints::do_make_from_field(bGenericType* tp,
											  long field,
											  long srcfield,
											  bool usevalue){
_bTrace_("bXMapMakeConstraints::do_make_from_field",true);
int                 k;
MakeConstraints_prm prm;
MCITp               pp;

	prm.tp=tp;
	prm.field=field;
	prm.srcfield=srcfield;
	prm.srcuse=usevalue?kMakeConstraintsUseValue:kMakeConstraintsUseLabel;

	pp.prm=&prm;
	pp.init=0;
	
char	mess[__MESSAGE_STRING_LENGTH_MAX__];

	tp->fields()->get_name(srcfield,mess);
	tp->fields()->get_name(field,mess);
	
	get_localized_name(mess,getbundle());
bProgressWait	wt(mess,"",true,prm.tp->nb_live()*2);
	pp.wt=&wt;
	pp.wtn=0;
 	
	if(prm.tp->fields()->count_constraints(prm.field)==0){
		if(prm.srcuse==kMakeConstraintsUseValue){
_tm_("nouvelle contrainte par valeur");
			prm.tp->fields()->get_kind(prm.field,&k);
			switch(k){
				case _char:{
					char	buff[1024];
					pp.val=buff;
					prm.tp->iterator()->iterate(&pp,fill_char);
				}break;
				case _bool:
				case _int:{
					int	buff;
					pp.val=&buff;
					prm.tp->iterator()->iterate(&pp,fill_int);
				}break;
				case _double:
				case _date:
				case _time:{
					double	buff;
					pp.val=&buff;
					prm.tp->iterator()->iterate(&pp,fill_double);
				}break;
			}
		}
		else{
_tm_("nouvelle contrainte par intitulé");
			int	buff=1;
			pp.val=&buff;
			pp.init=1;
			prm.tp->iterator()->iterate(&pp,fill_int);
		}
	}
	
	if(prm.srcuse==kMakeConstraintsUseValue){
		prm.tp->fields()->get_kind(prm.field,&k);
		switch(k){
			case _char:
				prm.tp->iterator()->iterate(&pp,analyse_char);
				break;
			case _bool:
			case _int:
				prm.tp->iterator()->iterate(&pp,analyse_int);
				break;
			case _double:
			case _date:
			case _time:
				prm.tp->iterator()->iterate(&pp,analyse_double);
				break;
		}
	}
	else{
		prm.tp->iterator()->iterate(&pp,analyse_char);
	}
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
int bXMapMakeConstraints::analyse_char(void *o, void *prm){
_bTrace_("bXMapMakeConstraints::analyse_char*",false);
bGenericGeoElement*	geo=(bGenericGeoElement*)o;
MCITp*				p=(MCITp*)prm;
char				val[1024];
int					index;

	p->wtn++;
	if(!p->wt->set_progress(p->wtn)){
		return(-1);
	}
	geo->getValue(p->prm->srcfield,val);
	index=p->prm->tp->fields()->get_constraint_index(p->prm->field,val);
	if(index==0){
		if(!p->prm->tp->fields()->add_constraint(p->prm->field,_char,val)){
_te_("echec ajout contrainte "+val);
		}
		else{
		}
	}
	if(p->prm->srcuse==kMakeConstraintsUseValue){
		geo->setValue(p->prm->field,val);
	}
	else{
		if(index==0){
			index=p->prm->tp->fields()->get_constraint_index(p->prm->field,val);
		}
		geo->setValue(p->prm->field,&index);
	}
	return(0);
}

// ---------------------------------------------------------------------------
// 
// ------------
int bXMapMakeConstraints::analyse_int(void *o, void *prm){
bGenericGeoElement*	geo=(bGenericGeoElement*)o;
MCITp*				p=(MCITp*)prm;
int					val;
	
	p->wtn++;
	if(!p->wt->set_progress(p->wtn)){
		return(-1);
	}
	geo->getValue(p->prm->srcfield,&val);
	if(p->prm->tp->fields()->get_constraint_index(p->prm->field,&val)==0){
		if(!p->prm->tp->fields()->add_constraint(p->prm->field,_int,&val)){
		}
		else{
		}
	}
	geo->setValue(p->prm->field,val);
	return(0);
}

// ---------------------------------------------------------------------------
// 
// ------------
int bXMapMakeConstraints::analyse_double(void *o, void *prm){
bGenericGeoElement*	geo=(bGenericGeoElement*)o;
MCITp*				p=(MCITp*)prm;
double				val;
	
	p->wtn++;
	if(!p->wt->set_progress(p->wtn)){
		return(-1);
	}
	geo->getValue(p->prm->srcfield,&val);
	if(p->prm->tp->fields()->get_constraint_index(p->prm->field,&val)==0){
		if(!p->prm->tp->fields()->add_constraint(p->prm->field,_double,&val)){
		}
		else{
		}
	}
	geo->setValue(p->prm->field,val);
	return(0);
}

// ---------------------------------------------------------------------------
// 
// ------------
int bXMapMakeConstraints::fill_char(void *o, void *prm){
bGenericGeoElement*	geo=(bGenericGeoElement*)o;
MCITp*				p=(MCITp*)prm;
	
	p->wtn++;
	if(!p->wt->set_progress(p->wtn)){
		return(-1);
	}
	if(p->init==0){
		geo->getValue(p->prm->srcfield,(char*)p->val);
		p->init=1;
	}
	geo->setValue(p->prm->field,(char*)p->val);
	return(0);
}

// ---------------------------------------------------------------------------
// 
// ------------
int bXMapMakeConstraints::fill_int(void *o, void *prm){
bGenericGeoElement*	geo=(bGenericGeoElement*)o;
MCITp*				p=(MCITp*)prm;
	
	p->wtn++;
	if(!p->wt->set_progress(p->wtn)){
		return(-1);
	}
	if(p->init==0){
		geo->getValue(p->prm->srcfield,(int*)p->val);
		p->init=1;
	}
	geo->setValue(p->prm->field,(*((int*)p->val)));
	return(0);
}

// ---------------------------------------------------------------------------
// 
// ------------
int bXMapMakeConstraints::fill_double(void *o, void *prm){
bGenericGeoElement*	geo=(bGenericGeoElement*)o;
MCITp*				p=(MCITp*)prm;
	
	p->wtn++;
	if(!p->wt->set_progress(p->wtn)){
		return(-1);
	}
	if(p->init==0){
		geo->getValue(p->prm->srcfield,(double*)p->val);
		p->init=1;
	}
	geo->setValue(p->prm->field,(*((double*)p->val)));
	return(0);
}
