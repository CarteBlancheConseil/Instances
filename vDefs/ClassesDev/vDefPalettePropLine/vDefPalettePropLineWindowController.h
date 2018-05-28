//----------------------------------------------------------------------------
// File : vDefPalettePropLineWindowController.h
// Project : MacMap
// Purpose : Header file : proportionnal line vdef window controller
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
// 29/01/2013 creation.
//----------------------------------------------------------------------------

#import <Cocoa/Cocoa.h>
#import <vdef_lib/bvDefPalettePropWindowController.h>
#import <std_ext/vDefPalettePreview.h>

//----------------------------------------------------------------------------
// Juste pour avoir la classe en local pour IB
@interface vDefPalettePropLinePanel : bStdNSPalettevDefPanel{
}

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------

@interface vDefPalettePropLineWindowController : bvDefPalettePropWindowController{
// Interface	
	IBOutlet NSPopUpButton*			_cap_pop;
	IBOutlet NSPopUpButton*			_jon_pop;
	IBOutlet NSButton*				_dsh_btn;
	IBOutlet NSPopUpButton*			_dsh_pop;
	IBOutlet NSTextField*			_mit_fld;
    IBOutlet NSPopUpButton*			_dec_pop;
    IBOutlet NSTextField*			_dec_fld;
	IBOutlet NSButton*				_smt_chk;
}

//----------------------------------------------------------------------------
// Actions principal
-(IBAction)doPutCap:(id)sender;
-(IBAction)doPutJoin:(id)sender;
-(IBAction)doAddDash:(id)sender;
-(IBAction)doPutDash:(id)sender;
-(IBAction)doPutMiter:(id)sender;
-(IBAction)doPutDec:(id)sender;
-(IBAction)doPutDecKind:(id)sender;
-(IBAction)doPutSmoothing:(id)sender;
-(IBAction)doChooseFillKind:(id)sender;

//----------------------------------------------------------------------------
// Gestion Interface
-(void)plot2Intf;
-(void)drawPreview:(CGRect)Line context:(CGContextRef)ctx;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
