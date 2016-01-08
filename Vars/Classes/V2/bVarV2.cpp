//----------------------------------------------------------------------------
// File : bVarV2.cpp
// Project : MacMap
// Purpose : C++ source file : Var "2" interface class
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

#include "bVarV2.h"
#include "bXMLfvar2.h"
#include <MacMapSuite/bString.h>
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bVarV2		::bVarV2(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
			: bStdVar(elt,gapp,bndl){
	setclassname("v2");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bVarV2::~bVarV2(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bVarV2::create(bGenericXMLBaseElement* elt){
	return(new bVarV2(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bVarV2::open(int* flags){
	bStdVar::open(flags);
	_root=(bStdXMLFormulaElement*)new bfvar2Element(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bVarV2::close(){
	bStdVar::close();
	if(_root){
		delete (bfvar2Element*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bVarV2::test(void* prm){
	if(!bStdVar::test(prm)){
		return(false);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
int bVarV2::kind(){
	return(_double);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bVarV2::write(bStdDBValue* val){
	if(!val){
		bStdVar::write(val);
		return;
	}
double	a;
	val->get(&a);
bString	str("");
	str+a;
	WriteMessage(_gapp,str.string());
}
