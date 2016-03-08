//----------------------------------------------------------------------------
// File : MakeConstraintsWindowController.h
// Project : MacMap
// Purpose : Header file : XMap make constraints window controller
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 1997-2015 Carte Blanche Conseil.
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
// 19/06/2008 creation.
//----------------------------------------------------------------------------

#import <Cocoa/Cocoa.h>
#import <mox_intf/bGenericType.h>
#import <std_ext/bStdNSAppModalWindowController.h>
#import "bXMapMakeConstraints.h"

//----------------------------------------------------------------------------
@interface MakeConstraintsWindowController : bStdNSAppModalWindowController{
	IBOutlet NSPopUpButton*	_typepopup;	
	IBOutlet NSPopUpButton*	_genderpopup;	

	IBOutlet NSTableView*	_fldtblvw;
	IBOutlet NSTableView*	_cnttblvw;

	IBOutlet NSTextField*	_textfld;
		
	IBOutlet NSButton*		_addbtn;
	IBOutlet NSButton*		_rmvbtn;
	IBOutlet NSButton*		_modibtn;
	
	IBOutlet NSPopUpButton*	_fieldfrompopup;	

	bGenericType*			_tp;
	long					_findex;
}

//----------------------------------------------------------------------------

-(IBAction)doChooseType:(id)sender;
-(IBAction)doChooseGender:(id)sender;
-(IBAction)doRemove:(id)sender;
-(IBAction)doAdd:(id)sender;
-(IBAction)doModify:(id)sender;
-(IBAction)doCreateFromField:(id)sender;

//----------------------------------------------------------------------------
// Gestion Interface
-(void)updateUI;
-(void)checkDel;
-(void)checkAdd;
-(void)checkModify;
-(void)checkKind;
-(void)checkCreate;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
