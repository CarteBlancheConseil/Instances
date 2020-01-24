//----------------------------------------------------------------------------
// File : CalcWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Calcs XMapBox window controller
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
// 21/01/2015 creation.
//----------------------------------------------------------------------------

#import "CalcWindowController.h"
#import "bXBoxCalc.h"
#import "CocoaStuff.h"

#import <mox_intf/endian.h>
#import <mox_intf/bGenericCalc.h>

#import <MacMapSuite/bTrace.h>
#import <MacMapStats/MacMapStats.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation CalcPanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation CalcWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[CalcWindowController init]",true);
	self=[super init];
	if(self){
	}
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[CalcWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
    [super awakeFromNib];
bGenericMacMapApp* gapp=(bGenericMacMapApp*)_ext->getapp();
    _mgr=gapp->calcMgr();
    _xsign=kXMLSubClassExtCalc;

bGenericExt* x=gapp->xmapMgr()->find('ClcE');
    if(x==NULL){
        [_add_btn setEnabled:NO];
        [_edt_btn setEnabled:NO];
    }
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[CalcWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doAdd:(id)sender{
_bTrace_("[CalcWindowController doAdd]",true);
bGenericMacMapApp*
    gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericExt* x=gapp->xmapMgr()->find('ClcE');
    if(x==NULL){
        return;
    }
    x->edit(NULL);
    [_mgr_viw reloadData];
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doEdit:(id)sender{
_bTrace_("[CalcWindowController doEdit]",true);
NSInteger rowNumber=[_mgr_viw selectedRow];
_tm_(rowNumber);
    if(rowNumber==-1){
        return;
    }
    
bGenericMacMapApp*
    gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericExt* ext=_mgr->get(rowNumber+1);
    if(ext==NULL){
        return;
    }
bGenericExt* x=gapp->xmapMgr()->find('ClcE');
    if(x==NULL){
        return;
    }
    x->edit(ext);
    [_mgr_viw reloadData];
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
//
// -----------
-(void)updateUI{
bGenericMacMapApp*
    gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericExt* ext=gapp->xmapMgr()->find('ClcE');
    
NSInteger rowNumber=[_mgr_viw selectedRow];
    [_rmv_btn setEnabled:(rowNumber>-1)];
    [_edt_btn setEnabled:(rowNumber>-1)&&(ext!=NULL)];
    [_dup_btn setEnabled:(rowNumber>-1)];
}

#pragma mark ---- Gestion TableView ----
// ---------------------------------------------------------------------------
//
// ------------
-(void)doubleClick:(id)object{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
    
    if(gapp->selMgr()->count()>1){
NSInteger           rowNumber=[_mgr_viw clickedRow];
bArray				arr(*(gapp->selMgr()->elements()));
MMsMatrix*			mx=MMsMatrixAlloc(arr.count(),1);
bGenericCalc*		clc=(bGenericCalc*)(void*)_mgr->get(rowNumber+1);
        if(!clc){
            return;
        }
bGenericGeoElement* o;
bStdDBValue*		val;
double				d;
        
        for(long i=1;i<=arr.count();i++){
            arr.get(i,&o);
            val=clc->solve(o);
            if(!val){
                break;
            }
            val->get(&d);
            MMsSetDouble(mx,i,1,d);
            delete val;
        }
        
        switch([_itr_pop indexOfSelectedItem]+1){
            case 1:
                d=MMsSum(1,mx);
                break;
            case 2:
                d=MMsAverage(1,mx);
                break;
            case 3:
                d=MMsMedian(1,mx);
                break;
            case 4:
                d=MMsVariance(1,mx);
                break;
            case 5:
                d=MMsStdDeviation(1,mx);
                break;
            case 6:
                MMsMatrixSort(mx);
                d=MMsGetDouble(mx,1,1);
                break;
            case 7:
                MMsMatrixSort(mx);
                d=MMsGetDouble(mx,mx->nl,1);
                break;
            default:
                d=nan("0");
                break;
        }
        MMsMatrixFree(mx);
        
char	s[256];
        sprintf(s,"%f",d);
        WriteMessage(gapp,s);
    }
    else{
        [super doubleClick:object];
    }
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

#pragma mark ---- CPP/Carbon Entry Point ----
// ---------------------------------------------------------------------------
// 
// ------------
void* initializeCocoa(void* gapp, 
					  void* ext) {
CalcWindowController	*controller;
NSAutoreleasePool			*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[CalcWindowController alloc] init];
    [controller setExt:(bStdNSXBox*)ext];
    [localPool release];
    return((void*)controller);
}

