//----------------------------------------------------------------------------
// File : ToolsWindowController.h
// Project : MacMap
// Purpose : Header file : Tools XMapBox window controller
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
// 31/12/2014 creation.
//----------------------------------------------------------------------------

#import <Cocoa/Cocoa.h>
#import <std_ext/bStdNSXBoxWindowController.h>

//----------------------------------------------------------------------------
// Juste pour avoir la classe en local pour IB

@interface ToolsPanel : bStdNSXBoxPanel{
}

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------

@interface ToolsWindowController : bStdNSXBoxWindowController{	
    IBOutlet NSButton*	_glb_btn;
    IBOutlet NSButton*	_mnu_btn;
    IBOutlet NSButton*	_trk_btn;

    IBOutlet NSButton*	_nav_btn;
    IBOutlet NSView*    _nav_viw;
    
    IBOutlet NSButton*	_geo_btn;
    IBOutlet NSView*    _geo_viw;

    IBOutlet NSButton*	_prs_btn;
    IBOutlet NSView*    _prs_viw;
    
    long                _cur;
    BOOL                _pop;
}

//----------------------------------------------------------------------------
// Actions
-(IBAction)doNav:(id)sender;
-(IBAction)doGeom:(id)sender;
-(IBAction)doPres:(id)sender;
-(IBAction)doTool:(id)sender;
-(IBAction)doMenuConfig:(id)sender;
-(IBAction)doEnableTrack:(id)sender;

//----------------------------------------------------------------------------
// Gestion Interface
-(void)updateUI;
-(void)hide:(long)index;
-(void)sizeBoxAtIndex:(long)index
               toSize:(CGFloat)newSize;

//----------------------------------------------------------------------------
// Interface XMapBox
-(void)prepareForClose;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
