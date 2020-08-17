//----------------------------------------------------------------------------
// File : bToolSymbRotation.cpp
// Project : MacMap
// Purpose : C++ source file : Object modification (symbols/text rotation by field) tool class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2007 Carte Blanche Conseil.
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
// 13/06/2007 creation.
// 19/03/2014 Ready for CG geometry	& drawing
// 24/03/2017 cocoa intf.
//----------------------------------------------------------------------------

#include "bToolSymbRotation.h"
#include "CocoaStuff.h"

#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/ext_utils.h>
#include <mox_intf/bEventLog.h>
#include <mox_intf/MacMapCWrappers.h>

#include <MacMapSuite/bTrace.h>
#include <MacMapSuite/C_Utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bToolSymbRotation	::bToolSymbRotation(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
					: bStdToolPres(elt,gapp,bndl){
	setclassname("symbrotationtool");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bToolSymbRotation::~bToolSymbRotation(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bToolSymbRotation::create(bGenericXMLBaseElement* elt){
	return(new bToolSymbRotation(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolSymbRotation::clic(CGPoint pt, int count){
	bStdToolPres::clic(pt,count);
	if(count>1){
		return;
	}
	set_use_angle(true);
	
bArray*					ga;
bArray					runs(sizeof(bGenericXMLBaseElement*));
bGenericXMLBaseElement	*run,*gm,*elt;
bGenericGeoElement*		o=NULL;
long                    i,n=_gapp->layersMgr()->count();
CGPoint					p;
	
	set_obj(NULL);
	
	get_clic(&p);
	_fa=0;
	_styl=NULL;
	for(i=n;i>0;i--){
        _styl=_gapp->layersMgr()->get(i);
		if(!_styl){
			continue;
		}	
		ga=_styl->objsatpoint(&p,true);
		if(!ga){
			continue;
		}
		if(ga->count()<=0){
			delete ga;
			continue;
		}
		if(ga->count()>1){
			delete ga;
			break;
		}
		ga->get(1,&o);
		delete ga;
		break;
	}
	
	if(!o){
		_styl=NULL;
		return;
	}

bGenericUnit*	scl=_gapp->scaleMgr()->get();

	_styl->get_styleruns(runs,o,scl->coef(),1);

char			val[_values_length_max_];
bGenericType	*tp=_gapp->typesMgr()->get(o->getType());

	for(int i=1;i<=runs.count();i++){
		runs.get(i,&run);
		_fa=0;
		gm=_gapp->classMgr()->NthElement(run,1,"angle");
		if(!gm){
			continue;
		}
		elt=_gapp->classMgr()->NthElement(gm,1,"field");
		if(!elt){
			continue;
		}
		elt->getvalue(val);
		_fa=tp->fields()->get_index(val);
		break;
	}
	if(_fa){
		o->getValue(_fa,&_ia);

CGRect	bnds;
		_styl->rect(o,&bnds);

CGPoint	p;
		p.x=CGRectGetMidX(bnds);
		p.y=CGRectGetMidY(bnds);
		set_clic(&p);
		
i2dvertex	north,co;
		Convert(&co,&p);
		p.x=CGRectGetMaxX(bnds);
		Convert(&north,&p);
		_dst=north.v-co.v;
		set_obj(o);
		set_use_drag(true);
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolSymbRotation::end_clic(){
	bStdToolPres::end_clic();
	if(!get_use_drag()){
		return;
	}
	if(!_fa||!_styl){
		return;
	}
	
bGenericGeoElement*	o=get_obj();
	if(!o){
		return;
	}
	
i2dvertex	vxa,vxb;
	get_clic(&vxb);
	get_cur(&vxa);
double		a=rad2deg(vx_angle(&vxb,&vxa));

	//clearTempPathContext(true);

// Pour avoir la valeur prŽcŽdente en annulation
	o->setValue(_fa,&_ia);
CGRect	bnds;
	_styl->rect(o,&bnds);
	_gapp->mapIntf()->inval(bnds);		

// Report de la nouvelle valeur
bEventLog	log(_gapp,this);
	o->setValue(_fa,&a);
	log.close();
	_styl->rect(o,&bnds);
	_gapp->mapIntf()->inval(bnds);		
	
	set_obj(NULL);
	set_use_drag(false);
	set_use_angle(false);

}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolSymbRotation::update(bool global){
	/*if(!global){
		clearTempPathContext(false);
	}*/
bGenericGeoElement*	o=get_obj();
	if(o){
		//clearTempPathContext(true);
		_gapp->layersMgr()->SwitchContext(kCtxGraphicContext,getTempPathContext());
		_styl->draw(o);
		_gapp->layersMgr()->SwitchContext(kCGGraphicContext,NULL);
		validTempPathContext();
	}
	if(!global){
		validTempPathContext();
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolSymbRotation::track_draw(){
i2dvertex	vxa,vxb;
	get_clic(&vxb);
	get_cur(&vxa);
double		a=rad2deg(vx_angle(&vxb,&vxa));
char		bf[256];
	sprintf(bf,"%.2f¡",a);
	WriteMessage(_gapp,bf);
	
bGenericGeoElement*	o=get_obj();
	if(!o){
		return;
	}
	o->setValue(_fa,&a);	
}

// ---------------------------------------------------------------------------
//
// -----------
bool bToolSymbRotation::edit(void* prm){
_bTrace_("bToolSymbRotation::edit",true);
long    result=0;
    
    set_on_edit(true);
    runCocoaAppModal(this,&result);
    if(result>0){
        save();
    }
    set_on_edit(false);
    
    return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bGenericXMLBaseElement* bToolSymbRotation::load(){
bGenericXMLBaseElement* groot=bStdToolPres::load();
bGenericXMLBaseElement* elt=NULL;
	if(!groot){
		return(NULL);
	}
bGenericXMLBaseElement* root=get_param(groot,"private");
	if(!root){
		_gapp->classMgr()->ReleaseXMLInstance(groot);
		return(NULL);
	}
char	val[_values_length_max_];
float	f;
	for(;;){
		elt=_gapp->classMgr()->NthElement(root,1,"bool");
		if(!elt){
			break;
		}
		elt->getvalue(val);
		set_use_angle(atoi(val));
		elt=_gapp->classMgr()->NthElement(root,1,"float");
		if(!elt){
			break;
		}
		elt->getvalue(val);
		f=matof(val);
		while(f>360){
			f-=360;
		}
		while(f<0){
			f+=360;
		}
		set_angle(f);
		break;
	}
	_gapp->classMgr()->ReleaseXMLInstance(groot);
	return(NULL);
}

// ---------------------------------------------------------------------------
// 
// -----------
bGenericXMLBaseElement* bToolSymbRotation::make(bArray &arr){
	add_cdesc(arr,0,"param","");
	add_cdesc(arr,1,"version",kCurrentToolParamVers);
	add_cdesc(arr,1,"param","");
	add_cdesc(arr,2,"sign","private");
	add_idesc(arr,2,"bool",get_use_angle());
	add_ddesc(arr,2,"float",get_angle(),0);
	return(bStdToolPres::make(arr));
}

