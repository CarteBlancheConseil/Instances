//----------------------------------------------------------------------------
// File : bvDefPropRectStyle.cpp
// Project : MacMap
// Purpose : C++ source file : proportionnal rectangle vdef style class
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
// 28/01/2013 creation.
//----------------------------------------------------------------------------

#include "bvDefPropRectStyle.h"
#include <limits.h>
#include <Carbon/Carbon.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefPropRectStyle	::bvDefPropRectStyle(	bGenericMacMapApp* gapp,
												bGenericType* gtp)
						:bvDefPalettePropStyle(gapp,gtp,true){
_bTrace_("bvDefPropRectStyle::bvDefPropRectStyle",true);
	_rat=1;
	_width=1;
	_stroke[0]=1;
	_stroke[1]=1;
	_stroke[2]=1;
	_stroke[3]=1;
	_stroke[4]=1;
	strcpy(_pat,"");
	_rradius=0;
	_centro=true;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefPropRectStyle::~bvDefPropRectStyle(){
_bTrace_("bvDefPropRectStyle::~bvDefPropRectStyle",true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPropRectStyle::load(bGenericXMLBaseElement* root){
bGenericXMLBaseElement	*chld,*elt;
char					val[_values_length_max_];
	
	if(!std_load(root)){
		return(false);
	}
	
	if(chld=_gapp->classMgr()->NthElement(_gstl,1,"stroke")){	
		if(elt=_gapp->classMgr()->NthElement(chld,1,"red")){
			elt->getvalue(val);
			_stroke[0]=matof(val);
			_cc=4;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"green")){
			elt->getvalue(val);
			_stroke[1]=matof(val);
			_cc=4;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"blue")){
			elt->getvalue(val);
			_stroke[2]=matof(val);
			_cc=4;
		}
		
		if(elt=_gapp->classMgr()->NthElement(chld,1,"cyan")){
			elt->getvalue(val);
			_stroke[0]=matof(val);
			_cc=5;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"magenta")){
			elt->getvalue(val);
			_stroke[1]=matof(val);
			_cc=5;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"yellow")){
			elt->getvalue(val);
			_stroke[2]=matof(val);
			_cc=5;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"black")){
			elt->getvalue(val);
			_stroke[3]=matof(val);
			_cc=5;
		}
		
		if(elt=_gapp->classMgr()->NthElement(chld,1,"alpha")){
			elt->getvalue(val);
			if(_cc==4){
				_stroke[3]=matof(val);
			}
			else{
				_stroke[4]=matof(val);
			}
		}
	}
	
	if(!sub_load(_gstl)){
		if(chld=_gapp->classMgr()->NthElement(_gstl,1,"fill")){	
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
		else if(chld=_gapp->classMgr()->NthElement(_gstl,1,"fillpattern")){
			chld->getvalue(_pat);
		}
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"stdgeometry")){		
double		dmy;
		prop_load(elt,&dmy);
		
		if(chld=_gapp->classMgr()->NthElement(elt,1,"width")){
			chld->getvalue(val);
			_width=matof(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"roundedradius")){
			chld->getvalue(val);
			_rradius=matof(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"centroid")){
			chld->getvalue(val);
			_centro=atoi(val);
		}
		else{
			_centro=false;
		}
	}
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPropRectStyle::dump(bArray& arr, int indent){
	if(_rref==0){
		return(true);
	}
	if(_width<=0){
		if(	((_arr.count()==0)||(_subfld<kOBJ_SubType_))	&&
			(_color[_cc-1]<=0)								&&
			(strlen(_pat)==0)								){
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
	if(_cc==4){
		add_ddesc(arr,indent+4,"red",_stroke[0],2);
		add_ddesc(arr,indent+4,"green",_stroke[1],2);
		add_ddesc(arr,indent+4,"blue",_stroke[2],2);
		add_ddesc(arr,indent+4,"alpha",_stroke[3],2);
	}
	else if(_cc==5){
		add_ddesc(arr,indent+4,"cyan",_stroke[0],2);
		add_ddesc(arr,indent+4,"magenta",_stroke[1],2);
		add_ddesc(arr,indent+4,"yellow",_stroke[2],2);
		add_ddesc(arr,indent+4,"black",_stroke[3],2);
		add_ddesc(arr,indent+4,"alpha",_stroke[4],2);
	}
	if((_arr.count()>1)&&(_subfld>=kOBJ_SubType_)){
		sub_dump(arr,indent+2);
	}
	else if(strlen(_pat)==0){
		add_cdesc(arr,indent+3,"fill","");
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
	else{
		add_cdesc(arr,indent+3,"fillpattern",_pat);
	}
/**/
	add_cdesc(arr,indent+3,"dash","");
/**/	
// Geometry
	add_cdesc(arr,indent+2,"stdgeometry","");
	if(!off_dump(arr,indent)){
		return(false);
	}
	
	if(!prop_dump(arr,indent+2,_rat)){
		return(false);
	}	
	
	add_ddesc(arr,indent+3,"width",_width,2);
	add_ddesc(arr,indent+3,"roundedradius",_rradius,2);
	if(_centro){
		add_idesc(arr,indent+3,"centroid",1);
	}
	return(true);
}

