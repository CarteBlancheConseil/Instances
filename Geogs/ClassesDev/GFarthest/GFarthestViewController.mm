//----------------------------------------------------------------------------
// File : GFarthestViewController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Farthest geog view controller
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
// Include with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// See the LICENSE.txt file for more information.
//
//----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------
// 06/10/2016 creation.
//----------------------------------------------------------------------------

#import "GFarthestViewController.h"
#import "CocoaStuff.h"
#import <mox_intf/NSUIUtils.h>
#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation GFarthestViewController
// ---------------------------------------------------------------------------
//
// ------------
+(id)allocWithNibNamed:(NSString*)nibNamed
                 class:(Class)loadClass{
//_bTrace_("[GFarthestViewController allocWithNibNamed owner class]",true);
    return [[loadClass alloc] initWithNibName:nibNamed
                                       bundle:[NSBundle bundleWithIdentifier:@"com.cbconseil.geogs.gfarthest"]];
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)setNumber:(long)val{
    [_val_txt setIntValue:val];
}

// ---------------------------------------------------------------------------
//
// ------------
-(long)getNumber{
    return [_val_txt intValue];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
//
// ------------
void* allocViewController(void* nsview){
//_bTrace_("GFarthestViewController allocViewController",true);
GFarthestViewController *ctrlr;
NSAutoreleasePool       *localPool;
NSView                  *ctnrview=(NSView*)nsview;
NSPoint                 o;

    localPool=[[NSAutoreleasePool alloc] init];
    ctrlr=[GFarthestViewController allocWithNibNamed:@"View"
                                               class:[GFarthestViewController class]];
    
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
                         long value){
//_bTrace_("GFarthestViewController setDataToController",true);
GFarthestViewController *controller=(GFarthestViewController*)ctrlr;
NSAutoreleasePool       *localPool;
    
    localPool=[[NSAutoreleasePool alloc] init];
    [controller setNumber:value];
    [localPool release];
}

// ---------------------------------------------------------------------------
//
// ------------
double getDataFromController(void* ctrlr){
//_bTrace_("GFarthestViewController getDataFromController",true);
GFarthestViewController *controller=(GFarthestViewController*)ctrlr;
NSAutoreleasePool       *localPool;
    
    localPool=[[NSAutoreleasePool alloc] init];
double  val=[controller getNumber];
    [localPool release];
    return val;
}

// ---------------------------------------------------------------------------
//
// ------------
void releaseViewController(void* ctrlr){
//_bTrace_("GFarthestViewController releaseViewController",true);
GFarthestViewController *controller=(GFarthestViewController*)ctrlr;
NSAutoreleasePool       *localPool;
    
    localPool=[[NSAutoreleasePool alloc] init];
    [[controller view] removeFromSuperview];
    [controller release];
    [localPool release];
}
