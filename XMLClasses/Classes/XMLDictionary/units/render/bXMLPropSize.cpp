//----------------------------------------------------------------------------
// File : bXMLPropSize.cpp
// Project : MacMap
// Purpose : C++ source file : proportionnal size tag class, used in styles
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
// 27/03/2007 creation.
//----------------------------------------------------------------------------

#include "bXMLPropSize.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// bPropSizeElement
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bPropSizeElement	::bPropSizeElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
					: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("propsize");
	setclasscompliant(true);
	setobjectcompliant(true);
	_qref=1;
	_qmax=1;
	_rref=1;
	_exp=1;
	_rat=1;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bPropSizeElement::create(bGenericXMLBaseElement* elt){
	return(new bPropSizeElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bPropSizeElement::~bPropSizeElement(){
}

// ---------------------------------------------------------------------------
// Init
// -----------
void bPropSizeElement::init(void *ctx){
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
	_rref=atof(val);
	
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

	sq=sqrt(pow(_qref,_exp));
	if(sq==0){
		_r=0;
	}
	else{
		_r=_rref/sq;
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bPropSizeElement::action(bGenericGraphicContext *ctx){
bGenericGeoElement*		geo=ctx->getCurElement();
	if(geo){
bStdXMLValueElement*	elt;
		_elts.get(1,&elt);
		elt->getvalue(geo,&_iq);
		_iq=fabs(_iq);
		if(_iq<_qref){
			_ir=0;
		}
		else if(_iq>_qmax){
			_ir=-sqrt(pow(_iq,_exp))*_r;
		}
		else{
			_ir=sqrt(pow(_iq,_exp))*_r;
		}
		if(_rat==1){
			ctx->setSize(_ir);
		}
		else{
			ctx->setVSize(_ir);
			ctx->setHSize(_ir*_rat);
		}
	}
	else{
		if(_rat==1){
			ctx->setSize(_rref);
		}
		else{
			ctx->setVSize(_rref);
			ctx->setHSize(_rref*_rat);
		}
	}
	return(true);
}

