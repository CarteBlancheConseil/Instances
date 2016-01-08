//----------------------------------------------------------------------------
// File : bCalcCArea.cpp
// Project : MacMap
// Purpose : C++ source file : Calc area interface class
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
// 01/12/2005 creation.
//----------------------------------------------------------------------------

#include "bCalcCArea.h"
#include "bXMLfcalcArea.h"
#include <MacMapSuite/bString.h>
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bCalcCArea		::bCalcCArea(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				: bStdCalc(elt,gapp,bndl){
	setclassname("carea");
	//_sign='cAre';
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bCalcCArea::~bCalcCArea(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bCalcCArea::create(bGenericXMLBaseElement* elt){
	return(new bCalcCArea(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCArea::open(int* flags){
	bStdCalc::open(flags);
	_root=(bStdXMLFormulaElement*)new bfcalcAreaElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCArea::close(){
	bStdCalc::close();
	if(_root){
		delete (bfcalcAreaElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bCalcCArea::test(void* prm){
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
int bCalcCArea::kind(){
	return(_double);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCArea::write(bStdDBValue* val){
	if(!val){
		WriteMessage(_gapp,"????");
		return;
	}
double			d;
bGenericUnit*	up=_gapp->distMgr()->get();
char			u[256];
char			str[256];
	val->get(&d);
	up->short_name(u);
	sprintf(str,"%.*f %s2",_gapp->document()->dist_pref_digits(),d,u);
	WriteMessage(_gapp,str);
}
