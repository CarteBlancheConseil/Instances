//----------------------------------------------------------------------------
// File : bCalcCCapLinOri.cpp
// Project : MacMap
// Purpose : C++ source file : Calc CapLinOri interface class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2017 Carte Blanche Conseil.
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
// 28/04/2017 creation.
//----------------------------------------------------------------------------

#include "bCalcCCapLinOri.h"
#include "bXMLfcalcCapLinOri.h"
#include <MacMapSuite/bString.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bCalcCCapLinOri		::bCalcCCapLinOri(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				: bStdCalc(elt,gapp,bndl){
	setclassname("ccaplinori");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bCalcCCapLinOri::~bCalcCCapLinOri(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bCalcCCapLinOri::create(bGenericXMLBaseElement* elt){
	return(new bCalcCCapLinOri(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCCapLinOri::open(int* flags){
	bStdCalc::open(flags);
	_root=(bStdXMLFormulaElement*)new bfcalcCapLinOriElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCCapLinOri::close(){
	bStdCalc::close();
	if(_root){
		delete (bfcalcCapLinOriElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bCalcCCapLinOri::test(void* prm){
	if(!bStdCalc::test(prm)){
		return(false);
	}
bArray*					arr=_gapp->selMgr()->elements();
bGenericGeoElement*		o;
	if(!arr->get(1,&o)){
		return(false);
	}
bGenericType*			tp=_gapp->typesMgr()->get(o->getType());
	return(tp->kind()==kBaseKindPolyline);
}

// ---------------------------------------------------------------------------
// 
// -----------
int bCalcCCapLinOri::kind(){
	return(_double);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCCapLinOri::write(bStdDBValue* val){
	if(!val){
		bStdCalc::write(val);
		return;
	}
double	a;
	val->get(&a);
bString	str("");
	str+a+"°";
	_gapp->statusIntf()->writeMessage((char*)(str.string()));
}
