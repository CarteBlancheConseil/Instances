//----------------------------------------------------------------------------
// File : bCalcCAngle.cpp
// Project : MacMap
// Purpose : C++ source file : Calc angle interface class
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
// 09/12/2005 creation.
//----------------------------------------------------------------------------

#include "bCalcCAngle.h"
#include "bXMLfcalcAngle.h"
#include <MacMapSuite/bString.h>
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bCalcCAngle		::bCalcCAngle(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				: bStdCalc(elt,gapp,bndl){
	setclassname("cangle");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bCalcCAngle::~bCalcCAngle(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bCalcCAngle::create(bGenericXMLBaseElement* elt){
	return(new bCalcCAngle(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCAngle::open(int* flags){
	bStdCalc::open(flags);
	_root=(bStdXMLFormulaElement*)new bfcalcAngleElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCAngle::close(){
	bStdCalc::close();
	if(_root){
		delete (bfcalcAngleElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bCalcCAngle::test(void* prm){
	if(!bStdCalc::test(prm)){
		return(false);
	}
	return(_gapp->cntMgr()->elements()->count()>0);
}

// ---------------------------------------------------------------------------
// 
// -----------
int bCalcCAngle::kind(){
	return(_double);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCAngle::write(bStdDBValue* val){
	if(!val){
		bStdCalc::write(val);
		return;
	}
double	a;
	val->get(&a);
bString	str("");
	str+a+"°";
	WriteMessage(_gapp,(char*)(str.string()));
}
