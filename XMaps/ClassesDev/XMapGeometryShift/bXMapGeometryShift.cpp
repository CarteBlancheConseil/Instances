//----------------------------------------------------------------------------
// File : bXMapGeometryShift.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, shift polyline and polygon (equal distance in every point)
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
// 17/07/2007 creation.
// 01/07/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapGeometryShift.h"
#include "CocoaStuff.h"

#include <mox_intf/bEventLog.h>
#include <mox_intf/Type_Utils.h>
#include <mox_intf/ext_utils.h>

#include <MacMapSuite/C_Utils.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapGeometryShift	::bXMapGeometryShift(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
					:bStdXMap(elt,gapp,bndl){
	setclassname("geometryshift2");
char	name[FILENAME_MAX];
GetName(this,name);
(void)_gapp->menuMgr()->add_item(kMenuMgrMenuPalettesID,name,GetSignature(this));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapGeometryShift::~bXMapGeometryShift(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapGeometryShift::create(bGenericXMLBaseElement* elt){
	return(new bXMapGeometryShift(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapGeometryShift::open(int* flags){	
	bStdXMap::open(flags);
	_dst=0;
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXMapGeometryShift::edit(void* prm){
_bTrace_("bXMapGeometryShift::edit()",true);
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
bool bXMapGeometryShift::process(int msg, void* prm){
	switch(msg){
		case kExtProcessCallFromIntf:
			shift();
			break;
		case kExtProcessCallWithParams:{
double			d=*((double*)prm);
				shift(Measure_d2i(_gapp,d));
			}
			break;
		case kExtProcessCallWithXMLTree:{
char					val[_values_length_max_];
bGenericXMLBaseElement*	elt;
double					d;
				elt=getelement(1);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				d=matof(val);
				shift(Measure_d2i(_gapp,d));
			}
			break;
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapGeometryShift::test(void* prm){
	return(SelectionIsMonoGender(_gapp)==kBaseKindPolyline);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapGeometryShift::shift(){
bEventLog	log(_gapp,this);
	shift(Measure_d2i(_gapp,_dst));
	log.close();
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapGeometryShift::shift(double d){
ivertices			*vxs,*vxr;
bGenericGeoElement*	o;
bArray				sel(*(_gapp->selMgr()->elements()));

	_gapp->layersMgr()->SetObjInvalidation(false);
	for(int i=1;i<=sel.count();i++){
		sel.get(i,&o);
		o->inval(kOBJ_Vertices_);
		o->getVertices(&vxs);
		ivs2ivs(vxs,&vxr);
		ivs_shift(&vxr,d);
		if(vxs){
			o->setVertices(vxr);
		}
	}
	_gapp->layersMgr()->SetObjInvalidation(true);
}
