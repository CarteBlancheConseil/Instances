//----------------------------------------------------------------------------
// File : bXMapSimplify.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, simplify selected geometries
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
// 29/11/2007 creation.
// 21/07/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapSimplify.h"
#include "CocoaStuff.h"

#include <mox_intf/bEventLog.h>
#include <mox_intf/ext_utils.h>
#include <mox_intf/Type_Utils.h>
#include <mox_intf/MacMapCWrappers.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapSimplify	::bXMapSimplify(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				:bStdXMap(elt,gapp,bndl){
	setclassname("simplify");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapSimplify::~bXMapSimplify(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapSimplify::create(bGenericXMLBaseElement* elt){
	return(new bXMapSimplify(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapSimplify::open(int* flags){	
	bStdXMap::open(flags);
	_a=0;
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapSimplify::process(int msg, void* prm){
	switch(msg){
		case kExtProcessCallFromIntf:
			return(simplify());
			break;
		case kExtProcessCallWithParams:{
double*		a=(double*)prm;
			return(simplify(*a));
			}break;
		case kExtProcessCallWithXMLTree:{
double					a;
char					val[_values_length_max_];
bGenericXMLBaseElement*	elt;
				elt=getelement(1);
				if(!elt){
					return(false);
				}
				elt->getvalue(val);
				a=atof(val);
				return(simplify(a));
			}	
			break;
		default:
			break;
	}
	return(false);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapSimplify::test(void* prm){
//	return(_gapp->selMgr()->count()>0);
int knd=SelectionIsMonoGender(_gapp);
    if((knd==kBaseKindPolyline)||(kBaseKindPolygon)){
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
//
// ------------
bool bXMapSimplify::edit(void* prm){
long    result=0;
    runCocoaAppModal(this,&result);
    if(result>0){
        return(process(kExtProcessCallFromIntf,prm));
    }
    return(false);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapSimplify::simplify(){
bEventLog	log(_gapp,this);
	(void)simplify(_a);
	log.close();
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapSimplify::simplify(double d){
ivertices			*vxo,*vxs;
bGenericType*       tp;
bGenericGeoElement*	o;
bArray				sel(*(_gapp->selMgr()->elements()));
bool                flg=false;
    
    FlushContrasts(_gapp);
    _gapp->layersMgr()->SetObjInvalidation(false);
	for(int i=1;i<=sel.count();i++){
		sel.get(i,&o);
		o->getVertices(&vxs);

        tp=_gapp->typesMgr()->get(o->getType());
        if(ivs_integrity(tp->kind(),vxs)){
            if(tp->kind()==kBaseKindPolyline){
                vxo=ivs_polylineFix(vxs);
            }
            else if(tp->kind()==kBaseKindPolygon){
                vxo=ivs_polygonFix(vxs);
            }
            else{
                vxo=NULL;
            }
            flg=true;
        }
        else{
            ivs2ivs(vxs,&vxo);
        }
        if(vxo==NULL){
            o->setcontrast(true,true);
            continue;
        }

        ivs_simplify_with_angle(&vxo,deg2rad(_a));
        
		if((flg)||(vxo->nv!=vxs->nv)){
			o->setVertices(vxo);
		}
		ivs_free(vxo);
	}
	_gapp->layersMgr()->SetObjInvalidation(true);
	return(true);
}
