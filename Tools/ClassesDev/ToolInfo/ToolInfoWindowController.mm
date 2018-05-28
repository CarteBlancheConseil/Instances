//----------------------------------------------------------------------------
// File : ToolInfoWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Tool Info window controller
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
// 24/03/2017 creation.
//----------------------------------------------------------------------------

#import "ToolInfoWindowController.h"
#import "bToolInfo.h"
#import "CocoaStuff.h"
#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/NSUIUtils.h>
#import <std_ext/bXMapStdIntf.h>
#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation ToolInfoWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[ToolInfoWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[ToolInfoWindowController awakeFromNib]",true);
    [super awakeFromNib];
    
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bToolInfo*          ext=(bToolInfo*)_ext;
   
    [_sht_chk setIntValue:ext->get_show_type()];
    
    NSPopupButtonRemoveAllItems(_typ_pop);
    NSPopupButtonPopulateWithTypes(_typ_pop,gapp,kBaseNoKind,1);
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
 
    if(!tp){
        return nil;
    }

NSString*   identifier=[aTableColumn identifier];
bToolInfo*  ext=(bToolInfo*)_ext;
   
    if([identifier compare:@"check"]==NSOrderedSame){
int     fid=tp->fields()->get_id(rowIndex+kOBJ_Name_);
int     idx=ext->get_index([_typ_pop indexOfSelectedItem]+1,fid);
        return [NSNumber numberWithInt:idx];
    }
    else if([identifier compare:@"name"]==NSOrderedSame){
char    value[256];
        tp->fields()->get_name(rowIndex+kOBJ_Name_,value);
        return [NSString stringWithCString:value encoding:NSMacOSRomanStringEncoding];
    }
    return nil;
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)	tableView:(NSTableView*)aTableView
   setObjectValue:(id)object
   forTableColumn:(NSTableColumn*)aTableColumn
              row:(NSInteger)rowIndex{
NSString*           identifier=[aTableColumn identifier];
    if([identifier compare:@"check"]==NSOrderedSame){
bToolInfo*          ext=(bToolInfo*)_ext;
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*       tp=gapp->typesMgr()->get([_typ_pop indexOfSelectedItem]+1);
bArray*             a;
fld                 f;
 
        f.fid=tp->fields()->get_id(rowIndex+kOBJ_Name_);
int     idx=ext->get_index([_typ_pop indexOfSelectedItem]+1,f.fid);
        ext->fields().get([_typ_pop indexOfSelectedItem]+1,&a);
        if(idx){
            a->rmv(idx);
        }
        else{
            a->add(&f);
        }
    }
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bToolInfo*    ext=(bToolInfo*)_ext;
    ext->set_show_type([_sht_chk intValue]);
    [super validDialog:sender];
}
// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doChooseType:(id)sender{
_bTrace_("[bToolInfo doChooseType]",true);
    [_fld_viw reloadData];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bToolInfo* ext,
					  long* code){
ToolInfoWindowController	*controller;
NSAutoreleasePool           *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];
    controller=[[ToolInfoWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
