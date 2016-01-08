//----------------------------------------------------------------------------
// File : bXBoxMacro.cpp
// Project : MacMap
// Purpose : C++ source file : Macros XMapBox class
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
// 20/01/2015 creation.
//----------------------------------------------------------------------------

#include "bXBoxMacro.h"
#include "CocoaStuff.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXBoxMacro	::bXBoxMacro(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
            : bStdNSXBox(elt,gapp,bndl){
	setclassname("xboxmacro");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXBoxMacro::~bXBoxMacro(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXBoxMacro::create(bGenericXMLBaseElement* elt){
	return(new bXBoxMacro(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void* bXBoxMacro::ccinit(){
	return(initializeCocoa(getapp(),this));
}
