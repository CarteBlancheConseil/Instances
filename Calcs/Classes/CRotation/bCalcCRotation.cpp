//----------------------------------------------------------------------------
// File : bCalcCRotation.cpp
// Project : MacMap
// Purpose : C++ source file : Calc rotation interface class
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
// 30/10/2006 creation.
//----------------------------------------------------------------------------

#include "bCalcCRotation.h"
#include "bXMLfcalcRotation.h"
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bCalcCRotation	::bCalcCRotation(	bGenericXMLBaseElement* elt, 
									bGenericMacMapApp* gapp, 
									CFBundleRef bndl) 
				: bStdCalc(elt,gapp,bndl){
	setclassname("crotation");
	_sign='cRot';
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bCalcCRotation::~bCalcCRotation(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bCalcCRotation::create(bGenericXMLBaseElement* elt){
	return(new bCalcCRotation(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCRotation::open(int* flags){
	bStdCalc::open(flags);
	_root=(bStdXMLFormulaElement*)new bfcalcRotationElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCRotation::close(){
	bStdCalc::close();
	if(_root){
		delete (bfcalcRotationElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bCalcCRotation::test(void* prm){
	if(!bStdCalc::test(prm)){
		return(false);
	}
bArray*				arr=_gapp->selMgr()->elements();
bGenericGeoElement*	o;
	if(!arr->get(1,&o)){
		return(false);
	}
bGenericType*		tp=_gapp->typesMgr()->get(o->getType());
	return(tp->kind()==kBaseKindPolygon);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCRotation::write(bStdDBValue* val){
	if(!val){
		bStdCalc::write(val);
		return;
	}
int		n;
	val->get(&n);
char	str[256];
	sprintf(str,"%d",n);
	WriteMessage(_gapp,str);
}

// ---------------------------------------------------------------------------
// 
// -----------
int bCalcCRotation::kind(){
	return(_int);
}

