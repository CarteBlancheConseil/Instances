//----------------------------------------------------------------------------
// File : bXMLStrSntFCUpr.cpp
// Project : MacMap
// Purpose : C++ source file : upper case first letter function tag class, used in formulas
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
// 29/12/2006 creation.
//----------------------------------------------------------------------------

#include "bXMLStrSntFCUpr.h"
#include <MacMapSuite/C_Utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bStrSntFCUprElement	::bStrSntFCUprElement(	bGenericXMLBaseElement* elt, 
											bGenericMacMapApp* gapp, 
											CFBundleRef bndl ) 
				: bStdXMLFunctionElement(elt,gapp,bndl){
	setclassname("strsntfcupr");
	_dbval=new bCharDBValue;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bStrSntFCUprElement::~bStrSntFCUprElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bStrSntFCUprElement::create(bGenericXMLBaseElement* elt){
	return(new bStrSntFCUprElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bStrSntFCUprElement::solve(bStdSolver* ctx){
	if(!bStdXMLFunctionElement::solve(ctx)){
		return(false);
	}
char	va[_values_length_max_]="";
	_a->get(va);
	strupperfcs(va);
	_dbval->put(va);
	return(ctx->add(_dbval));
}
