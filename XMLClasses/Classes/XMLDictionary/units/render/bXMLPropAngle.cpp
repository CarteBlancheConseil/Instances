//----------------------------------------------------------------------------
// File : bXMLPropAngle.cpp
// Project : MacMap
// Purpose : C++ source file : proportionnal angle tag class, used in styles
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
// 30/06/2008 creation.
//----------------------------------------------------------------------------

#include "bXMLPropAngle.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// bPropAngleElement
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bPropAngleElement	::bPropAngleElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
					: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("propangle");
	setclasscompliant(true);
	setobjectcompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bPropAngleElement::create(bGenericXMLBaseElement* elt){
	return(new bPropAngleElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bPropAngleElement::~bPropAngleElement(){
}

// ---------------------------------------------------------------------------
// Init
// -----------
void bPropAngleElement::init(void *ctx){
	bStdXMLLowRenderElement::init(ctx);
	_cur=0;
	if(_elts.count()<2){
		return;
	}
bStdXMLValueElement*	elt;
char					val[_values_length_max_];

	_elts.get(1,&elt);
	elt->getvalue(val);
	_cur=atoi(val);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bPropAngleElement::action(bGenericGraphicContext *ctx){
bGenericGeoElement*		geo=ctx->getCurElement();
	if(geo){
bStdXMLValueElement*	elt;
		
		_sum=0;		
		for(int i=1;i<_elts.count();i++){
			_elts.get(i+1,&elt);
			elt->getvalue(geo,&_x);
			if(i==_cur){
				_strt=_sum;
				_val=_x;
			}
			_sum+=_x;
		}
		if(_sum>0){
			_x=_strt/_sum*360.0;
			ctx->setStartAngle(_x*M_PI/180.0);
			_x=(_strt+_val)/_sum*360.0;
			ctx->setEndAngle(_x*M_PI/180.0);
		}
		else{
			ctx->setStartAngle(0);
			ctx->setEndAngle(0);
		}
	}
	else{
		ctx->setStartAngle(0);
		ctx->setEndAngle((float)(M_PI*2.0));
	}
	return(true);
}

