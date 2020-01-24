//----------------------------------------------------------------------------
// File : bvDefPropLineStyle.cpp
// Project : MacMap
// Purpose : C++ source file : proportionnal line vdef style class
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
// 29/01/2013 creation.
//----------------------------------------------------------------------------

#include "bvDefPropLineStyle.h"
#include <limits.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefPropLineStyle	::bvDefPropLineStyle(	bGenericMacMapApp* gapp,
												bGenericType* gtp)
						:bvDefPalettePropStyle(gapp,gtp,false){
_bTrace_("bvDefPropLineStyle::bvDefPropLineStyle",true);
	_rref=1;
	_cap=0;
	_join=0;
	strcpy(_dsh,"");
	_smooth=false;
	_dec=0;
    _wdec=false;
	_limit=0;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefPropLineStyle::~bvDefPropLineStyle(){
_bTrace_("bvDefPropLineStyle::~bvDefPropLineStyle",true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPropLineStyle::load(bGenericXMLBaseElement* root){
bGenericXMLBaseElement	*chld,*elt;
char					val[_values_length_max_];
	
	if(!std_load(root)){
		return(false);
	}
	
	if(!sub_load(_gstl)){
		if(chld=_gapp->classMgr()->NthElement(_gstl,1,"stroke")){	
			if(elt=_gapp->classMgr()->NthElement(chld,1,"red")){
				elt->getvalue(val);
				_color[0]=matof(val);
				_cc=4;
			}
			if(elt=_gapp->classMgr()->NthElement(chld,1,"green")){
				elt->getvalue(val);
				_color[1]=matof(val);
				_cc=4;
			}
			if(elt=_gapp->classMgr()->NthElement(chld,1,"blue")){
				elt->getvalue(val);
				_color[2]=matof(val);
				_cc=4;
			}
			
			if(elt=_gapp->classMgr()->NthElement(chld,1,"cyan")){
				elt->getvalue(val);
				_color[0]=matof(val);
				_cc=5;
			}
			if(elt=_gapp->classMgr()->NthElement(chld,1,"magenta")){
				elt->getvalue(val);
				_color[1]=matof(val);
				_cc=5;
			}
			if(elt=_gapp->classMgr()->NthElement(chld,1,"yellow")){
				elt->getvalue(val);
				_color[2]=matof(val);
				_cc=5;
			}
			if(elt=_gapp->classMgr()->NthElement(chld,1,"black")){
				elt->getvalue(val);
				_color[3]=matof(val);
				_cc=5;
			}
			
			if(elt=_gapp->classMgr()->NthElement(chld,1,"alpha")){
				elt->getvalue(val);
				if(_cc==4){
					_color[3]=matof(val);
				}
				else{
					_color[4]=matof(val);
				}
			}
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
	if((_join==kCGLineJoinMiter)&&
	   (elt=_gapp->classMgr()->NthElement(_gstl,1,"miterlimit"))){
		elt->getvalue(val);
		_limit=matof(val);
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"stdgeometry")){		
double		dmy;
		prop_load(elt,&dmy);
		if(chld=_gapp->classMgr()->NthElement(_gstl,1,"decal")){
			chld->getvalue(val);
			_dec=matof(val);
            _wdec=false;
		}
        else if(chld=_gapp->classMgr()->NthElement(_gstl,1,"widthdecal")){
            chld->getvalue(val);
            _dec=matof(val);
            _wdec=true;
        }
		if(chld=_gapp->classMgr()->NthElement(_gstl,1,"smooth")){
			chld->getvalue(val);
			_smooth=atoi(val);
		}
	}
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPropLineStyle::dump(bArray& arr, int indent){
	if(_rref<=0){
		return(true);
	}
// StyleRun & Validity
	if(!std_dump(arr,indent)){
		return(false);
	}
// Render
	add_cdesc(arr,indent+2,"render","");
	if((_arr.count()>1)&&(_subfld>=kOBJ_SubType_)){
		sub_dump(arr,indent+2);
	}
	else{
		add_cdesc(arr,indent+3,"stroke","");
		if(_cc==4){
			add_ddesc(arr,indent+4,"red",_color[0],2);
			add_ddesc(arr,indent+4,"green",_color[1],2);
			add_ddesc(arr,indent+4,"blue",_color[2],2);
			add_ddesc(arr,indent+4,"alpha",_color[3],2);
		}
		else if(_cc==5){
			add_ddesc(arr,indent+4,"cyan",_color[0],2);
			add_ddesc(arr,indent+4,"magenta",_color[1],2);
			add_ddesc(arr,indent+4,"yellow",_color[2],2);
			add_ddesc(arr,indent+4,"black",_color[3],2);
			add_ddesc(arr,indent+4,"alpha",_color[4],2);
		}
	}
	add_idesc(arr,indent+3,"cap",_cap);
	add_idesc(arr,indent+3,"join",_join);
	//if(strlen(_dsh)>0){
		add_cdesc(arr,indent+3,"dash",_dsh);
	//}
	if((_join==kCGLineJoinMiter)&&(_limit>0)){
		add_ddesc(arr,indent+3,"miterlimit",_limit,2);
	}
// Geometry
	add_cdesc(arr,indent+2,"stdgeometry","");
	if(!off_dump(arr,indent)){
		return(false);
	}
	
	if(!prop_dump(arr,indent+2,1)){
		return(false);
	}	
	
	if(_dec!=0){
		add_ddesc(arr,indent+3,_wdec?"widthdecal":"decal",_dec,2);
	}
	if(_smooth){
		add_idesc(arr,indent+3,"smooth",1);
	}
	
	return(true);
}

