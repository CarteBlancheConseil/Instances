//----------------------------------------------------------------------------
// File : bXMapBrowserContainer.cpp
// Project : MacMap
// Purpose : C++ source file : XMap Browser container class (possibility to open more than one browser)
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
// Dispatcher for multi browser
//----------------------------------------------------------------------------
// 06/02/2007 creation.
//----------------------------------------------------------------------------

#include "bXMapBrowserContainer.h"
#include "bXMapBrowser.h"
#include <mox_intf/Type_Utils.h>
#include <MacMapSuite/bTrace.h>
#include <Cocoa/Cocoa.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapBrowserContainer::bXMapBrowserContainer(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
			:bStdXMap(elt,gapp,bndl)
			,_elts(sizeof(bXMapBrowser*)){
	setclassname("browsercontainer");
	set_flags(kXMapNeedIdle+kXMapNeedEvents);
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapBrowserContainer::~bXMapBrowserContainer(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapBrowserContainer::create(bGenericXMLBaseElement* elt){
	return(new bXMapBrowserContainer(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapBrowserContainer::open(int* flags){
	bStdXMap::open(flags);
bXMapBrowser*	brow;
	for(int i=1;i<=_gapp->typesMgr()->count();i++){
		brow=new bXMapBrowser(NULL,_gapp,getbundle());
		brow->open(flags);
		_elts.add(&brow);
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapBrowserContainer::close(){
	bStdXMap::close();
bXMapBrowser*	brow;
	for(int i=1;i<=_elts.count();i++){
		_elts.get(i,&brow);
		brow->close();
		delete brow;
	}
	_elts.reset();
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapBrowserContainer::nsevent(void* nsevt){
//_bTrace_("bXMapBrowserContainer::nsevent",true);
bool			res=false;
bXMapBrowser*	brow;

NSEvent*        evt=(NSEvent*)nsevt;
    
	if( ([evt type]==NSEventTypeApplicationDefined)     &&
        ([evt subtype]==NSEventSubtypeMacMapDataBase)   ){
bArray*			arr=_gapp->eventMgr()->events();
bGenericEvent*	mevt;
bGenericType*	tp;
int				i,j,k;

		for(i=1;i<=arr->count();i++){
			arr->get(i,&mevt);
			switch(mevt->kind()){
				case kEventKindTypeElement:{
					if(mevt->action()==kEventActionDestroy){
						for(j=1;j<=mevt->elements()->count();j++){
							mevt->elements()->get(j,&tp);
							k=tp->index();
							_elts.get(k,&brow);
							if(brow){
								brow->close();
								delete brow;
								brow=NULL;
								_elts.put(k,&brow);
							}
						}
						for(int j=_elts.count();j>0;j--){
							_elts.get(j,&brow);
							if(brow==NULL){
								_elts.rmv(j);
							}
						}
						res=true;					
					}
					else if(mevt->action()==kEventActionCreate){
						for(j=1;j<=mevt->elements()->count();j++){
							brow=new bXMapBrowser(NULL,_gapp,getbundle());
							brow->open(&k);
							_elts.add(&brow);
						}
						res=true;					
					}
					}
					break;
			}
		}
		if(res==true){
			res=false;
			return(res);
		}
	}
	
	for(int i=1;i<=_elts.count();i++){
		_elts.get(i,&brow);
		res=brow->nsevent(nsevt);
		if(res){
			break;
		}
	}

	return(res);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bXMapBrowserContainer::idle(void* prm){
bXMapBrowser*	brow;
	for(int i=1;i<=_elts.count();i++){
		_elts.get(i,&brow);
		brow->idle(NULL);
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapBrowserContainer::process(int msg, void* prm){
	if(msg!=kExtProcessCallFromIntf){
		return(true);
	}
bXMapBrowser*	brow;
bGenericType*	tp;
	
	for(int i=1;i<=_elts.count();i++){
		_elts.get(i,&brow);
		tp=_gapp->typesMgr()->get(i);
		if(tp->nb_sel()>0){
			brow->edit(prm);
		}
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapBrowserContainer::test(void* prm){
	return(SelectionIsMonoType(_gapp));
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapBrowserContainer::edit(void* prm){
	return(process(kExtProcessCallFromIntf,prm));
}
