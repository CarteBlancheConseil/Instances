//----------------------------------------------------------------------------
// File : vDefPalettePieChartWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Pie chart vdef window controller
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
// 09/07/2013 creation.
//----------------------------------------------------------------------------

#import "vDefPalettePieChartWindowController.h"
#import "bvDefPalettePieChart.h"
#import "bvDefPieChartStyle.h"
#import "CocoaStuff.h"
#import <MacMapSuite/bTrace.h>

#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/bEventLog.h>
#import <mox_intf/ext_utils.h>
#import <mox_intf/Color_Utils.h>
#import <mox_intf/xmldesc_utils.h>
#import <mox_intf/NSUIUtils.h> 
#import <mox_intf/CGUtils.h> 

#import <std_ext/bXMapStdIntf.h>

#import <vdef_lib/vdef_utils.h>

// ---------------------------------------------------------------------------
// 
// ------------
static double text2val(char* text){
double	r=1;
char*	c=strchr(text,'=');
	if(!c){
		return(r);
	}
	c++;
	c++;
char* d=strchr(c,'/');
	if(!d){
		r=matof(c);
		if(r<=0){
			r=1;
		}
		return(r);
	}
	d[0]=0;
double	a=matof(c);
	d++;
double	b=matof(d);
	r=a/b;
	if(r<=0){
		r=1;
	}
	return(r);
}

// ---------------------------------------------------------------------------
// 
// ------------
static long val2index(double val, NSPopUpButton* c){
char	str[256];
long	best=0;
double	v,d,dmin=INT_MAX;
	
	for(long i=1;i<=[c numberOfItems];i++){
		NSPopupButtonGetMenuItemValue(c,i,str,sizeof(str)-1);
		v=text2val(str);
		d=fabs(v-val);
		if(d==0){
			return(i);
		}
		if(d<dmin){
			dmin=d;
			best=i;
		}
	}
	return(best);
}

// ---------------------------------------------------------------------------
// 
// ------------
@implementation vDefPalettePieChartPanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation vDefPalettePieChartWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[vDefPalettePieChartWindowController init]",true);
	self=[super init];
	if(self){
		_last_click=-1;
	}
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[vDefPalettePieChartWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[vDefPalettePieChartWindowController awakeFromNib]",true);
	[super awakeFromNib];

	// Nom du type et preview
char str[256];
	_ext->type_get()->name(str);
	[_tnm_fld setCharValue:str];
    [_tab_viw selectTabViewItemAtIndex:0];
	
	[_prvw installController:self];
		
	NSPopupButtonRemoveAllItems(_fld_pop);
	NSPopupButtonPopulateWithFields(_fld_pop,_ext->type_get(),kOBJ_Dir_+1,1);

	NSPopupButtonRemoveAllItems(_prop_fld_pop);
	NSPopupButtonPopulateWithFields(_prop_fld_pop,_ext->type_get(),kOBJ_Dir_+1,1);

bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();

	// Visibilité
	NSPopupButtonRemoveAllItems(_smn_pop);
	NSPopupButtonPopulateWithScales(_smn_pop,gapp,1);
	NSPopupButtonRemoveAllItems(_smx_pop);
	NSPopupButtonPopulateWithScales(_smx_pop,gapp,gapp->scaleMgr()->count());
	
	// Options
	NSPopupButtonPopulateWithScales(_o_srf_pop,gapp,1);
	NSPopupButtonRemoveAllItems(_o_cnf_pop);
	NSPopupButtonPopulateWithFields(_o_cnf_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonRemoveAllItems(_o_xof_pop);
	NSPopupButtonPopulateWithFields(_o_xof_pop,_ext->type_get(),kOBJ_Dir_+1,1);
	NSPopupButtonRemoveAllItems(_o_yof_pop);
	NSPopupButtonPopulateWithFields(_o_yof_pop,_ext->type_get(),kOBJ_Dir_+1,2);
	
	[self plot2Intf];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[vDefPalettePieChartWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions principal ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseField:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doChooseField]",true);
/*bvDefPieChartStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_rref=[_rad_fld floatValue];
	}
	[self updateUI];*/
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doAddField:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doAddField]",true);

long fld=[_fld_pop indexOfSelectedItem]+1+kOBJ_Dir_;
	((bvDefPalettePieChart*)_ext)->fields().add(&fld);
	((bvDefPalettePieChart*)_ext)->stl_alloc(true);
	[_run_tbl reloadData];
	[self updateUI];
	
_tm_(((bvDefPalettePieChart*)_ext)->fields().count()+":"+fld);
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doRemoveField:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doRemoveField]",true);
bvDefPieChartStyle*	stl;
	
	for(long i=_ext->runs().count();i>0;i--){
		if([_run_tbl isRowSelected:i-1]==YES){
			((bvDefPalettePieChart*)_ext)->fields().rmv(i);
			((bvDefPalettePieChart*)_ext)->runs().get(i,&stl);
			delete stl;
			((bvDefPalettePieChart*)_ext)->runs().rmv(i);
		}
	}	
	for(long i=1;i<=_ext->runs().count();i++){
		((bvDefPalettePieChart*)_ext)->runs().get(i,&stl);
		stl->_idx=i;
	}
	[_run_tbl reloadData];
	[self updateUI];
}


// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutRadius:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doPutRadius]",true);
bvDefPieChartStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_rref=[_rad_fld floatValue];
	}
	[self updateSizeMax];
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doChooseFillColor:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doChooseFillColor]",true);
bvDefPieChartStyle*	stl;
NSColor*			clr=[_fil_clr color];
NSColor*			cclr;
	
	if(_ext->cmyk_get()){
		cclr=[clr colorUsingColorSpaceName:@"NSDeviceCMYKColorSpace"];
	}
	else{
		cclr=[clr colorUsingColorSpaceName:@"NSDeviceRGBColorSpace"];
	}
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			if(_ext->cmyk_get()){
				stl->_fill[0]=[cclr cyanComponent];
				stl->_fill[1]=[cclr magentaComponent];
				stl->_fill[2]=[cclr yellowComponent];
				stl->_fill[3]=[cclr blackComponent];
			}
			else{
				stl->_fill[0]=[cclr redComponent];
				stl->_fill[1]=[cclr greenComponent];
				stl->_fill[2]=[cclr blueComponent];
			}
			stl->_fill[_ext->cmyk_get()?4:3]=[_fil_sld floatValue];
		}
	}	
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutFillAlpha:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doPutFillAlpha]",true);
bvDefPieChartStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fill[_ext->cmyk_get()?4:3]=[_fil_sld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutWidth:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doPutWidth]",true);
	((bvDefPalettePieChart*)_ext)->wdth_put([_wdt_fld doubleValue]);
	_tm_([_wdt_fld doubleValue]);
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutStrokeColor:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doPutStrokeColor]",true);
NSColor*	clr=[_stk_clr color];
NSColor*	cclr;
double		dclr[5]={0.5,0.5,0.5,0.5,0.5};
	
	if(_ext->cmyk_get()){
		cclr=[clr colorUsingColorSpaceName:@"NSDeviceCMYKColorSpace"];
		dclr[0]=[cclr cyanComponent];
		dclr[1]=[cclr magentaComponent];
		dclr[2]=[cclr yellowComponent];
		dclr[3]=[cclr blackComponent];
		dclr[4]=1;
	}
	else{
		cclr=[clr colorUsingColorSpaceName:@"NSDeviceRGBColorSpace"];
		dclr[0]=[cclr redComponent];
		dclr[1]=[cclr greenComponent];
		dclr[2]=[cclr blueComponent];
		dclr[3]=1;
	}

	((bvDefPalettePieChart*)_ext)->strk_put(dclr);

	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doCheckProp:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doCheckProp]",true);
