//----------------------------------------------------------------------------
// File : bToolContiguous.cpp
// Project : MacMap
// Purpose : C++ source file : Contiguous tool class (Select a set of connected lines having same value in a field, usefull for roadmaps).
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2006 Carte Blanche Conseil.
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
// 07/04/2006 creation.
// 19/03/2014 Ready for CG geometry	& drawing
// 03/03/2017 cocoa intf.
//----------------------------------------------------------------------------

#include "bToolContiguous.h"
#include "CocoaStuff.h"

#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/MacMapCWrappers.h>
#include <mox_intf/Type_Utils.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bToolContiguous	::bToolContiguous(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				: bStdToolNav(elt,gapp,bndl)
				,_types(sizeof(int)){
	setclassname("contiguoustool");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bToolContiguous::~bToolContiguous(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bToolContiguous::create(bGenericXMLBaseElement* elt){
	return(new bToolContiguous(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolContiguous::close(){
	bStdToolNav::close();
	_types.reset();
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolContiguous::clic(CGPoint pt, int count){
	bStdToolNav::clic(pt,count);
bArray*				ga;
bGenericStyle*		style;
bGenericGeoElement*	o=NULL;
	if(!is_modifiers(shiftKey)){
		FlushSelection(_gapp);
	}
	for(int i=CountLayers(_gapp);i>0;i--){
		style=(bGenericStyle*)GetIndLayer(_gapp,i);
		if(!style){
			continue;
		}
		if(style->gettype()==NULL){
			continue;
		}
		if(style->gettype()->kind()!=kBaseKindPolyline){
			continue;
		}
		ga=style->objsatpoint(&pt,false);
		if(!ga){
			continue;
		}
		if(ga->count()<=0){
			delete ga;
			continue;
		}
		ga->get(1,&o);
		o->setselect(true,true);
		delete ga;
		break;
	}
	if(o){
		line_propagate(o);
	}
}

// ---------------------------------------------------------------------------
//
// -----------
bool bToolContiguous::edit(void* prm){
_bTrace_("bToolContiguous::edit",true);
long    result=0;
  
/* A GERER PAR UN MAP EVENT*/
bGenericType*	tp;
int				fid;
    for(int i=_types.count()+1;i<=_gapp->typesMgr()->count();i++){
        tp=_gapp->typesMgr()->get(i);
        fid=tp->fields()->get_id(kOBJ_Name_);
        _types.add(&fid);
    }
    for(int i=_types.count();i>_gapp->typesMgr()->count();i--){
        _types.rmv(i);
    }
    for(int i=1;i<=_types.count();i++){
        tp=_gapp->typesMgr()->get(i);
        _types.get(i,&fid);
        if(!tp->fields()->get_index(fid)){
            fid=tp->fields()->get_id(kOBJ_Name_);
            _types.put(i,&fid);
        }
    }
/* A GERER PAR UN MAP EVENT*/

    set_on_edit(true);
    runCocoaAppModal(this,&result);
    if(result>0){
        _tm_("save");
        save();
    }
    else{
        _tm_("load");
        load();
    }
    set_on_edit(false);
    
    return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolContiguous::line_propagate(bGenericGeoElement* o){
bGenericType*	tp=_gapp->typesMgr()->get(o->getType());
ivertices		*vsa,*vsb;
i2dvertex		*pvxa,*pvxb;
ivx_rect		vr;
bArray			arr(sizeof(bGenericGeoElement*));
bArray*			buff;
int				i,j,k,l,na,nb;
int				fidx;
char			va[1024],vb[1024];

bCursWait		wt(true);

	i=tp->index();
    if(!_types.get(i,&j)){
        return;
    }
	fidx=tp->fields()->get_index(j);
	o->getValue(fidx,va);
	if(strlen(va)==0){
		return;
	}
	arr.add(&o);
	while(arr.count()>0){
		wt.set_progress(0);
		if(!wt.get_progress()){
			break;
		}

		for(i=arr.count();i>0;i--){
			arr.get(i,&o);
			o->getVertices(&vsa);
			arr.rmv(i);
			for(j=0;j<ivs_n_parts(vsa);j++){
				pvxa=ivs2_part(vsa,j,&na);
				if(na>1){
					ivrset(&vr,pvxa[0].h,pvxa[0].v,pvxa[0].h,pvxa[0].v);
					tp->iterator()->objs_in_rect(&buff,&vr);
					if(buff){
						if(buff->count()>0){
							for(k=1;k<=buff->count();k++){
								buff->get(k,&o);
								if(o->masked()){
									continue;
								}
								if(o->selected()){
									continue;
								}
								o->getValue(fidx,vb);
								if(strcmp(va,vb)){
									continue;
								}
								o->getVertices(&vsb);
								for(l=0;l<ivs_n_parts(vsb);l++){
									pvxb=ivs2_part(vsb,l,&nb);
									if(nb<=0){
										continue;
									}
									if(	(eq_ivx2(&pvxa[0],&pvxb[0]))	||
										(eq_ivx2(&pvxa[0],&pvxb[nb-1]))	){
										arr.add(&o);
										o->setselect(true,true);
										break;
									}
								}
							}
						}
						delete buff;
					}
					
					ivrset(&vr,pvxa[na-1].h,pvxa[na-1].v,pvxa[na-1].h,pvxa[na-1].v);
					tp->iterator()->objs_in_rect(&buff,&vr);
					if(buff){
						if(buff->count()>0){
							for(k=1;k<=buff->count();k++){
								buff->get(k,&o);
								if(o->masked()){
									continue;
								}
								if(o->selected()){
									continue;
								}
								o->getValue(fidx,vb);
								if(strcmp(va,vb)){
									continue;
								}
								o->getVertices(&vsb);
								for(l=0;l<ivs_n_parts(vsb);l++){
									pvxb=ivs2_part(vsb,l,&nb);
									if(nb<=0){
										continue;
									}
									if(	(eq_ivx2(&pvxa[na-1],&pvxb[0]))		||
										(eq_ivx2(&pvxa[na-1],&pvxb[nb-1]))	){
										arr.add(&o);
										o->setselect(true,true);
										break;
									}
								}
							}
						}
						delete buff;
					}
					
				}
			}
		}
	}

}

// ---------------------------------------------------------------------------
// 
// -----------
bGenericXMLBaseElement* bToolContiguous::load(){
bGenericXMLBaseElement* groot=bStdToolNav::load();
	
	if(groot){
		_gapp->classMgr()->ReleaseXMLInstance(groot);
	}
	_types.reset();
	for(int i=1;i<=_gapp->typesMgr()->count();i++){
		load_type(i);
	}
	return(NULL);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolContiguous::save(){
	bStdToolNav::save();
bGenericXMLBaseElement* root;
char					nm[_names_length_max_];
	getclassname(nm);
	for(int i=1;i<=_types.count();i++){
		root=make(i);
		if(!root){
			continue;
		}
		SetXMLParamToType(_gapp->typesMgr()->get(i),nm,"config.xml",root);
		_gapp->classMgr()->ReleaseXMLInstance(root);		
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
bGenericXMLBaseElement* bToolContiguous::make(bArray& arr){
	add_cdesc(arr,0,"param","");
	add_cdesc(arr,1,"version",kCurrentToolParamVers);
	return(bStdToolNav::make(arr));
}

// ---------------------------------------------------------------------------
// 
// -----------
bGenericXMLBaseElement* bToolContiguous::make(int tidx){
bGenericXMLBaseElement*	root;
bArray					arr(sizeof(xmlelt));
int						cid;
bGenericType*			tp=_gapp->typesMgr()->get(tidx);

	add_cdesc(arr,0,"param","");
	add_cdesc(arr,1,"version","3.0.0");
	_types.get(tidx,&cid);
	if(tp->fields()->get_index(cid)){
		add_idesc(arr,1,"int",cid);
	}
	root=_gapp->classMgr()->ParseXMLDescriptors(&arr);
	free_descs(arr);
	return(root);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bToolContiguous::load_type(int tidx){
_bTrace_("bToolContiguous::load_type",false);
bGenericXMLBaseElement* root=NULL;
bGenericXMLBaseElement* elt=NULL;
char					nm[_names_length_max_];
char					val[_values_length_max_];
bGenericType*			tp=_gapp->typesMgr()->get(tidx);
int						fid=tp->fields()->get_index(kOBJ_Name_);

	getclassname(nm);
	root=GetXMLParamFromType(_gapp,tp,nm,"config.xml");
	if(!root){
_tw_("!root");
		_types.add(&fid);
		return;
	}
	elt=_gapp->classMgr()->NthElement(root,1,"int");
	if(!elt){
_te_("!elt");
		_types.add(&fid);
		_gapp->classMgr()->ReleaseXMLInstance(root);
		return;
	}
	elt->getvalue(val);
	if(tp->fields()->get_index(atoi(val))){
		fid=atoi(val);
	}
	_types.add(&fid);
	_gapp->classMgr()->ReleaseXMLInstance(root);
}
