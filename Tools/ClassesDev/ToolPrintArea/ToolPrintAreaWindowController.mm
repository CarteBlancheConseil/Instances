//----------------------------------------------------------------------------
// File : ToolPrintAreaWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Tool PrintArea window controller
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
// 27/03/2017 creation.
//----------------------------------------------------------------------------

#import "ToolPrintAreaWindowController.h"
#import "bToolPrintArea.h"
#import "CocoaStuff.h"
#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/NSUIUtils.h>
#import <mox_intf/ext_utils.h>
#import <std_ext/bXMapStdIntf.h>
#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
//
// ------------

// ---------------------------------------------------------------------------
// 
// ------------
@implementation ToolPrintAreaWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[ToolPrintAreaWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[ToolPrintAreaWindowController awakeFromNib]",true);
    [super awakeFromNib];
    
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericUnit*       u=gapp->distMgr()->get();
bToolPrintArea*     ext=(bToolPrintArea*)_ext;
char                val[256];
    
    u->short_name(val);
    [_orx_unt setCharValue:val];
    [_ory_unt setCharValue:val];
    [_gwd_unt setCharValue:val];
    [_ght_unt setCharValue:val];

ivx_rect    vxr=ext->get_area();
i2dvertex	ivxa={vxr.left,vxr.top};
i2dvertex	ivxb={vxr.right,vxr.bottom};
d2dvertex	dvxa,dvxb;
    
    gapp->locConverter()->convert(&dvxa,&ivxa);
    gapp->locConverter()->convert(&dvxb,&ivxb);

    [_orx_txt setDoubleValue:dvxa.x];
    [_ory_txt setDoubleValue:dvxa.y];

    NSPopupButtonRemoveAllItems(_psz_pop);
    for(int i=0;i<_nppr;i++){
        NSPopupButtonAddMenuItemValue(_psz_pop,ppr[i].name);
    }

    [_shw_chk setIntValue:ext->get_draw()];
    [_hov_mtx selectCellAtRow:ext->get_pprnat()-1 column:0];
    [_psz_pop selectItemAtIndex:ext->get_pprkind()-1];
    [_knd_pop selectItemAtIndex:ext->get_sizekind()-1];

    switch([_knd_pop indexOfSelectedItem]){
        case 0:
            [self putAsGeometry];
            break;
        case 1:
            [self putAsPixel];
           break;
        case 2:
            [self putAsCustomPaperSize];
            break;
        case 3:
            break;
    }
    [_are_viw selectTabViewItemAtIndex:[_knd_pop indexOfSelectedItem]];
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)putAsGeometry{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bToolPrintArea*     ext=(bToolPrintArea*)_ext;
ivx_rect            vxr=ext->get_area();
i2dvertex           ivxa={vxr.left,vxr.top};
i2dvertex           ivxb={vxr.right,vxr.bottom};
d2dvertex           dvxa,dvxb;
    
    gapp->locConverter()->convert(&dvxa,&ivxa);
    gapp->locConverter()->convert(&dvxb,&ivxb);
    
    [_gwd_txt setDoubleValue:(dvxb.x-dvxa.x)];
    [_ght_txt setDoubleValue:(dvxa.y-dvxb.y)];
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)putAsPixel{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bToolPrintArea*     ext=(bToolPrintArea*)_ext;
ivx_rect            vxr=ext->get_area();
i2dvertex           ivxa={vxr.left,vxr.top};
i2dvertex           ivxb={vxr.right,vxr.bottom};
CGPoint             pa,pb;
    
    gapp->locConverter()->convert(&pa,&ivxa);
    gapp->locConverter()->convert(&pb,&ivxb);
    
    [_pwd_txt setDoubleValue:(pb.x-pa.x)];
    [_pht_txt setDoubleValue:(pa.y-pb.y)];
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)putAsCustomPaperSize{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bToolPrintArea*     ext=(bToolPrintArea*)_ext;
ivx_rect            vxr=ext->get_area();
i2dvertex           ivxa={vxr.left,vxr.bottom};
i2dvertex           ivxb={vxr.right,vxr.top};
CGPoint             pa,pb;
    
    gapp->locConverter()->convert(&pa,&ivxa);
    gapp->locConverter()->convert(&pb,&ivxb);
    
    [_cwd_txt setDoubleValue:(pb.x-pa.x)*(2.54/72.0)];
    [_cht_txt setDoubleValue:(pb.y-pa.y)*(2.54/72.0)];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)validDialog:(id)sender{
_bTrace_("[ToolPrintAreaWindowController validDialog]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bToolPrintArea*     ext=(bToolPrintArea*)_ext;
ivx_rect            vxr=ext->get_area();
i2dvertex           ivxa={vxr.left,vxr.bottom};
i2dvertex           ivxb={vxr.right,vxr.top};
d2dvertex           dvxa,dvxb;
CGPoint             pa,pb;
   
    dvxa.x=[_orx_txt doubleValue];
    dvxa.y=[_ory_txt doubleValue];

    switch([_knd_pop indexOfSelectedItem]){
        case 0:
            dvxb.x=dvxa.x+[_gwd_txt doubleValue];
            dvxb.y=dvxa.y-[_ght_txt doubleValue];
            break;
        case 1:
            gapp->locConverter()->convert(&pa,&dvxa);
            pb.x=pa.x+[_pwd_txt doubleValue];
            pb.y=pa.y-[_pht_txt doubleValue];
            gapp->locConverter()->convert(&dvxb,&pb);
            break;
        case 2:
            gapp->locConverter()->convert(&pa,&dvxa);
            pb.x=pa.x+((72.0/2.54)*[_cwd_txt doubleValue]);
            pb.y=pa.y-((72.0/2.54)*[_cht_txt doubleValue]);
            gapp->locConverter()->convert(&dvxb,&pb);
            break;
        case 3:
            gapp->locConverter()->convert(&pa,&dvxa);
            if([_hov_mtx selectedRow]==0){
                pb.x=pa.x+((72.0/2.54)*ppr[[_psz_pop indexOfSelectedItem]].w);
                pb.y=pa.y-((72.0/2.54)*ppr[[_psz_pop indexOfSelectedItem]].h);
            }
            else{
                pb.x=pa.x+((72.0/2.54)*ppr[[_psz_pop indexOfSelectedItem]].h);
                pb.y=pa.y-((72.0/2.54)*ppr[[_psz_pop indexOfSelectedItem]].w);
            }
            gapp->locConverter()->convert(&dvxb,&pb);
            break;
    }
    
    gapp->locConverter()->convert(&ivxa,&dvxa);
    vxr.left=ivxa.h;
    vxr.top=ivxa.v;
    gapp->locConverter()->convert(&ivxb,&dvxb);
    vxr.right=ivxb.h;
    vxr.bottom=ivxb.v;
    
    ext->set_area(vxr);
    ext->set_draw([_shw_chk intValue]);
    ext->set_pprnat([_hov_mtx selectedRow]+1);
    ext->set_pprkind([_psz_pop indexOfSelectedItem]+1);
    ext->set_sizekind([_knd_pop indexOfSelectedItem]+1);
    
    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doChooseMethod:(id)sender{
_bTrace_("[ToolPrintAreaWindowController doChooseMethod]",true);
    [_are_viw selectTabViewItemAtIndex:[_knd_pop indexOfSelectedItem]];
    switch([_knd_pop indexOfSelectedItem]){
        case 0:
            [self putAsGeometry];
            break;
        case 1:
            [self putAsPixel];
            break;
        case 2:
            [self putAsCustomPaperSize];
            break;
        case 3:
            break;
    }
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bToolPrintArea* ext,
					  long* code){
ToolPrintAreaWindowController	*controller;
NSAutoreleasePool               *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];
    controller=[[ToolPrintAreaWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
