//----------------------------------------------------------------------------
// File : bVarV1000.cpp
// Project : MacMap
// Purpose : C++ source file : Var "1000" interface class
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

#include "bVarV1000.h"
#include "bXMLfvar1000.h"
#include <MacMapSuite/bString.h>
#include <mox_intf/ext_utils.h>
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bVarV1000	::bVarV1000(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
			: bStdVar(elt,gapp,bndl){
	setclassname("v1000");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bVarV1000::~bVarV1000(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bVarV1000::create(bGenericXMLBaseElement* elt){
	return(new bVarV1000(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bVarV1000::open(int* flags){
	bStdVar::open(flags);
	_root=(bStdXMLFormulaElement*)new bfvar1000Element(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bVarV1000::close(){
	bStdVar::close();
	if(_root){
		delete (bfvar1000Element*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bVarV1000::test(void* prm){
	if(!bStdVar::test(prm)){
		return(false);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
int bVarV1000::kind(){
	return(_double);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bVarV1000::write(bStdDBValue* val){
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
