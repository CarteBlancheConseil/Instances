//----------------------------------------------------------------------------
// File : bXMLVirtualLayer.cpp
// Project : MacMap
// Purpose : C++ source file : virtual layer tag class, used in views
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
// 28/01/2009 creation.
//----------------------------------------------------------------------------

#include "bXMLVirtualLayer.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// VirtualLayer
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bVirtualLayerElement::bVirtualLayerElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
					: bStdXMLLayerElement(elt,gapp,bndl){
	setclassname("virtuallayer");
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bVirtualLayerElement::create(bGenericXMLBaseElement* elt){
	return(new bVirtualLayerElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bVirtualLayerElement::~bVirtualLayerElement(){
}

// ---------------------------------------------------------------------------
// Init
// ------------
void bVirtualLayerElement::init(void* ctx){
//    if(((bGenericLayerAccessContext*)ctx)->addvirtuallayer(this)){
    if(((bGenericLayersMgr*)ctx)->addvirtuallayer(this)){
		bStdXMLLayerElement::init(ctx);
	}
	else{
	}
}
