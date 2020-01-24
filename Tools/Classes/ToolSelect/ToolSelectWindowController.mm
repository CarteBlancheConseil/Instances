//----------------------------------------------------------------------------
// File : ToolSelectWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Tool Select window controller
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
// 31/01/2017 creation.
//----------------------------------------------------------------------------

#import "ToolSelectWindowController.h"
#import "bToolSelect.h"
#import "CocoaStuff.h"
#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/NSUIUtils.h>
#import <std_ext/bXMapStdIntf.h>
#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation ToolSelectWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[ToolSelectWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[ToolSelectWindowController awakeFromNib]",true);
    [super awakeFromNib];
    
bToolSelect*    ext=(bToolSelect*)_ext;
   
    [_alo_chk setIntValue:ext->get_pt_all_obj()];
    [_alt_chk setIntValue:ext->get_pt_all_typ()];
    [_flo_chk setIntValue:ext->get_full_include()];
    [_act_chk setIntValue:ext->get_poly_angle()];
    [_ang_txt setDoubleValue:ext->get_angle()];
    [self updateUI];
}

#pragma mark ---- Gestion Interface ----
// ---------------------------------------------------------------------------
//
// -----------
-(void)updateUI{
    [_ang_txt setEnabled:[_act_chk intValue]];
}

#pragma mark ---- Gestion TableView ----
// ---------------------------------------------------------------------------
//
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
    return gapp->typesMgr()->count();
}

// ---------------------------------------------------------------------------
//
// -----------
-(id)           tableView:(NSTableView*)aTableView
objectValueForTableColumn:(NSTableColumn*)aTableColumn
                      row:(NSInteger)rowIndex{
NSString*           identifier=[aTableColumn identifier];
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
    
    if([identifier compare:@"check"]==NSOrderedSame){
bToolSelect*    ext=(bToolSelect*)_ext;
TypeRec         p;
        ext->types().get(rowIndex+1,&p);
        if(aTableView==_psl_viw){
            return [NSNumber numberWithInt:p.swp];
        }
        else{
            return [NSNumber numberWithInt:p.sbd];
        }
    }
    else if([identifier compare:@"name"]==NSOrderedSame){
char            value[256];
bGenericType*   tp=gapp->typesMgr()->get(rowIndex+1);
        tp->name(value);
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
NSNumber*       value=(NSNumber*)object;
bToolSelect*    ext=(bToolSelect*)_ext;
TypeRec         p;
        ext->types().get(rowIndex+1,&p);
        if(aTableView==_psl_viw){
            p.swp=[value boolValue];
        }
        else{
            p.sbd=[value boolValue];
        }
        ext->types().put(rowIndex+1,&p);
    }
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bToolSelect*    ext=(bToolSelect*)_ext;
    ext->set_pt_all_obj([_alo_chk intValue]);
    ext->set_pt_all_typ([_alt_chk intValue]);
    ext->set_full_include([_flo_chk intValue]);
    ext->set_poly_angle([_act_chk intValue]);
    ext->set_angle([_ang_txt doubleValue]);
    if(ext->get_mnu_cmd()==kSelectDragPoly){
        ext->set_use_angle([_act_chk intValue]);
    }
    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doUseAngleConstraint:(id)sender{
_bTrace_("[ToolSelectWindowController doUseAngleConstraint]",true);
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bToolSelect* ext,
					  long* code){
ToolSelectWindowController	*controller;
NSAutoreleasePool           *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];
    controller=[[ToolSelectWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
