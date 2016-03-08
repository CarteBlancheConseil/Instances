//----------------------------------------------------------------------------
// File : ViewMgrWindowController.h
// Project : MacMap
// Purpose : Header file : XMap views management window controller
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

#import <Cocoa/Cocoa.h>
#import <mox_intf/bGenericType.h>
#import <std_ext/bStdNSAppModalWindowController.h>
#import "bXMapViewMgr.h"

//----------------------------------------------------------------------------
@interface ViewMgrWindowController : bStdNSAppModalWindowController{
	IBOutlet NSTableView*	_viwtbl;

	IBOutlet NSButton*		_addbtn;
	IBOutlet NSButton*		_rmvbtn;
    IBOutlet NSButton*		_dupbtn;
    IBOutlet NSButton*		_renbtn;
}

//----------------------------------------------------------------------------
// Actions
-(IBAction)doAdd:(id)sender;
-(IBAction)doRemove:(id)sender;
-(IBAction)doRename:(id)sender;
-(IBAction)doDuplicate:(id)sender;

//----------------------------------------------------------------------------
// Gestion Interface
-(void)updateUI;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
