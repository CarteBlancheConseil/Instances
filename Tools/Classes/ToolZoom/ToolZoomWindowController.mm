//----------------------------------------------------------------------------
// File : ToolZoomWindowController.h
// Project : MacMap
// Purpose : Header file : Tool Zoom window controller
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
// 02/03/2017 creation.
//----------------------------------------------------------------------------

#import "ToolZoomWindowController.h"
#import "bToolZoom.h"
#import "CocoaStuff.h"
#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/NSUIUtils.h>
#import <std_ext/bXMapStdIntf.h>
#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
//
// ------------
static int countScales(bArray& scales){
int     count=0;
scale   scl;
    for(int i=1;i<=scales.count();i++){
        scales.get(i,&scl);
        if(!scl.deleted){
            count++;
        }
    }
    return count;
}

// ---------------------------------------------------------------------------
//
// ------------
static int getScaleIndex(bArray& scales, int nth){
int     count=0;
scale   scl;
    for(int i=1;i<=scales.count();i++){
        scales.get(i,&scl);
        if(!scl.deleted){
            count++;
            if(count==nth){
                return i;
            }
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 
// ------------
@implementation ToolZoomWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[ToolZoomWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[ToolZoomWindowController awakeFromNib]",true);
    [super awakeFromNib];
    [self updateUI];
}

#pragma mark ---- Gestion Interface ----
// ---------------------------------------------------------------------------
//
// -----------
-(void)updateUI{
    [_rmv_btn setEnabled:(([_scl_viw selectedRow]>=0)&&
                          ([_scl_viw numberOfRows]>1))];
}

#pragma mark ---- Gestion TableView ----
// ---------------------------------------------------------------------------
//
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
bToolZoom*    ext=(bToolZoom*)_ext;
    return countScales(ext->scales());
}

// ---------------------------------------------------------------------------
//
// -----------
-(id)           tableView:(NSTableView*)aTableView
objectValueForTableColumn:(NSTableColumn*)aTableColumn
                      row:(NSInteger)rowIndex{
NSString*   identifier=[aTableColumn identifier];
bToolZoom*  ext=(bToolZoom*)_ext;
scale		scl;
    
    ext->scales().get(getScaleIndex(ext->scales(),rowIndex+1),&scl);
    if([identifier compare:@"value"]==NSOrderedSame){
        return [NSString stringWithFormat:@"%.0f",scl.value];
    }
    else if([identifier compare:@"name"]==NSOrderedSame){
        if(strlen(scl.name)>0){
            return [NSString stringWithCString:scl.name encoding:NSMacOSRomanStringEncoding];
        }
        else{
            return @"_";
        }
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
NSString*   identifier=[aTableColumn identifier];
bToolZoom*  ext=(bToolZoom*)_ext;
scale		scl;
    
    ext->scales().get(getScaleIndex(ext->scales(),rowIndex+1),&scl);
    if([identifier compare:@"value"]==NSOrderedSame){
NSNumber*   value=(NSNumber*)object;
        if([value doubleValue]>0){
            scl.value=[value doubleValue];
            if((!scl.created)&&(!scl.deleted)){
                scl.modified=true;
            }
        }
    }
    else if([identifier compare:@"name"]==NSOrderedSame){
NSString*   value=(NSString*)object;
        if([value compare:@"_"]!=NSOrderedSame){
            [value getCString:scl.name maxLength:255 encoding:NSMacOSRomanStringEncoding];
            if((!scl.created)&&(!scl.deleted)){
                scl.modified=true;
            }
        }
    }
    ext->scales().put(getScaleIndex(ext->scales(),rowIndex+1),&scl);
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)tableViewSelectionDidChange:(NSNotification*)notification{
    [self updateUI];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doAddScale:(id)sender{
bToolZoom*  ext=(bToolZoom*)_ext;
scale		scl;
    
    ext->scales().get(ext->scales().count(),&scl);
    scl.idx=ext->scales().count()+1;
    scl.name[0]=0;
    scl.value*=2.0;
    scl.created=true;
    scl.modified=false;
    scl.deleted=false;
    ext->scales().add(&scl);
    
    [_scl_viw reloadData];
    [_scl_viw selectRowIndexes:[NSIndexSet indexSetWithIndex:[_scl_viw numberOfRows]-1]
          byExtendingSelection:NO];

    [_scl_viw scrollRowToVisible:[_scl_viw numberOfRows]-1];

    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doRemoveScale:(id)sender{
bToolZoom*  ext=(bToolZoom*)_ext;
int         idx=getScaleIndex(ext->scales(),[_scl_viw selectedRow]+1);
scale		scl;
    
    ext->scales().get(idx,&scl);
    scl.modified=false;
    scl.created=false;
    scl.deleted=true;
    ext->scales().put(idx,&scl);
   
    [_scl_viw reloadData];
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bToolZoom* ext,
					  long* code){
ToolZoomWindowController    *controller;
NSAutoreleasePool           *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];
    controller=[[ToolZoomWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
