//----------------------------------------------------------------------------
// File : vDefPaletteRangeRectWindowController.h
// Project : MacMap
// Purpose : Header file : Range rectangle vdef window controller
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
// 30/08/2012 creation.
//----------------------------------------------------------------------------

#import <Cocoa/Cocoa.h>
#import <vdef_lib/bvDefPaletteRangeWindowController.h>
#import <std_ext/vDefPalettePreview.h>

//----------------------------------------------------------------------------
// Juste pour avoir la classe en local pour IB
@interface vDefPaletteRangeRectPanel : bStdNSPalettevDefPanel{
}

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------

@interface vDefPaletteRangeRectWindowController : bvDefPaletteRangeWindowController{
// Interface	

	IBOutlet NSTextField*			_hsz_fld;
	IBOutlet NSTextField*			_vsz_fld;

	IBOutlet NSSlider*				_fil_sld;
	IBOutlet NSTextField*			_wdt_fld;
	IBOutlet NSColorWell*			_stk_clr;

	IBOutlet NSButton*				_cnt_chk;
}

//----------------------------------------------------------------------------
// Actions principal

-(IBAction)doPutHSize:(id)sender;
-(IBAction)doPutVSize:(id)sender;
-(IBAction)doPutWidth:(id)sender;
-(IBAction)doPutFillAlpha:(id)sender;
-(IBAction)doPutStrokeColor:(id)sender;
-(IBAction)doPutCentroid:(id)sender;

-(IBAction)doChooseColorimetry:(id)sender;
-(IBAction)doChooseFillKind:(id)sender;
-(IBAction)doChooseFillColor:(id)sender;
-(IBAction)doChooseFillPattern:(id)sender;
-(IBAction)doChooseFillFromColor:(id)sender;
-(IBAction)doChooseFillToColor:(id)sender;

//----------------------------------------------------------------------------
// Gestion Interface
-(void)checkIntfAvailability;
-(void)plot2Intf;
-(void)convertColor;
-(void)drawPreview:(CGRect)Rect context:(CGContextRef)ctx;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
