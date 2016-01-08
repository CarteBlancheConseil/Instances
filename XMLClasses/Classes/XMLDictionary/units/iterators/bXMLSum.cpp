//----------------------------------------------------------------------------
// File : bXMLSum.cpp
// Project : MacMap
// Purpose : C++ source file : sum iterator tag class, used in formulas
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
// 16/05/2007 creation.
//----------------------------------------------------------------------------

#include "bXMLSum.h"
#include <MacMapStats/MacMapStats.h>
//#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bSumElement	::bSumElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
			: bStdXMLIteratorElement(elt,gapp,bndl){
	setclassname("sum");
	_dbval=new bDoubleDBValue;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bSumElement::~bSumElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bSumElement::create(bGenericXMLBaseElement* elt){
	return(new bSumElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bSumElement::solve(bStdSolver* ctx){
//_bTrace_("bSumElement::solve(void* ctx)",false);
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
MMsMatrix*					mmx=MMsMatrixAlloc(sel.count(),1);
double						v;

//_tm_(sel.count()+" selected");
	for(int i=1;i<=sel.count();i++){
		sel.get(i,&o);
		ctx->set_object(o);
		if(!frm->solve(ctx)){
			MMsMatrixFree(mmx);
			ctx->set_object(bk);
			return(false);
		}
		_a=ctx->get(first+1);
		_a->get(&v);
		if(!ctx->rmv(first+1)){	
			MMsMatrixFree(mmx);
			ctx->set_object(bk);
			return(false);
		}
		MMsSetDouble(mmx,i,1,v);
	}
	ctx->set_object(bk);
	v=MMsSum(1,mmx);
	MMsMatrixFree(mmx);
	_dbval->put(v);
	return(ctx->add(_dbval));
}

