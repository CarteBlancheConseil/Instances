//----------------------------------------------------------------------------
// File : bCalcCUpdtTime.cpp
// Project : MacMap
// Purpose : C++ source file : Calc modification time interface class
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
// 21/02/2007 creation.
//----------------------------------------------------------------------------

#include "bCalcCUpdtTime.h"
#include "bXMLfcalcUpdtTime.h"
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bCalcCUpdtTime	::bCalcCUpdtTime(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				: bStdCalc(elt,gapp,bndl){
	setclassname("updttime");
//	_sign='cUTm';
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bCalcCUpdtTime::~bCalcCUpdtTime(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bCalcCUpdtTime::create(bGenericXMLBaseElement* elt){
	return(new bCalcCUpdtTime(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCUpdtTime::open(int* flags){
	bStdCalc::open(flags);
	_root=(bStdXMLFormulaElement*)new bfcalcUpdtTimeElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCUpdtTime::close(){
	bStdCalc::close();
	if(_root){
		delete (bfcalcUpdtTimeElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCUpdtTime::write(bStdDBValue* val){
	if(!val){
		bStdCalc::write(val);
		return;
	}
char	vl[256];
	val->get(vl);
	WriteMessage(_gapp,vl);
}

// ---------------------------------------------------------------------------
// 
// -----------
int bCalcCUpdtTime::kind(){
	return(_time);
}


