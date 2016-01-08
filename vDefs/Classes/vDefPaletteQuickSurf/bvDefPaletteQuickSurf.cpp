//----------------------------------------------------------------------------
// File : bvDefPaletteQuickSurf.cpp
// Project : MacMap
// Purpose : C++ source file : Polygon vdef style class
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
// 22/06/2012 creation.
//----------------------------------------------------------------------------

#include "bvDefPaletteQuickSurf.h"
#include "bvDefQuickSurfStyle.h"
#include "CocoaStuff.h"
#include <MacMapSuite/bTrace.h>
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/endian.h>
#include <mox_intf/ext_utils.h>
#include <MacMapSuite/valconv.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefPaletteQuickSurf	::bvDefPaletteQuickSurf(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
						: bvDefPaletteQuick(elt,gapp,bndl){
	setclassname("palettequicksurf");
	strcpy(_stylename,"polygonstyle");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefPaletteQuickSurf::~bvDefPaletteQuickSurf(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bvDefPaletteQuickSurf::create(bGenericXMLBaseElement* elt){
	return(new bvDefPaletteQuickSurf(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPaletteQuickSurf::test(bGenericType* tp){
	if(bStdNSPalettevDef::test(tp)==false){
		return(false);
	}
	if(tp==NULL){
		return(false);
	}
	return(	(tp->kind()==kBaseKindPolygon)	||
			(tp->kind()==kBaseKindRaster)	);
}


// ---------------------------------------------------------------------------
// 
// -----------
void* bvDefPaletteQuickSurf::ccinit(){	
	return(initializeCocoa(getapp(),this));
}

// ---------------------------------------------------------------------------
// 
// ------------
void bvDefPaletteQuickSurf::stl_alloc(){
_bTrace_("bvDefPaletteQuickSurf::stl_alloc()",true);
int						n=_tp->fields()->count_constraints(_fld);
int						k=_tp->fields()->get_constraints_kind(_fld);
int						ib;
bvDefQuickSurfStyle*	stl;
double					cmin,cmax;
	
	for(int i=1;i<=n;i++){
		switch(k){
			case _int:
			case _bool:
				_tp->fields()->get_constraint(_fld,i,&ib);
				cmin=ib;
				if(i==n){
					cmax=cmin+1;
				}
				else{
					_tp->fields()->get_constraint(_fld,i+1,&ib);
					cmax=ib;
				}
				break;
			case _double:
			case _date:
			case _time:
				_tp->fields()->get_constraint(_fld,i,&cmin);
				if(i==n){
					cmax=cmin+1;
				}
				else{
					_tp->fields()->get_constraint(_fld,i+1,&cmax);
				}
				break;
			default:
				cmin=i;
				cmax=i+1;
				break;
		}
		stl=new bvDefQuickSurfStyle(_gapp,_tp,i);
		if(_cmyk){
			stl->_cc=5;
		}
		_styles.add(&stl);
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
void bvDefPaletteQuickSurf::stl_free(){
_bTrace_("bvDefPaletteQuickSurf::stl_free()",true);
bvDefQuickSurfStyle* stl;
	for(int i=1;i<=_styles.count();i++){
		_styles.get(i,&stl);
		delete stl;
	}
	_styles.reset();
}

