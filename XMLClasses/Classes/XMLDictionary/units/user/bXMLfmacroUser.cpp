//----------------------------------------------------------------------------
// File : bXMLfmacroUser.cpp
// Project : MacMap
// Purpose : C++ source file : user macro tag class, used in formulas
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
// For user macro access, when embeded in user calc
//----------------------------------------------------------------------------
// 10/05/2007 creation.
//----------------------------------------------------------------------------

#include "bXMLfmacroUser.h"
#include <mox_intf/bGenericCalc.h>
#include <mox_intf/endian.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bfmacroUserElement	::bfmacroUserElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
					:bStdXMLFormulaElement(elt,gapp,bndl){
	setclassname("fmacrouser");
	_dbval=new bIntDBValue;
	_ext=NULL;
	_subclss=kXMLSubClassMacro;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bfmacroUserElement::~bfmacroUserElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bfmacroUserElement::create(bGenericXMLBaseElement* elt){
	return(new bfmacroUserElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bfmacroUserElement::init(void* ctx){
//_bTrace_("bfmacroUserElement::init(void* ctx)",true);
//	if(_ext==NULL){
UInt32	k=*((UInt32*)_cfvalue);
#ifdef __LITTLE_ENDIAN__
	LBSwapWord(&k,sizeof(UInt32));
#endif
	_ext=_gapp->macroMgr()->find(k);
	if(!_ext){
//_te_(&k+" : macro not found");
	}
//	}
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bfmacroUserElement::solve(bStdSolver* ctx){
//_bTrace_("bfmacroUserElement::solve(void* ctx)",true);
	if(!_ext){
//_te_("no macro");
		return(false);
	}
// Astuce de la mort : on passe le solver en param 
// pour que la macro et l'éventuelle géog qu'elle
// contient puisse récupérer l'objet sur lequel on
// exécute la calc.
	_ext->process(kExtProcessCallFromIntf,ctx);
	_dbval->put(_gapp->selMgr()->count());
	return(ctx->add(_dbval));
}

