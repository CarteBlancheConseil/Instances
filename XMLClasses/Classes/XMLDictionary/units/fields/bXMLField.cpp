//----------------------------------------------------------------------------
// File : bXMLField.cpp
// Project : MacMap
// Purpose : C++ source file : database field tag class, used in styles
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
// 02/04/2003 creation.
//----------------------------------------------------------------------------

#include "bXMLField.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Field
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bFieldElement	::bFieldElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				: bStdXMLValueElement(elt,gapp,bndl){
	setclassname("field");
	_idx=-1;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bFieldElement::create(bGenericXMLBaseElement* elt){
	return(new bFieldElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bFieldElement::~bFieldElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
void bFieldElement::init(void* ctx){
//_bTrace_("bFieldElement::init",true);
	bStdXMLValueElement::init(ctx);
	if(_ctx){
char	val[_values_length_max_];
		bStdXMLValueElement::getvalue(val);
		_idx=_ctx->fields()->get_index(val);
//_tm_(_idx+" for "+val);
	}
	else{
//_te_("no _ctx");
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
void bFieldElement::getvalue(bGenericGeoElement* geo, char* value){
//_bTrace_("bFieldElement::getvalue(bGenericGeoElement* geo, char* value)",true);
	if((_idx<=0)||(geo==NULL)){
//_te_("(_idx<=0)||(geo==NULL)");
		return;
	}
	geo->getValue(_idx,value);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bFieldElement::getvalue(bGenericGeoElement* geo, bool* value){
	if((_idx<=0)||(geo==NULL)){
		return;
	}
int	val;
	geo->getValue(_idx,&val);
	(*value)=val;
}

// ---------------------------------------------------------------------------
// 
// -----------
void bFieldElement::getvalue(bGenericGeoElement* geo, int* value){
	if((_idx<=0)||(geo==NULL)){
		return;
	}
	geo->getValue(_idx,value);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bFieldElement::getvalue(bGenericGeoElement* geo, double* value){
	if((_idx<=0)||(geo==NULL)){
		return;
	}
	geo->getValue(_idx,value);
}

