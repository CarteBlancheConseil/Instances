//----------------------------------------------------------------------------
// File : bvDefHistoStyle.cpp
// Project : MacMap
// Purpose : C++ source file : Histogram vdef style class
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
// 09/07/2013 creation.
//----------------------------------------------------------------------------

#include "bvDefHistoStyle.h"
#include <limits.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefHistoStyle	::bvDefHistoStyle(bGenericMacMapApp* gapp,
								  bGenericType* gtp,
								  bArray* arr){
	_gapp=gapp;
	_gtp=gtp;
	_gstl=NULL;
	
	_fld=kOBJ_SubType_;
	
	_smin=1;
	_smax=INT_MAX;

	_dimx=0;
	_dimy=0;
	_dx=0;
	_dy=0;
		
	_offx=0;
	_offy=0;
	
	_arr=arr;
	
	_width=0;
	_stroke[0]=0;
	_stroke[1]=0;
	_stroke[2]=0;
	_stroke[3]=1;
	_stroke[4]=1;
	_fill[0]=0;
	_fill[1]=0;
	_fill[2]=0;
	_fill[3]=1;
	_fill[4]=1;
	_centro=true;
	_isback=false;
	
	_cc=4;
	
	_idx=arr->count();
	
	_vmin=0;
	_vmax=0;
	_spc=0;
	_onx=false;	
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefHistoStyle::~bvDefHistoStyle(){
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefHistoStyle::load(bGenericXMLBaseElement* root){
	if(std_load(root)==false){
		return(false);
	}
	
bGenericXMLBaseElement	*elt,*chld;
char					val[_values_length_max_];
	
	chld=_gapp->classMgr()->NthElement(_gstl,1,"prophsize");
	if(chld){
		_onx=true;
	}
	else{
		_onx=false;
		chld=_gapp->classMgr()->NthElement(_gstl,1,"propvsize");
	}
	if(!chld){

		chld=_gapp->classMgr()->NthElement(_gstl,1,"hsize");
		if(chld){
			chld->getvalue(val);
			_dimx=matof(val);
		}
		else{
			_dimx=30;
		}
		chld=_gapp->classMgr()->NthElement(_gstl,1,"vsize");
		if(chld){
			chld->getvalue(val);
			_dimy=matof(val);
		}
		else{
			_dimy=40;
		}
		
		chld=_gapp->classMgr()->NthElement(_gstl,1,"shiftx");
		if(chld){
			chld->getvalue(val);
			_dx=matof(val);
		}
		else{
			_dx=0;
		}
		chld=_gapp->classMgr()->NthElement(_gstl,1,"shifty");
		if(chld){
			chld->getvalue(val);
			_dy=matof(val);
		}
		else{
			_dy=0;
		}
		
		_isback=true;
		return(true);

		//return(false);
	}
	
	elt=_gapp->classMgr()->NthElement(chld,1,"field");
	if(elt){
		elt->getvalue(val);
		_fld=_gtp->fields()->get_index(val);
		if(_fld==0){
			_fld=kOBJ_SubType_;
		}
		_arr->add(&_fld);
	}
	
	elt=_gapp->classMgr()->NthElement(chld,1,"value");
	if(elt){
		elt->getvalue(val);
		_vmin=matof(val);
	}
	else{
		_vmin=0;
	}
	elt=_gapp->classMgr()->NthElement(chld,2,"value");
	if(elt){
		elt->getvalue(val);
		_vmax=matof(val);
	}
	else{
		_vmax=100;
	}
	elt=_gapp->classMgr()->NthElement(chld,3,"value");
	if(elt){
		elt->getvalue(val);
		if(_onx){
			_dimx=matof(val);
		}
		else{
			_dimy=matof(val);
		}
	}
	else{
		if(_onx){
			_dimx=30;
		}
		else{
			_dimy=40;
		}
	}
	
	
	chld=_gapp->classMgr()->NthElement(_gstl,1,(_onx)?"vsize":"hsize");
	if(chld){
		chld->getvalue(val);
		if(_onx){
			_dimy=matof(val);
		}
		else{
			_dimx=matof(val);
		}
	}
	else{
		if(_onx){
			_dimy=40;
		}
		else{
			_dimx=30;
		}
	}
	
	chld=_gapp->classMgr()->NthElement(_gstl,1,"shiftx");
	if(chld){
		chld->getvalue(val);
		_dx=matof(val);
	}
	else{
		_dx=0;
	}
	chld=_gapp->classMgr()->NthElement(_gstl,1,"shifty");
	if(chld){
		chld->getvalue(val);
		_dy=matof(val);
	}
	else{
		_dy=0;
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefHistoStyle::dump(bArray& arr, int indent){
_bTrace_("bvDefHistoStyle::dump",false);
	if((_dimx<=0)||(_dimy<=0)){
_tw_("bad dims "+_dimx+":"+_dimy);
		return(true);
	}
	if((_width<=0)&&(_fill[_cc-1]==0)){
_tw_("bad graphic prm "+_width+"/"+_fill[_cc-1]);
		return(true);
	}
	if(!_isback){
		if((_vmax-_vmin)<=0){
_tw_("bad values "+_vmax+">"+_vmin);
			return(true);
		}
	}

// StyleRun, Validity, Render, Geometry
	if(!std_dump(arr,indent)){
		return(false);
	}

	if(!_isback){
char	name[256];
double	bsz,bsp;
		if(_onx){
			add_cdesc(arr,indent+3,"prophsize","");
			_gtp->fields()->get_name(_fld,name);
			add_cdesc(arr,indent+4,"field",name);
			add_ddesc(arr,indent+4,"value",_vmin,6);
			add_ddesc(arr,indent+4,"value",_vmax,6);
			add_ddesc(arr,indent+4,"value",_dimx,2);
			bsp=_dimy/((double)_arr->count());
			bsz=bsp-_spc;
			add_ddesc(arr,indent+3,"vsize",bsz,2);
			add_ddesc(arr,indent+3,"shifty",_dy+((double)(_idx/*-1*/))*bsp+(0.5*_spc),2);
			add_ddesc(arr,indent+3,"shiftx",_dx,2);
		}
		else{
			add_cdesc(arr,indent+3,"propvsize","");
			_gtp->fields()->get_name(_fld,name);
			add_cdesc(arr,indent+4,"field",name);
			add_ddesc(arr,indent+4,"value",_vmin,6);
			add_ddesc(arr,indent+4,"value",_vmax,6);
			add_ddesc(arr,indent+4,"value",_dimy,2);
			bsp=_dimx/((double)_arr->count());
			bsz=bsp-_spc;
			add_ddesc(arr,indent+3,"hsize",bsz,2);
			add_ddesc(arr,indent+3,"shiftx",_dx+((double)(_idx/*-1*/))*bsp+(0.5*_spc),2);
			add_ddesc(arr,indent+3,"shifty",_dy,2);
		}
		add_ddesc(arr,indent+3,"hsizejustification",1,2);
		add_ddesc(arr,indent+3,"vsizejustification",1,2);
	}
	else{
		add_ddesc(arr,indent+3,"hsize",_dimx,2);
		add_ddesc(arr,indent+3,"vsize",_dimy,2);
		add_ddesc(arr,indent+3,"shiftx",_dx,2);
		add_ddesc(arr,indent+3,"shifty",_dy,2);
		add_ddesc(arr,indent+3,"hsizejustification",1,2);
		add_ddesc(arr,indent+3,"vsizejustification",1,2);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefHistoStyle::std_load(bGenericXMLBaseElement* root){
_bTrace_("bvDefHistogramsStdStyle::std_load",false);
	_gstl=NULL;
	find_stylerun(root);
	if(!_gstl){
		return(false);
	}
bGenericXMLBaseElement	*elt,*chld;
char					val[_values_length_max_];
	
	elt=_gapp->classMgr()->NthElement(_gstl,1,"scalemin");
	if(!elt){
		return(false);
	}
	elt->getvalue(val);
	_smin=matof(val);
	
	elt=_gapp->classMgr()->NthElement(_gstl,1,"scalemax");
	if(!elt){
		return(false);
	}
	elt->getvalue(val);
	_smax=matof(val);
	
	if((chld=_gapp->classMgr()->NthElement(_gstl,1,"stroke"))){
		if((elt=_gapp->classMgr()->NthElement(chld,1,"red"))){
			elt->getvalue(val);
			_stroke[0]=matof(val);
			_cc=4;
		}
		if((elt=_gapp->classMgr()->NthElement(chld,1,"green"))){
			elt->getvalue(val);
			_stroke[1]=matof(val);
			_cc=4;
		}
		if((elt=_gapp->classMgr()->NthElement(chld,1,"blue"))){
			elt->getvalue(val);
			_stroke[2]=matof(val);
			_cc=4;
		}
		
		if((elt=_gapp->classMgr()->NthElement(chld,1,"cyan"))){
			elt->getvalue(val);
			_stroke[0]=matof(val);
			_cc=5;
		}
		if((elt=_gapp->classMgr()->NthElement(chld,1,"magenta"))){
			elt->getvalue(val);
			_stroke[1]=matof(val);
			_cc=5;
		}
		if((elt=_gapp->classMgr()->NthElement(chld,1,"yellow"))){
			elt->getvalue(val);
			_stroke[2]=matof(val);
			_cc=5;
		}
		if((elt=_gapp->classMgr()->NthElement(chld,1,"black"))){
			elt->getvalue(val);
			_stroke[3]=matof(val);
			_cc=5;
		}
		
		if((elt=_gapp->classMgr()->NthElement(chld,1,"alpha"))){
			elt->getvalue(val);
			if(_cc==4){
				_stroke[3]=matof(val);
			}
			else{
				_stroke[4]=matof(val);
			}
		}
	}
	
	if((chld=_gapp->classMgr()->NthElement(_gstl,1,"fill"))){
		if((elt=_gapp->classMgr()->NthElement(chld,1,"red"))){
			elt->getvalue(val);
			_fill[0]=matof(val);
			_cc=4;
		}
		if((elt=_gapp->classMgr()->NthElement(chld,1,"green"))){
			elt->getvalue(val);
			_fill[1]=matof(val);
			_cc=4;
		}
		if((elt=_gapp->classMgr()->NthElement(chld,1,"blue"))){
			elt->getvalue(val);
			_fill[2]=matof(val);
			_cc=4;
		}
		
		if((elt=_gapp->classMgr()->NthElement(chld,1,"cyan"))){
			elt->getvalue(val);
			_fill[0]=matof(val);
			_cc=5;
		}
		if((elt=_gapp->classMgr()->NthElement(chld,1,"magenta"))){
			elt->getvalue(val);
			_fill[1]=matof(val);
			_cc=5;
		}
		if((elt=_gapp->classMgr()->NthElement(chld,1,"yellow"))){
			elt->getvalue(val);
			_fill[2]=matof(val);
			_cc=5;
		}
		if((elt=_gapp->classMgr()->NthElement(chld,1,"black"))){
			elt->getvalue(val);
			_fill[3]=matof(val);
			_cc=5;
		}
		
		if((elt=_gapp->classMgr()->NthElement(chld,1,"alpha"))){
			elt->getvalue(val);
			if(_cc==4){
				_fill[3]=matof(val);
			}
			else{
				_fill[4]=matof(val);
			}
		}
	}

	off_load(root);

	chld=_gapp->classMgr()->NthElement(_gstl,1,"centroid");
	if(chld){
		chld->getvalue(val);
		_centro=atoi(val);
	}
	else{
		_centro=0;
	}
	
	chld=_gapp->classMgr()->NthElement(_gstl,1,"width");
	if(chld){
		chld->getvalue(val);
		_width=matof(val);
	}
	else{
		_width=0;
	}
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefHistoStyle::std_dump(bArray& arr, int indent){
	add_cdesc(arr,indent+1,"stylerun","");
	add_cdesc(arr,indent+2,"validity","");
	add_idesc(arr,indent+3,"classmin",1);
	add_idesc(arr,indent+3,"classmax",INT_MAX);
	add_ddesc(arr,indent+3,"scalemin",_smin,6);
	add_ddesc(arr,indent+3,"scalemax",(_smax==INT_MAX)?_smax:_smax+1,6);
	add_idesc(arr,indent+3,"pass",1);
	add_cdesc(arr,indent+2,"render","");
	if(_width>0){
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
	}
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
	add_cdesc(arr,indent+3,"dash","");
// Geometry
	add_cdesc(arr,indent+2,"stdgeometry","");
	off_dump(arr,indent);	
	if(_centro){
		add_idesc(arr,indent+3,"centroid",1);
	}
	add_ddesc(arr,indent+3,"width",_width,2);	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefHistoStyle::off_load(bGenericXMLBaseElement* root){
bGenericXMLBaseElement*		chld;
bGenericXMLBaseElement*		elt;
char						val[_values_length_max_];
	
	chld=_gapp->classMgr()->NthElement(_gstl,1,"offsetcoord");
	if(!chld){
		_offx=0;
		_offy=0;
		return(true);
	}
	elt=_gapp->classMgr()->NthElement(chld,1,"field");
	if(!elt){
		_offx=0;
		_offy=0;
		return(true);
	}
	elt->getvalue(val);
	_offx=_gtp->fields()->get_index(val);
	elt=_gapp->classMgr()->NthElement(chld,2,"field");
	if(!elt){
		_offx=0;
		_offy=0;
		return(true);
	}
	elt->getvalue(val);
	_offy=_gtp->fields()->get_index(val);
	if(!_offx||!_offy){
		_offx=0;
		_offy=0;
		return(true);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefHistoStyle::off_dump(bArray& arr, int indent){
	if((_offx==0)||(_offy==0)){
		return(true);
	}
char	xname[256],yname[256];
	if(!_gtp->fields()->get_name(_offx,xname)){
		_offx=0;
	}
	if(!_gtp->fields()->get_name(_offy,yname)){
		_offy=0;
	}
	if((_offx>0)&&(_offy>0)){
		add_cdesc(arr,indent+3,"offsetcoord","");
		add_cdesc(arr,indent+4,"field",xname);
		add_cdesc(arr,indent+4,"field",yname);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bvDefHistoStyle::find_stylerun(bGenericXMLBaseElement* root){
	(void)root->dotoall(this,0,test_stylerun);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bvDefHistoStyle::test_stylerun(bGenericXMLBaseElement* root, void* prm, int indent){
bvDefHistoStyle*		stl=(bvDefHistoStyle*)prm;	
char					val[_values_length_max_];
bGenericXMLBaseElement*	elt;
	
	root->getclassname(val);
	if(!strcmp("stylerun",val)){
		elt=stl->_gapp->classMgr()->NthElement(root,1,"classmin");
		if(!elt){
			return(true);
		}		
		elt=stl->_gapp->classMgr()->NthElement(root,1,"pass");
		if(!elt){
			return(true);
		}
		stl->_gstl=root;
		return(false);
	}
	
	return(true);
}

