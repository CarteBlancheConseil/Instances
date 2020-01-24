//----------------------------------------------------------------------------
// File : MMWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Draw/junctions XMapBox window controller
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
// 19/06/2008 creation.
//----------------------------------------------------------------------------

#import "MMWindowController.h"
#import "bXBoxDrawII.h" 
#import "CocoaStuff.h" 

#import <MacMapSuite/bTrace.h> 
#import <mox_intf/bGenericMacMapApp.h> 
#import <mox_intf/CGUtils.h>
#import <mox_intf/NSUIUtils.h>
#import <mox_intf/ext_utils.h>
#import <std_ext/bXMapStdIntf.h>

// ---------------------------------------------------------------------------
// 
// ------------
#define kWDWidthOpened	100
#define kWDWidthClosed	24

// ---------------------------------------------------------------------------
// 
// ------------
void		put_data					(void* _ext, 
										 UInt32 sgn, 
										 double val);
double		get_data					(void* _ext, 
										 UInt32 sgn);
void		put_topo					(void* _ext, 
										 int val);
int			get_topo					(void* _ext);
void		put_netclean				(void* _ext, 
										 int val);
int			get_netclean				(void* _ext);

// ---------------------------------------------------------------------------
// 
// ------------
@implementation NSPanelNoKey

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation MMWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[MMWindowController init]",true);
	self=[super init];
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[MMWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)awakeFromNib{
_bTrace_("[MMWindowController awakeFromNib]",true);
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericExt*		ext;
    
    ext=gapp->xmapMgr()->find('NtCl');
    if(!ext){
        [bNet setEnabled:NO];
    }
    ext=gapp->xmapMgr()->find('NtCO');
    if(!ext){
        [(NSButton*)[mAuto cellAtRow:0 column:0] setEnabled:NO];
        [bNetC setEnabled:NO];
    }
    ext=gapp->xmapMgr()->find('ChTo');
    if(!ext){
        [(NSButton*)[mAuto cellAtRow:1 column:0] setEnabled:NO];
        [bTopC setEnabled:NO];
    }

    ext=gapp->xmapMgr()->find('JEnd');
    if(!ext){
        [bEnd setEnabled:NO];
        [tEnd setEnabled:NO];
    }
    ext=gapp->xmapMgr()->find('JAng');
    if(!ext){
        [bVertex setEnabled:NO];
        [tVertex setEnabled:NO];
    }
    ext=gapp->xmapMgr()->find('JNea');
    if(!ext){
        [bNearest setEnabled:NO];
        [tNearest setEnabled:NO];
    }
    ext=gapp->xmapMgr()->find('JDir');
    if(!ext){
        [bDir setEnabled:NO];
        [tDir setEnabled:NO];
    }
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)joinEnds:(id)sender{
	SendCommandToApplication('JEnd');
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)joinVertex:(id)sender{
	SendCommandToApplication('JAng');
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)joinNearest:(id)sender{
	SendCommandToApplication('JNea');
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)joinDir:(id)sender{
	SendCommandToApplication('JDir');
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)setEndDist:(id)sender{
	if([[(NSTextField*)sender stringValue] length]>0){
		put_data(_ext,'JEnd',[(NSTextField*)sender doubleValue]);
		[[self window] selectNextKeyView:self];
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)setVertexDist:(id)sender{
	if([[(NSTextField*)sender stringValue] length]>0){
		put_data(_ext,'JAng',[(NSTextField*)sender doubleValue]);
		[[self window] selectNextKeyView:nil];
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)setNearestDist:(id)sender{
	if([[(NSTextField*)sender stringValue] length]>0){
		put_data(_ext,'JNea',[(NSTextField*)sender doubleValue]);
		[[self window] selectNextKeyView:nil];
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)setDirDist:(id)sender{
	if([[(NSTextField*)sender stringValue] length]>0){
		put_data(_ext,'JDir',[(NSTextField*)sender doubleValue]);
		[[self window] selectNextKeyView:nil];
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)cleanConfig:(id)sender{
	SendCommandToApplication('NtCO');
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)topoConfig:(id)sender{
	SendCommandToApplication('ChTo');
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doClean:(id)sender{
	SendCommandToApplication('NtCl');
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)windowPop:(id)sender{
NSRect	frm=[[self window] frame];
	if([(NSButton*)sender intValue]==0){
		frm.size.width=kWDWidthClosed;
	}
	else{
		frm.size.width=kWDWidthOpened;
	}
	[[self window] setFrame:frm display:YES];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)setAuto:(id)sender{
int row=[(NSMatrix*)sender selectedRow];
int	b;

	if(row==1){
		b=get_netclean(_ext);
		put_netclean(_ext,!b);
	}
	if(row==0){
		b=get_topo(_ext);
		put_topo(_ext,!b);
	}
}

#pragma mark ---- Intf Externe/Cocoa ----
// ---------------------------------------------------------------------------
// 
// ------------
-(void)setExt:(bStdNSXBox*)ext{
	[super setExt:ext];
	
double		d;
	d=get_data(_ext,'JEnd');
	[tEnd setDoubleValue:d];
	d=get_data(_ext,'JAng');
	[tVertex setDoubleValue:d];
	d=get_data(_ext,'JNea');
	[tNearest setDoubleValue:d];
	d=get_data(_ext,'JDir');
	[tDir setDoubleValue:d];
	
	if(get_netclean(_ext)==1){
		[mAuto selectCellAtRow:1 column:0];	
	}
	if(get_topo(_ext)==1){
		[mAuto selectCellAtRow:0 column:0];	
	}
	
NSRect	frm=[[self window] frame];
	
	if(frm.size.height!=196){
		frm.size.height=196;
		[[self window] setFrame:frm display:NO];
CGRect	cgr=NSRectToCGRect(frm);
		_ext->set_bounds(&cgr);
	}
	
	if(frm.size.width>24){
		[bPop setIntValue:1];
	}
	else{
		[bPop setIntValue:0];
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
MMWindowController	*controller;
NSAutoreleasePool	*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[MMWindowController alloc] init];
    [controller setExt:(bStdNSXBox*)ext];
    [localPool release];
    return((void*)controller);
}

#pragma mark ---- MacMapUtils ----
// ---------------------------------------------------------------------------
// 
// ------------
void put_data(void* _ext, UInt32 sgn, double val){
bGenericExt*		ext=(bGenericExt*)_ext;
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)ext->getapp();
join_prm			p;
	ext=gapp->xmapMgr()->find(sgn);
	if(ext){
		ext->process(kExtProcessCallGetData,&p);
		p.dmax=val;
		ext->process(kExtProcessCallSetData,&p);
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
double get_data(void* _ext, UInt32 sgn){
bGenericExt*		ext=(bGenericExt*)_ext;
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)ext->getapp();
join_prm			p;
	p.dmax=0;
	ext=gapp->xmapMgr()->find(sgn);
	if(ext){
		ext->process(kExtProcessCallGetData,&p);
	}
	return(p.dmax);
}

// ---------------------------------------------------------------------------
// 
// ------------
void put_topo(void* _ext, int val){
_bTrace_("put_topo",true);
bGenericExt*		ext=(bGenericExt*)_ext;
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)ext->getapp();
topocheck_prm		p;
	ext=gapp->xmapMgr()->find('ChTo');
	if(ext){
		ext->process(kExtProcessCallGetData,&p);
		p.activated=val;
		_tm_("topo set to "+val);
		ext->process(kExtProcessCallSetData,&p);
	}
	else{
		_te_("ext not found");
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
int get_topo(void* _ext){
_bTrace_("get_topo",true);
bGenericExt*		ext=(bGenericExt*)_ext;
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)ext->getapp();
topocheck_prm		p;
	p.activated=0;
	ext=gapp->xmapMgr()->find('ChTo');
	if(ext){
		ext->process(kExtProcessCallGetData,&p);
	}
	else{
_te_("ext not found");
	}
	return(p.activated);
}

// ---------------------------------------------------------------------------
// 
// ------------
void put_netclean(void* _ext, int val){
bGenericExt*		ext=(bGenericExt*)_ext;
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)ext->getapp();
netcleancfg_prm		p;
	p.nodes=NULL;
	p.edges=NULL;
	ext=gapp->xmapMgr()->find('NtCl');
	if(ext){
		ext->process(kExtProcessCallGetData,&p);
		p.autoclean=val;
		ext->process(kExtProcessCallSetData,&p);
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
int get_netclean(void* _ext){
bGenericExt*		ext=(bGenericExt*)_ext;
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)ext->getapp();
netcleancfg_prm		p;
	p.nodes=NULL;
	p.edges=NULL;
	p.autoclean=0;
	ext=gapp->xmapMgr()->find('NtCl');
	if(ext){
		ext->process(kExtProcessCallGetData,&p);
	}
	return(p.autoclean);
}
