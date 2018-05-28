//----------------------------------------------------------------------------
// File : bXMLLayer.cpp
// Project : MacMap
// Purpose : C++ source file : layer tag class, used in views
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

#include "bXMLLayer.h"

// ---------------------------------------------------------------------------
// Layer
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bLayerElement	::bLayerElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				: bStdXMLLayerElement(elt,gapp,bndl){
	setclassname("layer");
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bLayerElement::create(bGenericXMLBaseElement* elt){
	return(new bLayerElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bLayerElement::~bLayerElement(){
}

// ---------------------------------------------------------------------------
// Init
// ------------
void bLayerElement::init(void* ctx){
//    if(((bGenericLayerAccessContext*)ctx)->addlayer(this)){
    if(((bGenericLayersMgr*)ctx)->addlayer(this)){
		bStdXMLLayerElement::init(ctx);
	}
	else{
	}
}
