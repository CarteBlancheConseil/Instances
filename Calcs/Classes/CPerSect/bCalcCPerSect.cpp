//----------------------------------------------------------------------------
// File : bCalcCPerSect.cpp
// Project : MacMap
// Purpose : C++ source file : Calc intersection percentage interface class
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
// 12/04/2007 creation.
//----------------------------------------------------------------------------

#include "bCalcCPerSect.h"
#include "bXMLfcalcPerSect.h"
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bCalcCPerSect	::bCalcCPerSect(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				: bStdCalc(elt,gapp,bndl){
	setclassname("cpersect");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bCalcCPerSect::~bCalcCPerSect(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bCalcCPerSect::create(bGenericXMLBaseElement* elt){
	return(new bCalcCPerSect(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCPerSect::open(int* flags){
	bStdCalc::open(flags);
	_root=(bStdXMLFormulaElement*)new bfcalcPerSectElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCPerSect::close(){
	bStdCalc::close();
	if(_root){
		delete (bfcalcPerSectElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bCalcCPerSect::test(void* prm){
	if(!bStdCalc::test(prm)){
		return(false);
	}
bArray*					arr=_gapp->selMgr()->elements();
bGenericGeoElement*		o;
	if(!arr->get(1,&o)){
		return(false);
	}
bGenericType*			tp=_gapp->typesMgr()->get(o->getType());
	return((tp->kind()==kBaseKindPolygon)||(tp->kind()==kBaseKindRaster));
}

// ---------------------------------------------------------------------------
// 
// -----------
int bCalcCPerSect::kind(){
	return(_double);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCPerSect::write(bStdDBValue* val){
	if(!val){
		WriteMessage(_gapp,"????");
		return;
	}
double			d;
char			msg[256];
	val->get(&d);
	snprintf(msg,255,"%.2f pct",d);
	WriteMessage(_gapp,msg);
}
