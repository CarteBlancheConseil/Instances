//----------------------------------------------------------------------------
// File : bXMLPropWidth.cpp
// Project : MacMap
// Purpose : C++ source file : proportionnal width tag class, used in styles
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
// 05/04/2007 creation.
//----------------------------------------------------------------------------

#include "bXMLPropWidth.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// bPropWidthElement
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bPropWidthElement	::bPropWidthElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
					: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("propwidth");
	setclasscompliant(true);
	setobjectcompliant(true);
	_qref=1;
	_qmax=1;
	_wref=1;
	_exp=1;
	_rat=1;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bPropWidthElement::create(bGenericXMLBaseElement* elt){
	return(new bPropWidthElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bPropWidthElement::~bPropWidthElement(){
}

// ---------------------------------------------------------------------------
// Init
// -----------
void bPropWidthElement::init(void *ctx){
	bStdXMLLowRenderElement::init(ctx);
	if(_elts.count()<5){
		return;
	}
bStdXMLValueElement*	elt;
char					val[_values_length_max_];
double					sq;

	_elts.get(2,&elt);
	elt->getvalue(val);
	_qref=atof(val);
	
	_elts.get(3,&elt);
	elt->getvalue(val);
	_qmax=atof(val);

	_elts.get(4,&elt);
	elt->getvalue(val);
	_wref=atof(val);
	
	_elts.get(5,&elt);
	elt->getvalue(val);
	_exp=atof(val);

	if(_elts.get(6,&elt)){
		elt->getvalue(val);
		_rat=atof(val);
	}
	else{
		_rat=1;
	}

	sq=pow(_qref,_exp);
	if(sq==0){
		_r=0;
	}
	else{
		_r=_wref/sq;
	}

}

// ---------------------------------------------------------------------------
// 
// -----------
bool bPropWidthElement::action(bGenericGraphicContext *ctx){
bGenericGeoElement*			geo=ctx->getCurElement();
	if(geo){
bStdXMLValueElement*	elt;
		_elts.get(1,&elt);
		elt->getvalue(geo,&_iq);
		if(_iq<_qref){
			_ir=0;
		}
		else if(_iq>_qmax){
			_ir=0;
		}
		else{
			_ir=pow(_iq,_exp)*_r;
		}
		ctx->setWidth(_ir*_rat);
	}
	else{
		ctx->setWidth(_wref*_rat);
	}
	return(true);
}
