//----------------------------------------------------------------------------
// File : ViewMgrWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap views management window controller
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
// 19/02/2016 creation.
//----------------------------------------------------------------------------

#import "ViewMgrWindowController.h"
#import "bXMapViewMgr.h"
#import "CocoaStuff.h"
#import <mox_intf/bEventLog.h>
#import <mox_intf/NSUIUtils.h>
#import <std_ext/bXMapStdIntf.h>
#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation ViewMgrWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[ViewMgrWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[ViewMgrWindowController awakeFromNib]",true);
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[ViewMgrWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doAdd:(id)sender{
_bTrace_("[ViewMgrWindowController doAdd]",true);
    if(((bXMapViewMgr*)_ext)->add()!=noErr){
        NSBeep();
    }
    [_viwtbl reloadData];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doRemove:(id)sender{
_bTrace_("[ViewMgrWindowController doRemove]",true);
    if(((bXMapViewMgr*)_ext)->remove([_viwtbl selectedRow]+1)!=noErr){
        NSBeep();
    }
    [_viwtbl reloadData];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doDuplicate:(id)sender{
_bTrace_("[ViewMgrWindowController doDuplicate]",true);
    if(((bXMapViewMgr*)_ext)->remove([_viwtbl selectedRow]+1)!=noErr){
        NSBeep();
    }
    [_viwtbl reloadData];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doRename:(id)sender{
_bTrace_("[ViewMgrWindowController doRename]",true);
    [_viwtbl editColumn:0 row:[_viwtbl selectedRow] withEvent:nil select:NO];
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateUI{
//_bTrace_("[ViewMgrWindowController updateUI]",true);
    [_rmvbtn setEnabled:[_viwtbl selectedRow]>=0    &&
                        ((bGenericMacMapApp*)_ext->getapp())->viewMgr()->get_current()!=[_viwtbl selectedRow]+1];
    [_dupbtn setEnabled:[_viwtbl selectedRow]>=0];
    [_renbtn setEnabled:[_viwtbl selectedRow]>=0];
}


#pragma mark ---- Gestion TableView ----
// ---------------------------------------------------------------------------
// 
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
    return(((bGenericMacMapApp*)_ext->getapp())->viewMgr()->count());
}

// ---------------------------------------------------------------------------
// 
// -----------
-(id)	tableView:(NSTableView*)aTableView 
		objectValueForTableColumn:(NSTableColumn*)aTableColumn 
		row:(NSInteger)rowIndex{
char    str[256];
    ((bGenericMacMapApp*)_ext->getapp())->viewMgr()->get_name(rowIndex+1,str);
	return [NSString stringWithCString:str encoding:NSMacOSRomanStringEncoding];
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)	tableView:(NSTableView *)aTableView
   setObjectValue:(id)anObject
   forTableColumn:(NSTableColumn*)aTableColumn
              row:(NSInteger)rowIndex{
NSString*	nsstr=(NSString*)anObject;
char        str[256];
    [nsstr getCString:str maxLength:sizeof(str)-1 encoding:NSMacOSRomanStringEncoding];
    if(((bXMapViewMgr*)_ext)->rename(rowIndex+1,str)!=noErr){
        NSBeep();
    }
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)tableViewSelectionDidChange:(NSNotification*)notification{
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapViewMgr* ext,
					  long* code){
ViewMgrWindowController	*controller;
NSAutoreleasePool		*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[ViewMgrWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
