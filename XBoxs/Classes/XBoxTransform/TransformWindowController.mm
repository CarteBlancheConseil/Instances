//----------------------------------------------------------------------------
// File : TransformWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Transformation XMapBox window controller
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
// 14/09/2011 creation.
//----------------------------------------------------------------------------

#import "TransformWindowController.h"
#import "bXBoxTransform.h"
#import "CocoaStuff.h"
#import <MacMapSuite/bTrace.h>

#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/NSUIUtils.h>
#import <mox_intf/bEventLog.h>
#import <mox_intf/ext_utils.h>
#import <mox_intf/xmldesc_utils.h>
#import <std_ext/bXMapStdIntf.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation TransformPanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation TransformWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[TransformWindowController init]",true);
	self=[super init];
	if(self){
        _lc=0;
        _ls=0;
        _lcs=0;
	}
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[TransformWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
	[super awakeFromNib];

bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericExt*		ext;
char				name[256];
	
	for(long i=1;i<[_btn1 numberOfItems];i++){
		ext=gapp->xmapMgr()->find(NSPopupButtonMenuItemGetTag(_btn1,i));
		if(ext){
			GetName(ext,name);
			NSPopupButtonMenuItemSetTitle(_btn1,i,name);
		}
	}
	for(long i=1;i<[_btn2 numberOfItems];i++){
		ext=gapp->xmapMgr()->find(NSPopupButtonMenuItemGetTag(_btn2,i));
		if(ext){
			GetName(ext,name);
			NSPopupButtonMenuItemSetTitle(_btn2,i,name);
		}
	}
	for(long i=1;i<[_btn3 numberOfItems];i++){
		ext=gapp->xmapMgr()->find(NSPopupButtonMenuItemGetTag(_btn3,i));
		if(ext){
			GetName(ext,name);
			NSPopupButtonMenuItemSetTitle(_btn3,i,name);
		}
	}
	
	[[_btn1 menu] setAutoenablesItems:NO];
	[[_btn2 menu] setAutoenablesItems:NO];
	[[_btn3 menu] setAutoenablesItems:NO];

	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[TransformWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doClick:(id)sender{
NSControl*			c=(NSControl*)sender;
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericExt*		ext=gapp->xmapMgr()->find([c tag]);
	if((ext)&&(ext->test(NULL))){
		ext->edit(NULL);
	}
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateUI{
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericExt*		ext;
	
	for(long i=1;i<[_btn1 numberOfItems];i++){
		ext=gapp->xmapMgr()->find(NSPopupButtonMenuItemGetTag(_btn1,i));
		if(ext&&(ext->test(NULL))){
			NSPopupButtonMenuItemEnable(_btn1,i);
		}
		else{
			NSPopupButtonMenuItemDisable(_btn1,i);
		}
	}
	for(long i=1;i<[_btn2 numberOfItems];i++){
		ext=gapp->xmapMgr()->find(NSPopupButtonMenuItemGetTag(_btn2,i));
		if(ext&&(ext->test(NULL))){
			NSPopupButtonMenuItemEnable(_btn2,i);
		}
		else{
			NSPopupButtonMenuItemDisable(_btn2,i);
		}
	}
	for(long i=1;i<[_btn3 numberOfItems];i++){
		ext=gapp->xmapMgr()->find(NSPopupButtonMenuItemGetTag(_btn3,i));
		if(ext&&(ext->test(NULL))){
			NSPopupButtonMenuItemEnable(_btn3,i);
		}
		else{
			NSPopupButtonMenuItemDisable(_btn3,i);
		}
	}	
}

#pragma mark ---- Interface XMapBox ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)idle{
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
	if(_ls!=gapp->selMgr()->getState()){
		_ls=gapp->selMgr()->getState();
		[self updateUI];
	}
    else if(_lc!=gapp->cntMgr()->getState()){
        _lc=gapp->cntMgr()->getState();
        [self updateUI];
    }
    else if(_lcs!=gapp->layersMgr()->get_current()){
        _lcs=gapp->layersMgr()->get_current();
        [self updateUI];
    }
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

#pragma mark ---- CPP/Carbon Entry Point ----
// ---------------------------------------------------------------------------
// 
// ------------
void* initializeCocoa(void* gapp, 
					  void* ext) {
TransformWindowController	*controller;
NSAutoreleasePool	*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[TransformWindowController alloc] init];
    [controller setExt:(bStdNSXBox*)ext];
    [localPool release];
    return((void*)controller);
}

