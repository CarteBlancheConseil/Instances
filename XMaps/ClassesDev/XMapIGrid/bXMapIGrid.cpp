//----------------------------------------------------------------------------
// File : bXMapIGrid.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, import grid and projection (type dispatch)
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2016 Carte Blanche Conseil.
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
// 24/11/2005 creation.
// 09/02/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapIGrid.h"
#include "CocoaStuff.h"
#include <MacMapSuite/bTrace.h>
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapIGrid	::bXMapIGrid(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
            :bStdXMap(elt,gapp,bndl){
	setclassname("igrid2");
               
char	name[FILENAME_MAX];
GetName(this,name);
(void)_gapp->menuMgr()->add_item(kMenuMgrMenuPalettesID,name,GetSignature(this));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapIGrid::~bXMapIGrid(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapIGrid::create(bGenericXMLBaseElement* elt){
	return(new bXMapIGrid(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapIGrid::open(int* flags){
	bStdXMap::open(flags);
	read_p();
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXMapIGrid::edit(void* prm){
_bTrace_("bXMapCloneDetector::edit()",true);
long    result=0;
    runCocoaAppModal(this,&result);
    if(result>0){
        return(process(kExtProcessCallFromIntf,prm));
    }
    return false;
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapIGrid::process(int msg, void* prm){
import_grid*	p;
	switch(msg){
        case kExtProcessCallFromIntf:
            write_p();
            break;
		case kExtProcessCallGetData:
			p=(import_grid*)prm;
			*p=_prm;
			break;
		case kExtProcessCallSetData:
			p=(import_grid*)prm;
			_prm=*p;
            write_p();
			break;
		case kExtProcessCallWithXMLTree:{
char					val[_values_length_max_];
bGenericType*			tp;
bGenericXMLBaseElement*	elt;
				elt=getelement(1);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				_prm.srid=atoi(val);
				
				elt=getelement(2);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				tp=_gapp->typesMgr()->get(_gapp->typesMgr()->index(val));
				_prm.t_point=(tp)?tp->tid():0;

				elt=getelement(3);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				tp=_gapp->typesMgr()->get(_gapp->typesMgr()->index(val));
				_prm.t_line=(tp)?tp->tid():0;
				
				elt=getelement(4);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				tp=_gapp->typesMgr()->get(_gapp->typesMgr()->index(val));
				_prm.t_text=(tp)?tp->tid():0;
			
				elt=getelement(5);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				tp=_gapp->typesMgr()->get(_gapp->typesMgr()->index(val));
				_prm.t_poly=(tp)?tp->tid():0;
				
				elt=getelement(6);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				tp=_gapp->typesMgr()->get(_gapp->typesMgr()->index(val));
				_prm.t_raster=(tp)?tp->tid():0;
				
				write_p();
			}break;

			break;
	}
	return(true);
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapIGrid::set_infos(import_grid prm){
    _prm=prm;
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapIGrid::get_infos(import_grid* prm){
    (*prm)=_prm;
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapIGrid::read_p(){
_bTrace_("bXMapIGrid::read_p",false);
char	name[_names_length_max_];
	getclassname(name);
bGenericXMLBaseElement* root=NULL;
bGenericXMLBaseElement* elt=NULL;
bool					b=_gapp->document()->readTree(&root,GetSignature(this),name);
char					val[_values_length_max_];
	
	_prm.t_point=0;
	_prm.t_line=0;
	_prm.t_poly=0;
	_prm.t_text=0;
	_prm.t_raster=0;
	_prm.srid=-1;

	if((!b)||(!root)){
		write_p();
		(void)_gapp->document()->readTree(&root,GetSignature(this),name);
		return;
	}
	if((!b)||(!root)){
_te_("((!b)||(!root)) for "+name);
		return;
	}
	elt=_gapp->classMgr()->NthElement(root,1,"float");
	if(!elt){
		return;
	}
	elt->getvalue(val);
	_prm.t_point=matof(val);
	
	elt=_gapp->classMgr()->NthElement(root,2,"float");
	if(!elt){
		return;
	}
	elt->getvalue(val);
	_prm.t_line=matof(val);
	
	elt=_gapp->classMgr()->NthElement(root,3,"float");
	if(!elt){
		return;
	}
	elt->getvalue(val);
	_prm.t_poly=matof(val);
	
	elt=_gapp->classMgr()->NthElement(root,4,"float");
	if(!elt){
		return;
	}
	elt->getvalue(val);
	_prm.t_text=matof(val);
	
	elt=_gapp->classMgr()->NthElement(root,5,"float");
	if(!elt){
		return;
	}
	elt->getvalue(val);
	_prm.t_raster=matof(val);

	elt=_gapp->classMgr()->NthElement(root,1,"int");
	if(elt){
		elt->getvalue(val);
		_prm.srid=atoi(val);
	}
	else{
		_prm.srid=-1;
	}
		
	_gapp->classMgr()->ReleaseXMLInstance(root);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapIGrid::write_p(){
bGenericXMLBaseElement* root=make_p();
	if(!root){
		return;
	}
char	name[_names_length_max_];
	getclassname(name);

	if(!_gapp->document()->writeTree(root,GetSignature(this),name)){
		return;
	}
	_gapp->classMgr()->ReleaseXMLInstance(root);
}

// ---------------------------------------------------------------------------
// 
// ------------
bGenericXMLBaseElement* bXMapIGrid::make_p(){
bArray	arr(sizeof(xmlelt));
	add_cdesc(arr,0,"param","");
	add_cdesc(arr,1,"version","3.0.0");

	add_ddesc(arr,1,"float",_prm.t_point,0);
	add_ddesc(arr,1,"float",_prm.t_line,0);
	add_ddesc(arr,1,"float",_prm.t_poly,0);
	add_ddesc(arr,1,"float",_prm.t_text,0);
	add_ddesc(arr,1,"float",_prm.t_raster,0);
	add_idesc(arr,1,"int",_prm.srid);

bGenericXMLBaseElement*	root=_gapp->classMgr()->ParseXMLDescriptors(&arr);
	free_descs(arr);
	return(root);
}
