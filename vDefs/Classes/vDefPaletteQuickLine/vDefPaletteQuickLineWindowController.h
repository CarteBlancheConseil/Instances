//----------------------------------------------------------------------------
// File : vDefPaletteQuickLineWindowController.h
// Project : MacMap
// Purpose : Header file : Line vdef window controller
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
// 27/06/2012 creation.
//----------------------------------------------------------------------------

#import <Cocoa/Cocoa.h>
#import <vdef_lib/bvDefPaletteQuickWindowController.h>
#import <std_ext/vDefPalettePreview.h>

//----------------------------------------------------------------------------
// Juste pour avoir la classe en local pour IB
@interface vDefPaletteQuickLinePanel : bStdNSPalettevDefPanel{
}

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------

@interface vDefPaletteQuickLineWindowController : bvDefPaletteQuickWindowController{
// Interface	
	IBOutlet NSPopUpButton*			_swc_pop;

	IBOutlet NSTextField*			_wdt_fld;
	IBOutlet NSPopUpButton*			_cap_pop;
	IBOutlet NSPopUpButton*			_jon_pop;
	IBOutlet NSButton*				_dsh_btn;
	IBOutlet NSPopUpButton*			_dsh_pop;
	IBOutlet NSColorWell*			_stk_clr;
	IBOutlet NSTextField*			_mit_fld;
	IBOutlet NSTextField*			_dec_fld;
	IBOutlet NSButton*				_smt_chk;
	
	IBOutlet NSPopUpButton*			_fwdt_pop;
	IBOutlet NSPopUpButton*			_fcap_pop;
	IBOutlet NSPopUpButton*			_fjon_pop;
	IBOutlet NSPopUpButton*			_fdsh_pop;
	IBOutlet NSPopUpButton*			_fstk_pop;
	IBOutlet NSPopUpButton*			_fmit_pop;
	IBOutlet NSPopUpButton*			_fdec_pop;
	IBOutlet NSPopUpButton*			_fsmt_pop;
	
	NSInteger						_cur;
}

//----------------------------------------------------------------------------
// Actions principal
-(IBAction)doSwitchLine:(id)sender;

-(IBAction)doPutWidth:(id)sender;
-(IBAction)doPutCap:(id)sender;
-(IBAction)doPutJoin:(id)sender;
-(IBAction)doAddDash:(id)sender;
-(IBAction)doPutDash:(id)sender;
-(IBAction)doPutStrokeColor:(id)sender;
-(IBAction)doPutMiter:(id)sender;
-(IBAction)doPutDec:(id)sender;
-(IBAction)doPutSmooth:(id)sender;

-(IBAction)doPutWidthField:(id)sender;
-(IBAction)doPutCapField:(id)sender;
-(IBAction)doPutJoinField:(id)sender;
-(IBAction)doPutDashField:(id)sender;
-(IBAction)doPutStrokeColorField:(id)sender;
-(IBAction)doPutMiterField:(id)sender;
-(IBAction)doPutDecField:(id)sender;
-(IBAction)doPutSmoothField:(id)sender;

//----------------------------------------------------------------------------
// Gestion Interface
-(void)checkIntfAvailability;
-(void)plot2Intf;
-(void)convertColor;
-(void)drawPreview:(CGRect)Line context:(CGContextRef)ctx;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
