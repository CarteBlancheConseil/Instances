//----------------------------------------------------------------------------
// File : bXMLPropHVSize.cpp
// Project : MacMap
// Purpose : C++ source file : proportionnal x&y size tag class, used in styles
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
// 22/06/2011 creation.
//----------------------------------------------------------------------------

#include "bXMLPropHVSize.h"
#include <MacMapSuite/bTrace.h>

#pragma mark ->bPropHVSizeElement
// ---------------------------------------------------------------------------
// bPropHVSizeElement
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bPropHVSizeElement	::bPropHVSizeElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
					: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclasscompliant(true);
	setobjectcompliant(true);
	_qref=0;
	_qmax=1;
	_vmax=1;
	_e=1;
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bPropHVSizeElement::~bPropHVSizeElement(){
}

// ---------------------------------------------------------------------------
// Init
// -----------
void bPropHVSizeElement::init(void *ctx){
	bStdXMLLowRenderElement::init(ctx);
	if(_elts.count()<4){
		return;
	}
bStdXMLValueElement*	elt;
char					val[_values_length_max_];

	_elts.get(2,&elt);
	elt->getvalue(val);
	_qref=atof(val);
	
	_elts.get(3,&elt);
	elt->getvalue(val);
	_qmax=atof(val);

	_elts.get(4,&elt);
	elt->getvalue(val);
	_vmax=atof(val);
	
	_e=(_qmax-_qref);
	if(_e==0){
		_e=0.0001;
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bPropHVSizeElement::action(bGenericGraphicContext *ctx){
bGenericGeoElement*		geo=ctx->getCurElement();
	if(geo){
bStdXMLValueElement*	elt;
		_elts.get(1,&elt);
		elt->getvalue(geo,&_iq);
		if(_iq<_qref){
			_ir=0;
		}
		else if(_iq>_qmax){
			_ir=_qmax;
		}
		else{
			_ir=((_iq-_qref)/_e)*_vmax;
		}
		set_size(ctx,_ir);
	}
	else{
		set_size(ctx,_vmax);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// Dummy
// ------------
void bPropHVSizeElement::set_size(bGenericGraphicContext* ctx, 
								  double sz){
}

#pragma mark ->bPropHSizeElement
// ---------------------------------------------------------------------------
// bPropHSizeElement
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bPropHSizeElement	::bPropHSizeElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
					: bPropHVSizeElement(elt,gapp,bndl){
	setclassname("prophsize");
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bPropHSizeElement::create(bGenericXMLBaseElement* elt){
	return(new bPropHSizeElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bPropHSizeElement::~bPropHSizeElement(){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bPropHSizeElement::set_size(bGenericGraphicContext* ctx, 
								 double sz){
	ctx->setHSize(_ir);
}

#pragma mark ->bPropVHSizeElement
// ---------------------------------------------------------------------------
// bPropVSizeElement
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bPropVSizeElement	::bPropVSizeElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
					: bPropHVSizeElement(elt,gapp,bndl){
	setclassname("propvsize");
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bPropVSizeElement::create(bGenericXMLBaseElement* elt){
	return(new bPropVSizeElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bPropVSizeElement::~bPropVSizeElement(){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bPropVSizeElement::set_size(bGenericGraphicContext* ctx, 
								 double sz){
	ctx->setVSize(_ir);
}

