//----------------------------------------------------------------------------
// File : vDefPaletteQuickDirWindowController.h
// Project : MacMap
// Purpose : Header file : Arrow (direction) vdef window controller
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
// 26/06/2012 creation.
//----------------------------------------------------------------------------

#import <Cocoa/Cocoa.h>
#import <vdef_lib/bvDefPaletteQuickWindowController.h>
#import <std_ext/vDefPalettePreview.h>

//----------------------------------------------------------------------------
// Juste pour avoir la classe en local pour IB
@interface vDefPaletteQuickDirPanel : bStdNSPalettevDefPanel{
}

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------

@interface vDefPaletteQuickDirWindowController : bvDefPaletteQuickWindowController{
// Interface	
	IBOutlet NSPopUpButton*			_fdir_pop;

	IBOutlet NSTextField*			_siz_fld;
	IBOutlet NSTextField*			_wdt_fld;
	IBOutlet NSPopUpButton*			_flk_pop;
	IBOutlet NSTabView*				_fil_tab;
	IBOutlet NSColorWell*			_fil_clr;
	IBOutlet NSButton*				_fil_img;
	IBOutlet NSSlider*				_fil_sld;
	IBOutlet NSColorWell*			_stk_clr;
	IBOutlet NSTextField*			_dec_fld;

	IBOutlet NSPopUpButton*			_fsiz_pop;
	IBOutlet NSPopUpButton*			_fwdt_pop;
	IBOutlet NSPopUpButton*			_ffil_pop;
	IBOutlet NSPopUpButton*			_fstk_pop;
	IBOutlet NSPopUpButton*			_fdec_pop;
}

//----------------------------------------------------------------------------
// Actions principal
-(IBAction)doPutDirField:(id)sender;

-(IBAction)doPutSize:(id)sender;
-(IBAction)doPutWidth:(id)sender;
-(IBAction)doChooseFillKind:(id)sender;//
-(IBAction)doPutFillColor:(id)sender;
-(IBAction)doPutFillImage:(id)sender;//
-(IBAction)doPutFillAlpha:(id)sender;
-(IBAction)doPutStrokeColor:(id)sender;
-(IBAction)doPutDec:(id)sender;

-(IBAction)doPutSizeField:(id)sender;//
-(IBAction)doPutWidthField:(id)sender;//
-(IBAction)doPutFillColorField:(id)sender;//
-(IBAction)doPutStrokeColorField:(id)sender;//
-(IBAction)doPutDecField:(id)sender;//

//----------------------------------------------------------------------------
// Gestion Interface
-(void)checkIntfAvailability;
-(void)plot2Intf;
-(void)convertColor;
-(void)drawPreview:(CGRect)Dir context:(CGContextRef)ctx;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
