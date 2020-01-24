//----------------------------------------------------------------------------
// File : ToolSelectWindowController.h
// Project : MacMap
// Purpose : Header file : Tool Select window controller
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2017 Carte Blanche Conseil.
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
// 31/01/2017 creation.
//----------------------------------------------------------------------------

#import <std_ext/bStdNSAppModalWindowController.h>

//----------------------------------------------------------------------------
@interface ToolSelectWindowController : bStdNSAppToolModalWindowController{
    IBOutlet NSButton*      _alo_chk;
    IBOutlet NSButton*      _alt_chk;
    IBOutlet NSTableView*	_psl_viw;
    
    IBOutlet NSButton*      _flo_chk;
    IBOutlet NSButton*      _act_chk;
    IBOutlet NSTextField*   _ang_txt;
    IBOutlet NSTableView*	_zsl_viw;
}

//----------------------------------------------------------------------------
-(IBAction)doUseAngleConstraint:(id)sender;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
