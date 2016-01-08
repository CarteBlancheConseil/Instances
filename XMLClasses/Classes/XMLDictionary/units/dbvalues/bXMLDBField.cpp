//----------------------------------------------------------------------------
// File : bXMLDBField.cpp
// Project : MacMap
// Purpose : C++ source file : database field tag class, used in solvers
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
// 09/03/2004 creation.
//----------------------------------------------------------------------------

#include "bXMLDBField.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bDBFieldElement	::bDBFieldElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				: bStdXMLDBField(elt,gapp,bndl),
				_crv(),
				_blv(),
				_itv(),
				_dbv(),
				_dtv(),
				_tmv(){
	setclassname("dbfield");
	_idx=-1;
	_kind=0;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bDBFieldElement::~bDBFieldElement(){
//_bTrace_("bDBFieldElement::~bDBFieldElement",true);
	_dbval=NULL;// Pour ne pas risquer un delete si le reset n'a pas été fait
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bDBFieldElement::create(bGenericXMLBaseElement* elt){
	return(new bDBFieldElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bDBFieldElement::init(void* ctx){
//_bTrace_("bDBFieldElement::init(void* ctx)",true);
bStdSolver*		_ctx=(bStdSolver*)ctx;
bGenericType*	tp=_ctx->get_type();
	if(!tp){
		return;
	}
char			vl[_values_length_max_];
	strcpy(vl,_cfvalue);
char*			adr=strchr(vl,':');
	if(adr){
		adr[0]=0;
		adr++;
		tp=_gapp->typesMgr()->get(_gapp->typesMgr()->index(vl));
		if(tp==NULL){
			tp=_ctx->get_type();
		}
		_idx=tp->fields()->get_index(adr);
//_tm_("field "+adr+"="+_idx);
	}
	else{
		_idx=tp->fields()->get_index(_cfvalue);
//_tm_("field "+_cfvalue+"="+_idx);
	}
	tp->fields()->get_kind(_idx,&_kind);
	switch(_kind){
		case _char:
			_dbval=&_crv;
			_io=io_chr;
			break;
		case _bool:
			_dbval=&_blv;
			_io=io_int;
			break;
		case _int:
			_dbval=&_itv;
			_io=io_int;
			break;
		case _double:
			_dbval=&_dbv;
			_io=io_dbl;
			break;
		case _date:
			_dbval=&_dtv;
			_io=io_dbl;
			break;
		case _time:
			_dbval=&_tmv;
			_io=io_dbl;
			break;
		default:
//_te_((UInt32*)&_kind+" : bad kind");
			break;
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bDBFieldElement::solve(bStdSolver* ctx){
//_bTrace_("bDBFieldElement::solve(void* ctx)",false);
	if(!_dbval){
//_te_("NULL _dbval");
		return(false);
	}
bGenericGeoElement*	o=ctx->get_object();
	if(!o){
//_te_("NULL o");
		return(true);
		return(false);
	}
	_io(o,_idx,_dbval);
	return(ctx->add(_dbval));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bDBFieldElement::reset(bStdSolver* ctx){
	_idx=-1;
	_kind=0;
	_dbval=NULL;
}

// ---------------------------------------------------------------------------
// 
// -----------
void bDBFieldElement::io_int(	bGenericGeoElement* o,
								int idx,
								bStdDBValue* v){
//_bTrace_("bDBFieldElement::io_int()",false);
int	vl;
	o->getValue(idx,&vl);
	v->put(vl);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bDBFieldElement::io_dbl(	bGenericGeoElement* o,
								int idx,
								bStdDBValue* v){
//_bTrace_("bDBFieldElement::io_dbl()",false);
double	vl;
	o->getValue(idx,&vl);
	v->put(vl);
//_tm_(vl);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bDBFieldElement::io_chr(	bGenericGeoElement* o,
								int idx,
								bStdDBValue* v){
//_bTrace_("bDBFieldElement::io_chr()",false);
char	vl[_values_length_max_];
	o->getValue(idx,vl);
	v->put(vl);
}
