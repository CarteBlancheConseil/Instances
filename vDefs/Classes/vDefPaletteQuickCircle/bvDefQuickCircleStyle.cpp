//----------------------------------------------------------------------------
// File : bvDefQuickCircleStyle.cpp
// Project : MacMap
// Purpose : C++ source file : Circle vdef style class
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

#include "bvDefQuickCircleStyle.h"
#include <limits.h>


// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefQuickCircleStyle::_centro=true;

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefQuickCircleStyle	::bvDefQuickCircleStyle(	bGenericMacMapApp* gapp,
										  bGenericType* gtp,
										  int clss)
					:bvDefPaletteQuickStyle(gapp,gtp,clss){
	_width=0;
	_fwidth=0;
	_stroke[0]=0;
	_stroke[1]=0;
	_stroke[2]=0;
	_stroke[3]=1;
	_stroke[4]=1;	
	_fstroke=0;
	_fill[0]=0;
	_fill[1]=0;
	_fill[2]=0;
	_fill[3]=1;
	_fill[4]=1;
	strcpy(_pat,"");
	_ffill=0;
	_radius=0;
	_fradius=0;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefQuickCircleStyle::~bvDefQuickCircleStyle(){
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefQuickCircleStyle::load(bGenericXMLBaseElement* root){
bGenericXMLBaseElement		*chld,*elt;
char						val[_values_length_max_];
	
	if(!std_load(root)){
// for new subtypes
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
		
		if(elt=_gapp->classMgr()->NthElement(chld,1,"colorfield16m")){
			elt->getvalue(val);
			_fstroke=_gtp->fields()->get_index(val);
		}
	}
	
	if(chld=_gapp->classMgr()->NthElement(_gstl,1,"fill")){	
		if(elt=_gapp->classMgr()->NthElement(chld,1,"red")){
			elt->getvalue(val);
			_fill[0]=matof(val);
			_cc=4;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"green")){
			elt->getvalue(val);
			_fill[1]=matof(val);
			_cc=4;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"blue")){
			elt->getvalue(val);
			_fill[2]=matof(val);
			_cc=4;
		}
		
		if(elt=_gapp->classMgr()->NthElement(chld,1,"cyan")){
			elt->getvalue(val);
			_fill[0]=matof(val);
			_cc=5;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"magenta")){
			elt->getvalue(val);
			_fill[1]=matof(val);
			_cc=5;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"yellow")){
			elt->getvalue(val);
			_fill[2]=matof(val);
			_cc=5;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"black")){
			elt->getvalue(val);
			_fill[3]=matof(val);
			_cc=5;
		}
		
		if(elt=_gapp->classMgr()->NthElement(chld,1,"alpha")){
			elt->getvalue(val);
			if(_cc==4){
				_fill[3]=matof(val);
			}
			else{
				_fill[4]=matof(val);
			}
		}
		
		if(elt=_gapp->classMgr()->NthElement(chld,1,"colorfield16m")){
			elt->getvalue(val);
			_ffill=_gtp->fields()->get_index(val);
		}
	}
	else if(chld=_gapp->classMgr()->NthElement(_gstl,1,"fillpattern")){
		chld->getvalue(_pat);
		if(elt=_gapp->classMgr()->NthElement(chld,1,"field")){
			elt->getvalue(val);
			_ffill=_gtp->fields()->get_index(val);
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"value")){
			elt->getvalue(_pat);
		}
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"size")){
		elt->getvalue(val);
		_radius=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fradius=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_radius=matof(val);
		}
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"width")){
		elt->getvalue(val);
		_width=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fwidth=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_width=matof(val);
		}
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
bool bvDefQuickCircleStyle::dump(bArray& arr, int indent){
char	nm[256];
	if((_radius==0)&&(_fradius==0)){
		return(true);
	}
	if(	(_width<=0)			&&
		(_fill[_cc-1]<=0)	&&
		(_fwidth==0)		&&
		(_ffill==0)			&&
		(strlen(_pat)==0)	){
		return(true);
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
	if(_fstroke){
		_gtp->fields()->get_name(_fstroke,nm);
		add_cdesc(arr,indent+4,"colorfield16m",nm);
	}
	if(strlen(_pat)==0){
		add_cdesc(arr,indent+3,"fill","");
		if(_cc==4){
			add_ddesc(arr,indent+4,"red",_fill[0],2);
			add_ddesc(arr,indent+4,"green",_fill[1],2);
			add_ddesc(arr,indent+4,"blue",_fill[2],2);
			add_ddesc(arr,indent+4,"alpha",_fill[3],2);
		}
		else if(_cc==5){
			add_ddesc(arr,indent+4,"cyan",_fill[0],2);
			add_ddesc(arr,indent+4,"magenta",_fill[1],2);
			add_ddesc(arr,indent+4,"yellow",_fill[2],2);
			add_ddesc(arr,indent+4,"black",_fill[3],2);
			add_ddesc(arr,indent+4,"alpha",_fill[4],2);
		}
		if(_ffill){
			_gtp->fields()->get_name(_ffill,nm);
			add_cdesc(arr,indent+4,"colorfield16m",nm);
		}
	}
	else{
		if(_ffill){
			add_cdesc(arr,indent+3,"fillpattern","");
			_gtp->fields()->get_name(_ffill,nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_cdesc(arr,indent+4,"value",_pat);
		}
		else{
			add_cdesc(arr,indent+3,"fillpattern",_pat);
		}
	}
/**/
	add_cdesc(arr,indent+3,"dash","");
/**/
// Geometry
	add_cdesc(arr,indent+2,"stdgeometry","");
	if(!off_dump(arr,indent)){
		return(false);
	}
	
	if(_fradius){
		add_cdesc(arr,indent+3,"size","");
		_gtp->fields()->get_name(_fradius,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_radius,2);
	}
	else{
		add_ddesc(arr,indent+3,"size",_radius,2);
	}
	
	if(_fwidth){
		add_cdesc(arr,indent+3,"width","");
		_gtp->fields()->get_name(_fwidth,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_width,2);
	}
	else{
		add_ddesc(arr,indent+3,"width",_width,2);
	}
	
	if(_centro){
		add_idesc(arr,indent+3,"centroid",1);
	}
	return(true);
}

