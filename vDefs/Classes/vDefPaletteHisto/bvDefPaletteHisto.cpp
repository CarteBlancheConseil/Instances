//----------------------------------------------------------------------------
// File : bvDefPaletteHisto.cpp
// Project : MacMap
// Purpose : C++ source file : Histogram vdef class
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

#include "bvDefPaletteHisto.h"
#include "bvDefHistoStyle.h"
#include "CocoaStuff.h"
#include <MacMapSuite/bTrace.h>
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/endian.h>
#include <mox_intf/ext_utils.h>
#include <MacMapSuite/valconv.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefPaletteHisto	::bvDefPaletteHisto(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
						: bStdNSPalettevDef(elt,gapp,bndl)
						,_fields(sizeof(int)){
	setclassname("palettehistogram");
	strcpy(_stylename,"rectstyle");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefPaletteHisto::~bvDefPaletteHisto(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bvDefPaletteHisto::create(bGenericXMLBaseElement* elt){
	return(new bvDefPaletteHisto(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPaletteHisto::test(bGenericType* tp){
	if(bStdNSPalettevDef::test(tp)==false){
		return(false);
	}
	if(tp==NULL){
		return(false);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
void* bvDefPaletteHisto::ccinit(){	
	return(initializeCocoa(getapp(),this));
}

// ---------------------------------------------------------------------------
// 
// ------------
void bvDefPaletteHisto::stl_alloc(bool){
_bTrace_("bvDefPaletteHisto::stl_alloc()",true);
	if(_fields.count()==0){
_tw_("pas de champ");
//		return;
	}
bvDefHistoStyle	*stl,*ref;
	stl=new bvDefHistoStyle(_gapp,_tp,&_fields);
	if(_styles.get(1,&ref)){
		stl->_smin=ref->_smin;
		stl->_smax=ref->_smax;
		stl->_offx=ref->_offx;
		stl->_offy=ref->_offy;
		stl->_centro=ref->_centro;
	}
	_styles.add(&stl);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bvDefPaletteHisto::stl_free(){
_bTrace_("bvDefPaletteHisto::stl_free()",true);
bvDefHistoStyle* stl;
	for(int i=1;i<=_styles.count();i++){
		_styles.get(i,&stl);
		delete stl;
	}
	_styles.reset();
	_fields.reset();
}

// ---------------------------------------------------------------------------
// 
// -----------
void bvDefPaletteHisto::make(){
bArray	arr(sizeof(xmlelt));
char	val[256];
UInt32	sign=_sign;
	
	_bck=false;
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
	
	add_cdesc(arr,0,_stylename,"");
	
// Identification		
	add_cdesc(arr,1,"styleidentification","");
	add_cdesc(arr,2,"name",_name);
	sprintf(val,"%.4s",(char*)&sign);
	add_cdesc(arr,2,"sign",val);
	add_cdesc(arr,2,"version",_vers);
	
// Globals
	add_cdesc(arr,1,"globals","");
	_tp->fields()->get_name(_fld,val);
	add_cdesc(arr,2,"classfield",val);
bGenericUnit*	u=_gapp->scaleMgr()->get();
	add_ddesc(arr,2,"scaleref",u->coef(),6);
	add_ddesc(arr,2,"unitcoef",1,0);
	add_idesc(arr,2,"sort",-1);
	add_idesc(arr,2,"passcount",1);
	add_cdesc(arr,2,"classboundsarray","");
	add_ddesc(arr,3,"classbound",1,0);
	add_cdesc(arr,3,"classname","min");
	add_ddesc(arr,3,"classbound",INT_MAX,0);
	add_cdesc(arr,3,"classname","max");
	
// Condition	
	add_cdesc(arr,1,"condition","");

// Nothing else, condition are optional.
	
	_root=_gapp->classMgr()->ParseXMLDescriptors(&arr);
	free_descs(arr);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPaletteHisto::read(){
_bTrace_("bvDefPaletteHistoc::read",true);
bool	made=false,b=false;

	_bck=false;
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
	
	if(!_root){
		make();
		made=true;
	}
	
bGenericXMLBaseElement* chld;
bGenericXMLBaseElement* elt;
bvDefHistoStyle*		stl;
char					val[_values_length_max_];
int						i,n;
double					bmax=INT_MAX;
	
	for(;;){
// Identification		
		chld=_gapp->classMgr()->NthElement(_root,1,"styleidentification");
		if(!chld){
			break;
		}
		elt=_gapp->classMgr()->NthElement(chld,1,"name");
		if(!elt){
			break;
		}
		elt->getvalue(_name);
		elt=_gapp->classMgr()->NthElement(chld,1,"version");
		if(!elt){
			break;
		}
		elt->getvalue(_vers);
		if(strlen(_vers)==0){
			strcpy(_vers,"3.0.0");
		}
// Globals
		chld=_gapp->classMgr()->NthElement(_root,1,"globals");
		if(!chld){
			break;
		}
		
		elt=_gapp->classMgr()->NthElement(chld,1,"classfield");
		if(!elt){
			break;
		}
		elt->getvalue(val);
		_fld=_tp->fields()->get_index(val);
		if(_fld==0){
			_fld=kOBJ_SubType_;
		}
		
		i=0;
		do{	
			i++;
			elt=_gapp->classMgr()->NthElement(chld,i,"classbound");
			if(elt){
				elt->getvalue(val);
				bmax=matof(val);
			}
		}while(elt);
		
		elt=_gapp->classMgr()->NthElement(chld,1,"scaleref");
		if(!elt){
			break;
		}
		elt->getvalue(val);
		_sref=matof(val);
		elt=_gapp->classMgr()->NthElement(chld,1,"unitcoef");
		if(!elt){
			break;
		}
		elt->getvalue(val);
		_coef=matof(val);
		
// Condition		
		chld=_gapp->classMgr()->NthElement(_root,1,"condition");
		if(!chld){
			break;
		}
		if(chld->countelements()>0){
			elt=chld->getelement(1);
			elt->getclassname(val);
			for(i=1;i<=nsvdef_op_max;i++){
				if(!strcmp(val,nsvdef_op_list[i])){
					chld=elt;
					if(chld->countelements()==2){
						elt=chld->getelement(1);
						elt->getvalue(val);
						_cfld=_tp->fields()->get_index(val);
						if(_cfld){
							elt=chld->getelement(2);
							elt->getvalue(_cval);
						}
					}
					else{
						_cfld=0;
					}
					break;
				}
			}
			if(i==nsvdef_op_max+1){
				_cfld=0;
			}
			else{
				_cop=i;
			}
		}
		else{
			_cfld=0;
		}
		
// StyleRuns
		n=_gapp->classMgr()->CountElements(_root,"stylerun");
		for(i=1;i<=n;i++){
			chld=_gapp->classMgr()->NthElement(_root,i,"stylerun");
			stl_alloc(true);
			_styles.get(i,&stl);
			stl->load(chld);
			if(stl->is_back()){
				_stroke[0]=stl->_stroke[0];
				_stroke[1]=stl->_stroke[1];
				_stroke[2]=stl->_stroke[2];
				_stroke[3]=stl->_stroke[3];
				_stroke[4]=stl->_stroke[4];
				_fill[0]=stl->_fill[0];
				_fill[1]=stl->_fill[1];
				_fill[2]=stl->_fill[2];
				_fill[3]=stl->_fill[3];
				_fill[4]=stl->_fill[4];
				_width=stl->_width;
				_bck=true;
			}
			_cmyk=(stl->_cc==5);
		}
		for(i=_styles.count();i>0;i--){
			_styles.get(i,&stl);
			if(stl->is_back()){
				_styles.rmv(i);
				delete stl;
			}
		}
		
		b=true;
		break;
	}

	if(made){
		_gapp->classMgr()->ReleaseXMLInstance(_root);
		_root=NULL;
	}
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPaletteHisto::write(){
_bTrace_("bvDefPaletteHistoc::write",true);
bArray			arr(sizeof(xmlelt));
char			val[_values_length_max_];
int				n;
bvDefHistoStyle	*stl,*src;
UInt32			sign=_sign;
	
//	if(_styles.get(1,&stl)){
//		qref=stl->_qref;
//		qmax=stl->_qmax;
//	}
	
	add_cdesc(arr,0,_stylename,"");
	
// Identification			
	add_cdesc(arr,1,"styleidentification","");
	add_cdesc(arr,2,"name",_name);
	sprintf(val,"%.4s",&sign);
	add_cdesc(arr,2,"sign",val);
	add_cdesc(arr,2,"version",_vers);
	
// Globals		
	add_cdesc(arr,1,"globals","");
	_tp->fields()->get_name(_fld,val);
	add_cdesc(arr,2,"classfield",val);
	add_ddesc(arr,2,"scaleref",_sref,0);
	add_ddesc(arr,2,"unitcoef",_coef,6);
	add_idesc(arr,2,"sort",0);
	add_idesc(arr,2,"passcount",1);
	add_cdesc(arr,2,"classboundsarray","");
	add_idesc(arr,3,"classbound",1);
	add_cdesc(arr,3,"classname","min");
	add_idesc(arr,3,"classbound",INT_MAX);
	add_cdesc(arr,3,"classname","max");
	
// Conditions	
	add_cdesc(arr,1,"condition","");
	if(_cfld){
		add_cdesc(arr,2,nsvdef_op_list[_cop],"");
		_tp->fields()->get_name(_cfld,val);
		add_cdesc(arr,3,"dbfield",val);
		_tp->fields()->get_kind(_cfld,&n);
		switch(n){
			case _bool:
				add_cdesc(arr,3,"dbbool",_cval);
				break;
			case _int:
				add_cdesc(arr,3,"dbint",_cval);
				break;
			case _double:
				add_cdesc(arr,3,"dbfloat",_cval);
				break;
			case _date:
				add_cdesc(arr,3,"dbdate",_cval);
				break;
			case _time:
				add_cdesc(arr,3,"dbtime",_cval);
				break;
			default:
				add_cdesc(arr,3,"dbchar",_cval);
				break;
		}
	}
	
	// StyleRuns
	if(_bck){
_tm_("insertion du style background");
		if(_styles.get(1,&src)){
			stl_alloc(true);
			_styles.get(_styles.count(),&stl);
			stl->_stroke[0]=_stroke[0];
			stl->_stroke[1]=_stroke[1];
			stl->_stroke[2]=_stroke[2];
			stl->_stroke[3]=_stroke[3];
			stl->_stroke[4]=_stroke[4];
			stl->_fill[0]=_fill[0];
			stl->_fill[1]=_fill[1];
			stl->_fill[2]=_fill[2];
			stl->_fill[3]=_fill[3];
			stl->_fill[4]=_fill[4];
			stl->_width=_width;
			stl->_isback=true;
			stl->_cc=_cmyk?5:4;
			stl->_smin=src->_smin;
			stl->_smax=src->_smax;
			stl->_offx=src->_offx;
			stl->_offy=src->_offy;
			stl->_dimx=src->_dimx;
			stl->_dimy=src->_dimy;
			stl->_dx=src->_dx;
			stl->_dy=src->_dy;
			stl->_spc=src->_spc;
			stl->_onx=src->_onx;
			stl->_centro=src->_centro;
			
			_styles.rmv(_styles.count());
			_styles.insert(1,&stl);
		}
	}
	for(int i=1;i<=_styles.count();i++){
_tm_("dump style "+i);
		_styles.get(i,&stl);
		stl->dump(arr,0);
	}
	if(_bck){
_tm_("retrait du style background");
		_styles.get(1,&stl);
		_styles.rmv(1);
		delete stl;
	}
	
	_root=_gapp->classMgr()->ParseXMLDescriptors(&arr);
	
	free_descs(arr);
	
	return(true);
}
