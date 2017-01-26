//----------------------------------------------------------------------------
// File : RasterImportWindowController.h
// Project : MacMap
// Purpose : Header file : XMap raster import window controller
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2016 Carte Blanche Conseil.
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
// 14/03/2016 creation.
//----------------------------------------------------------------------------

#import <std_ext/bStdNSAppModalWindowController.h>

//----------------------------------------------------------------------------
@interface RasterImportWindowController : bStdNSAppModalWindowController{
    IBOutlet NSTextField*		_xtltxt;
    IBOutlet NSTextField*		_xtulbl;
    
    IBOutlet NSTextField*		_ytltxt;
    IBOutlet NSTextField*		_ytulbl;

    IBOutlet NSPopUpButton*		_chcpop;

    IBOutlet NSTextField*		_xbrtxt;
    IBOutlet NSTextField*		_xbrlbl;
    IBOutlet NSTextField*		_xbulbl;
    
    IBOutlet NSTextField*		_ybrtxt;
    IBOutlet NSTextField*		_ybrlbl;
    IBOutlet NSTextField*		_ybulbl;
    
    IBOutlet NSTextField*		_scltxt;
    IBOutlet NSTextField*		_scllbl;
}

//----------------------------------------------------------------------------
-(IBAction)chooseMethod:(id)sender;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
