//----------------------------------------------------------------------------
// File : bXMLfcalcCapLinOri.cpp
// Project : MacMap
// Purpose : C++ source file : Calc CapLinOri formula class. Return angle between start and end point of a line.
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2017 Carte Blanche Conseil.
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
// 28/04/2017 creation.
//----------------------------------------------------------------------------

#include "bXMLfcalcCapLinOri.h"
#include <MacMapSuite/vx_lib.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bfcalcCapLinOriElement	::bfcalcCapLinOriElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
					: bStdXMLCalc(elt,gapp,bndl){
	setclassname("fcalccaplinori");
	_dbval=new bDoubleDBValue;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bfcalcCapLinOriElement::~bfcalcCapLinOriElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bfcalcCapLinOriElement::create(bGenericXMLBaseElement* elt){
	return(new bfcalcCapLinOriElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bfcalcCapLinOriElement::init(void* ctx){
	bStdXMLCalc::init(ctx);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bfcalcCapLinOriElement::solve(bStdSolver* ctx){
bGenericGeoElement*	o=ctx->get_object();
	if(!o){
		return(false);
	}
    if(!o->selected()){
        return(false);
    }
    
int	val=0;
    
    if(o->getDirection()==0){
long				i;
bGenericGeoElement*	prv;
bArray				sel((*(_gapp->selMgr()->elements())));
ivertices			*vso,*vsp;
        
        for(i=1;i<=sel.count();i++){
            sel.get(i,&prv);
            if(prv==o){
                if(i==1){
                    if(!sel.get(i+1,&prv)){
                        return(false);
                    }
                    break;
                }
                else{
                    if(!sel.get(i-1,&prv)){
                        return(false);
                    }
                    break;
                }
            }
            prv=NULL;
        }
        if(prv==NULL){
            return false;
        }
        o->getVertices(&vso);
        prv->getVertices(&vsp);
        if(i==1){
            if(	(eq_ivx2(&vso->vx.vx2[0],&vsp->vx.vx2[0]))			||
                (eq_ivx2(&vso->vx.vx2[0],&vsp->vx.vx2[vsp->nv-1]))	){
                val=-1;
            }
            else if((eq_ivx2(&vso->vx.vx2[vso->nv-1],&vsp->vx.vx2[0]))		||
                    (eq_ivx2(&vso->vx.vx2[vso->nv-1],&vsp->vx.vx2[vsp->nv-1]))){
                val=1;
            }
            else{
                return false;
            }			
        }
        else{
            if(	(eq_ivx2(&vso->vx.vx2[0],&vsp->vx.vx2[0]))			||
                (eq_ivx2(&vso->vx.vx2[0],&vsp->vx.vx2[vsp->nv-1]))	){
                val=1;
            }
            else if((eq_ivx2(&vso->vx.vx2[vso->nv-1],&vsp->vx.vx2[0]))		||
                    (eq_ivx2(&vso->vx.vx2[vso->nv-1],&vsp->vx.vx2[vsp->nv-1]))){
                val=-1;
            }
            else{
                return false;
            }
        }
    }
    else{
        val=o->getDirection();
    }

    
    
    
ivertices*  vxs;
	o->getVertices(&vxs);
    
double	a;
    if(val==-1){
        a=rad2deg(hv_vx_angle(&vxs->vx.vx2[vxs->nv-1],&vxs->vx.vx2[0]));
    }
    else if(val==1){
        a=rad2deg(hv_vx_angle(&vxs->vx.vx2[0],&vxs->vx.vx2[vxs->nv-1]));
    }
    else{
        return false;
    }
    a+=90.0;
    if(a>=360.0){
        a-=360.0;
    }
	_dbval->put(a);
	return(ctx->add(_dbval));
}

