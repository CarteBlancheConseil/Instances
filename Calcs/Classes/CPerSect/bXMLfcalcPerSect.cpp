//----------------------------------------------------------------------------
// File : bXMLfcalcPerSect.cpp
// Project : MacMap
// Purpose : C++ source file : Calc intersection percentage formula class. Return intersection percentage between an object and contrasts centroïds.
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
// 12/04/2007 creation.
//----------------------------------------------------------------------------

#include "bXMLfcalcPerSect.h"
#include <MacMapSuite/vx_lib.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bfcalcPerSectElement::bfcalcPerSectElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
					: bStdXMLCalc(elt,gapp,bndl){
	setclassname("fcalcpersect");
	_dbval=new bDoubleDBValue;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bfcalcPerSectElement::~bfcalcPerSectElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bfcalcPerSectElement::create(bGenericXMLBaseElement* elt){
	return(new bfcalcPerSectElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bfcalcPerSectElement::solve(bStdSolver* ctx){
//bTrace	trc("bfcalcPerSectElement::solve",true);
bGenericGeoElement	*oa=ctx->get_object(),*ob;
	_dbval->put(0);
	if(!oa){
//trc.msg("oa==NULL");
		return(ctx->add(_dbval));
	}
bGenericType		*tp;
	tp=_gapp->typesMgr()->get(oa->getType());
int	k=tp->kind();
	if(	(k==kBaseKindPoint)	||
		(k==kBaseKindText)	||
		(k==kBaseKindRaster)||
		(k==kBaseNoKind)	){
//trc.msg("bad kind");
		return(ctx->add(_dbval));
	}
ivertices			*vsa,*vsb,*vsc;
ivx_rect			ra,rb;
	oa->getVertices(&vsa);
	oa->getBounds(&ra);
double				la=ivs_surf(vsa);
double				lb=0;
bArray*				arr=_gapp->cntMgr()->elements();


	if(k==kBaseKindPolygon){
		for(int i=1;i<=arr->count();i++){
			arr->get(i,&ob);
			tp=_gapp->typesMgr()->get(ob->getType());
			if(tp->kind()!=k){
				continue;
			}
			ob->getBounds(&rb);
			if(ivr_sect(&ra,&rb,&rb)){
				ob->getVertices(&vsb);
				vsc=ivs_intersect_as_surf(vsa,vsb);
				if(vsc){
					lb+=ivs_surf(vsc);
					ivs_free(vsc);
				}
			}	
		}
	}
	else if(k==kBaseKindPolyline){
		for(int i=1;i<=arr->count();i++){
			arr->get(i,&ob);
			tp=_gapp->typesMgr()->get(ob->getType());
			if(tp->kind()!=k){
				continue;
			}
			ob->getBounds(&rb);
			if(ivr_sect(&ra,&rb,&rb)){
				ob->getVertices(&vsb);
				vsc=ivs_intersect_as_line(vsa,vsb);
				if(vsc){
					lb+=ivs_length(vsc);
					ivs_free(vsc);
				}
			}	
		}
	}
	la=lb/la;
	if(la>1){
		la=1;
	}
	la*=100;
	_dbval->put(la);
	return(ctx->add(_dbval));
}


