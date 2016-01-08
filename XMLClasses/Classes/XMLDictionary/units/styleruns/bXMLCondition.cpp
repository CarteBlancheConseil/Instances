//----------------------------------------------------------------------------
// File : bXMLCondition.cpp
// Project : MacMap
// Purpose : C++ source file : condition tag class, used in styles
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
// 06/02/2004 creation.
//----------------------------------------------------------------------------

#include "bXMLCondition.h"
#include <std_ext/bStdXMLFormulaElement.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Condition
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bConditionElement	::bConditionElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
					: bStdXMLRenderingElement(elt,gapp,bndl)
					, _solver(gapp){
	setclassname("condition");
	setobjectcompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bConditionElement::create(bGenericXMLBaseElement* elt){
	return(new bConditionElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bConditionElement::~bConditionElement(){
}

// ---------------------------------------------------------------------------
// Initialisation
// -----------
void bConditionElement::init(void* ctx){
	((bGenericStyle*)ctx)->setcondition(this);	
bGenericType*	tp=((bGenericStyle*)ctx)->gettype();
	_solver.set_type(tp);
	bStdXMLBaseElement::init(&_solver);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bConditionElement::action(bGenericGraphicContext *ctx){
//_bTrace_("bConditionElement::action",false);
//_tm_("");
bool	status=true;
	if(_elts.count()>0){
bGenericXMLFormulaElement*	elt;
bStdDBValue*				val;
bGenericGeoElement*			geo=ctx->getCurElement();
		
		_solver.set_object(geo);
		for(int i=1;i<=_elts.count();i++){
			_solver.reset();
			if(_elts.get(i,&elt)){
				if(!elt->solve(&_solver)){
					status=false;
//trc.err("elt->solve() failed for %d",i);
					break;
				}
			}
			else{
				status=false;
//trc.err("_elts.get() failed for %d",i);
				break;
			}
			if(!_solver.result(&val)){
				status=false;
//trc.err("_solver->result() returns false");
				break;
			}
			val->get(&status);
			if(status==false){
				break;
			}
		}
	}
	_solver.reset();
	return(status);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bConditionElement::applyforscale(bGenericGraphicContext *ctx){
//_bTrace_("bConditionElement::applyforscale",false);
//_tm_("");
	if(!scalecompliant()){
		return(true);
	}
	return(action(ctx));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bConditionElement::applyforclass(bGenericGraphicContext *ctx){
//_bTrace_("bConditionElement::applyforclass",false);
//_tm_("");
	if(!classcompliant()){
		return(true);
	}
	return(action(ctx));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bConditionElement::applyforobject(bGenericGraphicContext *ctx){
//_bTrace_("bConditionElement::applyforobject",false);
//_tm_("");
	if(!objectcompliant()){
		return(true);
	}
	return(action(ctx));
}
