//----------------------------------------------------------------------------
// File : vDefPaletteQuickSymbWindowController.h
// Project : MacMap
// Purpose : Header file : Symbols vdef window controller
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
@interface vDefPaletteQuickSymbPanel : bStdNSPalettevDefPanel{
}

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------

@interface vDefPaletteQuickSymbWindowController : bvDefPaletteQuickWindowController{
// Interface	
	IBOutlet NSButton*				_cnt_chk;

	IBOutlet NSButton*				_smb_btn;
	IBOutlet NSTextField*			_smb_fld;
	IBOutlet NSTextField*			_dmw_fld;
	IBOutlet NSTextField*			_dmh_fld;
	IBOutlet NSTextField*			_rot_fld;
	IBOutlet NSSlider*				_alp_sld;
	
	IBOutlet NSPopUpButton*			_fsmb_pop;
	IBOutlet NSPopUpButton*			_fdmw_pop;
	IBOutlet NSPopUpButton*			_fdmh_pop;
	IBOutlet NSPopUpButton*			_frot_pop;
	IBOutlet NSPopUpButton*			_falp_pop;
}

//----------------------------------------------------------------------------
// Actions principal
-(IBAction)doPutCentroid:(id)sender;

-(IBAction)doPutSymb:(id)sender;//
-(IBAction)doPutDimW:(id)sender;
-(IBAction)doPutDimH:(id)sender;
-(IBAction)doPutRotation:(id)sender;
-(IBAction)doPutAlpha:(id)sender;

-(IBAction)doPutSymbField:(id)sender;//
-(IBAction)doPutDimWField:(id)sender;//
-(IBAction)doPutDimHField:(id)sender;//
-(IBAction)doPutRotationField:(id)sender;//
-(IBAction)doPutAlphaField:(id)sender;

//----------------------------------------------------------------------------
// Gestion Interface
-(void)checkIntfAvailability;
-(void)plot2Intf;
-(void)drawPreview:(CGRect)rect context:(CGContextRef)ctx;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
