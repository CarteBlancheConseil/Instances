//----------------------------------------------------------------------------
// File : bCalcCNbVertices.cpp
// Project : MacMap
// Purpose : C++ source file : Calc nb vertices interface class
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

#include "bCalcCNbVertices.h"
#include "bXMLfcalcNbVertices.h"
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bCalcCNbVertices::bCalcCNbVertices(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				: bStdCalc(elt,gapp,bndl){
	setclassname("cnbvertices");
//	_sign='cNvx';
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bCalcCNbVertices::~bCalcCNbVertices(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bCalcCNbVertices::create(bGenericXMLBaseElement* elt){
	return(new bCalcCNbVertices(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCNbVertices::open(int* flags){
	bStdCalc::open(flags);
	_root=(bStdXMLFormulaElement*)new bfcalcNbVerticesElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCNbVertices::close(){
	bStdCalc::close();
	if(_root){
		delete (bfcalcNbVerticesElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
int bCalcCNbVertices::kind(){
	return(_int);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCNbVertices::write(bStdDBValue* val){
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

