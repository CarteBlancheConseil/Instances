//----------------------------------------------------------------------------
// File : bXMLBgFill.cpp
// Project : MacMap
// Purpose : C++ source file : background fill color tag class, used in styles
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
// 05/10/2010 creation.
//----------------------------------------------------------------------------

#include "bXMLBgFill.h"

// ---------------------------------------------------------------------------
// BgFill
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bBgFillElement	::bBgFillElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
				: bStdXMLRenderingElement(elt,gapp,bndl){
	setclassname("bgfill");
	setclasscompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bBgFillElement::create(bGenericXMLBaseElement* elt){
	return(new bBgFillElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bBgFillElement::~bBgFillElement(){
}

// ---------------------------------------------------------------------------
// Init
// -----------
void bBgFillElement::init(void *ctx){
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
bool bBgFillElement::applyforclass(bGenericGraphicContext* ctx){
	ctx->setColorLevel(_backfill);
bool b=bStdXMLRenderingElement::applyforclass(ctx);
//	ctx->plotColor(); -> non car on risque d'écraser le fill dans les CGContext
	return(b);
}

// ---------------------------------------------------------------------------
// Action
// -----------
bool bBgFillElement::applyforobject(bGenericGraphicContext* ctx){
	ctx->setColorLevel(_backfill);
bool b=bStdXMLRenderingElement::applyforobject(ctx);
//	ctx->plotColor(); -> non car on risque d'écraser le fill dans les CGContext
	return(b);
}


// ---------------------------------------------------------------------------
// Back
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bBackElement	::bBackElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
				: bBgFillElement(elt,gapp,bndl){
	setclassname("back");
	setclasscompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bBackElement::create(bGenericXMLBaseElement* elt){
	return(new bBackElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bBackElement::~bBackElement(){
}

