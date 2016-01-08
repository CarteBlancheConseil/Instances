//----------------------------------------------------------------------------
// File : StyleMgrWindowController.h
// Project : MacMap
// Purpose : Header file : Styles manager XMapBox window controller
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
// 12/11/2014 creation.
//----------------------------------------------------------------------------

#import <Cocoa/Cocoa.h>
#import <std_ext/bStdNSXBoxWindowController.h>

//----------------------------------------------------------------------------
// Juste pour avoir la classe en local pour IB

@interface StyleMgrPanel : bStdNSXBoxPanel{
}

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------

@interface StyleMgrWindowController : bStdNSXBoxWindowController{	
	IBOutlet NSTableView*	_stl_tbl;

	IBOutlet NSPopUpButton*	_typ_pop;
	IBOutlet NSPopUpButton*	_stl_pop;

	IBOutlet NSButton*		_new_btn;
	IBOutlet NSButton*		_edt_btn;
	IBOutlet NSButton*		_dup_btn;
	IBOutlet NSButton*		_ren_btn;
	IBOutlet NSButton*		_del_btn;
	IBOutlet NSButton*		_xml_btn;
	IBOutlet NSButton*		_avw_btn;
		
	NSInteger				_tp_index;
	unsigned int			_vdef_sgn;
}

//----------------------------------------------------------------------------
// Actions
-(IBAction)doChooseType:(id)sender;
-(IBAction)doChooseStyle:(id)sender;

-(IBAction)doAddStyle:(id)sender;
-(IBAction)doEditStyle:(id)sender;
-(IBAction)doDuplicateStyle:(id)sender;
-(IBAction)doRenameStyle:(id)sender;
-(IBAction)doDeleteStyle:(id)sender;
-(IBAction)doEditStyleAsXML:(id)sender;
-(IBAction)doAddStyleToView:(id)sender;

//----------------------------------------------------------------------------
// Gestion table
-(NSInteger)	numberOfRowsInTableView:(NSTableView*)aTableView;
-(id)			tableView:(NSTableView *)aTableView 
				objectValueForTableColumn:(NSTableColumn*)aTableColumn 
				row:(NSInteger)rowIndex;
-(void)			tableView:(NSTableView *)aTableView
				setObjectValue:(id)anObject
				forTableColumn:(NSTableColumn*)aTableColumn
				row:(NSInteger)rowIndex;
-(void)			tableViewSelectionDidChange:(NSNotification*)notification;

-(NSInteger)	getStyleIndex:(NSInteger)rowIndex;

//----------------------------------------------------------------------------
// Gestion Interface
-(void)updateUI;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
