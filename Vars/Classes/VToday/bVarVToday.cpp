//----------------------------------------------------------------------------
// File : bVarVToday.cpp
// Project : MacMap
// Purpose : C++ source file : Var "Today" interface class
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

#include "bVarVToday.h"
#include "bXMLfvarToday.h"
#include <MacMapSuite/bString.h>
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bVarVToday		::bVarVToday(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
			: bStdVar(elt,gapp,bndl){
	setclassname("vtoday");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bVarVToday::~bVarVToday(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bVarVToday::create(bGenericXMLBaseElement* elt){
	return(new bVarVToday(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bVarVToday::open(int* flags){
	bStdVar::open(flags);
	_root=(bStdXMLFormulaElement*)new bfvarTodayElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bVarVToday::close(){
	bStdVar::close();
	if(_root){
		delete (bfvarTodayElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bVarVToday::test(void* prm){
	if(!bStdVar::test(prm)){
		return(false);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
int bVarVToday::kind(){
	return(_date);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bVarVToday::write(bStdDBValue* val){
	if(!val){
		bStdVar::write(val);
		return;
	}
char	t[256];
	val->get(t);
	WriteMessage(_gapp,t);
}