bvDefPieChartStyle*	stl;
	
	((bvDefPalettePieChart*)_ext)->prop_put([_prop_chk intValue]);
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_prop=[_prop_chk intValue];
	}
	
	if([_prop_chk intValue]==0){
		for(long i=1;i<=_ext->runs().count();i++){
			_ext->runs().get(i,&stl);
			stl->_qref=1;
			stl->_qmax=1;
			stl->_rref=5;
			stl->_exp=1;			
		}
	}
	else{
		[self doChoosePropField:sender];
		[self doChoosePropMethod:sender];
		[self doPutMin:sender];
		[self doPutMax:sender];
	}
	[self updateSizeMax];
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doChoosePropField:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doChoosePropField]",true);
bvDefPieChartStyle*	stl;
long				fld=[_prop_fld_pop indexOfSelectedItem]+1+kOBJ_Dir_;
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_fld=fld;
	}
	((bvDefPalettePieChart*)_ext)->fld_put(fld);
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doChoosePropMethod:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doChoosePropMethod]",true);
char				val[256];
double				d;
bvDefPieChartStyle*	stl;
	
	NSPopupButtonGetMenuItemValue(_prop_prp_pop,[_prop_prp_pop indexOfSelectedItem]+1,val,sizeof(val)-1);
	d=text2val(val);
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_exp=d;
	}
	[self updateSizeMax];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doChooseMin:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doChooseMin]",true);
long	k=[_prop_min_pop indexOfSelectedItem];
double	val;
	getMin((bGenericMacMapApp*)_ext->getapp(),_ext->type_get(),_ext->fld_get(),k,&val);
	[_prop_min_fld setDoubleValue:val];
bvDefPieChartStyle*	stl;	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_qref=[_prop_min_fld floatValue];
	}
	[self updateSizeMax];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutMin:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doPutMin]",true);
bvDefPieChartStyle*	stl;
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_qref=[_prop_min_fld floatValue];
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doChooseMax:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doChooseMax]",true);
long	k=[_prop_max_pop indexOfSelectedItem];
double	val;
	getMax((bGenericMacMapApp*)_ext->getapp(),_ext->type_get(),_ext->fld_get(),k,&val);
	[_prop_max_fld setDoubleValue:val];
bvDefPieChartStyle*	stl;	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_qmax=[_prop_max_fld floatValue];
	}
	[self updateSizeMax];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutMax:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doPutMax]",true);
bvDefPieChartStyle*	stl;
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_qmax=[_prop_max_fld floatValue];
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseScaleMin:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doChooseScaleMin]",true);
bGenericUnit*			u=((bGenericMacMapApp*)_ext->getapp())->scaleMgr()->get([_smn_pop indexOfSelectedItem]+1);
bvDefPaletteRangeStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_smin=u->coef();
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseScaleMax:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doChooseScaleMax]",true);
bGenericUnit*			u=((bGenericMacMapApp*)_ext->getapp())->scaleMgr()->get([_smx_pop indexOfSelectedItem]+1);
bvDefPaletteRangeStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_smax=u->coef()+1.0;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doClickPreview:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doClickPreview]",true);
}

#pragma mark ---- Actions options ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseScaleRef:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doChooseScaleRef]",true);
	if([_o_srf_pop indexOfSelectedItem]==0){
		_ext->sref_put(0);
	}
	else{
		bGenericUnit*	u=((bGenericMacMapApp*)_ext->getapp())->scaleMgr()->get([_o_srf_pop indexOfSelectedItem]-1);
		_ext->sref_put(u->coef());
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseUnit:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doChooseUnit]",true);
	switch([_o_unt_pop indexOfSelectedItem]){
		case 0:
			_ext->coef_put(1);
			break;
		case 1:
			_ext->coef_put(_pm_coef_);
			break;	
		default:
			_ext->coef_put(1);
			break;
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseColorSpace:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doChooseColorSpace]",true);
	_ext->cmyk_put([_o_cls_chk intValue]);
	[self convertColor];
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doCheckCondition:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doCheckCondition]",true);
	if([_o_dif_chk intValue]==1){
		[self doChooseCondField:sender];
		[self doChooseCondOperator:sender];
		[self doPutCondValue:sender];
	}
	else{
		_ext->cfld_put(0);
		_ext->cop_put(1);
		_ext->cval_put("");
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseCondField:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doChooseCondField]",true);
	_ext->cfld_put([_o_cnf_pop indexOfSelectedItem]+kOBJ_Name_);
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseCondOperator:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doChooseCondOperator]",true);
	_ext->cop_put([_o_cno_pop indexOfSelectedItem]+1);
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutCondValue:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doPutCondValue]",true);
char	val[256];
	NSTextFieldGetValue(_o_val_fld,val,sizeof(val)-1);
	_ext->cval_put(val);
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doCheckOffset:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doCheckOffset]",true);
bvDefPaletteRangeStyle*	stl;
	if([_o_off_chk intValue]==1){
		[self doChooseOffsetXField:sender];
		[self doChooseOffsetYField:sender];
	}
	else{
		for(long i=1;i<=_ext->runs().count();i++){
			_ext->runs().get(i,&stl);
			stl->_offx=0;
			stl->_offy=0;
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseOffsetXField:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doChooseOffsetXField]",true);
bvDefPaletteRangeStyle*	stl;
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_offx=[_o_xof_pop indexOfSelectedItem]+kOBJ_Dir_+1;
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseOffsetYField:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doChooseOffsetYField]",true);
bvDefPaletteRangeStyle*	stl;
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_offy=[_o_yof_pop indexOfSelectedItem]+kOBJ_Dir_+1;
	}		
}

