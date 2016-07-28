//----------------------------------------------------------------------------
// File : ShortCutsWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap shortcuts window controller
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
// 29/02/2016 creation.
//----------------------------------------------------------------------------

#import "ShortCutsWindowController.h"
#import "bXMapShortCuts.h" 
#import "CocoaStuff.h" 

#import <mox_intf/NSUIUtils.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation ShortCutsWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[ShortCutsWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[ShortCutsWindowController awakeFromNib]",true);
    _curk=0;
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[ShortCutsWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseGender:(id)sender{
//_bTrace_("[ShortCutsWindowController doChooseGender]",true);
    [_fcttbl reloadData];
    [self checkApply];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doApply:(id)sender{
//_bTrace_("[ShortCutsWindowController doApply]",true);
bXMapShortCuts*	ext=(bXMapShortCuts*)_ext;
shortcut_prm    p;
char            val[256];
int             fld=[_fcttbl selectedRow];
    if(fld<0){
        return;
    }
    switch([_gndpop indexOfSelectedItem]){
        case 0:
            ext->getxmap().get(fld+1,&p);
            break;
        case 1:
            ext->getxbox().get(fld+1,&p);
            break;
        case 2:
            ext->getscrp().get(fld+1,&p);
            break;
        case 3:
            ext->getmacr().get(fld+1,&p);
            break;
        default:
            return;
    }
    
    p.modi=0;
    p.key=_curk;
    if(p.key==51){
        p.key=0;
    }
    p.inmenu=false;
    
    NSTextFieldGetValue(_keytxt,val,sizeof(val)-1);
    if(val[0]!=0){
        if([_shtbtn intValue]){
            p.modi|=shiftKey;
        }
        if([_ctrbtn intValue]){
            p.modi|=controlKey;
        }
        if([_altbtn intValue]){
            p.modi|=optionKey;
        }
        if([_cmdbtn intValue]){
            p.modi|=cmdKey;
        }
    }
    p.code=val[0];
    switch([_gndpop indexOfSelectedItem]){
        case 0:
            ext->getxmap().put(fld+1,&p);
            break;
        case 1:
            ext->getxbox().put(fld+1,&p);
            break;
        case 2:
            ext->getscrp().put(fld+1,&p);
            break;
        case 3:
            ext->getmacr().put(fld+1,&p);
            break;
        default:
            return;
    }

    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doUpdate:(id)sender{
//_bTrace_("[ShortCutsWindowController doUpdate]",true);
    [self checkApply];
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateUI{
//_bTrace_("[ShortCutsWindowController updateUI]",true);
int fld=[_fcttbl selectedRow];
    if(fld<0){
        [_keytxt setStringValue:@""];
        [_numlbl setStringValue:@""];
        [_shtbtn setIntValue:0];
        [_altbtn setIntValue:0];
        [_ctrbtn setIntValue:0];
        [_cmdbtn setIntValue:0];
        
        [_keytxt setEnabled:NO];
        [_numlbl setEnabled:NO];
        [_shtbtn setEnabled:NO];
        [_altbtn setEnabled:NO];
        [_ctrbtn setEnabled:NO];
        [_cmdbtn setEnabled:NO];
        [_appbtn setEnabled:NO];
    }
    else{
bXMapShortCuts* ext=(bXMapShortCuts*)_ext;
shortcut_prm	p;
char            str[32];
        switch([_gndpop indexOfSelectedItem]){
            case 0:
                ext->getxmap().get(fld+1,&p);
                break;
            case 1:
                ext->getxbox().get(fld+1,&p);
                break;
            case 2:
                ext->getscrp().get(fld+1,&p);
                break;
            case 3:
                ext->getmacr().get(fld+1,&p);
                break;
            default:
                return;
        }

        [_keytxt setEnabled:YES];
        [_numlbl setEnabled:YES];
        [_shtbtn setEnabled:YES];
        [_altbtn setEnabled:YES];
        [_ctrbtn setEnabled:YES];
        [_cmdbtn setEnabled:YES];

        str[1]=0;
        str[0]=p.code;
        [_keytxt setCharValue:str];
        
        if((p.code==0)&&(p.key==0)){
            sprintf(str,"");
        }
        else if(p.code==0){
            sprintf(str,"/%d",(int)p.key);
        }
        else if(p.key==0){
            sprintf(str,"%c/",p.code);
        }
        else{
            sprintf(str,"%c/%d",p.code,(int)p.key);
        }
        [_numlbl setCharValue:str];
        
        [_shtbtn setIntValue:(p.modi&shiftKey)!=0];
        [_altbtn setIntValue:(p.modi&optionKey)!=0];
        [_ctrbtn setIntValue:(p.modi&controlKey)!=0];
        [_cmdbtn setIntValue:(p.modi&cmdKey)!=0];

        [self checkApply];
    }
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)checkApply{
//_bTrace_("[ShortCutsWindowController checkApply]",true);
bXMapShortCuts* ext=(bXMapShortCuts*)_ext;
UInt32          xtrn;
UInt32          modi=0;
bool            b;
char            val[256];
BOOL            good=NO;
shortcut_prm    p;
int             fct=[_fcttbl selectedRow];
    if(fct<0){
        [self updateUI];
        return;
    }
    switch([_gndpop indexOfSelectedItem]){
        case 0:
            ext->getxmap().get(fct+1,&p);
            break;
        case 1:
            ext->getxbox().get(fct+1,&p);
            break;
        case 2:
            ext->getscrp().get(fct+1,&p);
            break;
        case 3:
            ext->getmacr().get(fct+1,&p);
            break;
        default:
            return;
    }
    
    if([_shtbtn intValue]){
        modi|=shiftKey;
    }
    if([_ctrbtn intValue]){
        modi|=controlKey;
    }
    if([_altbtn intValue]){
        modi|=optionKey;
    }
    if([_cmdbtn intValue]){
        modi|=cmdKey;
    }
    NSTextFieldGetValue(_keytxt,val,sizeof(val)-1);
    
    if(p.inmenu){
        good=NO;
    }
    else if((strlen(val)==0)&&(modi==0)){
        good=(val[0]!=p.code)&&(p.key!=0)&&(p.modi!=0);
    }
    else if((strlen(val)!=0)&&(modi!=0)){
        for(;;){
//_tm_("search for modi="+(int)modi+" key="+(int)_curk+" code="+val[0]);
            xtrn=ext->scan_array(ext->getxmap(),val[0],_curk,modi,&b);
            if(xtrn){
//_tm_("found in xmap "+(int*)&xtrn);
                break;
            }
            xtrn=ext->scan_array(ext->getxbox(),val[0],_curk,modi,&b);
            if(xtrn){
//_tm_("found in xbox "+(int*)&xtrn);
                break;
            }
            xtrn=ext->scan_array(ext->getscrp(),val[0],_curk,modi,&b);
            if(xtrn){
//_tm_("found in srcp "+(int*)&xtrn);
                break;
            }
            xtrn=ext->scan_array(ext->getmacr(),val[0],_curk,modi,&b);
            if(xtrn){
//_tm_("found in macr "+(int*)&xtrn);
                break;
            }
//_tm_("not found");
//_tm_("(!b)="+(int)(!b));
//_tm_("(modi!=p.modi)="+(int)(modi!=p.modi));
//_tm_("(_curk!=p.key)="+(int)(_curk!=p.key)+" - "+(int)_curk+"/"+(int)p.key);
//_tm_("(val[0]!=p.code)="+(int)(val[0]!=p.code)+" - "+val[0]+"/"+p.code);
            good=(!b)&&((modi!=p.modi)||(_curk!=p.key)||(val[0]!=p.code));
            break;
        }
    }
    else{
        good=NO;
    }

    [_appbtn setEnabled:good];
}

#pragma mark ---- Gestion TableView ----
// ---------------------------------------------------------------------------
// 
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
bXMapShortCuts*     ext=(bXMapShortCuts*)_ext;
    switch([_gndpop indexOfSelectedItem]){
        case 0:
            return ext->getxmap().count();
            break;
        case 1:
            return ext->getxbox().count();
            break;
        case 2:
            return ext->getscrp().count();
            break;
        case 3:
            return ext->getmacr().count();
            break;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(id)	tableView:(NSTableView*)aTableView 
		objectValueForTableColumn:(NSTableColumn*)aTableColumn 
		row:(NSInteger)rowIndex{	
bXMapShortCuts* ext=(bXMapShortCuts*)_ext;
shortcut_prm	p;
    
    switch([_gndpop indexOfSelectedItem]){
        case 0:
            ext->getxmap().get(rowIndex+1,&p);
            break;
        case 1:
            ext->getxbox().get(rowIndex+1,&p);
            break;
        case 2:
            ext->getscrp().get(rowIndex+1,&p);
            break;
        case 3:
            ext->getmacr().get(rowIndex+1,&p);
            break;
        default:
            return nil;
    }
	return [NSString stringWithCString:p.name encoding:NSMacOSRomanStringEncoding];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)tableViewSelectionDidChange:(NSNotification*)notification{
long fct=[_fcttbl selectedRow];
    if(fct<0){
        [self updateUI];
        return;
    }

bXMapShortCuts* ext=(bXMapShortCuts*)_ext;
shortcut_prm	p;
    
    p.inmenu=true;
    switch([_gndpop indexOfSelectedItem]){
        case 0:
            ext->getxmap().get(fct+1,&p);
            break;
        case 1:
            ext->getxbox().get(fct+1,&p);
            break;
        case 2:
            ext->getscrp().get(fct+1,&p);
            break;
        case 3:
            ext->getmacr().get(fct+1,&p);
            break;
        default:
            return nil;
    }
    if(!p.inmenu){
        _curk=p.key;
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)controlTextDidChange:(NSNotification*)notification{
//_bTrace_("[ShortCutsWindowController controlTextDidChange]",false);
    _curk=[[NSApp currentEvent] keyCode];
//_tm_((int)_curk);
char    val[256];
    NSTextFieldGetValue(_keytxt,val,sizeof(val)-1);
    if(strlen(val)>1){
        val[1]=0;
    }
    strupper(val);
    [_keytxt setCharValue:val];
    [self checkApply];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapShortCuts* ext,
					  long* code){
ShortCutsWindowController	*controller;
NSAutoreleasePool			*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[ShortCutsWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
