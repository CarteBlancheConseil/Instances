//----------------------------------------------------------------------------
// File : bVarVNow.cpp
// Project : MacMap
// Purpose : C++ source file : Var "Now" interface class
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
// 06/10/2008 creation.
//----------------------------------------------------------------------------

#include "bVarVNow.h"
#include "bXMLfvarNow.h"
#include <MacMapSuite/bString.h>
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bVarVNow	::bVarVNow(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
			: bStdVar(elt,gapp,bndl){
	setclassname("vnow");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bVarVNow::~bVarVNow(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bVarVNow::create(bGenericXMLBaseElement* elt){
	return(new bVarVNow(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bVarVNow::open(int* flags){
	bStdVar::open(flags);
	_root=(bStdXMLFormulaElement*)new bfvarNowElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bVarVNow::close(){
	bStdVar::close();
	if(_root){
		delete (bfvarNowElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bVarVNow::test(void* prm){
	if(!bStdVar::test(prm)){
		return(false);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
int bVarVNow::kind(){
	return(_time);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bVarVNow::write(bStdDBValue* val){
	if(!val){
		bStdVar::write(val);
		return;
	}
char	t[256];
	val->get(t);
	WriteMessage(_gapp,t);
}
