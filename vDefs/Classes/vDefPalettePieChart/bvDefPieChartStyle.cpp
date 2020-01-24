//----------------------------------------------------------------------------
// File : bvDefPieChartStyle.cpp
// Project : MacMap
// Purpose : C++ source file : Pie chart vdef style class
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

#include "bvDefPieChartStyle.h"
#include <limits.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefPieChartStyle	::bvDefPieChartStyle(bGenericMacMapApp* gapp,
										 bGenericType* gtp,
										 bool prop,
										 bArray* arr){
	_gapp=gapp;
	_gtp=gtp;
	_gstl=NULL;
	
	_fld=kOBJ_SubType_;
	
	_qref=1;
	_qmax=1;
	_rref=5;
	_exp=1;
	
	_smin=1;
	_smax=LONG_MAX;
	
	_offx=0;
	_offy=0;
	
	_prop=prop;
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
	_isstrk=false;
	
	_cc=4;
	
	_idx=arr->count();
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefPieChartStyle::~bvDefPieChartStyle(){
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPieChartStyle::load(bGenericXMLBaseElement* root){
bGenericXMLBaseElement	*chld,*elt,*e2;
char					val[_values_length_max_];
int						fid,n;
	
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
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"stdgeometry")){		
		chld=_gapp->classMgr()->NthElement(elt,1,"propangle");
		if(chld){
			_isstrk=false;
			e2=_gapp->classMgr()->NthElement(chld,1,"value");
			if(e2){
				e2->getvalue(val);
				_idx=atoi(val);
			}
			if(_arr->count()==0){
				n=_gapp->classMgr()->CountElements(chld,"field");
				for(int i=1;i<=n;i++){
					e2=_gapp->classMgr()->NthElement(chld,i,"field");
					if(!e2){
						break;
					}
					e2->getvalue(val);
					//fid=_gtp->fields()->get_id(_gtp->fields()->get_index(val));
					fid=_gtp->fields()->get_index(val);
					_arr->add(&fid);
				}
			}
		}
		else{
			_isstrk=true;
		}
		prop_load(elt);
		
		if(chld=_gapp->classMgr()->NthElement(elt,1,"width")){
			chld->getvalue(val);
			_width=matof(val);
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
bool bvDefPieChartStyle::dump(bArray& arr, int indent){
_bTrace_("bvDefPieChartStyle::dump",true);
	if(_rref==0){
		return(true);
	}
	if((_isstrk)&&(_width<=0)){
		return(true);
	}
	// StyleRun & Validity
	if(!std_dump(arr,indent)){
		return(false);
	}
	if((_isstrk)&&(_fill[_cc-1]!=0)){
		_fill[_cc-1]=0;
	}
	else if((!_isstrk)&&(_stroke[_cc-1]!=0)){
		_stroke[_cc-1]=0;
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
	/**/
	add_cdesc(arr,indent+3,"dash","");
	/**/	
	// Geometry
	add_cdesc(arr,indent+2,"stdgeometry","");
	if(!off_dump(arr,indent)){
		return(false);
	}
	
	if(!_isstrk){
		add_cdesc(arr,indent+3,"propangle","");
		add_idesc(arr,indent+4,"value",_idx);
int		fid;
char	name[256];
		for(int i=1;i<=_arr->count();i++){
			_arr->get(i,&fid);
			//_gtp->fields()->get_name(_gtp->fields()->get_index(fid),name);
			_gtp->fields()->get_name(fid,name);
			add_cdesc(arr,indent+4,"field",name);
		}
	}
	else{
		add_idesc(arr,indent+3,"startangle",0);
		add_idesc(arr,indent+3,"endangle",360);
	}
	
	if(!prop_dump(arr,indent+2)){
		return(false);
	}	
	
	add_ddesc(arr,indent+3,"width",_width,2);
	if(_centro){
		add_idesc(arr,indent+3,"centroid",1);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPieChartStyle::std_load(bGenericXMLBaseElement* root){
	_gstl=NULL;
	find_stylerun(root);
	if(!_gstl){
		return(false);
	}
bGenericXMLBaseElement*		elt;
char						val[_values_length_max_];
	
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
	
	off_load(root);
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPieChartStyle::std_dump(bArray& arr, int indent){
	add_cdesc(arr,indent+1,"stylerun","");
	add_cdesc(arr,indent+2,"validity","");
	add_idesc(arr,indent+3,"classmin",1);
	add_idesc(arr,indent+3,"classmax",LONG_MAX);
	add_ddesc(arr,indent+3,"scalemin",_smin,6);
	add_ddesc(arr,indent+3,"scalemax",(_smax==LONG_MAX)?_smax:_smax+1,6);
	add_idesc(arr,indent+3,"pass",1);
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPieChartStyle::prop_load(bGenericXMLBaseElement* root){
bGenericXMLBaseElement*		chld;
bGenericXMLBaseElement*		elt;
char						val[_values_length_max_];
	
	chld=_gapp->classMgr()->NthElement(_gstl,1,"propsize");
	if(!chld){
		_prop=false;
		elt=_gapp->classMgr()->NthElement(_gstl,1,"size");
		if(elt){
			elt->getvalue(val);
			_rref=matof(val);
			if(_rref==0){
				_rref=1;
			}
		}
		return(true);
	}
	_prop=true;
	elt=_gapp->classMgr()->NthElement(chld,1,"field");
	if(!elt){
		_fld=kOBJ_SubType_;
	}
	else{
		elt->getvalue(val);
		_fld=_gtp->fields()->get_index(val);
		if(!_fld){
			_fld=kOBJ_SubType_;
		}
	}
	
	elt=_gapp->classMgr()->NthElement(chld,1,"value");
	if(elt){
		elt->getvalue(val);
		_qref=matof(val);
		if(_qref==0){
			_qref=1;
		}
	}
	elt=_gapp->classMgr()->NthElement(chld,2,"value");
	if(elt){
		elt->getvalue(val);
		_qmax=matof(val);
		if(_qmax==0){
			_qmax=1;
		}
	}
	elt=_gapp->classMgr()->NthElement(chld,3,"value");
	if(elt){
		elt->getvalue(val);
		_rref=matof(val);
		if(_rref==0){
			_rref=1;
		}
	}
	elt=_gapp->classMgr()->NthElement(chld,4,"value");
	if(elt){
		elt->getvalue(val);
		_exp=matof(val);
		if(_exp==0){
			_exp=1;
		}
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPieChartStyle::prop_dump(bArray& arr, int indent){
char	nm[256];
	
	_gtp->fields()->get_name(_fld,nm);
	if(_prop){
		add_cdesc(arr,indent+1,"propsize","");
		add_cdesc(arr,indent+2,"field",nm);
		add_ddesc(arr,indent+2,"value",_qref,6);
		add_ddesc(arr,indent+2,"value",_qmax,6);
		add_ddesc(arr,indent+2,"value",_rref,2);
		add_ddesc(arr,indent+2,"value",_exp,15);
	}
	else{
		add_ddesc(arr,indent+1,"size",_rref,2);
	}
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPieChartStyle::off_load(bGenericXMLBaseElement* root){
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
bool bvDefPieChartStyle::off_dump(bArray& arr, int indent){
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
void bvDefPieChartStyle::find_stylerun(bGenericXMLBaseElement* root){
	(void)root->dotoall(this,0,test_stylerun);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bvDefPieChartStyle::test_stylerun(bGenericXMLBaseElement* root, void* prm, int indent){
bvDefPieChartStyle*			stl=(bvDefPieChartStyle*)prm;	
char						val[_values_length_max_];
bGenericXMLBaseElement*		elt;
	
	root->getclassname(val);
	if(!strcmp("stylerun",val)){
		elt=stl->_gapp->classMgr()->NthElement(root,1,"classmin");
		if(!elt){
			return(true);
		}
		//		elt->getvalue(val);
		//		if(stl->_clss!=atoi(val)){
		//			return(true);
		//		}
		
		elt=stl->_gapp->classMgr()->NthElement(root,1,"pass");
		if(!elt){
			return(true);
		}
		//		elt->getvalue(val);
		//		if(stl->_pass!=atoi(val)){
		//			return(true);
		//		}
		stl->_gstl=root;
		return(false);
	}
	
	return(true);
}

