//----------------------------------------------------------------------------
// File : bSubStyle.cpp
// Project : MacMap
// Purpose : C++ source file : substyle class, used in complex styles
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
// 02/02/2004 creation.
// 27/03/2007 fonctionne avec les tris inverses
//----------------------------------------------------------------------------

#include "bSubStyle.h"
#include <mox_intf/bGenericXMLRenderingElement.h>
#include <mox_intf/CGUtils.h>
#include <mox_intf/bStdWait.h>
#include <std_ext/bStdXMLRenderingElement.h>
#include <MacMapSuite/bStdDirectory.h>	
#include <MacMapSuite/vx_lib.h>
#include <MacMapSuite/bTrace.h>	

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bSubStyle	::bSubStyle()
			:_valbounds(sizeof(double))
			,_styleruns(sizeof(bGenericXMLBaseElement*)){	
	_tp=NULL;
	_fieldname=NULL;
	_fieldindex=0;
	_root=NULL;
	_ctx=NULL;
	_curclass=1;
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bSubStyle::~bSubStyle(){	
	if(_fieldname){
		free(_fieldname);
	}
	_valbounds.reset();
	_styleruns.reset();
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setglobals(void *elt){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setidentification(void *elt){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setcondition(void *elt){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setdrawingmethod(int k){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setclassfield(const char *name){
	if(_fieldname){
		free(_fieldname);
		_fieldname=NULL;
	}
	_fieldname=strdup(name);
	_fieldindex=_tp->fields()->get_index(_fieldname);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setpasscount(int n){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setscaleref(double d){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setunitcoef(double d){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setsortkind(int k){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::addclassbound(double d){
	if(!_valbounds.add(&d)){
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::addclassname(const char* name){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::addstylerun(void *elt){
	_styleruns.add(&elt);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setrunvalidity(void *elt){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setrunrender(void *elt){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setrungeometry(void *elt){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setrunscalemin(double d){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setrunscalemax(double d){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setrunclassmin(long idx){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setrunclassmax(long idx){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setrunpass(long idx){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::settype(const char *name){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setname(const char *name){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setvisible(bool vis){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setselectable(bool sel){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setroot(void* elt){
	_root=(bGenericXMLRenderingElement*)elt;
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setlayer(void* elt){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setmargin(int margin){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setbounds(ivx_rect* bounds){
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::setcontext(bGenericGraphicContext* ctx){
	_ctx=ctx;
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::draw(bStdWait& wt){
bGenericGeoElement*				o=_ctx->getCurElement();
	if(!o){
		return;
	}
	
bStdXMLRenderingElement*		elt;
bArray							arr(sizeof(bStdXMLRenderingElement*));
	get_styleruns(arr,o,0,0);
	for(int i=1;i<=arr.count();i++){
		arr.get(i,&elt);
		if(!elt->applyforobject(_ctx)){
		}
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::draw(bGenericGeoElement* o){
	if(!o){
		return;
	}
	
bStdXMLRenderingElement*		elt;
bArray							arr(sizeof(bStdXMLRenderingElement*));
	get_styleruns(arr,o,0,0);
	for(int i=1;i<=arr.count();i++){
		arr.get(i,&elt);
		if(!elt->applyforobject(_ctx)){
		}
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::rect(bGenericGeoElement* o, CGRect* bounds){
}

// ---------------------------------------------------------------------------
// 
// ------------
bGenericGraphicContext* bSubStyle::get_context_for_object(bGenericGeoElement* o, int pass, bool render){
	return(_ctx);
}

// ---------------------------------------------------------------------------
// 
// ------------
bGenericGraphicContext* bSubStyle::get_context_for_class(int clss, int pass, bool render){
	return(_ctx);
}

// ---------------------------------------------------------------------------
// 
// ------------
bGenericType* bSubStyle::gettype(){
	return(_tp);
}

// ---------------------------------------------------------------------------
// 
// ------------
char* bSubStyle::getname(){
	return(NULL);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bSubStyle::visible(){
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bSubStyle::selectable(){
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
int bSubStyle::getdrawingmethod(){
	return(0);
}

// ---------------------------------------------------------------------------
// 
// ------------
char* bSubStyle::getclassfield(){
	return(_fieldname);
}

// ---------------------------------------------------------------------------
// 
// ------------
int bSubStyle::getpasscount(){
	return(0);
}

// ---------------------------------------------------------------------------
// 
// ------------
double bSubStyle::getscaleref(){
	return(0);
}

// ---------------------------------------------------------------------------
// 
// ------------
double bSubStyle::getunitcoef(){
	return(0);
}

// ---------------------------------------------------------------------------
// 
// ------------
int bSubStyle::getsortkind(){
	return(0);
}

// ---------------------------------------------------------------------------
// 
// ------------
int bSubStyle::getclasscount(){
	return(_valbounds.count());
}

// ---------------------------------------------------------------------------
// 
// ------------
double bSubStyle::getclassbound(int idx){
double	v=__nan();
	_valbounds.get(idx,&v);
	return(v);
}

// ---------------------------------------------------------------------------
// 
// ------------
char* bSubStyle::getclassname(int idx){
	return(NULL);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::set_curclass(int idx){
	if((idx>0)&&(idx>=_valbounds.count())){
		_curclass=idx;
	}
}
		
// ---------------------------------------------------------------------------
// 
// ------------
int bSubStyle::get_curclass(){
	return(_curclass);
}

// ---------------------------------------------------------------------------
// 
// ------------
int bSubStyle::getmargin(){
	return(0);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::report(){	
}

// ---------------------------------------------------------------------------
// 
// ------------
bArray* bSubStyle::objsinrect(CGRect* cgr, bool strict){
	return(NULL);
}

// ---------------------------------------------------------------------------
// 
// ------------
bArray* bSubStyle::objsincircle(CGRect* cgr, bool strict){
	return(NULL);
}

// ---------------------------------------------------------------------------
// 
// ------------
bArray* bSubStyle::objsinpath(CGPoint* cgp, int nb, bool strict){
	return(NULL);
}

// ---------------------------------------------------------------------------
// 
// ------------
bArray* bSubStyle::objsatpoint(CGPoint* cgp, bool all){
	return(NULL);
}

// ---------------------------------------------------------------------------
// 
// ------------
bGenericXMLBaseElement* bSubStyle::root(){
	return(_root);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::get_styleruns(	bArray& arr,
								bGenericGeoElement* o,
								double scale,
								int pass){
	arr.reset();
	if(o->masked()){
		return;
	}
	
double						val;
	_valbounds.get(1,&_minbound);
	_valbounds.get(_valbounds.count(),&_maxbound);
	o->getValue(_fieldindex,&val);
	if((val<_minbound)||(val>_maxbound)){
		return;
	}
int							clss=findclass(val);
bGenericXMLBaseElement*		elt;
	if(_styleruns.get(clss,&elt)){
		arr.add(&elt);
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
int bSubStyle::findclass(double val){
double	a,b;
	
	_valbounds.get(1,&a);
	for(int i=1;i<_valbounds.count();i++){
		_valbounds.get(i+1,&b);
		if((val>=a)&&(val<b)){
			return(i);
		}
		a=b;
	}
	return(0);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSubStyle::settype(bGenericType* tp){
	_tp=tp;
}

