//----------------------------------------------------------------------------
// File : DBStructureWindowController.h
// Project : MacMap
// Purpose : Header file : XMap database structure window controller
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2015 Carte Blanche Conseil.
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
// 02/09/2015 creation.
//----------------------------------------------------------------------------

#import <std_ext/bStdNSAppModalWindowController.h>

//----------------------------------------------------------------------------
@interface DBStructureWindowController : bStdNSAppModalWindowController{

	IBOutlet NSPopUpButton*	_typepopup;	
	IBOutlet NSPopUpButton*	_genderpopup;	

	IBOutlet NSTableView*	_fldtblvw;

	IBOutlet NSTextField*	_namefld;
    IBOutlet NSTextField*	_lengfld;
    IBOutlet NSTextField*	_lenmfld;
    IBOutlet NSTextField*	_valufld;
    IBOutlet NSTextField*	_vanmfld;

    IBOutlet NSButton*		_maskbtn;
    IBOutlet NSButton*		_delpbtn;
    IBOutlet NSButton*		_edtpbtn;
    
    IBOutlet NSTextField*	_infofld;

	IBOutlet NSButton*		_addbtn;
	IBOutlet NSButton*		_rmvbtn;
	IBOutlet NSButton*		_modibtn;
	
	bGenericType*			_tp;
}

//----------------------------------------------------------------------------

-(IBAction)doChooseType:(id)sender;
-(IBAction)doChooseGender:(id)sender;
-(IBAction)doRemove:(id)sender;
-(IBAction)doAdd:(id)sender;
-(IBAction)doModify:(id)sender;
-(IBAction)doConstraints:(id)sender;

//----------------------------------------------------------------------------
// Gestion Interface
-(void)updateUI;
-(void)checkDel;
-(void)checkAdd;
-(void)checkModify;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
