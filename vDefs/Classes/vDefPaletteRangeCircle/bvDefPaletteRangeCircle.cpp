//----------------------------------------------------------------------------
// File : bvDefPaletteRangeCircle.cpp
// Project : MacMap
// Purpose : C++ source file : Range circle vdef class
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
// 26/06/2012 creation.
//----------------------------------------------------------------------------

#include "bvDefPaletteRangeCircle.h"
#include "bvDefRangeCircleStyle.h"
#include "CocoaStuff.h"
#include <MacMapSuite/bTrace.h>
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/endian.h>
#include <mox_intf/ext_utils.h>
#include <MacMapSuite/valconv.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefPaletteRangeCircle	::bvDefPaletteRangeCircle(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
						: bvDefPaletteRange(elt,gapp,bndl){
	setclassname("paletterangecircle");
	strcpy(_stylename,"circlestyle");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefPaletteRangeCircle::~bvDefPaletteRangeCircle(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bvDefPaletteRangeCircle::create(bGenericXMLBaseElement* elt){
	return(new bvDefPaletteRangeCircle(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPaletteRangeCircle::test(bGenericType* tp){
	if(bStdNSPalettevDef::test(tp)==false){
		return(false);
	}
	if(tp==NULL){
		return(false);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
void* bvDefPaletteRangeCircle::ccinit(){	
	return(initializeCocoa(getapp(),this));
}

// ---------------------------------------------------------------------------
// 
// ------------
void bvDefPaletteRangeCircle::stl_alloc(int idx){
bvDefRangeCircleStyle*	stl;
	
	if(!idx){
		for(int i=1;i<_limits.count();i++){
			stl=new bvDefRangeCircleStyle(_gapp,_tp,i);
			_styles.add(&stl);
		}
	}
	else{
bvDefRangeCircleStyle*	prv;
		if(_styles.count()>=1){
			_styles.get(_styles.count(),&prv);
			stl=new bvDefRangeCircleStyle(prv,_limits.count()-1);
		}
		else{
			stl=new bvDefRangeCircleStyle(_gapp,_tp,_limits.count()-1);
		}
		_styles.add(&stl);
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
void bvDefPaletteRangeCircle::stl_free(){
_bTrace_("bvDefPaletteRangeCircle::stl_free()",true);
bvDefRangeCircleStyle* stl;
	for(int i=1;i<=_styles.count();i++){
		_styles.get(i,&stl);
		delete stl;
	}
	_styles.reset();
}

// ---------------------------------------------------------------------------
// 
// ------------
void bvDefPaletteRangeCircle::rebuild_limits(){
bArray	tmp(_styles);
	_styles.reset();
	
bvDefRangeCircleStyle	*prv,*stl;
long				max;
	
	if(tmp.count()<=_limits.count()-1){
		max=tmp.count();
	}
	else{
		max=_limits.count()-1;
	}
	
	for(long i=1;i<=max;i++){
		tmp.get(i,&prv);
		stl=new bvDefRangeCircleStyle(prv,i);
		_styles.add(&stl);
	}
	for(long i=max+1;i<_limits.count();i++){
		stl=new bvDefRangeCircleStyle(_gapp,_tp,i);
        _styles.add(&stl);
	}
	
	for(long i=1;i<=tmp.count();i++){
		tmp.get(i,&stl);
		delete stl;
	}
	
	for(long i=1;i<=_styles.count();i++){
		_styles.get(i,&stl);
		_limits.get(i,&stl->_vmin);
		_limits.get(i+1,&stl->_vmax);
	}	
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPaletteRangeCircle::read(){
	(void)bvDefPaletteRange::read();
bvDefRangeCircleStyle *stl,*prv=NULL;
	for(int i=1;i<=_styles.count();i++){
		_styles.get(i,&prv);
		if(prv->_visible){
			for(i=1;i<=_styles.count();i++){
				_styles.get(i,&stl);
				stl->_width=prv->_width;
				stl->_radius=prv->_radius;
				stl->_centro=prv->_centro;
				stl->_stroke[0]=prv->_stroke[0];
				stl->_stroke[1]=prv->_stroke[1];
				stl->_stroke[2]=prv->_stroke[2];
				stl->_stroke[3]=prv->_stroke[3];
				stl->_stroke[4]=prv->_stroke[4];
			}
			break;
		}
	}
	return(true);
}
