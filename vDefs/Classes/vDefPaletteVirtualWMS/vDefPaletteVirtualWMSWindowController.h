//----------------------------------------------------------------------------
// File : vDefPaletteVirtualWMSWindowController.h
// Project : MacMap
// Purpose : Header file : WMS vdef window controller
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
// 13/07/2013 creation.
//----------------------------------------------------------------------------

#import <Cocoa/Cocoa.h>
#import <std_ext/bStdNSPalettevDefWindowController.h>
#import <std_ext/vDefPalettePreview.h>

//----------------------------------------------------------------------------
// Juste pour avoir la classe en local pour IB
@interface vDefPaletteVirtualWMSPanel : bStdNSPalettevDefPanel{
}

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------

@interface vDefPaletteVirtualWMSWindowController : bStdNSPalettevDefWindowController{
// Interface
// Std Cocoa Palette vDef
	IBOutlet NSTableView*			_run_tbl;	// StyleRuns
	IBOutlet vDefPalettePreview*	_prvw;		// Preview
	
	IBOutlet NSTextField*			_url_fld;
	IBOutlet NSButton*				_con_btn;
	IBOutlet NSButton*				_exp_btn;
	
	IBOutlet NSSlider*				_alp_sld;
	
// Visibilité
	IBOutlet NSPopUpButton*			_smn_pop;	// Echelle min
	IBOutlet NSPopUpButton*			_smx_pop;	// Echelle max
		
	IBOutlet NSButton*				_upd_btn;
	
	NSInteger						_last_click;
}


//----------------------------------------------------------------------------
// Actions principal
-(IBAction)doConnect:(id)sender;
-(IBAction)doExport:(id)sender;
-(IBAction)doPutAlpha:(id)sender;
-(IBAction)doChooseLayer:(id)sender;

-(IBAction)doChooseScaleMin:(id)sender;
-(IBAction)doChooseScaleMax:(id)sender;

-(IBAction)doClickPreview:(id)sender;//

// Actions appliquer
-(IBAction)doApply:(id)sender;

//----------------------------------------------------------------------------
// Gestion table
-(NSInteger)	numberOfRowsInTableView:(NSTableView*)aTableView;
-(id)			tableView:(NSTableView *)aTableView 
				objectValueForTableColumn:(NSTableColumn*)aTableColumn 
				row:(NSInteger)rowIndex;
-(void)			tableViewSelectionDidChange:(NSNotification*)notification;

//----------------------------------------------------------------------------
// Gestion Interface
-(void)updateUI;
-(void)checkIntfAvailability;
-(void)plot2Intf;
-(void)drawPreview:(CGRect)rect context:(CGContextRef)ctx;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
