//----------------------------------------------------------------------------
// File : StringProcessingWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap string processing window controller
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

#import "StringProcessingWindowController.h"
#import "bXMapStringProcessing.h"
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
@implementation StringProcessingWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[StringProcessingWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[StringProcessingWindowController awakeFromNib]",true);
bXMapStringProcessing*  ext=(bXMapStringProcessing*)_ext;
    NSPopupButtonRemoveAllItems(_filpop);
    NSPopupButtonPopulateWithFields(_filpop,ext->get_type(),kOBJ_Name_,1);
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[StringProcessingWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bXMapStringProcessing*  ext=(bXMapStringProcessing*)_ext;
strprocess_prm          prm;

    ext->get_params(&prm);
    NSTextFieldGetValue(_septxt,prm.sep,sizeof(prm.sep)-1);
    prm.cas=[_caspop indexOfSelectedItem]+1;
    NSTextFieldGetValue(_rpftxt,prm.srch,sizeof(prm.srch)-1);
    NSTextFieldGetValue(_rpttxt,prm.repl,sizeof(prm.repl)-1);
    NSTextFieldGetValue(_fmttxt,prm.fmt,sizeof(prm.fmt)-1);
    prm.target=[_filpop indexOfSelectedItem]+kOBJ_Name_;
    ext->set_params(prm);
    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doAdd:(id)sender{
_bTrace_("[StringProcessingWindowController doAdd]",true);
bXMapStringProcessing*  ext=(bXMapStringProcessing*)_ext;
strprocess_prm          prm;
int                     idx=[_flftbl selectedRow];

    if(idx<0){
        return;
    }
    idx+=kOBJ_Name_;
    ext->get_params(&prm);
    prm.arr->add(&idx);
    [_flttbl reloadData];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doRemove:(id)sender{
bXMapStringProcessing*  ext=(bXMapStringProcessing*)_ext;
strprocess_prm          prm;
int                     idx=[_flttbl selectedRow];
    
    if(idx<0){
        return;
    }
    idx+=1;
    ext->get_params(&prm);
    prm.arr->rmv(idx);
    [_flttbl reloadData];
}

#pragma mark ---- Gestion TableView ----
// -------------------------------------------------------------------------;--
//
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
bXMapStringProcessing*  ext=(bXMapStringProcessing*)_ext;
strprocess_prm          prm;
    
    ext->get_params(&prm);
    if(ext->get_type()==NULL){
        return 0;
    }
    if(aTableView==_flftbl){
        return(ext->get_type()->fields()->count()-kOBJ_Name_+1);
    }
    else{
        return(prm.arr->count());
    }
    return 0;
}

// ---------------------------------------------------------------------------
//
// -----------
-(id)	tableView:(NSTableView*)aTableView
objectValueForTableColumn:(NSTableColumn*)aTableColumn
            row:(NSInteger)rowIndex{
bXMapStringProcessing*  ext=(bXMapStringProcessing*)_ext;
strprocess_prm          prm;
NSString*               nsstr;
char                    str[256];

    ext->get_params(&prm);
    if(aTableView==_flftbl){
        ext->get_type()->fields()->get_name(rowIndex+kOBJ_Name_,str);
        nsstr=[NSString stringWithCString:str encoding:NSMacOSRomanStringEncoding];
    }
    else{
int     idx;
        if(prm.arr->get(rowIndex+1,&idx)){
            ext->get_type()->fields()->get_name(idx,str);
        }
        else{
            strcpy(str,"????");
        }
        nsstr=[NSString stringWithCString:str encoding:NSMacOSRomanStringEncoding];
    }
    return nsstr;
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
-(void)updateUI{
    [_addbtn setEnabled:([_flftbl selectedRow]>=0)];
    [_rmvbtn setEnabled:([_flttbl selectedRow]>=0)];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapStringProcessing* ext,
					  long* code){
StringProcessingWindowController	*controller;
NSAutoreleasePool               *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[StringProcessingWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
