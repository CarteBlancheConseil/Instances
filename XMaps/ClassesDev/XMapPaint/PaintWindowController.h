//----------------------------------------------------------------------------
// File : PaintWindowController.h
// Project : MacMap
// Purpose : Header file : XMap paint window controller
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2015 Carte Blanche Conseil.
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
// 20/08/2015 creation.
//----------------------------------------------------------------------------

#import <Cocoa/Cocoa.h>
#import <std_ext/bStdNSXMapWindowController.h>
#import <MacMapSuite/bArray.h>

//----------------------------------------------------------------------------

@interface PaintPanel : bStdNSXMapPanel{
}

//----------------------------------------------------------------------------

@end


//----------------------------------------------------------------------------

@interface PaintWindowController : bStdNSXMapWindowController{
	IBOutlet NSButton*	_blk;
	IBOutlet NSButton*	_wht;
	IBOutlet NSButton*	_red;
	IBOutlet NSButton*	_grn;
	IBOutlet NSButton*	_blu;
	IBOutlet NSButton*	_cyn;
	IBOutlet NSButton*	_mgt;
	IBOutlet NSButton*	_ylw;
	
	long				_ls;
}

//----------------------------------------------------------------------------
// Actions
-(IBAction)doPaint:(id)sender;

//----------------------------------------------------------------------------
// Gestion Interface
-(void)updateUI;

//----------------------------------------------------------------------------
// Interface XMap
-(bGenericMacMapApp*)getApp;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
