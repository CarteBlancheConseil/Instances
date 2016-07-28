//----------------------------------------------------------------------------
// File : PrefsWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap preferences window controller
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
// 25/02/2016 creation.
//----------------------------------------------------------------------------

#import "PrefsWindowController.h"
#import "bXMapPrefs.h"
#import "CocoaStuff.h"

#import <mox_intf/xmldesc_utils.h>
#import <mox_intf/NSUIUtils.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>
#import <MacMapSuite/bStdProj.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation PrefsWindowController
// ---------------------------------------------------------------------------
//
// ------------
-(id)initWithExt:(bStdExt*)ext{
_bTrace_("[ToolMenuConfigWindowController initWithExt]",true);
    self=[super initWithExt:ext];
    if(self){
        _tbl=wprj_gettable();
        if(_tbl==NULL){
_te_("GetProjTable failed");
        }
    }
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[PrefsWindowController dealloc]",true);
_tm_((void*)self);
    if(_tbl){
        wtbl_free(_tbl);
        _tbl=NULL;
    }
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[PrefsWindowController awakeFromNib]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
    NSPopupButtonRemoveAllItems(_untpop);
    NSPopupButtonPopulateWithUnits(_untpop,gapp,gapp->distMgr()->get_current());
   
bGenericUnit*	u=gapp->document()->dist_resolution_unit();
char			un[256];
char            str[256];
    u->short_name(un);
    sprintf(str,"%.6f %s",gapp->document()->dist_resolution(),un);
    [_reslbl setCharValue:str];

    [_dectxt setIntValue:gapp->document()->dist_pref_digits()];

d2dvertex	origin=gapp->document()->get_origin();
    [_orxtxt setDoubleValue:origin.x];
    [_orytxt setDoubleValue:origin.y];

    [_epgtxt setIntValue:gapp->document()->srid()];
int tmp;
    for(long i=1;i<=_tbl->CountRecords();i++){
        _tbl->ReadVal(i,1,&tmp);
        if([_epgtxt intValue]==tmp){
            [_prjtbl scrollRowToVisible:i-1];
            [_prjtbl selectRowIndexes:[NSIndexSet indexSetWithIndex:i-1] byExtendingSelection:NO];
            break;
        }
    }
    if(gapp->document()->srid()>0){
        [_prjtbl setEnabled:NO];
        [_epgtxt setEnabled:NO];
    }

double  color[4];
    for(long i=1;i<=4;i++){
        color[i-1]=1;
    }
bGenericXMLBaseElement	*root,*elt;
    if(gapp->document()->readTree(&root,kBackgroundSignature,kBackgroundConfigName)){
        for(long i=1;i<=4;i++){
            elt=gapp->classMgr()->NthElement(root,i,"float");
            if(elt){
                elt->getvalue(str);
                color[i-1]=matof(str);
            }
            else{
                break;
            }
        }
        gapp->classMgr()->ReleaseXMLInstance(root);
    }
    [_bkgclr setColor:[NSColor colorWithDeviceRed:color[0]
                                             green:color[1]
                                              blue:color[2]
                                             alpha:color[3]]];


    [_savchk setIntValue:gapp->document()->get_save_objstate()];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[PrefsWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
    
    gapp->distMgr()->set_current([_untpop indexOfSelectedItem]+1);
    
    gapp->document()->set_dist_pref_digits([_dectxt intValue]);

    if(gapp->document()->srid()==-1){
        if([_epgtxt intValue]>0){
            gapp->document()->set_srid([_epgtxt intValue]);
        }
    }
    
d2dvertex	origin;
    origin.x=[_orxtxt doubleValue];
    origin.y=[_orytxt doubleValue];
    gapp->document()->set_origin(origin);

    
NSColor*    clr=[[_bkgclr color] colorUsingColorSpaceName:@"NSDeviceRGBColorSpace"];
bArray		arr(sizeof(xmlelt));
    
    add_cdesc(arr,0,"param","");
    add_cdesc(arr,1,"version","3.0.0");
    add_ddesc(arr,1,"float",[clr redComponent],2);
    add_ddesc(arr,1,"float",[clr greenComponent],2);
    add_ddesc(arr,1,"float",[clr blueComponent],2);
    add_ddesc(arr,1,"float",[clr alphaComponent],2);
   
bGenericXMLBaseElement* root=gapp->classMgr()->ParseXMLDescriptors(&arr);
    free_descs(arr);
    if(!gapp->document()->writeTree(root,kBackgroundSignature,kBackgroundConfigName)){
    }
    gapp->classMgr()->ReleaseXMLInstance(root);
    gapp->layersMgr()->BackgroundChanged();

    gapp->document()->set_save_objstate([_savchk intValue]);
    
    [super validDialog:sender];
}

#pragma mark ---- Gestion TableView ----
// -------------------------------------------------------------------------;--
//
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
    return _tbl->CountRecords();
}

// ---------------------------------------------------------------------------
//
// -----------
-(id)           tableView:(NSTableView*)aTableView
objectValueForTableColumn:(NSTableColumn*)aTableColumn
                      row:(NSInteger)rowIndex{
    if([[aTableColumn identifier] compare:@"epsgid"]==NSOrderedSame){
int     srid;
        _tbl->ReadVal(rowIndex+1,1,&srid);
        return [NSNumber numberWithInt:srid];
    }
    else if([[aTableColumn identifier] compare:@"projname"]==NSOrderedSame){
char    str[256];
        _tbl->ReadVal(rowIndex+1,2,str);
        return [NSString stringWithCString:str encoding:NSMacOSRomanStringEncoding];
    }
    return nil;
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)tableViewSelectionDidChange:(NSNotification*)notification{
int         srid;
    _tbl->ReadVal([_prjtbl selectedRow]+1,1,&srid);
bool		b;
bStdProj	p(srid,&b);
    if(b){
        if(p.is_latlong()){
            NSBeep();
           [_prjtbl deselectRow:[_prjtbl selectedRow]];
        }
        else if(srid!=[_epgtxt intValue]){
            [_epgtxt setIntValue:srid];
        }
    }
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)controlTextDidChange:(NSNotification*)notification{
long    srid=[_epgtxt intValue];
    if(srid>0){
bool		b;
bStdProj	p(srid,&b);
        if(b){
            if(p.is_latlong()){
                NSBeep();
            }
            else{
int             tmp;
                for(long i=1;i<=_tbl->CountRecords();i++){
                    _tbl->ReadVal(i,1,&tmp);
                    if(srid==tmp){
                        [_prjtbl scrollRowToVisible:i-1];
                        [_prjtbl selectRowIndexes:[NSIndexSet indexSetWithIndex:i-1] byExtendingSelection:NO];
                        break;
                    }
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapPrefs* ext,
					  long* code){
PrefsWindowController	*controller;
NSAutoreleasePool               *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[PrefsWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
