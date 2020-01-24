//----------------------------------------------------------------------------
// File : bvDefRangeLineStyle.cpp
// Project : MacMap
// Purpose : C++ source file : Range line vdef style class
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

#include "bvDefRangeLineStyle.h"
#include <limits.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefRangeLineStyle	::bvDefRangeLineStyle(bGenericMacMapApp* gapp,
										  bGenericType* gtp,
										  int clss)
					:bvDefPaletteRangeStyle(gapp,gtp,clss){
_bTrace_("bvDefRangeLineStyle::bvDefRangeLineStyle",true);
	_width=1;
	_cap=0;
	_join=0;
	strcpy(_dsh,"");
	_smooth=false;
	_dec=0;
    _wdec=false;
	_limit=0;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefRangeLineStyle	::bvDefRangeLineStyle(bvDefRangeLineStyle* stl,
												int clss)
						:bvDefPaletteRangeStyle(stl,clss){
_bTrace_("bvDefRangeLineStyle::bvDefRangeLineStyle",true);				
	_width=stl->_width;
	_cap=stl->_cap;
	_join=stl->_join;
	strcpy(_dsh,stl->_dsh);
	_smooth=stl->_smooth;
	_dec=stl->_dec;
    _wdec=stl->_wdec;
	_limit=stl->_limit;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefRangeLineStyle::~bvDefRangeLineStyle(){
_bTrace_("bvDefRangeLineStyle::~bvDefRangeLineStyle",true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefRangeLineStyle::load(bGenericXMLBaseElement* root){
bGenericXMLBaseElement		*chld,*elt;
char						val[_values_length_max_];
	
	if(!std_load(root)){
// for new subtypes
		return(false);
	}
	if(chld=_gapp->classMgr()->NthElement(_gstl,1,"stroke")){
		if(!prop_load(chld)){
			color_load(chld,_fcolor);
		}
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"cap")){
		elt->getvalue(val);
		_cap=atoi(val);
	}
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"join")){
		elt->getvalue(val);
		_join=atoi(val);
	}
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"dash")){
		elt->getvalue(_dsh);
	}
	if(	(_join==kCGLineJoinMiter)&&
	   (elt=_gapp->classMgr()->NthElement(_gstl,1,"miterlimit"))){
		elt->getvalue(val);
		_limit=matof(val);
	}
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"width")){
		elt->getvalue(val);
		_width=matof(val);
	}
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"decal")){
		elt->getvalue(val);
		_dec=matof(val);
        _wdec=false;
	}
    else if(elt=_gapp->classMgr()->NthElement(_gstl,1,"widthdecal")){
        elt->getvalue(val);
        _dec=matof(val);
        _wdec=true;
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
bool bvDefRangeLineStyle::dump(bArray& arr, int indent){
	if(!_visible){
		return(true);
	}
	if(_width<=0){
		return(false);
	}
// StyleRun & Validity
	if(!std_dump(arr,indent)){
		return(false);
	}
// Render
	add_cdesc(arr,indent+2,"render","");
	add_cdesc(arr,indent+3,"stroke","");
	if(!prop_dump(arr,indent+4)){
		color_dump(arr,indent+4,_fcolor);
	}
	
	add_idesc(arr,indent+3,"cap",_cap);
	add_idesc(arr,indent+3,"join",_join);
	if(strlen(_dsh)>0){
		add_cdesc(arr,indent+3,"dash",_dsh);
	}
	if((_join==kCGLineJoinMiter)&&(_limit>0)){
		add_ddesc(arr,indent+3,"miterlimit",_limit,2);
	}
// Geometry
	add_cdesc(arr,indent+2,"stdgeometry","");
	if(!off_dump(arr,indent)){
		return(false);
	}
	add_ddesc(arr,indent+3,"width",_width,2);
	if(_dec!=0){
		add_ddesc(arr,indent+3,_wdec?"widthdecal":"decal",_dec,2);
	}
	if(_smooth){
		add_idesc(arr,indent+3,"smooth",1);
	}
	return(true);
}

