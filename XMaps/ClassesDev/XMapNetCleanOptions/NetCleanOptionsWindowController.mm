//----------------------------------------------------------------------------
// File : NetCleanOptionsWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap clone detector window controller
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
// 08/03/2016 creation.
//----------------------------------------------------------------------------

#import "NetCleanOptionsWindowController.h"
#import "bXMapNetCleanOptions.h" 
#import "CocoaStuff.h" 
#import <MacMapSuite/bTrace.h> 
#import <mox_intf/bGenericMacMapApp.h> 
#import <mox_intf/Carb_Utils.h> 
#import <mox_intf/bEventLog.h>
#import <mox_intf/ext_utils.h>
#import <mox_intf/xmldesc_utils.h> 
#import <mox_intf/NSUIUtils.h> 
#import <mox_intf/mm_messages.h>
#import <mox_intf/mm_errors.h>
#import <mox_intf/bStdAlert.h>
#import <std_ext/bXMapStdIntf.h>


// ---------------------------------------------------------------------------
// 
// ------------
@implementation NetCleanOptionsWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[NetCleanOptionsWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[NetCleanOptionsWindowController awakeFromNib]",true);
bGenericMacMapApp*      gapp=(bGenericMacMapApp*)_ext->getapp();
char                    msg[__MESSAGE_STRING_LENGTH_MAX__];

    NSPopupButtonRemoveAllItems(_ndspop);
    NSPopupButtonPopulateWithTypes(_ndspop,gapp,kBaseKindPoint,0);

    NSPopupButtonRemoveAllItems(_edspop);
    NSPopupButtonPopulateWithTypes(_edspop,gapp,kBaseKindPolyline,0);

    [_intpop removeAllItems];
    NSPopupButtonPopulateWithTypes(_intpop,gapp,kBaseKindPoint,0);
    [_inspop removeAllItems];

    [_brtpop removeAllItems];
    NSPopupButtonPopulateWithTypes(_brtpop,gapp,kBaseKindPoint,0);
    [_brspop removeAllItems];

    
bStdXMap*            netext=(bStdXMap*)(void*)gapp->xmapMgr()->find('NtCl');
    if(!netext){
        b_message_string(kXMapNetCleanOptionPluginNotFound,msg,_ext->getbundle(),1);
bAlertStop	alrt(msg,"");
        return;
    }
netcleancfg_prm	prm;

    prm.nodes=new bArray(sizeof(bGenericType*));
    prm.edges=new bArray(sizeof(bGenericType*));

    netext->process(kExtProcessCallGetData,&prm);

bGenericType*	tp;

    for(long i=1;i<=prm.nodes->count();i++){
        prm.nodes->get(i,&tp);
        if(tp){
            [[_ndspop itemAtIndex:tp->index()] setState:NSOnState];
        }
    }
    for(long i=1;i<=prm.edges->count();i++){
        prm.edges->get(i,&tp);
        if(tp){
            [[_edspop itemAtIndex:tp->index()] setState:NSOnState];
        }
    }
    
    delete prm.nodes;
    delete prm.edges;
    
    for(long i=1;i<[_ndspop numberOfItems];i++){
        [[_intpop itemAtIndex:i-1] setEnabled:[[_ndspop itemAtIndex:i] state]];
        [[_brtpop itemAtIndex:i-1] setEnabled:[[_ndspop itemAtIndex:i] state]];
    }

    if(prm.tnod){
        [_intpop selectItemAtIndex:prm.tnod->index()-1];
        NSPopupButtonPopulateWithConstraints(_inspop,prm.tnod,kOBJ_SubType_,1);
        [_inspop selectItemAtIndex:prm.stnod-1];
    }
    [_inntxt setCharValue:prm.name];
    
    if(prm.tbdg){
        [_brtpop selectItemAtIndex:prm.tbdg->index()-1];
        NSPopupButtonPopulateWithConstraints(_brspop,prm.tbdg,kOBJ_SubType_,1);
        [_brspop selectItemAtIndex:prm.stbdg-1];
    }

    [_indtxt setDoubleValue:prm.dnod];
    [_brdtxt setDoubleValue:prm.dbdg];
    
bGenericUnit*   u=gapp->distMgr()->get();
    u->short_name(msg);
    [_inulbl setCharValue:msg];
    [_brulbl setCharValue:msg];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[NetCleanOptionsWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bGenericMacMapApp*      gapp=(bGenericMacMapApp*)_ext->getapp();
char                    msg[__MESSAGE_STRING_LENGTH_MAX__];
bStdXMap*               netext=(bStdXMap*)(void*)gapp->xmapMgr()->find('NtCl');
    if(!netext){
        b_message_string("",msg,_ext->getbundle(),1);
bAlertStop	alrt(msg,"");
        return;
    }
    netcleancfg_prm	prm;
    
    prm.nodes=new bArray(sizeof(bGenericType*));
    prm.edges=new bArray(sizeof(bGenericType*));
    
bGenericType*	tp;
    
    for(long i=1;i<[_ndspop numberOfItems];i++){
        if([[_ndspop itemAtIndex:i] state]==NSOnState){
            tp=gapp->typesMgr()->get(i);
        }
        else{
            tp=NULL;
        }
        prm.nodes->add(&tp);
        if([[_edspop itemAtIndex:i] state]==NSOnState){
            tp=gapp->typesMgr()->get(i);
        }
        else{
            tp=NULL;
        }
        prm.edges->add(&tp);
    }
    
    prm.tnod=gapp->typesMgr()->get([_intpop indexOfSelectedItem]+1);
    prm.stnod=[_inspop indexOfSelectedItem]+1;
    NSTextFieldGetValue(_inntxt, prm.name,sizeof(prm.name)-1);
    prm.tbdg=gapp->typesMgr()->get([_brtpop indexOfSelectedItem]+1);
    prm.stbdg=[_brspop indexOfSelectedItem]+1;
    
    prm.dnod=[_indtxt doubleValue];
    prm.dbdg=[_brdtxt doubleValue];
    
    netext->process(kExtProcessCallSetData,&prm);

    delete prm.nodes;
    delete prm.edges;

    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doCheckNodeTypes:(id)sender{
_bTrace_("[NetCleanOptionsWindowController doCheckNodeTypes]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*       tp;
    
    [[_ndspop selectedItem] setState:(![[_ndspop selectedItem] state])];
    for(long i=1;i<[_ndspop numberOfItems];i++){
        [[_intpop itemAtIndex:i-1] setEnabled:[[_ndspop itemAtIndex:i] state]];
        [[_brtpop itemAtIndex:i-1] setEnabled:[[_ndspop itemAtIndex:i] state]];
    }
    if([_intpop indexOfSelectedItem]<0){
        [_intpop selectItemAtIndex:[_ndspop indexOfSelectedItem]-1];
        [self doChooseIntersection:sender];
    }
    else if([[_ndspop itemAtIndex:[_intpop indexOfSelectedItem]+1] state]==NSOffState){
        [_intpop selectItemAtIndex:-1];
        [_inspop removeAllItems];
        for(long i=1;i<[_ndspop numberOfItems];i++){
            if([[_ndspop itemAtIndex:i] state]==NSOnState){
                [_intpop selectItemAtIndex:i-1];
                tp=gapp->typesMgr()->get(i);
                NSPopupButtonPopulateWithConstraints(_inspop,tp,kOBJ_SubType_,1);
                break;
            }
        }
    }
            
    if([_brtpop indexOfSelectedItem]<0){
        [_brtpop selectItemAtIndex:[_ndspop indexOfSelectedItem]-1];
        [self doChooseBridge:sender];
    }
    else if([[_ndspop itemAtIndex:[_brtpop indexOfSelectedItem]+1] state]==NSOffState){
        [_brtpop selectItemAtIndex:-1];
        [_brspop removeAllItems];
        for(long i=1;i<[_ndspop numberOfItems];i++){
            if([[_ndspop itemAtIndex:i] state]==NSOnState){
                [_brtpop selectItemAtIndex:i-1];
                tp=gapp->typesMgr()->get(i);
                NSPopupButtonPopulateWithConstraints(_brspop,tp,kOBJ_SubType_,1);
                break;
            }
        }
    }
   
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doCheckEdgeTypes:(id)sender{
_bTrace_("[NetCleanOptionsWindowController doCheckEdgeTypes]",true);
    [[_edspop selectedItem] setState:(![[_edspop selectedItem] state])];
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doChooseIntersection:(id)sender{
_bTrace_("[NetCleanOptionsWindowController doChooseIntersection]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*       tp=gapp->typesMgr()->get([_intpop indexOfSelectedItem]+1);
    
    [_inspop removeAllItems];
    if(tp){
        NSPopupButtonPopulateWithConstraints(_inspop,tp,kOBJ_SubType_,1);
        [_inspop selectItemAtIndex:0];
    }
    else{
        [_inspop selectItemAtIndex:-1];
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doChooseBridge:(id)sender{
_bTrace_("[NetCleanOptionsWindowController doChooseBridge]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*       tp=gapp->typesMgr()->get([_intpop indexOfSelectedItem]+1);
    
    [_brspop removeAllItems];
    if(tp){
        NSPopupButtonPopulateWithConstraints(_brspop,tp,kOBJ_SubType_,1);
        [_brspop selectItemAtIndex:0];
    }
    else{
        [_brspop selectItemAtIndex:-1];
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)updateUI{
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapNetCleanOptions* ext,
					  long* code){
NetCleanOptionsWindowController    *controller;
NSAutoreleasePool           *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[NetCleanOptionsWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
