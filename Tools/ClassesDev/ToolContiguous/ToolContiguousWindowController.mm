//----------------------------------------------------------------------------
// File : ToolContiguousWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Tool Contiguous window controller
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2017 Carte Blanche Conseil.
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
// 03/03/2017 creation.
//----------------------------------------------------------------------------

#import "ToolContiguousWindowController.h"
#import "bToolContiguous.h"
#import "CocoaStuff.h"
#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/NSUIUtils.h>
#import <mox_intf/ext_utils.h>
#import <std_ext/bXMapStdIntf.h>
#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation ToolContiguousWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[ToolContiguousWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[ToolContiguousWindowController awakeFromNib]",true);
    [super awakeFromNib];
    
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*       tp=NthTypeOfKind(gapp,1,kBaseKindPolyline);
long                i=tp?tp->index():0;
    
    NSPopupButtonRemoveAllItems(_typ_pop);
    NSPopupButtonPopulateWithTypes(_typ_pop,gapp,kBaseKindPolyline,i);
    
bToolContiguous*    ext=(bToolContiguous*)_ext;
    tp=gapp->typesMgr()->get([_typ_pop indexOfSelectedItem]+1);
    if(tp){
int     x;
        if(ext->types().get(tp->index(),&x)){
            x=tp->fields()->get_index(x);
            if(x>0){
                [_fld_viw selectRowIndexes:[NSIndexSet indexSetWithIndex:x-kOBJ_Name_]
                      byExtendingSelection:NO];
                [_fld_viw scrollRowToVisible:x-kOBJ_Name_];
            }
        }
    }
}

#pragma mark ---- Gestion TableView ----
// ---------------------------------------------------------------------------
//
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*       tp=gapp->typesMgr()->get([_typ_pop indexOfSelectedItem]+1);
    
    if(tp){
        return tp->fields()->count()-kOBJ_Vertices_;
    }
    return 0;
}

// ---------------------------------------------------------------------------
//
// -----------
-(id)           tableView:(NSTableView*)aTableView
objectValueForTableColumn:(NSTableColumn*)aTableColumn
                      row:(NSInteger)rowIndex{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*       tp=gapp->typesMgr()->get([_typ_pop indexOfSelectedItem]+1);
    
    if(tp){
char    value[256];
        tp->fields()->get_name(rowIndex+kOBJ_Name_,value);
        return [NSString stringWithCString:value encoding:NSMacOSRomanStringEncoding];
    }
    return nil;
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)tableViewSelectionDidChange:(NSNotification*)notification{
_bTrace_("[ToolContiguousWindowController tableViewSelectionDidChange]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*       tp=gapp->typesMgr()->get([_typ_pop indexOfSelectedItem]+1);
bToolContiguous*    ext=(bToolContiguous*)_ext;
    if(tp){
int     x=tp->fields()->get_id([_fld_viw selectedRow]+kOBJ_Name_);
        ext->types().put(tp->index(),&x);
    }
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doChooseType:(id)sender{
_bTrace_("[ToolContiguousWindowController doChooseType]",true);
    [_fld_viw reloadData];
    
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*       tp=gapp->typesMgr()->get([_typ_pop indexOfSelectedItem]+1);
bToolContiguous*    ext=(bToolContiguous*)_ext;
    if(tp){
int     x;
        if(ext->types().get(tp->index(),&x)){
            x=tp->fields()->get_index(x);
            if(x>0){
                [_fld_viw selectRowIndexes:[NSIndexSet indexSetWithIndex:x-kOBJ_Name_]
                      byExtendingSelection:NO];
                [_fld_viw scrollRowToVisible:x-kOBJ_Name_];
            }
        }
    }
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bToolContiguous* ext,
					  long* code){
ToolContiguousWindowController	*controller;
NSAutoreleasePool           *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];
    controller=[[ToolContiguousWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
