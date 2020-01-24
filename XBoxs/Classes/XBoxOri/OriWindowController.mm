//----------------------------------------------------------------------------
// File : OriWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Orientation XMapBox window controller
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

#import "OriWindowController.h"
#import "bXBoxOri.h"
#import "CocoaStuff.h"
#import <MacMapSuite/bTrace.h>

#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/bEventLog.h>
#import <mox_intf/ext_utils.h>
#import <mox_intf/xmldesc_utils.h>
#import <std_ext/bXMapStdIntf.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation OriPanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation OriWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[OriWindowController init]",true);
	self=[super init];
	if(self){
		_lc=0;
	}
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[OriWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[OriWindowController awakeFromNib]",true);
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericExt*		ext;
char				name[256];
NSString*			nstr;
	ext=gapp->xmapMgr()->find([_btn1 tag]);
	if(ext){
		GetName(ext,name);
		nstr=[NSString stringWithCString:name encoding:NSMacOSRomanStringEncoding];
		[_btn1 setToolTip:nstr];
	}
	ext=gapp->xmapMgr()->find([_btn2 tag]);
	if(ext){
		GetName(ext,name);
		nstr=[NSString stringWithCString:name encoding:NSMacOSRomanStringEncoding];
		[_btn2 setToolTip:nstr];
	}
	ext=gapp->xmapMgr()->find([_btn3 tag]);
	if(ext){
		GetName(ext,name);
		nstr=[NSString stringWithCString:name encoding:NSMacOSRomanStringEncoding];
		[_btn3 setToolTip:nstr];
	}
	
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[OriWindowController close]",true);
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
	ext=gapp->xmapMgr()->find([_btn1 tag]);
	[_btn1 setEnabled:(ext&&(ext->test(NULL)))];
	ext=gapp->xmapMgr()->find([_btn2 tag]);
	[_btn2 setEnabled:(ext&&(ext->test(NULL)))];
	ext=gapp->xmapMgr()->find([_btn3 tag]);
	[_btn3 setEnabled:(ext&&(ext->test(NULL)))];
}

#pragma mark ---- Interface XMapBox ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)idle{
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
	if(_lc!=gapp->selMgr()->getState()){
		_lc=gapp->selMgr()->getState();
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
OriWindowController	*controller;
NSAutoreleasePool	*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[OriWindowController alloc] init];
    [controller setExt:(bStdNSXBox*)ext];
    [localPool release];
    return((void*)controller);
}

