//----------------------------------------------------------------------------
// File : DataJoinWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap data fill window controller
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
// 03/03/2016 creation.
//----------------------------------------------------------------------------

#import "DataJoinWindowController.h"
#import "bXMapDataJoin.h"
#import "CocoaStuff.h"

#import <mox_intf/NSUIUtils.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation DataJoinWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[DataJoinWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[DataJoinWindowController awakeFromNib]",true);
bXMapDataJoin*    ext=(bXMapDataJoin*)_ext;
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
    
    NSPopupButtonRemoveAllItems(_typpop);
    NSPopupButtonPopulateWithTypes(_typpop,gapp,kBaseNoKind,ext->get_type_index());

bGenericType*	tp=gapp->typesMgr()->get(ext->get_type_index());
    NSPopupButtonRemoveAllItems(_fldpop);
    NSPopupButtonPopulateWithFields(_fldpop,tp,kOBJ_Dir_+1,1);
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[DataJoinWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doChooseType:(id)sender{
bXMapDataJoin*      ext=(bXMapDataJoin*)_ext;
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
    ext->set_type_index([_typpop indexOfSelectedItem]+1);
bGenericType*       tp=gapp->typesMgr()->get(ext->get_type_index());
    NSPopupButtonRemoveAllItems(_fldpop);
    NSPopupButtonPopulateWithFields(_fldpop,tp,kOBJ_Dir_+1,1);
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doChooseAction:(id)sender{
bXMapDataJoin*  ext=(bXMapDataJoin*)_ext;
datajoin_act    action;
    ext->actions().get([_fcltbl selectedRow]+1,&action);
    action.k=([_actpop indexOfSelectedItem]==0)?kDataJoinActionSearch:kDataJoinActionCreate;
    ext->actions().put([_fcltbl selectedRow]+1,&action);
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doChooseField:(id)sender{
bXMapDataJoin*  ext=(bXMapDataJoin*)_ext;
datajoin_act    action;
    ext->actions().get([_fcltbl selectedRow]+1,&action);
    action.fidx=[_fldpop indexOfSelectedItem]+kOBJ_Dir_+1;
    ext->actions().put([_fcltbl selectedRow]+1,&action);
    [self updateUI];
}

#pragma mark ---- Gestion TableView ----
// -------------------------------------------------------------------------;--
//
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
bXMapDataJoin*  ext=(bXMapDataJoin*)_ext;
    return ext->table()->CountFields();
}

// ---------------------------------------------------------------------------
//
// -----------
-(id)	tableView:(NSTableView*)aTableView
objectValueForTableColumn:(NSTableColumn*)aTableColumn
            row:(NSInteger)rowIndex{
bXMapDataJoin*  ext=(bXMapDataJoin*)_ext;
char            str[256];
    ext->table()->FieldName(rowIndex+1,str);
    return [NSString stringWithCString:str encoding:NSMacOSRomanStringEncoding];
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)tableViewSelectionDidChange:(NSNotification*)notification{
    [self updateUI];
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
//
// -----------
-(BOOL)testSearch{
    if([_fcltbl selectedRow]<0){
        return NO;
    }
bXMapDataJoin*  ext=(bXMapDataJoin*)_ext;
long            f=[_fcltbl selectedRow]+1;
datajoin_act    action;
bool            srch=false;
long            i;
    for(i=1;i<=ext->actions().count();i++){
        ext->actions().get(i,&action);
        if(action.k==kDataJoinActionSearch){
            srch=true;
            break;
        }
    }
    return((srch&&(f==i))||(!srch));
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)updateUI{
    if([_fcltbl selectedRow]<0){
        [_actpop setEnabled:NO];
        [_fldpop setEnabled:NO];
        return;
    }
bXMapDataJoin*  ext=(bXMapDataJoin*)_ext;
datajoin_act    action;
    
    if(!ext->actions().get([_fcltbl selectedRow]+1,&action)){
    }

    [_actpop setEnabled:[self testSearch]];
    [_actpop selectItemAtIndex:(action.k==kDataJoinActionSearch)?0:1];
    
    if(action.k==kDataJoinActionSearch){
        [_fldlbl setHidden:NO];
        [_fldpop setHidden:NO];
        [_fldpop setEnabled:YES];
        [_fldpop selectItemAtIndex: action.fidx<kOBJ_Dir_+1?
                                    0:
                                    action.fidx-kOBJ_Dir_-1];
    }
    else{
        [_fldlbl setHidden:YES];
        [_fldpop setHidden:YES];
        [_fldpop setEnabled:NO];
        [_fldpop selectItemAtIndex:0];
    }
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapDataJoin* ext,
					  long* code){
DataJoinWindowController    *controller;
NSAutoreleasePool           *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[DataJoinWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
