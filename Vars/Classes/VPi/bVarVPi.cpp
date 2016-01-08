//----------------------------------------------------------------------------
// File : bVarVPi.cpp
// Project : MacMap
// Purpose : C++ source file : Var "π" interface class
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

#include "bVarVPi.h"
#include "bXMLfvarPi.h"
#include <MacMapSuite/bString.h>
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bVarVPi		::bVarVPi(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
			: bStdVar(elt,gapp,bndl){
	setclassname("vpi");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bVarVPi::~bVarVPi(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bVarVPi::create(bGenericXMLBaseElement* elt){
	return(new bVarVPi(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bVarVPi::open(int* flags){
	bStdVar::open(flags);
	_root=(bStdXMLFormulaElement*)new bfvarPiElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bVarVPi::close(){
	bStdVar::close();
	if(_root){
		delete (bfvarPiElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bVarVPi::test(void* prm){
	if(!bStdVar::test(prm)){
		return(false);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
int bVarVPi::kind(){
	return(_double);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bVarVPi::write(bStdDBValue* val){
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
