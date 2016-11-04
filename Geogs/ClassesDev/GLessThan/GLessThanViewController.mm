//----------------------------------------------------------------------------
// File : GLessThanViewController.mm
// Project : MacMap
// Purpose : Objective C++ source file : LessThan geog view controller
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
// LessThan with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// See the LICENSE.txt file for more information.
//
//----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------
// 06/10/2016 creation.
//----------------------------------------------------------------------------

#import "GLessThanViewController.h"
#import "CocoaStuff.h"
#import <mox_intf/NSUIUtils.h>
#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation GLessThanViewController
// ---------------------------------------------------------------------------
//
// ------------
+(id)allocWithNibNamed:(NSString*)nibNamed
                 class:(Class)loadClass{
//_bTrace_("[GLessThanViewController allocWithNibNamed owner class]",true);
    return [[loadClass alloc] initWithNibName:nibNamed
                                       bundle:[NSBundle bundleWithIdentifier:@"com.cbconseil.geogs.glessthan"]];
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)setValue:(double)val
           unit:(char*)unt {
    [_val_txt setDoubleValue:val];
    [_unt_txt setCharValue:unt];
}

// ---------------------------------------------------------------------------
//
// ------------
-(double)getValue{
    return [_val_txt doubleValue];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
//
// ------------
void* allocViewController(void* nsview){
//_bTrace_("GLessThanViewController allocViewController",true);
GLessThanViewController *ctrlr;
NSAutoreleasePool       *localPool;
NSView                  *ctnrview=(NSView*)nsview;
NSPoint                 o;

    localPool=[[NSAutoreleasePool alloc] init];
    ctrlr=[GLessThanViewController allocWithNibNamed:@"View"
                                            class:[GLessThanViewController class]];
    
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
                         double value,
                         char* unit){
//_bTrace_("GLessThanViewController setDataToController",true);
GLessThanViewController *controller=(GLessThanViewController*)ctrlr;
NSAutoreleasePool       *localPool;
    
    localPool=[[NSAutoreleasePool alloc] init];
    [controller setValue:value unit:unit];
    [localPool release];
}

// ---------------------------------------------------------------------------
//
// ------------
double getDataFromController(void* ctrlr){
//_bTrace_("GLessThanViewController getDataFromController",true);
GLessThanViewController *controller=(GLessThanViewController*)ctrlr;
NSAutoreleasePool       *localPool;
    
    localPool=[[NSAutoreleasePool alloc] init];
double  val=[controller getValue];
    [localPool release];
    return val;
}

// ---------------------------------------------------------------------------
//
// ------------
void releaseViewController(void* ctrlr){
//_bTrace_("GLessThanViewController releaseViewController",true);
GLessThanViewController *controller=(GLessThanViewController*)ctrlr;
NSAutoreleasePool       *localPool;
    
    localPool=[[NSAutoreleasePool alloc] init];
    [[controller view] removeFromSuperview];
    [controller release];
    [localPool release];
}
