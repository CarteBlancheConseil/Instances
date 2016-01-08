//----------------------------------------------------------------------------
// File : bvDefQuickRasterStyle.cpp
// Project : MacMap
// Purpose : C++ source file : Raster vdef style class
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
// 27/06/2012 creation.
//----------------------------------------------------------------------------

#include "bvDefQuickRasterStyle.h"
#include <limits.h>
#include <Carbon/Carbon.h>
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefQuickRasterStyle	::bvDefQuickRasterStyle(bGenericMacMapApp* gapp,
												bGenericType* gtp,
												int clss)
						:bvDefPaletteQuickStyle(gapp,gtp,clss){
	_fld=kOBJ_Name_;
	_vis=true;
	_alpha=1;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefQuickRasterStyle::~bvDefQuickRasterStyle(){
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefQuickRasterStyle::load(bGenericXMLBaseElement* root){
bGenericXMLBaseElement		*elt,*chld;
char						val[_values_length_max_];
	
	if(!std_load(root)){
// for new subtypes
		_vis=false;
		return(false);
	}
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"raster")){
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fld=_gtp->fields()->get_index(val);
		}
	}
	char	value[_values_length_max_];
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"alpha")){
		elt->getvalue(value);
		_alpha=matof(value);
	}
	else{
		_alpha=1;
	}
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefQuickRasterStyle::dump(bArray& arr, int indent){
char						val[_values_length_max_];
	
	if(!_vis){
		return(true);
	}
	// StyleRun & Validity
	if(!std_dump(arr,indent)){
		return(false);
	}
	// Render
	add_cdesc(arr,indent+2,"render","");
	add_cdesc(arr,indent+3,"fill","");
	add_ddesc(arr,indent+4,"alpha",_alpha,2);
	add_cdesc(arr,indent+3,"raster","");
	_gtp->fields()->get_name(_fld,val);
	add_cdesc(arr,indent+4,"field",val);
	
	// Geometry
	add_cdesc(arr,indent+2,"stdgeometry","");
	add_ddesc(arr,indent+3,"width",0.0,2);
	return(true);
}
