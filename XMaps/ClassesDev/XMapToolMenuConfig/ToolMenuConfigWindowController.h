//----------------------------------------------------------------------------
// File : ToolMenuConfigWindowController.h
// Project : MacMap
// Purpose : Header file : XMap tool menu configuration window controller
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
// 24/02/2016 creation.
//----------------------------------------------------------------------------

#import <Cocoa/Cocoa.h>
#import <mox_intf/bGenericType.h>
#import <std_ext/bStdNSAppModalWindowController.h>
#import "bXMapToolMenuConfig.h"

//----------------------------------------------------------------------------
@interface ToolMenuConfigWindowController : bStdNSAppModalWindowController{
    IBOutlet NSTableView*	_flftbl;
    IBOutlet NSTableView*	_flttbl;

    IBOutlet NSButton*		_addbtn;
    IBOutlet NSButton*		_insbtn;
    IBOutlet NSButton*		_allbtn;
    IBOutlet NSButton*		_rmvbtn;
    
    bArray* _arr;
}

//----------------------------------------------------------------------------
-(IBAction)doAdd:(id)sender;
-(IBAction)doInsert:(id)sender;
-(IBAction)doAll:(id)sender;
-(IBAction)doRemove:(id)sender;

//----------------------------------------------------------------------------
-(void)updateUI;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