#pragma mark ---- Actions appliquer ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doApply:(id)sender{
_bTrace_("[vDefPalettePieChartWindowController doApply]",true);
	_ext->update();
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateUI{
	[_prvw setNeedsDisplay:YES];
	[self checkIntfAvailability];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateSizeMax{
	[_szx_fld setDoubleValue:[self sizeMax]];
	[_prvw setNeedsDisplay:YES];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)checkIntfAvailability{
BOOL	state=NO;
	if([_run_tbl numberOfSelectedRows]>0){
		state=YES;
	}
	[_fil_clr setEnabled:state];
	[_fil_sld setEnabled:state];
//	[_smn_pop setEnabled:state];
//	[_smx_pop setEnabled:state];
	[_rmv_btn setEnabled:[_run_tbl numberOfSelectedRows]==1];
	
// Proportionnalité
	state=([_prop_chk intValue]==1);
	[_prop_fld_pop setEnabled:state];
	[_prop_prp_pop setEnabled:state];
	[_prop_min_pop setEnabled:state];
	[_prop_min_fld setEnabled:state];
	[_prop_max_pop setEnabled:state];
	[_prop_max_fld setEnabled:state];
	
// Options
	state=([_o_dif_chk intValue]==1);
	[_o_cnf_pop setEnabled:state];
	[_o_cno_pop setEnabled:state];
	[_o_val_fld setEnabled:state];
	
	if(_ext->type_get()->fields()->count()==kOBJ_Dir_){
		state=NO;
		[_o_off_chk setEnabled:state];
	}
	else{
		[_o_off_chk setEnabled:YES];
		state=([_o_off_chk intValue]==1);
	}
	[_o_xof_pop setEnabled:state];
	[_o_yof_pop setEnabled:state];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)plot2Intf{
_bTrace_("[vDefPalettePieChartWindowController plot2Intf]",true);

	[_prop_chk setIntValue:((bvDefPalettePieChart*)_ext)->prop_get()];
	[_wdt_fld setDoubleValue:((bvDefPalettePieChart*)_ext)->wdth_get()];

long				idx;
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bvDefPieChartStyle*	stl=NULL;
	if(!_ext->runs().get(1,&stl)){
		return;
	}

// Options + Visibilité
	idx=GetBestScaleIndexForValue(gapp,stl->_smin);
	[_smn_pop selectItemAtIndex:(idx-1)];
	idx=GetBestScaleIndexForValue(gapp,stl->_smax);
	[_smx_pop selectItemAtIndex:(idx-1)];					
	
	if(_ext->sref_get()==0){
		idx=1;
	}
	else{
		idx=GetBestScaleIndexForValue(gapp,_ext->sref_get())/*+2*/;
	}
	[_o_srf_pop selectItemAtIndex:(idx-1)];
	[_o_unt_pop selectItemAtIndex:(_ext->coef_get()==1)?0:1];
	[_o_cls_chk setIntValue:_ext->cmyk_get()];
	[_o_xof_pop selectItemAtIndex:((stl->_offx)?(stl->_offx-kOBJ_Dir_-1):0)];
	[_o_yof_pop selectItemAtIndex:((stl->_offy)?(stl->_offy-kOBJ_Dir_-1):1)];
	if((stl->_offx)&&(stl->_offy)){
		[_o_off_chk setIntValue:1];
	}
	else{
		[_o_off_chk setIntValue:0];
	}
	if(_ext->cfld_get()){
		[_o_dif_chk setIntValue:1];
	}
	else{
		[_o_dif_chk setIntValue:0];
	}
	
	[_o_cnf_pop selectItemAtIndex:((_ext->cfld_get())?(_ext->cfld_get()-kOBJ_Name_):1)];
	[_o_cno_pop selectItemAtIndex:((_ext->cop_get())?(_ext->cop_get()-1):0)];
char	val[256];
	_ext->cval_get(val);
	[_o_val_fld setCharValue:val];

// Taille
	[_rad_fld setDoubleValue:stl->_rref];
	
// Proportionnalité	
	if([_prop_chk intValue]){
		[_prop_fld_pop selectItemAtIndex:(_ext->fld_get()-(kOBJ_Dir_+1))];
		[_prop_prp_pop selectItemAtIndex:val2index(stl->_exp,_prop_prp_pop)-1];
		[_prop_min_fld setDoubleValue:stl->_qref];
		[_prop_max_fld setDoubleValue:stl->_qmax];
	}
	else{
		[_prop_fld_pop selectItemAtIndex:0];
		[_prop_prp_pop selectItemAtIndex:0];
		[_prop_min_fld setDoubleValue:0];
		[_prop_max_fld setDoubleValue:0];		
	}
	
double*	stroke=((bvDefPalettePieChart*)_ext)->strk_get();
	if(_ext->cmyk_get()){
		[_stk_clr setColor:[NSColor colorWithDeviceCyan:stroke[0] 
												magenta:stroke[1] 
												 yellow:stroke[2] 
												  black:stroke[3] 
												  alpha:1]];
	}
	else{
		[_stk_clr setColor:[NSColor colorWithDeviceRed:stroke[0]
												 green:stroke[1] 
												  blue:stroke[2] 
												 alpha:1]];
	}
		
// Les paramètres de classe	
long	cur=[_run_tbl selectedRow]+1;
	
	if(cur){
		_ext->runs().get(cur,&stl);
		if(_ext->cmyk_get()){
			[_fil_clr setColor:[NSColor colorWithDeviceCyan:stl->_fill[0] 
													magenta:stl->_fill[1] 
													 yellow:stl->_fill[2] 
													  black:stl->_fill[3] 
													  alpha:1]];
			[_fil_sld setFloatValue:stl->_fill[4]];
		}
		else{
			[_fil_clr setColor:[NSColor colorWithDeviceRed:stl->_fill[0]
													 green:stl->_fill[1] 
													  blue:stl->_fill[2] 
													 alpha:1]];
			[_fil_sld setFloatValue:stl->_fill[3]];
		}
	}
	else{
		[_fil_clr setColor:[NSColor blackColor]];
		[_fil_sld setFloatValue:1.00];
	}
}	

// ---------------------------------------------------------------------------
// 
// -----------
-(void)convertColor{
bvDefPieChartStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		if(_ext->cmyk_get()){
			compRGB2CMYK64(stl->_stroke);
			compRGB2CMYK64(stl->_fill);
			stl->_cc=5;
		}
		else{
			compCMYK2RGB64(stl->_stroke);
			compCMYK2RGB64(stl->_fill);
			stl->_cc=4;
		}
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)drawPreview:(CGRect)rect context:(CGContextRef)ctx{
_bTrace_("[vDefPalettePieChartWindowController drawPreview]",true);
HIRect				hir=(*((CGRect*)(&rect)));
	
	hir=CGRectInset(hir,1,1);	
	
bvDefPieChartStyle*		stl;
	if(!_ext->runs().get(1,&stl)){
		CGContextSetEmptyStyle(ctx,rect);
		return;
	}
	
double	a=(2.0*M_PI)/(double)_ext->runs().count();
double	sz;
float	y;
int		nsv=0;
	
	if(((bvDefPalettePieChart*)_ext)->prop_get()){
		sz=sqrt(pow(stl->_qmax,stl->_exp))*(stl->_rref/sqrt(pow(stl->_qref,stl->_exp)));
		y=hir.origin.y+sz+2.0+((bvDefPalettePieChart*)_ext)->wdth_get()/2.0;
		for(int i=1;i<=_ext->runs().count();i++){
			_ext->runs().get(i,&stl);
			MMCGContextSetFillColor64(ctx,
									  stl->_fill,
									  _ext->cmyk_get());
			CGContextMoveToPoint(ctx,CGRectGetMidX(hir),y);
			CGContextAddArc(ctx,CGRectGetMidX(hir),y,sz,(float)(i)*(float)a,(float)(i-1)*(float)a,1);
			CGContextAddLineToPoint(ctx,CGRectGetMidX(hir),y);
			CGContextFillPath(ctx);
			if(sz>0){
				nsv++;
			}
		}
		
		if(((bvDefPalettePieChart*)_ext)->wdth_get()>0){
			MMCGContextSetStrokeColor64(ctx,
										((bvDefPalettePieChart*)_ext)->strk_get(),
										_ext->cmyk_get());
			CGContextSetLineWidth(ctx,((bvDefPalettePieChart*)_ext)->wdth_get()*_ext->coef_get());
			CGContextAddArc(ctx,CGRectGetMidX(hir),y,sz,0,(2.0*M_PI),1);
			CGContextStrokePath(ctx);
		}
	}
	
	sz=stl->_rref*_ext->coef_get();
	y=hir.origin.y+sz+2.0+((bvDefPalettePieChart*)_ext)->wdth_get()/2.0;
	for(int i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		MMCGContextSetFillColor64(ctx,
								  stl->_fill,
								  _ext->cmyk_get());
		CGContextMoveToPoint(ctx,CGRectGetMidX(hir),y);
		CGContextAddArc(ctx,CGRectGetMidX(hir),y,sz,(float)(i)*(float)a,(float)(i-1)*(float)a,1);
		CGContextAddLineToPoint(ctx,CGRectGetMidX(hir),y);
		CGContextFillPath(ctx);
		if(sz>0){
			nsv++;
		}
	}
	if(((bvDefPalettePieChart*)_ext)->wdth_get()>0){
		MMCGContextSetStrokeColor64(ctx,
									((bvDefPalettePieChart*)_ext)->strk_get(),
									_ext->cmyk_get());
		CGContextSetLineWidth(ctx,((bvDefPalettePieChart*)_ext)->wdth_get()*_ext->coef_get());
		CGContextAddArc(ctx,CGRectGetMidX(hir),y,sz,0,(2.0*M_PI),1);
		CGContextStrokePath(ctx);
	}
	
	if(nsv==0){
		CGContextSetEmptyStyle(ctx,rect);
	}
}

#pragma mark ---- Gestion TableView ----
// ---------------------------------------------------------------------------
// 
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
//_bTrace_("[vDefPalettePieChartWindowController numberOfRowsInTableView]",true);
	return ((bvDefPalettePieChart*)_ext)->fields().count();
}

