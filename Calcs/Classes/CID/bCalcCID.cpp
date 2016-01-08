//----------------------------------------------------------------------------
// File : bCalcCID.cpp
// Project : MacMap
// Purpose : C++ source file : Calc ID interface class
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
// 29/03/2006 creation.
//----------------------------------------------------------------------------

#include "bCalcCID.h"
#include "bXMLfcalcID.h"
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bCalcCID	::bCalcCID(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
			: bStdCalc(elt,gapp,bndl){
	setclassname("cid");
//	_sign='cID_';
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bCalcCID::~bCalcCID(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bCalcCID::create(bGenericXMLBaseElement* elt){
	return(new bCalcCID(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCID::open(int* flags){
	bStdCalc::open(flags);
	_root=(bStdXMLFormulaElement*)new bfcalcIDElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCID::close(){
	bStdCalc::close();
	if(_root){
		delete (bfcalcIDElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCID::write(bStdDBValue* val){
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
int bCalcCID::kind(){
	return(_int);
}


