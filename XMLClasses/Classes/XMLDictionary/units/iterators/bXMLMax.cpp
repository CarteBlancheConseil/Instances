//----------------------------------------------------------------------------
// File : bXMLMax.cpp
// Project : MacMap
// Purpose : C++ source file : max iterator tag class, used in formulas
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

#include "bXMLMax.h"
#include <MacMapStats/MacMapStats.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bMaxElement	::bMaxElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
			: bStdXMLIteratorElement(elt,gapp,bndl){
	setclassname("max");
	_dbval=new bDoubleDBValue;
	_dbval->put(0);
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bMaxElement::~bMaxElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bMaxElement::create(bGenericXMLBaseElement* elt){
	return(new bMaxElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bMaxElement::solve(bStdSolver* ctx){
//_bTrace_("bMaxElement::solve",false);
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
bGenericGeoElement			*o,*bk=ctx->get_object();
bStdDBValue*				bst;
double						a,b=NAN;

	_dbval->put(NAN);

	_a=NULL;
	bst=NULL;
	for(int i=1;i<=sel.count();i++){
		sel.get(i,&o);
		ctx->set_object(o);
		if(!frm->solve(ctx)){
			ctx->set_object(bk);
//_te_("solve returns false");
			return(false);
		}
		_a=ctx->get(first+1);
		_a->get(&a);
		if(bst==NULL){
			bst=_a;
			b=a;
		}
		else if(a>b){
			b=a;
		}
		if(!ctx->rmv(first+1)){	
			ctx->set_object(bk);
//_te_("ctx->rmv");
			return(false);
		}		
	}
	ctx->set_object(bk);
	if(bst){
		_dbval->put(b);
	}
	return(ctx->add(_dbval));
}

