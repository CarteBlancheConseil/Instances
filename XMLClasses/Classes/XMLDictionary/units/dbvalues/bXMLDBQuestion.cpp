//----------------------------------------------------------------------------
// File : bXMLDBQuestion.cpp
// Project : MacMap
// Purpose : C++ source file : question tag class, used in selection solvers for user value query
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
// 09/03/2004 creation.
//----------------------------------------------------------------------------

#include "bXMLDBQuestion.h"
#include <MacMapSuite/bTrace.h>
#include <MacMapSuite/valconv.h>
#include <mox_intf/ext_utils.h>
#include <mox_intf/Carb_Utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bDBQuestionElement	::bDBQuestionElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
					: bStdXMLConstant(elt,gapp,bndl){
	setclassname("dbquestion");
	_dbval=new bCharDBValue;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bDBQuestionElement::~bDBQuestionElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bDBQuestionElement::create(bGenericXMLBaseElement* elt){
	return(new bDBQuestionElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bDBQuestionElement::init(void* ctx){
//_bTrace_("bDBQuestionElement::init",true);	
	bStdXMLConstant::init(ctx);

bStdSolver*		solver=(bStdSolver*)ctx;
bGenericType*	tp=solver->get_type();
	if(!tp){
		return;
	}
char			vl[_values_length_max_];
	strcpy(vl,_cfvalue);
char*			adr1=strchr(vl,':');
char*			adr2=NULL;
	if(adr1){
		adr1[0]=0;
		adr1++;
		adr2=strchr(adr1,':');
	}

int				idx=0;

	if(adr1&&adr2){// 2 séparateurs = type+champ/calc+prompt
//_tm_("adr1&&adr2");
		adr2[0]=0;
		adr2++;
		tp=_gapp->typesMgr()->get(_gapp->typesMgr()->index(vl));
		if(tp==NULL){
			tp=solver->get_type();
		}
		idx=tp->fields()->get_index(adr1);
//		sprintf(vl,adr2);
		strcpy(vl,adr2);
//_tm_(adr1+"->"+adr1+"->"+vl);
//_tm_("idx="+idx);
	}
	else if(adr1){// 1 séparateur = champ/calc+prompt
//_tm_("adr1");
		idx=tp->fields()->get_index(vl);
//_tm_(adr1+"->"+vl);
//_tm_("idx="+idx);
//		sprintf(vl,adr1);
		strcpy(vl,adr1);
	}
	else{// Houla ! Bon ben on va considérer que c'est le prompt
//_tm_("!adr1&&!adr2");
//_tm_(vl);
		// Du coup, rien à faire
	}
	
char			value[_values_length_max_]="";
	GetAValue(tp,idx,vl,value);
	_dbval->put(value);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bDBQuestionElement::solve(bStdSolver* ctx){
	return(ctx->add(_dbval));
}
