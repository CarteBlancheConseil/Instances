//----------------------------------------------------------------------------
// File : bVarV0.cpp
// Project : MacMap
// Purpose : C++ source file : Var "0" interface class
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
// 30/07/2010 creation.
//----------------------------------------------------------------------------

#include "bVarV0.h"
#include "bXMLfvar0.h"
#include <MacMapSuite/bString.h>
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bVarV0		::bVarV0(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
			: bStdVar(elt,gapp,bndl){
	setclassname("v0");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bVarV0::~bVarV0(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bVarV0::create(bGenericXMLBaseElement* elt){
	return(new bVarV0(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bVarV0::open(int* flags){
	bStdVar::open(flags);
	_root=(bStdXMLFormulaElement*)new bfvar0Element(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bVarV0::close(){
	bStdVar::close();
	if(_root){
		delete (bfvar0Element*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bVarV0::test(void* prm){
	if(!bStdVar::test(prm)){
		return(false);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
int bVarV0::kind(){
	return(_double);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bVarV0::write(bStdDBValue* val){
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
