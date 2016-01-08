//----------------------------------------------------------------------------
// File : bCalcCPerimeter.cpp
// Project : MacMap
// Purpose : C++ source file : Calc perimeter interface class
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
// 01/12/2005 creation.
//----------------------------------------------------------------------------

#include "bCalcCPerimeter.h"
#include "bXMLfcalcPerimeter.h"

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bCalcCPerimeter	::bCalcCPerimeter(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				: bStdCalc(elt,gapp,bndl){
	setclassname("cperimeter");
//	_sign='cPer';
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bCalcCPerimeter::~bCalcCPerimeter(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bCalcCPerimeter::create(bGenericXMLBaseElement* elt){
	return(new bCalcCPerimeter(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCPerimeter::open(int* flags){
	bStdCalc::open(flags);
	_root=(bStdXMLFormulaElement*)new bfcalcPerimeterElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCPerimeter::close(){
	bStdCalc::close();
	if(_root){
		delete (bfcalcPerimeterElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bCalcCPerimeter::test(void* prm){
	if(!bStdCalc::test(prm)){
		return(false);
	}
bArray*				arr=_gapp->selMgr()->elements();
bGenericGeoElement*	o;
	if(!arr->get(1,&o)){
		return(false);
	}
bGenericType*		tp=_gapp->typesMgr()->get(o->getType());
	return((tp->kind()==kBaseKindPolygon)||(tp->kind()==kBaseKindRaster));
}

// ---------------------------------------------------------------------------
// 
// -----------
int bCalcCPerimeter::kind(){
	return(_double);
}

