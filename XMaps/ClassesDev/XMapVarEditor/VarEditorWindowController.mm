//----------------------------------------------------------------------------
// File : VarEditorWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Constants editor window controller
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
// 04/02/2016 creation.
//----------------------------------------------------------------------------

#import "VarEditorWindowController.h"
#import "bXMapVarEditor.h" 
#import "CocoaStuff.h"

#import <mox_intf/NSUIUtils.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation VarEditorWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[VarEditorWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[VarEditorWindowController awakeFromNib]",true);
    [[_genderpopup menu] setAutoenablesItems:NO];
    
bXMapVarEditor* ext=(bXMapVarEditor*)_ext;
char            name[_values_length_max_];
char            value[_values_length_max_];
UInt32          kind;
    ext->get_infos(name,value,&kind);
    [self setKind:kind];
    [_namefld setCharValue:name];
    [_valuefld setCharValue:value];
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[VarEditorWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bXMapVarEditor* ext=(bXMapVarEditor*)_ext;
char            name[_values_length_max_];
char            value[_values_length_max_];
UInt32          kind;
    
    switch([_genderpopup indexOfSelectedItem]){
        case 0:
            kind=_char;
            break;
        case 1:
            kind=_bool;
            break;
        case 2:
            kind=_int;
            break;
        case 3:
            kind=_double;
            break;
        case 4:
            kind=_date;
            break;
        case 5:
            kind=_time;
            break;
        default:
            kind=_char;
            break;
    }
    [self setKind:kind];
    NSTextFieldGetValue(_namefld,name,_values_length_max_-1);
    NSTextFieldGetValue(_valuefld,value,_values_length_max_-1);
    ext->set_infos(name,value,kind);
    [super validDialog:sender];
}


#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
//
// -----------
-(void)setKind:(long)kind{
long    k;
    switch(kind){
        case _char:
            k=0;
            break;
        case _bool:
            k=1;
            break;
        case _int:
            k=2;
            break;
        case _double:
            k=3;
            break;
        case _date:
            k=4;
            break;
        case _time:
            k=5;
            break;
        default:
            k=0;
            break;
    }
    [_genderpopup selectItemAtIndex:k];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateUI{
    [_okbtn setEnabled:([[_namefld stringValue] length]>0)&&([[_valuefld stringValue] length]>0)];
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)controlTextDidChange:(NSNotification*)notification{
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapVarEditor* ext,
					  long* code){
VarEditorWindowController	*controller;
NSAutoreleasePool			*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[VarEditorWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
