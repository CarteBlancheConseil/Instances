//----------------------------------------------------------------------------
// File : DataImportWindowController.mm
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
// 19/02/2016 creation.
//----------------------------------------------------------------------------

#import "DataImportWindowController.h"
#import "bXMapDataImport.h"
#import "CocoaStuff.h"

#import <mox_intf/NSUIUtils.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation DataImportWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[DataImportWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[DataImportWindowController awakeFromNib]",true);
bXMapDataImport*    ext=(bXMapDataImport*)_ext;
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
    
    NSPopupButtonRemoveAllItems(_typpop);
    NSPopupButtonPopulateWithTypes(_typpop,gapp,kBaseNoKind,ext->get_type_index());

bGenericType*	tp=gapp->typesMgr()->get(ext->get_type_index());
    NSPopupButtonRemoveItemsFrom(_fldpop,1);
    NSPopupButtonPopulateWithFields(_fldpop,tp,kOBJ_Vertices_,1);
    if(ext->table()->signature()!=kTableMMText){
        NSPopupButtonMenuItemDisable(_fldpop,2);
    }
    
    [_onlbtn setIntValue:ext->get_unique()];
    [_mskbtn setIntValue:ext->get_use_masked()];
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[DataImportWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bXMapDataImport*  ext=(bXMapDataImport*)_ext;
    
    ext->set_unique([_onlbtn intValue]);
    ext->set_use_masked([_mskbtn intValue]);
    
    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doChooseType:(id)sender{
_bTrace_("[DataImportWindowController doChooseType]",true);
bXMapDataImport*    ext=(bXMapDataImport*)_ext;
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
    ext->set_type_index([_typpop indexOfSelectedItem]+1);
bGenericType*       tp=gapp->typesMgr()->get(ext->get_type_index());
    NSPopupButtonRemoveItemsFrom(_fldpop,1);
    NSPopupButtonPopulateWithFields(_fldpop,tp,kOBJ_Vertices_,1);
    if(ext->table()->signature()!=kTableMMText){
        NSPopupButtonMenuItemDisable(_fldpop,2);
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doChooseAction:(id)sender{
_bTrace_("[DataImportWindowController doChooseAction]",true);
bXMapDataImport*    ext=(bXMapDataImport*)_ext;
datajoin_act        action;
    ext->actions().get([_fcltbl selectedRow]+1,&action);
    action.k=[_actpop indexOfSelectedItem]+1;
    ext->actions().put([_fcltbl selectedRow]+1,&action);
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doChooseField:(id)sender{
_bTrace_("[DataImportWindowController doChooseField]",true);
bXMapDataImport*    ext=(bXMapDataImport*)_ext;
datajoin_act        action;
    ext->actions().get([_fcltbl selectedRow]+1,&action);
    action.fidx=[_fldpop indexOfSelectedItem]-2+kOBJ_Vertices_;
    ext->actions().put([_fcltbl selectedRow]+1,&action);
    [self updateUI];
}

#pragma mark ---- Gestion TableView ----
// -------------------------------------------------------------------------;--
//
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
bXMapDataImport*  ext=(bXMapDataImport*)_ext;
    return ext->table()->CountFields();
}

// ---------------------------------------------------------------------------
//
// -----------
-(id)	tableView:(NSTableView*)aTableView
objectValueForTableColumn:(NSTableColumn*)aTableColumn
            row:(NSInteger)rowIndex{
bXMapDataImport*  ext=(bXMapDataImport*)_ext;
char                    str[256];
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
-(BOOL)testIgnore{
    if([_fcltbl selectedRow]<0){
        return NO;
    }
    return(true);
}

// ---------------------------------------------------------------------------
//
// -----------
-(BOOL)testSearch{
    if([_fcltbl selectedRow]<0){
        return NO;
    }
bXMapDataImport*    ext=(bXMapDataImport*)_ext;
long                f=[_fcltbl selectedRow]+1;
datajoin_act        action;
bool                srch=false;
int                 i;
    for(i=1;i<=ext->actions().count();i++){
        ext->actions().get(i,&action);
        if(action.k==kDataJoinActionSearch){
            srch=true;
            break;
        }
    }
    if(!srch){
        ext->table()->FieldSign(f,&i);
        if( (i!=_char)	&&
           (i!=_int)	&&
           (i!=_bool)	&&
           (i!=_double)&&
           (i!=_date)	&&
           (i!=_time)	){
            return(false);
        }
    }
    return((srch&&(f==i))||(!srch));
}

// ---------------------------------------------------------------------------
//
// -----------
-(BOOL)testFill{
    if([_fcltbl selectedRow]<0){
        return NO;
    }
    return YES;
}

// ---------------------------------------------------------------------------
//
// -----------
-(BOOL)testCreate{
    if([_fcltbl selectedRow]<0){
        return NO;
    }
bXMapDataImport*    ext=(bXMapDataImport*)_ext;
long                f=[_fcltbl selectedRow]+1;
int                 k;
    ext->table()->FieldSign(f,&k);
    if( (k!=_char)	&&
        (k!=_int)	&&
        (k!=_bool)	&&
        (k!=_double)&&
        (k!=_date)	&&
        (k!=_time)	){
        return(false);
    }
    
datajoin_act	action;
char			name[256];
    ext->actions().get(f,&action);
    ext->table()->FieldName(f,name);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*       tp=gapp->typesMgr()->get(ext->get_type_index());
    return(tp->fields()->get_index(name)==0);
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
bXMapDataImport*    ext=(bXMapDataImport*)_ext;
datajoin_act        action;
    
    if(!ext->actions().get([_fcltbl selectedRow]+1,&action)){
    }
    
    [_actpop setEnabled:YES];
    [_actpop selectItemAtIndex:action.k-1];
    if(![self testIgnore]){
        NSPopupButtonMenuItemDisable(_actpop,kDataJoinActionIgnore-1);
    }
    else{
        NSPopupButtonMenuItemEnable(_actpop,kDataJoinActionIgnore-1);
    }
    if(![self testSearch]){
        NSPopupButtonMenuItemDisable(_actpop,kDataJoinActionSearch-1);
    }
    else{
        NSPopupButtonMenuItemEnable(_actpop,kDataJoinActionSearch-1);
    }
    if(![self testFill]){
        NSPopupButtonMenuItemDisable(_actpop,kDataJoinActionFill-1);
    }
    else{
        NSPopupButtonMenuItemEnable(_actpop,kDataJoinActionFill-1);
    }
    if(![self testCreate]){
        NSPopupButtonMenuItemDisable(_actpop,kDataJoinActionCreate-1);
    }
    else{
        NSPopupButtonMenuItemEnable(_actpop,kDataJoinActionCreate-1);
    }
    
    [_fldpop setEnabled:(action.k!=kDataJoinActionIgnore)&&
     (action.k!=kDataJoinActionCreate)];
    
    [_fldpop selectItemAtIndex: action.fidx<kOBJ_Vertices_?
     0:
     action.fidx-kOBJ_Vertices_+2];

}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapDataImport* ext,
					  long* code){
DataImportWindowController  *controller;
NSAutoreleasePool           *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[DataImportWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
