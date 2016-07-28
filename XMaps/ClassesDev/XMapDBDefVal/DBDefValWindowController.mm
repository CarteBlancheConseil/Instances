//----------------------------------------------------------------------------
// File : DBDefValWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap default values window controller
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
// 11/02/2016 creation.
//----------------------------------------------------------------------------

#import "DBDefValWindowController.h"
#import "bXMapDBDefVal.h" 
#import "CocoaStuff.h" 

#import <mox_intf/NSUIUtils.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation DBDefValWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[DBDefValWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[DBDefValWindowController awakeFromNib]",true);
	NSPopupButtonRemoveAllItems(_typpop);
    NSPopupButtonPopulateWithTypes(_typpop,(bGenericMacMapApp*)_ext->getapp(),kBaseNoKind,1);
    _tp=((bGenericMacMapApp*)_ext->getapp())->typesMgr()->get(1);
    [_cntpop setHidden:YES];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[DBDefValWindowController close]",true);
	_tp=NULL;
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseType:(id)sender{
//_bTrace_("[DBDefValWindowController doChooseType]",true);
	_tp=((bGenericMacMapApp*)_ext->getapp())->typesMgr()->get([_typpop indexOfSelectedItem]+1);
    [self doChooseField:sender];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doChooseField:(id)sender{
//_bTrace_("[DBDefValWindowController doChooseField]",true);
long    fidx=kOBJ_Name_+[_fldpop indexOfSelectedItem];
char	def[512]="";
int		n=_tp->fields()->count_constraints(fidx);
    
    if(n>0){
int		idx=0;
        
        _tp->fields()->get_default_value(fidx,def);
        idx=_tp->fields()->get_constraint_index(fidx,def);
        NSPopupButtonRemoveAllItems(_cntpop);
        NSPopupButtonPopulateWithConstraints(_cntpop,_tp,fidx,idx);
        [_valfld setHidden:YES];
        [_cntpop setHidden:NO];
    }
    else{
        _tp->fields()->get_default_value(fidx,def);
        [_valfld setCharValue:def];
        [_valfld setHidden:NO];
        [_cntpop setHidden:YES];
    }
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doModify:(id)sender{
//_bTrace_("[DBDefValWindowController doModify]",true);
bXMapDBDefVal*  ext=(bXMapDBDefVal*)_ext;
char            value[256];
    
    if(NSTextFieldGetValue(_valfld,value,sizeof(value)-1)){
        ext->modify(_tp,[_fldpop indexOfSelectedItem]+kOBJ_Name_,[_cntpop indexOfSelectedItem]+1,value);
    }
    else{
        NSBeep();
    }
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapDBDefVal* ext,
					  long* code){
DBDefValWindowController	*controller;
NSAutoreleasePool			*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[DBDefValWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
