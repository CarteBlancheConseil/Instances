//----------------------------------------------------------------------------
// File : XLinkWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap link (i.e. url) window controller
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
// 18/04/2014 creation.
//----------------------------------------------------------------------------

#import "XLinkWindowController.h"
#import <MacMapSuite/bTrace.h>
#import <mox_intf/mm_messages.h>

// ---------------------------------------------------------------------------
// 
// ------------
#define	kXMapXLinkFiedMessageID	"LinkField"

// ---------------------------------------------------------------------------
// 
// ------------
@implementation XLinkWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[XLinkWindowController init]",true);
	self=[super init];
	if(self){
	}
_tm_((void*)self);	
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[XLinkWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[XLinkWindowController awakeFromNib]",true);
	[super awakeFromNib];
	_ls=0;		
	b_message_string(kXMapXLinkFiedMessageID,_fld,_ext->getbundle(),0);
	[[self window] makeKeyWindow];
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)checkMacMapEvent{
//	_bTrace_("[FicheWindowController checkMacMapEvent]",true);
//	bGenericMacMapApp*	gapp=[self getApp];
//	bArray*				arr=gapp->eventMgr()->events();
//	bGenericEvent*		evt;
//	int					i,j,k;
//	bool				needinval=false;
//	
//	for(i=1;i<=arr->count();i++){
//		arr->get(i,&evt);
//		switch(evt->kind()){
//			case kEventKindGeoElement:{
//				bGenericGeoElement	*o,*mo;
//				int					k;
//				if(evt->action()==kEventActionModify){
//					bArray					tmp(*_arr);
//					tmp.sort(ObjRefComp);
//					for(j=1;j<=evt->elements()->count();j++){
//						evt->elements()->get(j,&mo);
//						o=mo->get_ref();
//						if(tmp.search(&o,ObjRefComp)){
//							needinval=true;
//							break;
//						}
//					}
//				}
//				else if(evt->action()==kEventActionDestroy){
//					bArray				tmp(*(evt->elements()));
//					tmp.sort(ObjRefComp);
//					for(j=_arr->count();j>0;j--){
//						_arr->get(j,&o);
//						if((k=tmp.search(&o,ObjRefComp))){
//							needinval=true;
//							_arr->rmv(j);
//						}
//					}
//				}
//			}
//				break;
//			case kEventKindDataStruct:{
//				bGenericGeoElement*	o;
//				_arr->get(_cur,&o);
//				bGenericType*		tp=gapp->typesMgr()->get(o->getType());
//				
//				field_info			fi;
//				if(evt->action()==kEventActionModify){
//					for(j=1;j<=evt->elements()->count();j++){
//						evt->elements()->get(j,&fi);
//						if(fi.tp!=tp){
//							continue;
//						}
//						needinval=true;
//						[_viw updateField:fi.fid];
//					}
//				}
//				else if(evt->action()==kEventActionDestroy){
//					for(j=1;j<=evt->elements()->count();j++){
//						evt->elements()->get(j,&fi);
//						if(fi.tp!=tp){
//							continue;
//						}
//						needinval=true;
//						[_viw removeField:fi.fid];
//					}
//				}
//				else if(evt->action()==kEventActionCreate){
//					for(j=1;j<=evt->elements()->count();j++){
//						evt->elements()->get(j,&fi);
//						if(fi.tp!=tp){
//							continue;
//						}
//						needinval=true;
//						[_viw addField:fi.fid];	
//					}
//				}
//			}
//				break;
//			case kEventKindTypeElement:{
//				bGenericType*		tp;
//				bGenericGeoElement*	o;
//				if(evt->action()==kEventActionDestroy){
//					for(k=_arr->count();k>0;k--){
//						_arr->get(k,&o);
//						for(j=1;j<=evt->elements()->count();j++){
//							evt->elements()->get(j,&tp);
//							if(o->getType()==tp->index()){
//								_arr->rmv(k);
//								break;
//							}
//						}
//					}
//				}
//			}
//				break;
//		}
//	}
//	if(_arr->count()==0){
//		[self prepareForClose];
//		return;
//	}
//	if(needinval){
//		if(_cur>_arr->count()){
//			_cur=_arr->count();
//		}
//		[self updateUI:YES];
//	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)idle{
bGenericMacMapApp*	gapp=[self getApp];
	if(_ls!=gapp->selMgr()->getState()){
		[self updateUI];
		_ls=gapp->selMgr()->getState();
	}
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateUI{
_bTrace_("[XLinkWindowController updateUI]",true);	
CFURLRef	url;
char		msg[__MESSAGE_STRING_LENGTH_MAX__]="";
	if([self getApp]->selMgr()->count()==1){
bGenericGeoElement*	geo;
		[self getApp]->selMgr()->elements()->get(1,&geo);
		geo->getValue(_fld,msg);
		if(strlen(msg)==0){
			url=CFBundleCopyResourceURL(_ext->getbundle(),CFSTR("no_link"),CFSTR("html"),NULL);	
		}
		else{
			url=CFURLCreateWithBytes(kCFAllocatorDefault,(UInt8*)msg,strlen(msg),kCFStringEncodingMacRoman,NULL);
		}
	}
	else if([self getApp]->selMgr()->count()==0){
		url=CFBundleCopyResourceURL(_ext->getbundle(),CFSTR("no_object"),CFSTR("html"),NULL);	
	}
	else{
		url=CFBundleCopyResourceURL(_ext->getbundle(),CFSTR("too_much_object"),CFSTR("html"),NULL);	
	}
	if(!url){
		return;
	}
NSURLRequest*	request=[NSURLRequest requestWithURL:(NSURL*)url];
	[[_wvw mainFrame] loadRequest:request];	
}

#pragma mark ---- Intf Externe/Cocoa ----
// ---------------------------------------------------------------------------
// 
// ------------
-(bGenericMacMapApp*)getApp{
	return((bGenericMacMapApp*)_ext->getapp());
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

#pragma mark ---- CPP/Carbon Entry Point ----
