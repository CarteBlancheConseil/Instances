//----------------------------------------------------------------------------
// File : NetCleanWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap clone detector window controller
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2016 Carte Blanche Conseil.
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
// 09/02/2016 creation.
//----------------------------------------------------------------------------

#import "NetCleanWindowController.h"
#import "bXMapNetClean.h" 
#import "CocoaStuff.h" 
#import <MacMapSuite/bTrace.h> 
#import <mox_intf/bGenericMacMapApp.h> 
#import <mox_intf/Carb_Utils.h> 
#import <mox_intf/bEventLog.h>
#import <mox_intf/ext_utils.h>
#import <mox_intf/xmldesc_utils.h> 
#import <mox_intf/NSUIUtils.h> 
#import <mox_intf/mm_messages.h>
#import <mox_intf/mm_errors.h>
#import <mox_intf/bStdAlert.h>
#import <std_ext/bXMapStdIntf.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation NetCleanWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[NetCleanWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[NetCleanWindowController awakeFromNib]",true);
bXMapNetClean*  ext=(bXMapNetClean*)_ext;
netcleanact_prm prm;

    ext->get_prm(&prm);
    if(!prm.create_nodes){
        prm.cut_edges=false;
    }
    [_crnchk setIntValue:prm.create_nodes];
    [_ctechk setIntValue:prm.cut_edges];
    [_jonchk setIntValue:prm.join_on_nodes||prm.join_on_edges];
    [_jntpop selectItemAtIndex:prm.join_on_nodes?0:1];
    [_cknchk setIntValue:prm.check_nodes];
    [_ckechk setIntValue:prm.check_edges];

    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[NetCleanWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bXMapNetClean*  ext=(bXMapNetClean*)_ext;
netcleanact_prm prm;
    
    prm.create_nodes=[_crnchk intValue];
    prm.cut_edges=[_ctechk intValue];
    if(!prm.create_nodes){
        prm.cut_edges=false;
    }
    if([_jonchk intValue]){
        prm.join_on_nodes=[_jntpop indexOfSelectedItem]==0;
        prm.join_on_edges=[_jntpop indexOfSelectedItem]==1;
    }
    else{
        prm.join_on_nodes=false;
        prm.join_on_edges=false;
    }
    prm.check_nodes=[_cknchk intValue];
    prm.check_edges=[_ckechk intValue];
 
    ext->set_prm(prm);
    
    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doUpdate:(id)sender{
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)updateUI{
    [_ctechk setEnabled:[_crnchk intValue]];
    [_jntpop setEnabled:[_jonchk intValue]];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapNetClean* ext,
					  long* code){
NetCleanWindowController    *controller;
NSAutoreleasePool           *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[NetCleanWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
