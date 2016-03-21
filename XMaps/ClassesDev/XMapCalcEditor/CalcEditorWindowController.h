//----------------------------------------------------------------------------
// File : CalcEditorWindowController.h
// Project : MacMap
// Purpose : Header file : MapCalculator window controller
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
// 16/03/2016 creation.
//----------------------------------------------------------------------------

#import <Cocoa/Cocoa.h>
#import <mox_intf/bGenericType.h>
#import <std_ext/bStdNSAppModalWindowController.h>
#import "bXMapCalcEditor.h"

//----------------------------------------------------------------------------
@interface CalcObjView : NSView{
    NSPoint _origin;
}

//----------------------------------------------------------------------------
@end


//----------------------------------------------------------------------------
@interface CalcEditorWindowController : bStdNSAppModalWindowController{
    IBOutlet NSPopUpButton*	_opkpop;
    IBOutlet NSTextField*	_tpflbl;
    IBOutlet NSPopUpButton*	_tpfpop;

    IBOutlet NSButton*      _delbtn;

    IBOutlet NSTableView*   _itmtbl;
    IBOutlet CalcObjView*   _treviw;

    IBOutlet NSPopUpButton*	_rtkpop;

	IBOutlet NSTextField*	_namtxt;
}

//----------------------------------------------------------------------------
-(IBAction)doChooseItemKind:(id)sender;
-(IBAction)doChooseType:(id)sender;
-(IBAction)doDelete:(id)sender;

//----------------------------------------------------------------------------
// Gestion Interface
-(void)updateUI;
-(bXMapCalcCell*)root;

//----------------------------------------------------------------------------
@end

//----------------------------------------------------------------------------
