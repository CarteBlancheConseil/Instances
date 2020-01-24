//----------------------------------------------------------------------------
// File : bvDefRangeSurfStyle.cpp
// Project : MacMap
// Purpose : C++ source file : Choropleth vdef style class
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
// 30/08/2012 creation.
//----------------------------------------------------------------------------

#include "bvDefRangeSurfStyle.h"
#include <limits.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefRangeSurfStyle	::bvDefRangeSurfStyle(bGenericMacMapApp* gapp,
										  bGenericType* gtp,
										  int clss)
					:bvDefPaletteRangeStyle(gapp,gtp,clss){
_bTrace_("bvDefRangeSurfStyle::bvDefRangeSurfStyle",true);
	_width=0;
	_stroke[0]=0;
	_stroke[1]=0;
	_stroke[2]=0;
	_stroke[3]=1;
	_stroke[4]=1;
	strcpy(_pat,"");
	_smooth=false;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefRangeSurfStyle	::bvDefRangeSurfStyle(bvDefRangeSurfStyle* stl,
										  int clss)
						:bvDefPaletteRangeStyle(stl,clss){
_bTrace_("bvDefRangeSurfStyle::bvDefRangeSurfStyle",true);
	_width=stl->_width;
	_stroke[0]=stl->_stroke[0];
	_stroke[1]=stl->_stroke[1];
	_stroke[2]=stl->_stroke[2];
	_stroke[3]=stl->_stroke[3];
	_stroke[4]=stl->_stroke[4];
	strcpy(_pat,stl->_pat);
	_smooth=stl->_smooth;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefRangeSurfStyle::~bvDefRangeSurfStyle(){
_bTrace_("bvDefRangeSurfStyle::~bvDefRangeSurfStyle",true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefRangeSurfStyle::load(bGenericXMLBaseElement* root){
bGenericXMLBaseElement		*chld,*elt;
char						val[_values_length_max_];
	
	if(!std_load(root)){
		// for new subtypes
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
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"width")){
		elt->getvalue(val);
		_width=matof(val);
	}
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"smooth")){
		elt->getvalue(val);
		_smooth=atoi(val);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefRangeSurfStyle::dump(bArray& arr, int indent){
	if(!_visible){
		return(true);
	}
	if(strlen(_fld)==0){
		if(strlen(_pat)==0){
			if((_width<=0)&&(_fcolor[_cc-1]<=0)){
				return(true);
			}
		}
	}
	else{
		if((_width<=0)&&(_fcolor[_cc-1]<=0)&&(_tcolor[_cc-1]<=0)){
			return(true);
		}			
	}
	
// StyleRun & Validity
	if(!std_dump(arr,indent)){
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
	add_idesc(arr,indent+3,"cap",kCGLineCapButt);
	add_idesc(arr,indent+3,"join",kCGLineJoinMiter);
	add_cdesc(arr,indent+3,"dash","");
// Geometry
	add_cdesc(arr,indent+2,"stdgeometry","");
	if(!off_dump(arr,indent)){
		return(false);
	}
	add_ddesc(arr,indent+3,"width",_width,2);
	if(_smooth){
		add_idesc(arr,indent+3,"smooth",1);
	}
	return(true);
}

