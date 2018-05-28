//----------------------------------------------------------------------------
// File : bXMLFillPattern.cpp
// Project : MacMap
// Purpose : C++ source file : fill pattern tag class, used in styles
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
// 30/05/2006 creation.
//----------------------------------------------------------------------------

#include "bXMLFillPattern.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// FillPattern
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bFillPatternElement	::bFillPatternElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
					: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("fillpattern");
	setclasscompliant(true);
	_data=NULL;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bFillPatternElement::create(bGenericXMLBaseElement* elt){
	return(new bFillPatternElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bFillPatternElement::~bFillPatternElement(){
}

// ---------------------------------------------------------------------------
// Init
// -----------
void bFillPatternElement::init(void *ctx){
	if(_data){
		free(_data);
		_data=NULL;
	}
	_sz=0;
	_last[0]=0;
	bStdXMLLowRenderElement::init(ctx);
	_tp=((bGenericStyle*)ctx)->gettype();
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bFillPatternElement::actionval(bGenericGraphicContext* ctx,
									bStdXMLValueElement* elt,
									bGenericGeoElement* geo){
char	val[_values_length_max_];
	elt->getvalue(geo,val);	
	if(strlen(val)==0){
		ctx->setFillPattern(NULL,0,"");
		return(false);
	}
	if(!strcmp(_last,val)){
		ctx->setFillPattern(_data,_sz,val);
		return(_data!=NULL);
	}
	if(_data){
		strcpy(_last,"");
		free(_data);
		_data=NULL;
		_sz=0;
	}
	if(!_tp->fields()->get_param("patterns",val,&_data,&_sz)){
		return(false);
	}
	strcpy(_last,val);
	ctx->setFillPattern(_data,_sz,val);
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bFillPatternElement::actionstd(bGenericGraphicContext* ctx){
char	val[_values_length_max_];
	ctx->setColorLevel(_fill);
	ctx->setAlpha(1);	
	if(objectcompliant()){
bStdXMLValueElement*	elt=find_value();
		if(elt==NULL){
			return(true);
		}
		elt->getvalue(NULL,val);
	}
	else{
		getvalue(val);
	}
	if(_data==NULL){
		if(strlen(val)==0){
			ctx->setFillPattern(NULL,0,"");
            //return(objectcompliant());
            return(false);
		}
		if(!_tp->fields()->get_param("patterns",val,&_data,&_sz)){
			ctx->setFillPattern(NULL,0,"");
            //return(objectcompliant());
            return(false);
		}
		strcpy(_last,val);
	}
	ctx->setFillPattern(_data,_sz,val);
	if(_data==NULL){
		return(objectcompliant());
	}
	return(true);
}
