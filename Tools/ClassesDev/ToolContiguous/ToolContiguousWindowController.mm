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
-(id)initWithExt:(bStdExt *)ext{
_bTrace_("[ToolContiguousWindowController init]",true);
    self=[super initWithExt:ext];
    _arr=NULL;
    if(self){
        _arr=new bArray(sizeof(int));
    }
_tm_((void*)self);
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[ToolContiguousWindowController dealloc]",true);
_tm_((void*)self);
    if(_arr){
        delete _arr;
        _arr=NULL;
    }
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[ToolContiguousWindowController awakeFromNib]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*       tp=NthTypeOfKind(gapp,1,kBaseKindPolyline);
long                i=tp?tp->index():0;
    
    NSPopupButtonRemoveAllItems(_typ_pop);
    NSPopupButtonPopulateWithTypes(_typ_pop,gapp,kBaseKindPolyline,i);
    
bToolContiguous*    ext=(bToolContiguous*)_ext;
    if(!_arr){
        _arr=new bArray(sizeof(int));
    }
bool    b=(*_arr)+ext->types();
_tm_("ext->types().count()="+ext->types().count());
_tm_("_arr->count()="+_arr->count());
    tp=gapp->typesMgr()->get([_typ_pop indexOfSelectedItem]+1);
    if(tp){
int     x;
        if(_arr->get(tp->index(),&x)){
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
-(void)close{
_bTrace_("[ToolContiguousWindowController close]",true);
	[super close];
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
_bTrace_("[ToolContiguousWindowController doChooseType]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*       tp=gapp->typesMgr()->get([_typ_pop indexOfSelectedItem]+1);
    if(tp){
int     x=tp->fields()->get_id([_fld_viw selectedRow]+kOBJ_Name_);
_tm_("x="+x);
        _arr->put(tp->index(),&x);
    }
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bToolContiguous*    ext=(bToolContiguous*)_ext;

//bToolContiguous*    ext=(bToolContiguous*)_ext;
//        ext->set_pt_all_obj([_alo_chk intValue]);
//        ext->set_pt_all_typ([_alt_chk intValue]);
//        ext->set_full_include([_flo_chk intValue]);
//        ext->set_poly_angle([_act_chk intValue]);
//        ext->set_angle([_ang_txt doubleValue]);
//        if(ext->get_mnu_cmd()==kContiguousDragPoly){
//            ext->set_use_angle([_act_chk intValue]);
//        }
    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doChooseType:(id)sender{
_bTrace_("[ToolContiguousWindowController doChooseType]",true);
    [_fld_viw reloadData];

_tm_("pop index="+([_typ_pop indexOfSelectedItem]+1));
    
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*       tp=gapp->typesMgr()->get([_typ_pop indexOfSelectedItem]+1);
    if(tp){
_tm_("tp->index()="+tp->index());

int     x;
        if(_arr->get(tp->index(),&x)){
_tm_("x="+x);
            x=tp->fields()->get_index(x);
_tm_("x="+x);
            if(x>0){
                [_fld_viw selectRowIndexes:[NSIndexSet indexSetWithIndex:x-kOBJ_Name_]
                      byExtendingSelection:NO];
                [_fld_viw scrollRowToVisible:x-kOBJ_Name_];
            }
        }
        else{
_te_("arr->get failed, arr->count()="+_arr->count());

        }
    }
    else{
_te_("tp=NULL");

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
