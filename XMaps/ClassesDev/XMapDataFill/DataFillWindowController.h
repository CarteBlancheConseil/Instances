//----------------------------------------------------------------------------
// File : DataFillWindowController.h
// Project : MacMap
// Purpose : Header file : XMap data fill window controller
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
// 15/02/2016 creation.
//----------------------------------------------------------------------------

#import <std_ext/bStdNSAppModalWindowController.h>

//----------------------------------------------------------------------------
@interface DataFillWindowController : bStdNSAppModalWindowController{
    IBOutlet NSTableView*	_fldtbl;
    IBOutlet NSPopUpButton*	_wthpop;
    
    IBOutlet NSPopUpButton*	_chspop;
    IBOutlet NSComboBox*	_valcmb;
    
    IBOutlet NSTableView*	_runtbl;
    IBOutlet NSButton*		_addbtn;
    IBOutlet NSButton*		_rmvbtn;
}

//----------------------------------------------------------------------------
// Actions
-(IBAction)doChooseKind:(id)sender;
-(IBAction)doConstraint:(id)sender;
-(IBAction)doAdd:(id)sender;
-(IBAction)doRemove:(id)sender;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
