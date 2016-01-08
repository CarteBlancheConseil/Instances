//----------------------------------------------------------------------------
// File : vDefPaletteUltraWindowController.h
// Project : MacMap
// Purpose : Header file : Ultra vdef window controller
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
// 12/08/2013 creation.
//----------------------------------------------------------------------------

#import <Cocoa/Cocoa.h>
#import <std_ext/bStdNSPalettevDefWindowController.h>
#import <std_ext/vDefPalettePreview.h>

//----------------------------------------------------------------------------
// Juste pour avoir la classe en local pour IB
@interface vDefPaletteUltraPanel : bStdNSPalettevDefPanel{
}

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------

@interface vDefPaletteUltraWindowController : bStdNSPalettevDefWindowController{
	IBOutlet NSTextField*	_txt_fld;
	IBOutlet NSButton*		_upd_btn;
}


//----------------------------------------------------------------------------
// Actions principal
-(IBAction)doPutXML:(id)sender;

// Actions appliquer
-(IBAction)doApply:(id)sender;

//----------------------------------------------------------------------------
// Gestion Interface
-(void)updateUI;
-(void)checkIntfAvailability;
-(void)plot2Intf;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
