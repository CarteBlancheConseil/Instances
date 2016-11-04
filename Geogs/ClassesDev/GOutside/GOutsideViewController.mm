//----------------------------------------------------------------------------
// File : GOutsideViewController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Outside geog view controller
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
// Outside with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// See the LICENSE.txt file for more information.
//
//----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------
// 06/10/2016 creation.
//----------------------------------------------------------------------------

#import "GOutsideViewController.h"
#import "CocoaStuff.h"
#import <mox_intf/NSUIUtils.h>
#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation GOutsideViewController
// ---------------------------------------------------------------------------
//
// ------------
+(id)allocWithNibNamed:(NSString*)nibNamed
                 class:(Class)loadClass{
//_bTrace_("[GOutsideViewController allocWithNibNamed owner class]",true);
    return [[loadClass alloc] initWithNibName:nibNamed
                                       bundle:[NSBundle bundleWithIdentifier:@"com.cbconseil.geogs.goutside"]];
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)setFull:(bool)full{
    [_ful_mtx selectCellAtRow:(full)?1:0 column:0];
}

// ---------------------------------------------------------------------------
//
// ------------
-(BOOL)getFull{
    return ([_ful_mtx selectedRow]==1);
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)setStrict:(bool)strict{
    [_str_chk setIntValue:strict];
}

// ---------------------------------------------------------------------------
//
// ------------
-(BOOL)getStrict{
    return [_str_chk intValue];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
//
// ------------
void* allocViewController(void* nsview){
//_bTrace_("GOutsideViewController allocViewController",true);
GOutsideViewController  *ctrlr;
NSAutoreleasePool       *localPool;
NSView                  *ctnrview=(NSView*)nsview;
NSPoint                 o;

    localPool=[[NSAutoreleasePool alloc] init];
    ctrlr=[GOutsideViewController allocWithNibNamed:@"View"
                                            class:[GOutsideViewController class]];
    
    o.x=[[ctrlr view] frame].origin.x;
    o.y=NSMaxY([ctnrview frame])-[[ctrlr view] frame].size.height;
    [[ctrlr view] setFrameOrigin:o];
    [ctnrview addSubview:[ctrlr view]];

    [localPool release];
    return((void*)ctrlr);
}

// ---------------------------------------------------------------------------
//
// ------------
void setDataToController(void* ctrlr,
                         bool full,
                         bool strict){
//_bTrace_("GOutsideViewController setDatToController",true);
GOutsideViewController  *controller=(GOutsideViewController*)ctrlr;
NSAutoreleasePool       *localPool;
    
    localPool=[[NSAutoreleasePool alloc] init];
    [controller setFull:full];
    [controller setStrict:strict];
    [localPool release];
}

// ---------------------------------------------------------------------------
//
// ------------
void getDataFromController(void* ctrlr,
                           bool* full,
                           bool* strict){
//_bTrace_("GOutsideViewController getDataFromController",true);
GOutsideViewController  *controller=(GOutsideViewController*)ctrlr;
NSAutoreleasePool       *localPool;
    
    localPool=[[NSAutoreleasePool alloc] init];
    *full=[controller getFull];
    *strict=[controller getStrict];
    [localPool release];
}

// ---------------------------------------------------------------------------
//
// ------------
void releaseViewController(void* ctrlr){
//_bTrace_("GOutsideViewController releaseViewController",true);
GOutsideViewController  *controller=(GOutsideViewController*)ctrlr;
NSAutoreleasePool       *localPool;
    
    localPool=[[NSAutoreleasePool alloc] init];
    [[controller view] removeFromSuperview];
    [controller release];
    [localPool release];
}
