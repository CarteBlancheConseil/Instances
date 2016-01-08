//----------------------------------------------------------------------------
// File : bCalcCDist.cpp
// Project : MacMap
// Purpose : C++ source file : Calc distance interface class
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

#include "bCalcCDist.h"
#include "bXMLfcalcDist.h"

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bCalcCDist		::bCalcCDist(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				: bStdCalc(elt,gapp,bndl){
	setclassname("cdist");
//	_sign='cDst';
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bCalcCDist::~bCalcCDist(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bCalcCDist::create(bGenericXMLBaseElement* elt){
	return(new bCalcCDist(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCDist::open(int* flags){
	bStdCalc::open(flags);
	_root=(bStdXMLFormulaElement*)new bfcalcDistElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCDist::close(){
	bStdCalc::close();
	if(_root){
		delete (bfcalcDistElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bCalcCDist::test(void* prm){
	if(!bStdCalc::test(prm)){
		return(false);
	}
	return(_gapp->cntMgr()->elements()->count()>0);
}

// ---------------------------------------------------------------------------
// 
// -----------
int bCalcCDist::kind(){
	return(_double);
}
