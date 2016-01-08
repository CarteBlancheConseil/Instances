//----------------------------------------------------------------------------
// File : bXMLPropColor.cpp
// Project : MacMap
// Purpose : C++ source file : proportionnal color tag class, used in styles
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
// 30/06/2008 creation.
//----------------------------------------------------------------------------

#include "bXMLPropColor.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// bPropColorElement
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bPropColorElement	::bPropColorElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
					: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("propcolor");
	setclasscompliant(true);
	setobjectcompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bPropColorElement::create(bGenericXMLBaseElement* elt){
	return(new bPropColorElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bPropColorElement::~bPropColorElement(){
}

// ---------------------------------------------------------------------------
// Init
// -----------
void bPropColorElement::init(void *ctx){
	bStdXMLLowRenderElement::init(ctx);
	_ncc=0;
	if(_elts.count()<10){
		return;
	}
bStdXMLValueElement*	elt;
char					val[_values_length_max_];

	_elts.get(2,&elt);
	elt->getvalue(val);
	_qmin=atof(val);
	
	_elts.get(3,&elt);
	elt->getvalue(val);
	_qmax=atof(val);

	_ncc=(_elts.count()-3)/2;
	if(_ncc>5){
		_ncc=5;
	}
	for(int i=0;i<_ncc;i++){
		_elts.get(i+4,&elt);
		elt->getvalue(val);
		_cmin[i]=atof(val);
		
		_elts.get(i+4+_ncc,&elt);
		elt->getvalue(val);
		_cmax[i]=atof(val);
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bPropColorElement::action(bGenericGraphicContext *ctx){
bGenericGeoElement*			geo=ctx->getCurElement();
	if(geo){
bStdXMLValueElement*	elt;
		
		_elts.get(1,&elt);
		elt->getvalue(geo,&_x);
		_x-=_qmin;
		_x/=(_qmax-_qmin);
		for(int i=0;i<_ncc;i++){
			_c[i]=_cmin[i]+_x*(_cmax[i]-_cmin[i]);
		}
		if(_ncc==4){//RGB
			ctx->setRed(_c[0]);
			ctx->setGreen(_c[1]);
			ctx->setBlue(_c[2]);
			ctx->setAlpha(_c[3]);
		}
		else if(_ncc==5){//CMYK
			ctx->setCyan(_c[0]);
			ctx->setMagenta(_c[1]);
			ctx->setYellow(_c[2]);
			ctx->setBlack(_c[3]);		
			ctx->setAlpha(_c[4]);		
		}
		else{//????
			ctx->setRed(0);
			ctx->setGreen(0);
			ctx->setBlue(0);
			ctx->setAlpha(1);
		}
	}
	else{
		ctx->setRed(0);
		ctx->setGreen(0);
		ctx->setBlue(0);
		ctx->setAlpha(1);
	}
	return(true);
}

