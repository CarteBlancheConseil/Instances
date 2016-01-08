//----------------------------------------------------------------------------
// File : CocoaStuff.mm
// Project : MacMap
// Purpose : Objective C++ source file : Cocoa C wrappers
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
// 18/04/2014 creation.
//----------------------------------------------------------------------------

#import "StatUniWindowController.h"
#import "CocoaStuff.h"

// ---------------------------------------------------------------------------
// 
// ------------
void* initializeStatCocoa(void* gapp, 
						  void* ext) {
StatUniWindowController	*controller;
NSAutoreleasePool		*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[StatUniWindowController alloc] init];
    [controller setExt:(bStdNSXMap*)ext];
    [localPool release];
    return((void*)controller);
}

// ---------------------------------------------------------------------------
// 
// ------------
void* initializeStatCocoaAtPath(void* gapp, 
								void* ext,
								const char* path){
StatUniWindowController*	controller;
NSAutoreleasePool*			localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[StatUniWindowController alloc] init];
    if([controller setExt:(bStdNSXMap*)ext atPath:path]==NO){
		[controller close];
		controller=nil;
	}
    [localPool release];
    return((void*)controller);
}

// ---------------------------------------------------------------------------
// 
// ------------
void disposeStatCocoa(const void* instance){
NSAutoreleasePool		*localPool;
StatUniWindowController	*mmc=(StatUniWindowController*)instance;
	
	if(mmc==NULL){
		return;
	}
	
    localPool=[[NSAutoreleasePool alloc] init];        
	[mmc release];
    [localPool release];
}

// ---------------------------------------------------------------------------
// 
// ------------
void closeStatCocoa(const void* instance){
NSAutoreleasePool		*localPool;
StatUniWindowController	*mmc=(StatUniWindowController*)instance;
	
	if(mmc==NULL){
		return;
	}
	
    localPool=[[NSAutoreleasePool alloc] init];        
	[mmc close];
    [localPool release];
}

