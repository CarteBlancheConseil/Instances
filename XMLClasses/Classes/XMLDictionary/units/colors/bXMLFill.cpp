//----------------------------------------------------------------------------
// File : bXMLFill.cpp
// Project : MacMap
// Purpose : C++ source file : fill color tag class, used in styles
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
// 02/04/2003 creation.
//----------------------------------------------------------------------------

#include "bXMLFill.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Fill
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bFillElement	::bFillElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
				: bStdXMLRenderingElement(elt,gapp,bndl){
	setclassname("fill");
	setclasscompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bFillElement::create(bGenericXMLBaseElement* elt){
	return(new bFillElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bFillElement::~bFillElement(){
}

// ---------------------------------------------------------------------------
// Init
// -----------
void bFillElement::init(void *ctx){
	bStdXMLRenderingElement::init(ctx);
	if(objectcompliant()){
bStdXMLRenderingElement*	elt;
		for(int i=1;i<=_elts.count();i++){
			_elts.get(i,&elt);
			elt->setobjectcompliant(true);
		}
	}
}

// ---------------------------------------------------------------------------
// Action
// -----------
bool bFillElement::applyforclass(bGenericGraphicContext* ctx){
	ctx->setColorLevel(_fill);
	bool b=bStdXMLRenderingElement::applyforclass(ctx);
	ctx->plotColor();
	return(b);
}

// ---------------------------------------------------------------------------
// Action
// -----------
bool bFillElement::applyforobject(bGenericGraphicContext* ctx){
	ctx->setColorLevel(_fill);
	bool b=bStdXMLRenderingElement::applyforobject(ctx);
	ctx->plotColor();
	return(b);
}
