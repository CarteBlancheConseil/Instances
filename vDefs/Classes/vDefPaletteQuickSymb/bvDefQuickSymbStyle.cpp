//----------------------------------------------------------------------------
// File : bvDefQuickSymbStyle.cpp
// Project : MacMap
// Purpose : C++ source file : Symbols vdef style class
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

#include "bvDefQuickSymbStyle.h"
#include <limits.h>
#include <Carbon/Carbon.h>
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefQuickSymbStyle::_centro=true;

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefQuickSymbStyle	::bvDefQuickSymbStyle(	bGenericMacMapApp* gapp,
										  bGenericType* gtp,
										  int clss)
					:bvDefPaletteQuickStyle(gapp,gtp,clss){
	_h=0;
	_fh=0;	
	_v=0;
	_fv=0;
	_a=0;
	_fa=0;
	_alpha=1;
	_falpha=0;
	strcpy(_smb,"");
	_fsmb=0;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefQuickSymbStyle::~bvDefQuickSymbStyle(){
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefQuickSymbStyle::load(bGenericXMLBaseElement* root){
bGenericXMLBaseElement		*elt,*chld;
char						val[_values_length_max_];
	
	if(!std_load(root)){
// for new subtypes
		return(false);
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"pdfdocument")){
		elt->getvalue(_smb);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fsmb=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(_smb);
		}
	}
	else if(elt=_gapp->classMgr()->NthElement(_gstl,1,"image")){
		elt->getvalue(_smb);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fsmb=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(_smb);
		}
	}
	else if(elt=_gapp->classMgr()->NthElement(_gstl,1,"icon")){
		elt->getvalue(_smb);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fsmb=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(_smb);
		}
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"hsize")){
		elt->getvalue(val);
		_h=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fh=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_h=matof(val);
		}
	}
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"vsize")){
		elt->getvalue(val);
		_v=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fv=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_v=matof(val);
		}
	}
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"angle")){
		elt->getvalue(val);
		_a=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fa=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_a=matof(val);
		}
	}
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"alpha")){
		elt->getvalue(val);
		_alpha=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_falpha=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_alpha=matof(val);
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
bool bvDefQuickSymbStyle::dump(bArray& arr, int indent){
char	nm[256];
	if((_h==0)&&(_fh==0)){
		return(true);
	}
	if((_v==0)&&(_fv==0)){
		return(true);
	}
	if((strlen(_smb)==0)&&(_fsmb==0)){
		return(true);
	}
// StyleRun & Validity
	if(!std_dump(arr,indent)){
		return(false);
	}
// Render
	add_cdesc(arr,indent+2,"render","");
	if(GetImageKind(_smb)==kQTFileTypePDF){
		if(_fsmb){
			add_cdesc(arr,indent+3,"pdfdocument","");
			_gtp->fields()->get_name(_fsmb,nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_cdesc(arr,indent+4,"value",_smb);
		}
		else{
			add_cdesc(arr,indent+3,"pdfdocument",_smb);
		}
	}
	else{
		if(_fsmb){
			add_cdesc(arr,indent+3,"image","");
			_gtp->fields()->get_name(_fsmb,nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_cdesc(arr,indent+4,"value",_smb);
		}
		else{
			add_cdesc(arr,indent+3,"image",_smb);
		}
	}
	add_cdesc(arr,indent+3,"fill","");
	if(_falpha){
		add_cdesc(arr,indent+4,"alpha","");
		_gtp->fields()->get_name(_falpha,nm);
		add_cdesc(arr,indent+5,"field",nm);
		add_ddesc(arr,indent+5,"value",_alpha,2);
	}
	else{
		add_ddesc(arr,indent+4,"alpha",_alpha,2);
	}
	
	// Geometry
	add_cdesc(arr,indent+2,"stdgeometry","");
	if(!off_dump(arr,indent)){
		return(false);
	}
	if(_centro){
		add_idesc(arr,indent+3,"centroid",1);
	}
	
	if(GetImageKind(_smb)==kQTFileTypePDF){
		if(_fsmb){
			add_cdesc(arr,indent+3,"pdfdocument","");
			_gtp->fields()->get_name(_fsmb,nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_cdesc(arr,indent+4,"value",_smb);
		}
		else{
			add_cdesc(arr,indent+3,"pdfdocument",_smb);
		}
	}
	else{
		if(_fsmb){
			add_cdesc(arr,indent+3,"image","");
			_gtp->fields()->get_name(_fsmb,nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_cdesc(arr,indent+4,"value",_smb);
		}
		else{
			add_cdesc(arr,indent+3,"image",_smb);
		}
	}
	
	if(_fh){
		add_cdesc(arr,indent+3,"hsize","");
		_gtp->fields()->get_name(_fh,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_h,2);
	}
	else{
		add_ddesc(arr,indent+3,"hsize",_h,2);
	}
	if(_fv){
		add_cdesc(arr,indent+3,"vsize","");
		_gtp->fields()->get_name(_fh,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_v,2);
	}
	else{
		add_ddesc(arr,indent+3,"vsize",_v,2);
	}
	if(_fa){
		add_cdesc(arr,indent+3,"angle","");
		_gtp->fields()->get_name(_fa,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_a,2);
	}
	else{
		add_ddesc(arr,indent+3,"angle",_a,2);
	}
	return(true);
}

