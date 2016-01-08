//----------------------------------------------------------------------------
// File : bXMLSingle.cpp
// Project : MacMap
// Purpose : C++ source file : single iterator tag class, used in formulas
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
// 21/05/2007 creation.
//----------------------------------------------------------------------------

#include "bXMLSingle.h"
#include <MacMapStats/MacMapStats.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bSingleElement	::bSingleElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
			: bStdXMLIteratorElement(elt,gapp,bndl){
	setclassname("single");
	_dbval=new bDoubleDBValue;
	_dbval->put(0);	
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bSingleElement::~bSingleElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bSingleElement::create(bGenericXMLBaseElement* elt){
	return(new bSingleElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bSingleElement::solve(bStdSolver* ctx){
int	first=ctx->count();
	
bGenericXMLFormulaElement*	frm;
	if(_elts.count()>1){
		_elts.get(1,&frm);
		if(!frm->solve(ctx)){
			return(false);
		}
		if(!ctx->rmv(first+1)){	
			return(false);
		}
		_elts.get(2,&frm);
	}
	else{
		_elts.get(1,&frm);
	}
	
bArray						sel(*_gapp->selMgr()->elements());
	if(sel.count()!=1){
		return(ctx->add(_dbval));
	}
bGenericGeoElement			*o,*bk=ctx->get_object();

	sel.get(1,&o);
	ctx->set_object(o);
	if(!frm->solve(ctx)){
		ctx->set_object(bk);
		return(false);
	}
	ctx->set_object(bk);
	return(true);
}