// ---------------------------------------------------------------------------
// 
// -----------
-(id)	tableView:(NSTableView*)aTableView 
		objectValueForTableColumn:(NSTableColumn*)aTableColumn 
		row:(NSInteger)rowIndex{
//_bTrace_("[vDefPalettePieChartWindowController tableView objectValueForTableColumn row]",true);
NSString*	nsstr;
char		str[256];
long		fld;
	
	((bvDefPalettePieChart*)_ext)->fields().get(rowIndex+1,&fld);
	_ext->type_get()->fields()->get_name(fld,str);
	nsstr=[NSString stringWithCString:str encoding:NSMacOSRomanStringEncoding];
	return nsstr;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)tableViewSelectionDidChange:(NSNotification*)notification{
	[self plot2Intf];
	[self updateUI];
	_last_click=[_run_tbl selectedRow];
}

#pragma mark ---- Calcul des tailles max ----
// ---------------------------------------------------------------------------
// 
// -----------
-(double)sizeMax{
bvDefPieChartStyle*	stl;
	if(!_ext->runs().get(1,&stl)){
		return(0);
	}
	return(sqrt(pow(stl->_qmax,stl->_exp))*(stl->_rref/sqrt(pow(stl->_qref,stl->_exp))));
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
vDefPalettePieChartWindowController	*controller;
NSAutoreleasePool						*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[vDefPalettePieChartWindowController alloc] init];
    [controller setExt:(bStdNSPalettevDef*)ext];
    [localPool release];
    return((void*)controller);
}

