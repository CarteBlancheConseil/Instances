//----------------------------------------------------------------------------
// File : bvDefPalettePropLine.cpp
// Project : MacMap
// Purpose : C++ source file : proportionnal line vdef class
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
// 29/01/2013 creation.
//----------------------------------------------------------------------------

#include "bvDefPalettePropLine.h"
#include "bvDefPropLineStyle.h"
#include "CocoaStuff.h"
#include <MacMapSuite/bTrace.h>
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/endian.h>
#include <mox_intf/ext_utils.h>
#include <MacMapSuite/valconv.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefPalettePropLine	::bvDefPalettePropLine(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
						: bvDefPaletteProp(elt,gapp,bndl){
	setclassname("palettepropline");
	strcpy(_stylename,"polylinestyle");
	bvDefPaletteProp::oor_put(kvDefPropOutOfRangeInvisible);
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefPalettePropLine::~bvDefPalettePropLine(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bvDefPalettePropLine::create(bGenericXMLBaseElement* elt){
	return(new bvDefPalettePropLine(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPalettePropLine::test(bGenericType* tp){
	if(bStdNSPalettevDef::test(tp)==false){
		return(false);
	}
	if(tp==NULL){
		return(false);
	}
	return((tp->kind()==kBaseKindPolygon)	||
		   (tp->kind()==kBaseKindPolyline)	||
		   (tp->kind()==kBaseKindRaster)	);
}

// ---------------------------------------------------------------------------
// 
// -----------
void* bvDefPalettePropLine::ccinit(){	
	return(initializeCocoa(getapp(),this));
}

// ---------------------------------------------------------------------------
// 
// ------------
void bvDefPalettePropLine::stl_alloc(){
bvDefPropLineStyle*	stl;
	stl=new bvDefPropLineStyle(_gapp,_tp);
	_styles.add(&stl);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bvDefPalettePropLine::stl_free(){
_bTrace_("bvDefPalettePropLine::stl_free()",true);
bvDefPropLineStyle* stl;
	for(int i=1;i<=_styles.count();i++){
		_styles.get(i,&stl);
		delete stl;
	}
	_styles.reset();
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPalettePropLine::read(){
	(void)bvDefPaletteProp::read();
	return(true);
}
