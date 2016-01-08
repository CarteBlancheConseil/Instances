//----------------------------------------------------------------------------
// File : bXMLfvarUser.cpp
// Project : MacMap
// Purpose : C++ source file : user variable/constant tag class, used in formulas
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
// For user var access, when embeded in user calc
//----------------------------------------------------------------------------
// 10/05/2007 creation.
//----------------------------------------------------------------------------

#include "bXMLfvarUser.h"
#include <mox_intf/bGenericCalc.h>
#include <mox_intf/endian.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bfvarUserElement	::bfvarUserElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
					: bStdXMLConstant(elt,gapp,bndl){
	setclassname("fvaruser");
	_root=NULL;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bfvarUserElement::~bfvarUserElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bfvarUserElement::create(bGenericXMLBaseElement* elt){
	return(new bfvarUserElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bfvarUserElement::init(void* ctx){
//	bStdXMLConstant::init(ctx);
//_bTrace_("bfvarUserElement::init(void* ctx)",true);
UInt32	k=*((UInt32*)_cfvalue);
#ifdef __LITTLE_ENDIAN__
	LBSwapWord(&k,sizeof(UInt32));
#endif
bGenericCalc*	clc=(bGenericCalc*)(void*)_gapp->varMgr()->find(k);
	if(clc){
		_root=clc->root();
		if(_root){
			_root->init(ctx);
		}
		else{
//_te_("no root");
		}
	}
	else{
//_te_(&k+" : var not found");
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bfvarUserElement::solve(bStdSolver* ctx){
//_bTrace_("bfvarUserElement::solve(bStdSolver* ctx)",true);
	if(!_root){
		return(false);
	}
	return(_root->solve(ctx));
}

