//----------------------------------------------------------------------------
// File : TypeManagerWindowController.h
// Project : MacMap
// Purpose : Header file : XMap type manager window controller
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
// 16/06/2011
//----------------------------------------------------------------------------

#import <Cocoa/Cocoa.h>
#import "bXMapTypeManager.h"
//#import <std_ext/bStdNSAppModalWindowController.h>

//----------------------------------------------------------------------------

@interface TypeManagerWindowController : NSWindowController/*bStdNSAppModalWindowController*/{

	IBOutlet NSButton*		_okbtn;	
	IBOutlet NSButton*		_cancelbtn;	
	bXMapTypeManager*		_ext;
	long					_code;
	
	IBOutlet NSTableView*	_typetbl;

	IBOutlet NSButton*		_newbtn;
	IBOutlet NSButton*		_opnbtn;
	IBOutlet NSButton*		_rmvbtn;
	IBOutlet NSButton*		_renbtn;
	IBOutlet NSButton*		_prtbtn;
	IBOutlet NSButton*		_unpbtn;

	IBOutlet NSTextField*	_pathfld;
	IBOutlet NSTextField*	_unitfld;
	IBOutlet NSTextField*	_resofld;
	IBOutlet NSTextField*	_olivfld;
	IBOutlet NSTextField*	_okilfld;
	IBOutlet NSTextField*	_gndrfld;
	IBOutlet NSTextField*	_projfld;
	IBOutlet NSTextField*	_sridfld;
	IBOutlet NSTextField*	_tpidfld;
	IBOutlet NSTextField*	_crdtfld;
	IBOutlet NSTextField*	_nbflfld;
}

//----------------------------------------------------------------------------
// Std 
-(id)initWithExt:(bXMapTypeManager*)ext;
-(void)runTypeManagerCocoaAppModal:(long*)code;

//----------------------------------------------------------------------------
// Validation Dialogue 
-(IBAction)validDialog:(id)sender;
-(IBAction)cancelDialog:(id)sender;

//----------------------------------------------------------------------------

-(IBAction)doNew:(id)sender;
-(IBAction)doOpen:(id)sender;
-(IBAction)doRemove:(id)sender;
-(IBAction)doRename:(id)sender;
-(IBAction)doProtect:(id)sender;
-(IBAction)doUnprotect:(id)sender;

//----------------------------------------------------------------------------
// Gestion Interface
-(void)updateUI;
-(void)checkRemove;
-(void)checkRename;
-(void)checkProtect;
-(void)checkUnprotect;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
