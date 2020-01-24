//----------------------------------------------------------------------------
// File : bvDefRangeCircleStyle.cpp
// Project : MacMap
// Purpose : C++ source file : Range circle vdef style class
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

#include "bvDefRangeCircleStyle.h"
#include <limits.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefRangeCircleStyle	::bvDefRangeCircleStyle(bGenericMacMapApp* gapp,
												bGenericType* gtp,
												int clss)
						:bvDefPaletteRangeStyle(gapp,gtp,clss){
_bTrace_("bvDefRangeCircleStyle::bvDefRangeCircleStyle",true);
	_width=0;
	_stroke[0]=0;
	_stroke[1]=0;
	_stroke[2]=0;
	_stroke[3]=1;
	_stroke[4]=1;
	strcpy(_pat,"");
	_radius=3;
	_centro=true;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefRangeCircleStyle	::bvDefRangeCircleStyle(bvDefRangeCircleStyle* stl,
												int clss)
						:bvDefPaletteRangeStyle(stl,clss){
_bTrace_("bvDefRangeCircleStyle::bvDefRangeCircleStyle",true);
	_width=stl->_width;
	_stroke[0]=stl->_stroke[0];
	_stroke[1]=stl->_stroke[1];
	_stroke[2]=stl->_stroke[2];
	_stroke[3]=stl->_stroke[3];
	_stroke[4]=stl->_stroke[4];
	strcpy(_pat,stl->_pat);
	_radius=stl->_radius;
	_centro=stl->_centro;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefRangeCircleStyle::~bvDefRangeCircleStyle(){
_bTrace_("bvDefRangeCircleStyle::~bvDefRangeCircleStyle",true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefRangeCircleStyle::load(bGenericXMLBaseElement* root){
bGenericXMLBaseElement		*chld,*elt;
char						val[_values_length_max_];
	
	if(!std_load(root)){
		return(false);
	}
	
	if(chld=_gapp->classMgr()->NthElement(_gstl,1,"stroke")){
		if(!prop_load(chld)){
			color_load(chld,_stroke);
		}
	}
	
	if(chld=_gapp->classMgr()->NthElement(_gstl,1,"fill")){
		if(!prop_load(chld)){
			color_load(chld,_fcolor);
		}
	}
	else if(chld=_gapp->classMgr()->NthElement(_gstl,1,"fillpattern")){
		chld->getvalue(_pat);
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"size")){
		elt->getvalue(val);
		_radius=matof(val);
	}
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"width")){
		elt->getvalue(val);
		_width=matof(val);
	}
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"centroid")){
		elt->getvalue(val);
		_centro=atoi(val);
	}
	else{
		_centro=false;
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefRangeCircleStyle::dump(bArray& arr, int indent){
_bTrace_("bvDefRangeCircleStyle::dump",true);
	if(!_visible){
_tm_("not visible");
		return(true);
	}
	if(_radius==0){
_tm_("_radius == 0");
		return(true);
	}
	if(strlen(_fld)==0){
		if(strlen(_pat)==0){
			if((_width<=0)&&(_fcolor[_cc-1]<=0)){
_tm_("(_width<=0)&&(_fcolor[_cc-1]<=0)");
				return(true);
			}
		}
	}
	else{
		if((_width<=0)&&(_fcolor[_cc-1]<=0)&&(_tcolor[_cc-1]<=0)){
_tm_("((_width<=0)&&(_fcolor[_cc-1]<=0)&&(_tcolor[_cc-1]<=0))");
			return(true);
		}			
	}
	
// StyleRun & Validity
	if(!std_dump(arr,indent)){
_tm_("!std_dump(arr,indent)");
		return(false);
	}
// Render
	add_cdesc(arr,indent+2,"render","");
	add_cdesc(arr,indent+3,"stroke","");
	color_dump(arr,indent+4,_stroke);
	if(strlen(_pat)==0){
		add_cdesc(arr,indent+3,"fill","");
		if(!prop_dump(arr,indent+4)){
			color_dump(arr,indent+4,_fcolor);
		}
	}
	else{
		add_cdesc(arr,indent+3,"fillpattern",_pat);
	}
	add_cdesc(arr,indent+3,"dash","");
// Geometry
	add_cdesc(arr,indent+2,"stdgeometry","");
	if(!off_dump(arr,indent)){
_tm_("!off_dump(arr,indent)");
		return(false);
	}
	add_ddesc(arr,indent+3,"size",_radius,2);
	add_ddesc(arr,indent+3,"width",_width,2);
	if(_centro){
		add_idesc(arr,indent+3,"centroid",1);
	}
	return(true);
}

