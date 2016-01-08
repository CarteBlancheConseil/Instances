//----------------------------------------------------------------------------
// File : bXMLBgStroke.cpp
// Project : MacMap
// Purpose : C++ source file : background stroke color tag class, used in styles
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

#include "bXMLBgStroke.h"

// ---------------------------------------------------------------------------
// BgStroke
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bBgStrokeElement	::bBgStrokeElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
				: bStdXMLRenderingElement(elt,gapp,bndl){
	setclassname("bgstroke");
	setclasscompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bBgStrokeElement::create(bGenericXMLBaseElement* elt){
	return(new bBgStrokeElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bBgStrokeElement::~bBgStrokeElement(){
}

// ---------------------------------------------------------------------------
// Init
// -----------
void bBgStrokeElement::init(void *ctx){
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
bool bBgStrokeElement::applyforclass(bGenericGraphicContext* ctx){
	ctx->setColorLevel(_backstroke);
bool b=bStdXMLRenderingElement::applyforclass(ctx);
//	ctx->plotColor(); -> non car on risque d'écraser le Stroke dans les CGContext
	return(b);
}

// ---------------------------------------------------------------------------
// Action
// -----------
bool bBgStrokeElement::applyforobject(bGenericGraphicContext* ctx){
	ctx->setColorLevel(_backstroke);
bool b=bStdXMLRenderingElement::applyforobject(ctx);
//	ctx->plotColor(); -> non car on risque d'écraser le Stroke dans les CGContext
	return(b);
}
