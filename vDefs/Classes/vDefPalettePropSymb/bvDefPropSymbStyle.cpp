//----------------------------------------------------------------------------
// File : bvDefPropSymbStyle.cpp
// Project : MacMap
// Purpose : C++ source file : proportionnal symbols vdef style class
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

#include "bvDefPropSymbStyle.h"
#include <limits.h>
#include <Carbon/Carbon.h>
#include <mox_intf/ext_utils.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefPropSymbStyle	::bvDefPropSymbStyle(bGenericMacMapApp* gapp,
										 bGenericType* gtp)
					:bvDefPalettePropStyle(gapp,gtp,true){
_bTrace_("bvDefPropSymbStyle::bvDefPropSymbStyle",true);
	_rat=1;
	_alpha=1;
	strcpy(_smb,"");
	_centro=true;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefPropSymbStyle::~bvDefPropSymbStyle(){
_bTrace_("bvDefPropSymbStyle::~bvDefPropSymbStyle",true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPropSymbStyle::load(bGenericXMLBaseElement* root){
bGenericXMLBaseElement	*chld,*elt;
char					val[_values_length_max_];
	
	if(!std_load(root)){
		return(false);
	}
	if(!sub_load(_gstl)){
		if(elt=_gapp->classMgr()->NthElement(_gstl,1,"pdfdocument")){
			elt->getvalue(_smb);
		}
		else if(elt=_gapp->classMgr()->NthElement(_gstl,1,"image")){
			elt->getvalue(_smb);
		}
		else if(elt=_gapp->classMgr()->NthElement(_gstl,1,"icon")){
			elt->getvalue(_smb);
		}
		if(elt=_gapp->classMgr()->NthElement(_gstl,1,"alpha")){
			elt->getvalue(val);
			_alpha=matof(val);
		}
	}
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"stdgeometry")){		
		prop_load(elt,&_rat);		
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
bool bvDefPropSymbStyle::dump(bArray& arr, int indent){
	if(_rref==0){
		return(true);
	}
	if(	(strlen(_smb)==0)				&&
		(	(_arr.count()==0)			||
			(_subfld<kOBJ_SubType_))	){
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
		if(GetImageKind(_smb)==kQTFileTypePDF){
			add_cdesc(arr,indent+3,"pdfdocument",_smb);
		}
		else{
			add_cdesc(arr,indent+3,"image",_smb);
		}
		add_cdesc(arr,indent+3,"fill","");
		add_ddesc(arr,indent+4,"alpha",_alpha,2);
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
	if(_centro){
		add_idesc(arr,indent+3,"centroid",1);
	}
	return(true);
}

