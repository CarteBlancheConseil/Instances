//----------------------------------------------------------------------------
// File : CalcEditorWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : MapCalculator window controller
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
// 16/03/2016 creation.
//----------------------------------------------------------------------------

#import "CalcEditorWindowController.h"
#import "bXMapCalcEditor.h" 
#import "CocoaStuff.h" 

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

#import <MacMapSuite/bTrace.h>


// ---------------------------------------------------------------------------
//
// ------------
@implementation CalcObjView

// ---------------------------------------------------------------------------
//
// ------------
-(id)initWithFrame:(NSRect)frameRect{
    if((self=[super initWithFrame:frameRect])!=nil){
        _origin.x=5;
        _origin.y=NSMidY(frameRect)-frameRect.origin.y;
    }
    return self;
}

// ---------------------------------------------------------------------------
//
// ------------
-(BOOL)acceptsFirstResponder{
    return(YES);
}

// ---------------------------------------------------------------------------
//
// -----------
-(BOOL)isFlipped{
    return YES;
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)mouseDown:(NSEvent*)event{
CalcEditorWindowController* ctrlr=(CalcEditorWindowController*)[[self window] windowController];
bXMapCalcCell*              root=[ctrlr root];
    if(root){
CGPoint cgp=NSPointToCGPoint([self convertPoint:[event locationInWindow] fromView:nil]);
        root->click(cgp);
    }
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)mouseUp:(NSEvent*)event{
    [self setNeedsDisplay:YES];
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)mouseDragged:(NSEvent*)event{
    _origin.x+=[event deltaX];
    _origin.y+=[event deltaY];
    [self setNeedsDisplay:YES];
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)drawRect:(NSRect)rect{
    [NSGraphicsContext saveGraphicsState];

    [[NSColor whiteColor] set];
    NSRectFill(rect);
    
CalcEditorWindowController* ctrlr=(CalcEditorWindowController*)[[self window] windowController];
bXMapCalcCell*              root=[ctrlr root];
    if(root){
        root->draw((CGContextRef)[[NSGraphicsContext currentContext] graphicsPort],NSPointToCGPoint(_origin));
    }
    
    [NSGraphicsContext restoreGraphicsState];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end






// ---------------------------------------------------------------------------
// 
// ------------
@implementation CalcEditorWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[CalcEditorWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[CalcEditorWindowController awakeFromNib]",true);
bXMapCalcEditor*    ext=(bXMapCalcEditor*)_ext;
char                str[256];
    
    ext->get_name(str);
    [_namtxt setCharValue:str];
    [_rtkpop selectItemAtIndex:ext->get_kind()-1];
    
    switch(ext->get_kind()){
        case _char:
            [_rtkpop selectItemAtIndex:0];
            break;
        case _bool:
            [_rtkpop selectItemAtIndex:1];
            break;
        case _int:
            [_rtkpop selectItemAtIndex:2];
            break;
        case _double:
            [_rtkpop selectItemAtIndex:3];
            break;
        case _date:
            [_rtkpop selectItemAtIndex:4];
            break;
        case _time:
            [_rtkpop selectItemAtIndex:5];
            break;
        default:
            [_rtkpop selectItemAtIndex:0];
            break;
    }

    
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
    
    [_tpfpop removeAllItems];
    NSPopupButtonPopulateWithTypes(_tpfpop,gapp,kBaseNoKind,1);

    [self doChooseItemKind:self];
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[CalcEditorWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bXMapCalcEditor* ext=(bXMapCalcEditor*)_ext;
char            name[_values_length_max_];
    
    NSTextFieldGetValue(_namtxt,name,sizeof(name)-1);
    ext->set_name(name);    
    switch([_rtkpop indexOfSelectedItem]){
        case 0:
            ext->set_kind(_char);
            break;
        case 1:
            ext->set_kind(_bool);
            break;
        case 2:
            ext->set_kind(_int);
            break;
        case 3:
            ext->set_kind(_double);
            break;
        case 4:
            ext->set_kind(_date);
            break;
        case 5:
            ext->set_kind(_time);
            break;
    }
    
    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doChooseItemKind:(id)sender{
    [self updateUI];
    [_itmtbl reloadData];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doChooseType:(id)sender{
    [_itmtbl reloadData];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doDelete:(id)sender{
bXMapCalcEditor*    ext=(bXMapCalcEditor*)_ext;
bXMapCalcCell*      root=ext->get_root();
    if(root){
bXMapCalcCell*	slct=bXMapCalcCell::get_select();
        if(!slct){
            NSBeep();
        }
        else{
            if(slct->parent()){
bXMapCalcCell*	par=slct->parent();
                if(!par->remove(slct)){
                    NSBeep();
                }
            }
            else{
                root->select(false);
                delete root;
                ext->set_root(NULL);
            }
        }
    }
    else{
        NSBeep();
    }
    [self updateUI];
}

#pragma mark ---- TableView ----
// ---------------------------------------------------------------------------
//
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*		tp;
bArray				arr(sizeof(bGenericXMLBaseElement*));

    switch([_opkpop indexOfSelectedItem]){
        case 0:
            gapp->classMgr()->FindXMLInstanceBySubClass(arr,kXMLSubClassOperator);
            return arr.count();
            break;
        case 1:
            gapp->classMgr()->FindXMLInstanceBySubClass(arr,kXMLSubClassIterator);
            return arr.count();
            break;
        case 2:
            gapp->classMgr()->FindXMLInstanceBySubClass(arr,kXMLSubClassFunction);
            return arr.count();
            break;
        case 3:
            return gapp->varMgr()->count();
            break;
        case 4:
            tp=gapp->typesMgr()->get([_tpfpop indexOfSelectedItem]+1);
            if(tp){
                return tp->fields()->count()-kOBJ_Vertices_;
            }
            break;
        case 5:
            return gapp->calcMgr()->count();
            break;
        case 6:
            return gapp->macroMgr()->count();
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
bGenericMacMapApp*      gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*           tp;
bGenericXMLBaseElement*	elt;
bArray                  arr(sizeof(bGenericXMLBaseElement*));
char                    str[256]="";
    
    switch([_opkpop indexOfSelectedItem]){
        case 0:
            gapp->classMgr()->FindXMLInstanceBySubClass(arr,kXMLSubClassOperator);
            if(arr.get(rowIndex+1,&elt)){
                elt->getclassname(str);
            }
            break;
        case 1:
            gapp->classMgr()->FindXMLInstanceBySubClass(arr,kXMLSubClassIterator);
            if(arr.get(rowIndex+1,&elt)){
                elt->getclassname(str);
            }
            break;
        case 2:
            gapp->classMgr()->FindXMLInstanceBySubClass(arr,kXMLSubClassFunction);
            if(arr.get(rowIndex+1,&elt)){
                elt->getclassname(str);
            }
            break;
        case 3:
            gapp->varMgr()->ext_name(rowIndex+1,str);
            break;
        case 4:
            tp=gapp->typesMgr()->get([_tpfpop indexOfSelectedItem]+1);
            if(tp){
                tp->fields()->get_name(rowIndex+1+kOBJ_Vertices_,str);
            }
            break;
        case 5:
            gapp->calcMgr()->ext_name(rowIndex+1,str);
            break;
        case 6:
            gapp->macroMgr()->ext_name(rowIndex+1,str);
            break;
    }
    return [NSString stringWithCString:str encoding:NSMacOSRomanStringEncoding];
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)tableViewSelectionDidChange:(NSNotification*)notification{
    if([_itmtbl selectedRow]<0){
        return;
    }
bGenericMacMapApp*      gapp=(bGenericMacMapApp*)_ext->getapp();
bXMapCalcCell*			cell;
char					name[256];
bGenericXMLBaseElement*	elt;
bGenericType*			tp;
bArray					arr(sizeof(bGenericXMLBaseElement*));
    
    switch([_opkpop indexOfSelectedItem]){
        case 0:
            gapp->classMgr()->FindXMLInstanceBySubClass(arr,kXMLSubClassOperator);
            if(arr.get([_itmtbl selectedRow]+1,&elt)){
                elt->getclassname(name);
            }
            cell=new bXMapCalcCellOperator(gapp,name);
            break;
        case 1:
            gapp->classMgr()->FindXMLInstanceBySubClass(arr,kXMLSubClassIterator);
            if(arr.get([_itmtbl selectedRow]+1,&elt)){
                elt->getclassname(name);
            }
            cell=new bXMapCalcCellIterator(gapp,name);
            break;
        case 2:
            gapp->classMgr()->FindXMLInstanceBySubClass(arr,kXMLSubClassFunction);
            if(arr.get([_itmtbl selectedRow]+1,&elt)){
                elt->getclassname(name);
            }
            cell=new bXMapCalcCellFunction(gapp,name);
            break;
        case 3:
            gapp->varMgr()->ext_name([_itmtbl selectedRow]+1,name);
            cell=new bXMapCalcCellConstant(gapp,name);
            break;
        case 4:
            tp=gapp->typesMgr()->get([_tpfpop indexOfSelectedItem]+1);
            if(tp){
                tp->fields()->get_name([_itmtbl selectedRow]+1+kOBJ_Vertices_,name);
            }
            cell=new bXMapCalcCellField(gapp,name,tp);
            break;
        case 5:
            gapp->calcMgr()->ext_name([_itmtbl selectedRow]+1,name);
            cell=new bXMapCalcCellCalc(gapp,name);
            break;
        case 6:
            gapp->macroMgr()->ext_name([_itmtbl selectedRow]+1,name);
            cell=new bXMapCalcCellMacro(gapp,name);
            break;
    }
bXMapCalcEditor*    ext=(bXMapCalcEditor*)_ext;
bXMapCalcCell*      root=ext->get_root();
    if(root){
bXMapCalcCell*	slct=bXMapCalcCell::get_select();
        if(!slct){
            delete cell;
            NSBeep();
        }
        else{
            if(slct->parent()){
                slct=slct->parent();
                if(!slct->add(cell)){
                    delete cell;
                    NSBeep();
                }
                else{
                    cell->select(true);
                }
            }
            else if(slct->kind()==[_opkpop indexOfSelectedItem]+1){
                cell->set_left(slct->left());
                cell->set_right(slct->right());
                slct->set_left(NULL);
                slct->set_right(NULL);
                delete slct;
                root=cell;
                root->select(true);
                ext->set_root(root);
            }
        }
    }
    else{
        root=cell;
        root->select(true);
        ext->set_root(root);
    }

    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)controlTextDidChange:(NSNotification*)notification{
    [self updateUI];
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateUI{
    [_tpflbl setHidden:([_opkpop indexOfSelectedItem]!=4)];
    [_tpfpop setHidden:([_opkpop indexOfSelectedItem]!=4)];
    [_okbtn setEnabled:([[_namtxt stringValue] length]>0)&&([self root]!=NULL)];
    
    [_treviw setNeedsDisplay:YES];
}

// ---------------------------------------------------------------------------
//
// -----------
-(bXMapCalcCell*)root{
bXMapCalcEditor* ext=(bXMapCalcEditor*)_ext;
    return ext->get_root();
}


// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapCalcEditor* ext,
					  long* code){
CalcEditorWindowController	*controller;
NSAutoreleasePool			*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[CalcEditorWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
