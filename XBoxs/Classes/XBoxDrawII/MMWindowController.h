//----------------------------------------------------------------------------
// File : MMWindowController.h
// Project : MacMap
// Purpose : Header file : Draw/junctions XMapBox window controller
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
// 19/06/2008 creation.
//----------------------------------------------------------------------------

#import <Cocoa/Cocoa.h>
#import <std_ext/bStdNSXBoxWindowController.h>

//----------------------------------------------------------------------------
// Juste pour avoir la classe en local pour IB

@interface NSPanelNoKey : bStdNSXBoxPanel{
}

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------

@interface MMWindowController : bStdNSXBoxWindowController{
    IBOutlet NSTextField*	tEnd;
    IBOutlet NSTextField*	tVertex;
    IBOutlet NSTextField*	tNearest;
    IBOutlet NSTextField*	tDir;
	
    IBOutlet NSMatrix*		mAuto;
    IBOutlet NSButton*		bPop;
}

//----------------------------------------------------------------------------

-(IBAction)joinEnds:(id)sender;
-(IBAction)joinVertex:(id)sender;
-(IBAction)joinNearest:(id)sender;
-(IBAction)joinDir:(id)sender;

-(IBAction)setEndDist:(id)sender;
-(IBAction)setVertexDist:(id)sender;
-(IBAction)setNearestDist:(id)sender;
-(IBAction)setDirDist:(id)sender;

-(IBAction)setAuto:(id)sender;

-(IBAction)cleanConfig:(id)sender;
-(IBAction)topoConfig:(id)sender;
-(IBAction)doClean:(id)sender;

-(IBAction)windowPop:(id)sender;

//----------------------------------------------------------------------------

-(void)setExt:(bStdNSXBox*)ext;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
