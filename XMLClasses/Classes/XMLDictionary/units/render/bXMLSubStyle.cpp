//----------------------------------------------------------------------------
// File : bXMLSubStyle.cpp
// Project : MacMap
// Purpose : C++ source file : substyle tag class, used in complex styles
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

#include "bXMLSubStyle.h"
#include <mox_intf/ext_utils.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bSubStyleElement::bSubStyleElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
				:bStdXMLRenderingElement(elt,gapp,bndl)
				,_stl()
				,_arr(sizeof(bGenericXMLBaseElement*)){
	setclassname("substyle");
	setobjectcompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bSubStyleElement::create(bGenericXMLBaseElement* elt){
	return(new bSubStyleElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bSubStyleElement::~bSubStyleElement(){
}

// ---------------------------------------------------------------------------
// Init
// -----------
void bSubStyleElement::init(void *ctx){
	_stl.settype(((bGenericStyle*)ctx)->gettype());
	_stl.setroot(this);
	bStdXMLRenderingElement::init(&_stl);
	dotoall(NULL,0,ocompliant);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bSubStyleElement::applyforscale(bGenericGraphicContext *ctx){
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bSubStyleElement::applyforclass(bGenericGraphicContext *ctx){
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bSubStyleElement::applyforobject(bGenericGraphicContext *ctx){
bGenericGeoElement*				o=ctx->getCurElement();
	if(!o){
		return(true);
	}
	
bStdXMLRenderingElement*		elt;
	_stl.get_styleruns(_arr,o,0,0);
	if(_arr.count()==0){
		return(false);
	}
	for(int i=1;i<=_arr.count();i++){
		_arr.get(i,&elt);
		if(!elt->applyforobject(ctx)){
			return(false);
		}
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bSubStyleElement::ocompliant(bGenericXMLBaseElement* elt, void* prm, int indent){
	if(	(elt->getsubclass()==kXMLClassRendering)		||
		(elt->getsubclass()==kXMLSubClassLowRendering)	){
bStdXMLRenderingElement*	rnd=(bStdXMLRenderingElement*)(void*)elt;
		rnd->setobjectcompliant(true);
	}
	return(true);
}

