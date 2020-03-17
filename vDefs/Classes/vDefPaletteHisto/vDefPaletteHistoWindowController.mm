//----------------------------------------------------------------------------
// File : vDefPaletteHistoWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Histogram vdef window controller
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

#import "vDefPaletteHistoWindowController.h"
#import "bvDefPaletteHisto.h"
#import "bvDefHistoStyle.h"
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
@implementation vDefPaletteHistoPanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation vDefPaletteHistoWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[vDefPaletteHistoWindowController init]",true);
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
_bTrace_("[vDefPaletteHistoWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[vDefPaletteHistoWindowController awakeFromNib]",true);
	[super awakeFromNib];

	// Nom du type et preview
char str[256];
	_ext->type_get()->name(str);
	[_tnm_fld setCharValue:str];
    [_tab_viw selectTabViewItemAtIndex:0];

	[_prvw installController:self];
		
	NSPopupButtonRemoveAllItems(_fld_pop);
	NSPopupButtonPopulateWithFields(_fld_pop,_ext->type_get(),kOBJ_Dir_+1,1);

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
	
long	i;
	
// Recalculer dx/dy global, dimx/dimy
bvDefHistoStyle	*bstl,*bstl2;
//	if(((bvDefPaletteHisto*)_ext)->bck_get()){
//		if(_ext->runs().count()>0){
//			_ext->runs().get(1,&bstl);
//double		bx=bstl->_dimx,by=bstl->_dimy,d,spc;
//			if(bstl->_onx){
//				d=by*(double)_ext->runs().count();
//				if(fabs(d-_bck->_dimy)>0.001){
//					spc=(_bck->_dimy-d)/(double)_ext->runs().count();
//				}
//			}
//			else{
//				d=bx*(double)_ext->runs().count();
//				if(fabs(d-_bck->_dimx)>0.001){
//					spc=(_bck->_dimx-d)/(double)_ext->runs().count();
//				}
//			}
//			for(i=1;i<=_ext->runs().count();i++){
//				_ext->runs().get(i,&bstl);
//				bstl->_dimx=_bck->_dimx;
//				bstl->_dimy=_bck->_dimy;
//				bstl->_dx=_bck->_dx;
//				bstl->_dy=_bck->_dy;
//				bstl->_spc=spc;
//			}		
//		}
//	}
//	else
	if(_ext->runs().count()>1){
		_ext->runs().get(1,&bstl);
		_ext->runs().get(2,&bstl2);
_tm_(bstl2->_dimx+":"+bstl2->_dimy);
_tm_(bstl->_dx+":"+bstl->_dy);
_tm_(bstl2->_dx+":"+bstl2->_dy);
		
double	spc=	(bstl->_onx)					?
		((bstl2->_dy-bstl->_dy)-bstl2->_dimy)	:
		((bstl2->_dx-bstl->_dx)-bstl2->_dimx)	;
		
double	off=	(bstl->_onx)	?
		(bstl->_dy-(spc*0.5))	:
		(bstl->_dx-(spc*0.5))	;
		
		for(i=1;i<=_ext->runs().count();i++){
			_ext->runs().get(i,&bstl);
			if(bstl->_onx){
				bstl->_dy=off;
				bstl->_dimy+=spc;
				bstl->_dimy*=((double)_ext->runs().count());
			}
			else{
				bstl->_dx=off;
				bstl->_dimx+=spc;
				bstl->_dimx*=((double)_ext->runs().count());
			}
			bstl->_spc=spc;
		}		
	}
	else if(_ext->runs().count()==1){
		_ext->runs().get(1,&bstl);
		bstl->_spc=0;
	}
	
	
	[self plot2Intf];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[vDefPaletteHistoWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions principal ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseField:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doChooseField]",true);
/*bvDefHistoStyle*	stl;
	
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
_bTrace_("[vDefPaletteHistoWindowController doAddField]",true);
bvDefHistoStyle*	stl;
long				fld=[_fld_pop indexOfSelectedItem]+1+kOBJ_Dir_;
	((bvDefPaletteHisto*)_ext)->fields().add(&fld);
	((bvDefPaletteHisto*)_ext)->stl_alloc(true);
	_ext->runs().get(_ext->runs().count(),&stl);
	stl->_fld=fld;
	stl->_idx--;
	getBornes((bGenericMacMapApp*)_ext->getapp(),_ext->type_get(),stl->_fld,&stl->_vmin,&stl->_vmax);
	[self doPutHeight:sender];
	[self doPutWidth:sender];
	[self doPutSpacing:sender];
	[self doChooseOrientation:sender];
	[self doPutDx:sender];
	[self doPutDy:sender];
		
	[_run_tbl reloadData];
	[self updateUI];
	
_tm_(((bvDefPaletteHisto*)_ext)->fields().count()+":"+fld);
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doRemoveField:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doRemoveField]",true);
bvDefHistoStyle*	stl;
	
	for(long i=_ext->runs().count();i>0;i--){
		if([_run_tbl isRowSelected:i-1]==YES){
			((bvDefPaletteHisto*)_ext)->fields().rmv(i);
			((bvDefPaletteHisto*)_ext)->runs().get(i,&stl);
			delete stl;
			((bvDefPaletteHisto*)_ext)->runs().rmv(i);
		}
	}	
	for(long i=1;i<=_ext->runs().count();i++){
		((bvDefPaletteHisto*)_ext)->runs().get(i,&stl);
		stl->_idx=i-1;
	}
	[_run_tbl reloadData];
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutHeight:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doPutHeight]",true);
bvDefHistoStyle*	stl;
_tm_([_hsz_fld floatValue]);
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_dimy=[_hsz_fld floatValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutWidth:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doPutWidth]",true);
bvDefHistoStyle*	stl;
_tm_([_wsz_fld floatValue]);
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_dimx=[_wsz_fld floatValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutSpacing:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doPutSpacing]",true);
bvDefHistoStyle*	stl;
_tm_([_spc_fld floatValue]);
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_spc=[_spc_fld floatValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseOrientation:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doPutRounding]",true);
bvDefHistoStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_onx=([_hov_pop indexOfSelectedItem]==1);
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutDx:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doPutDx]",true);
bvDefHistoStyle*	stl;
_tm_([_dx__fld floatValue]);
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_dx=[_dx__fld floatValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutDy:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doPutDy]",true);
bvDefHistoStyle*	stl;
_tm_([_dy__fld floatValue]);
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_dy=[_dy__fld floatValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doCalcSeriesMinMax:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController calcSeriesMinMax]",true);
bvDefHistoStyle*	stl;
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		getBornes((bGenericMacMapApp*)_ext->getapp(),_ext->type_get(),stl->_fld,&stl->_vmin,&stl->_vmax);
_tm_(i+":"+stl->_fld+"=["+stl->_vmin+";"+stl->_vmax+"]");
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doNormalize:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doNormalize]",true);
bvDefHistoStyle*	stl;
	if([_cks_btn intValue]==0){
double	min,max;
		_ext->runs().get(1,&stl);
		min=stl->_vmin;
		max=stl->_vmax;
		for(long i=2;i<=_ext->runs().count();i++){
			_ext->runs().get(i,&stl);
			if(stl->_vmin<min){
				min=stl->_vmin;
			}
			if(stl->_vmax>max){
				max=stl->_vmax;
			}
		}	
		for(long i=1;i<=_ext->runs().count();i++){
			_ext->runs().get(i,&stl);
			stl->_vmin=min;
			stl->_vmax=max;
		}
		[_min_fld setFloatValue:min];
		[_max_fld setFloatValue:max];
	}
	else{
		for(long i=1;i<=_ext->runs().count();i++){
			_ext->runs().get(i,&stl);
			getBornes((bGenericMacMapApp*)_ext->getapp(),_ext->type_get(),stl->_fld,&stl->_vmin,&stl->_vmax);
		}	
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutMin:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doPutMin]",true);
bvDefHistoStyle*	stl;
_tm_([_min_fld floatValue]);
	
	for(long i=1;i<=_ext->runs().count();i++){
		if(([_run_tbl isRowSelected:i-1]==YES)||([_cks_btn intValue]==0)){
			_ext->runs().get(i,&stl);
			stl->_vmin=[_min_fld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutMax:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doPutMax]",true);
bvDefHistoStyle*	stl;
_tm_([_max_fld floatValue]);
	
	for(long i=1;i<=_ext->runs().count();i++){
		if(([_run_tbl isRowSelected:i-1]==YES)||([_cks_btn intValue]==0)){
			_ext->runs().get(i,&stl);
			stl->_vmax=[_max_fld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutBarAlpha:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doPutBarAlpha]",true);
bvDefHistoStyle*	stl;
_tm_([_bro_sld floatValue]);
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fill[_ext->cmyk_get()?4:3]=[_bro_sld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutBarColor:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doPutBarColor]",true);
bvDefHistoStyle*	stl;
NSColor*					clr=[_bar_clr color];
NSColor*					cclr;
	
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
		}
	}	
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doCheckBackground:(id)sender{
	if([_ckb_btn intValue]==1){
		((bvDefPaletteHisto*)_ext)->bck_put(true);

		[self doPutBackFillColor:sender];		
		[self doPutBackStrokeColor:sender];		
		[self doPutBackStrokeWidth:sender];		
		[self doPutBackFillAlpha:sender];		
	}
	else{
		((bvDefPaletteHisto*)_ext)->bck_put(false);
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutBackFillAlpha:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doPutBackFillAlpha]",true);
	if(((bvDefPaletteHisto*)_ext)->bck_get()){
double*		colors=((bvDefPaletteHisto*)_ext)->fill_get();
		colors[_ext->cmyk_get()?4:3]=[_bkf_sld floatValue];
		((bvDefPaletteHisto*)_ext)->fill_put(colors);
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutBackFillColor:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doPutBackFillColor]",true);
	if(((bvDefPaletteHisto*)_ext)->bck_get()){
NSColor*	clr=[_bkf_clr color];
NSColor*	cclr;
double		colors[5]={0,0,0,1,1};
		
		if(_ext->cmyk_get()){
			cclr=[clr colorUsingColorSpaceName:@"NSDeviceCMYKColorSpace"];
		}
		else{
			cclr=[clr colorUsingColorSpaceName:@"NSDeviceRGBColorSpace"];
		}
		if(_ext->cmyk_get()){
			colors[0]=[cclr cyanComponent];
			colors[1]=[cclr magentaComponent];
			colors[2]=[cclr yellowComponent];
			colors[3]=[cclr blackComponent];
		}
		else{
			colors[0]=[cclr redComponent];
			colors[1]=[cclr greenComponent];
			colors[2]=[cclr blueComponent];
		}
		((bvDefPaletteHisto*)_ext)->fill_put(colors);
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutBackStrokeColor:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doPutBackStrokeColor]",true);
	if(((bvDefPaletteHisto*)_ext)->bck_get()){
NSColor*	clr=[_bks_clr color];
NSColor*	cclr;
double		colors[5]={0,0,0,1,1};
		
		if(_ext->cmyk_get()){
			cclr=[clr colorUsingColorSpaceName:@"NSDeviceCMYKColorSpace"];
		}
		else{
			cclr=[clr colorUsingColorSpaceName:@"NSDeviceRGBColorSpace"];
		}
		if(_ext->cmyk_get()){
			colors[0]=[cclr cyanComponent];
			colors[1]=[cclr magentaComponent];
			colors[2]=[cclr yellowComponent];
			colors[3]=[cclr blackComponent];
		}
		else{
			colors[0]=[cclr redComponent];
			colors[1]=[cclr greenComponent];
			colors[2]=[cclr blueComponent];
		}
		((bvDefPaletteHisto*)_ext)->strk_put(colors);
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutBackStrokeWidth:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doPutBackStrokeWidth]",true);
	if(((bvDefPaletteHisto*)_ext)->bck_get()){		
		((bvDefPaletteHisto*)_ext)->wdth_put([_bks_fld floatValue]);
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseScaleMin:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doChooseScaleMin]",true);
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
_bTrace_("[vDefPaletteHistoWindowController doChooseScaleMax]",true);
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
_bTrace_("[vDefPaletteHistoWindowController doClickPreview]",true);
}

#pragma mark ---- Actions options ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseScaleRef:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doChooseScaleRef]",true);
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
_bTrace_("[vDefPaletteHistoWindowController doChooseUnit]",true);
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
_bTrace_("[vDefPaletteHistoWindowController doChooseColorSpace]",true);
	_ext->cmyk_put([_o_cls_chk intValue]);
	[self convertColor];
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doCheckCondition:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doCheckCondition]",true);
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
_bTrace_("[vDefPaletteHistoWindowController doChooseCondField]",true);
	_ext->cfld_put([_o_cnf_pop indexOfSelectedItem]+kOBJ_Name_);
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseCondOperator:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doChooseCondOperator]",true);
	_ext->cop_put([_o_cno_pop indexOfSelectedItem]+1);
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutCondValue:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doPutCondValue]",true);
char	val[256];
	NSTextFieldGetValue(_o_val_fld,val,sizeof(val)-1);
	_ext->cval_put(val);
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doCheckOffset:(id)sender{
_bTrace_("[vDefPaletteHistoWindowController doCheckOffset]",true);
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
_bTrace_("[vDefPaletteHistoWindowController doChooseOffsetXField]",true);
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
_bTrace_("[vDefPaletteHistoWindowController doChooseOffsetYField]",true);
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
_bTrace_("[vDefPaletteHistoWindowController doApply]",true);
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
-(void)checkIntfAvailability{
BOOL	state=NO;
	if([_run_tbl numberOfSelectedRows]>0){
		state=YES;
	}
	[_rmv_btn setEnabled:[_run_tbl numberOfSelectedRows]==1];

//	[_hghtfld setEnabled:state];
//	[_wdthfld setEnabled:state];
//	[_spcefld setEnabled:state];
//	[_rondfld setEnabled:state];
//	[_horvpop setEnabled:state];
//	[_dx__fld setEnabled:state];
//	[_dy__fld setEnabled:state];
	
//	[_mimapop setEnabled:state];
//	[_ckscbtn setEnabled:state];
	[_min_fld setEnabled:state];
	[_max_fld setEnabled:state];
	
	[_bro_sld setEnabled:state];
	[_bar_clr setEnabled:state];
	
	state=((_ext->runs().count()>0)==1);
	[_ckb_btn setEnabled:state];
	state=([_ckb_btn intValue]==1);
	[_bkf_sld setEnabled:state];
	[_bkf_clr setEnabled:state];
	[_bks_clr setEnabled:state];
	[_bks_fld setEnabled:state];
	
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
_bTrace_("[vDefPaletteHistoWindowController plot2Intf]",true);
long				cur=[_run_tbl selectedRow]+1;
bvDefHistoStyle*	stl;
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
	
	if(cur){
		if(!_ext->runs().get(cur,&stl)){
			return;
		}
		
		[_min_fld setFloatValue:stl->_vmin];
		[_max_fld setFloatValue:stl->_vmax];
		[_bro_sld setFloatValue:stl->_fill[_ext->cmyk_get()?4:3]];
		if(_ext->cmyk_get()){
			[_bar_clr setColor:[NSColor colorWithDeviceCyan:stl->_fill[0] 
													magenta:stl->_fill[1] 
													 yellow:stl->_fill[2] 
													  black:stl->_fill[3] 
													  alpha:1]];
		}
		else{
			[_bar_clr setColor:[NSColor colorWithDeviceRed:stl->_fill[0]
													 green:stl->_fill[1] 
													  blue:stl->_fill[2] 
													 alpha:1]];
		}
		[_spc_fld setFloatValue:stl->_spc];
		[_hov_pop selectItemAtIndex:stl->_onx];		
	}
	else{
		[_min_fld setStringValue:@""];
		[_max_fld setStringValue:@""];
		[_bro_sld setFloatValue:1];
		[_bar_clr setColor:[NSColor blackColor]];
		[_spc_fld setFloatValue:0];
		[_hov_pop selectItemAtIndex:0];		
	}
	
	if(((bvDefPaletteHisto*)_ext)->bck_get()){
double*	colors;
		if(_ext->cmyk_get()){
			colors=((bvDefPaletteHisto*)_ext)->fill_get();
			[_bkf_sld setFloatValue:colors[4]];
			[_bkf_clr setColor:[NSColor colorWithDeviceCyan:colors[0] 
													magenta:colors[1] 
													 yellow:colors[2] 
													  black:colors[3] 
													  alpha:1]];
			colors=((bvDefPaletteHisto*)_ext)->strk_get();
			[_bks_clr setColor:[NSColor colorWithDeviceCyan:colors[0] 
													magenta:colors[1] 
													 yellow:colors[2] 
													  black:colors[3] 
													  alpha:1]];
		}
		else{
			colors=((bvDefPaletteHisto*)_ext)->fill_get();
			[_bkf_sld setFloatValue:colors[3]];
			[_bkf_clr setColor:[NSColor colorWithDeviceRed:colors[0] 
													 green:colors[1] 
													  blue:colors[2] 
													 alpha:1]];
			colors=((bvDefPaletteHisto*)_ext)->strk_get();
			[_bks_clr setColor:[NSColor colorWithDeviceRed:colors[0] 
													 green:colors[1] 
													  blue:colors[2] 
													 alpha:1]];
		}
		[_bks_fld setFloatValue:((bvDefPaletteHisto*)_ext)->wdth_get()];
		[_ckb_btn setIntValue:1];
	}
	else{
		[_bkf_sld setFloatValue:1];
		[_bkf_clr setColor:[NSColor blackColor]];
		[_bks_clr setColor:[NSColor blackColor]];
		[_bks_fld setFloatValue:0];
		[_ckb_btn setIntValue:0];
	}
	
	if((_ext->runs().count()>0)/*||_bck*/){
bvDefHistoStyle	*std;
		if(_ext->runs().count()==0){
			//std=_bck;
			return;
		}
		else{
			_ext->runs().get(1,&std);
		}
		[_hsz_fld setFloatValue:std->_dimy];
		[_wsz_fld setFloatValue:std->_dimx];
		[_dx__fld setFloatValue:std->_dx];
		[_dy__fld setFloatValue:std->_dy];
	}
	else{
		[_hsz_fld setFloatValue:30];
		[_wsz_fld setFloatValue:40];
		[_dx__fld setFloatValue:0];
		[_dy__fld setFloatValue:0];
	}
	
	if((_ext->runs().count()>0)||(cur==0)){	
		if(!_ext->runs().get(1,&stl)){
			return;
		}
		[_spc_fld setFloatValue:stl->_spc];
		[_hov_pop selectItemAtIndex:stl->_onx];		
	}
	
	if(!_ext->runs().get(1,&stl)){
		return;
	}
	
long	idx;
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
}	

// ---------------------------------------------------------------------------
// 
// -----------
-(void)convertColor{
bvDefHistoStyle*	stl;
	
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
_bTrace_("[vDefPaletteHistoWindowController drawPreview]",true);
long	n=_ext->runs().count();
	if(n==0){
		CGContextSetEmptyStyle(ctx,rect);
		return;
	}
bvDefHistoStyle*	stl;
	_ext->runs().get(1,&stl);
	
CGPoint	o=CGPointMake(CGRectGetMidX(rect),CGRectGetMidY(rect));
CGRect	cgr;
int		nsv=0;
	if(((bvDefPaletteHisto*)_ext)->bck_get()){
		cgr.origin.x=o.x-stl->_dimx/2.0;
		cgr.origin.y=o.y-stl->_dimy/2.0;
		cgr.size.width=stl->_dimx;
		cgr.size.height=stl->_dimy;
		
		CGContextSetLineWidth(ctx,((bvDefPaletteHisto*)_ext)->wdth_get());
		MMCGContextSetStrokeColor64(ctx,((bvDefPaletteHisto*)_ext)->strk_get(),_ext->cmyk_get());
		MMCGContextSetFillColor64(ctx,((bvDefPaletteHisto*)_ext)->fill_get(),_ext->cmyk_get());
		CGContextAddRect(ctx,cgr);
		CGContextDrawPath(ctx,kCGPathFillStroke);
		
		if(!CGRectIsEmpty(cgr)){
			nsv++;
		}
	}
	
double	bsz,bsp,rdc=0.80/(double)n;
	
	if(stl->_onx){
		bsp=stl->_dimy/((double)n);
		bsz=bsp-stl->_spc;
	}
	else{
		bsp=stl->_dimx/((double)n);
		bsz=bsp-stl->_spc;
	}
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		if(stl->_onx){
			cgr.origin.x=o.x-stl->_dimx/2.0;
			cgr.origin.y=o.y-stl->_dimy/2.0+((double)(i-1))*bsp+(0.5*stl->_spc);
			cgr.size.width=stl->_dimx*(1.0-((double)i)*rdc);
			cgr.size.height=bsz;
		}
		else{
			cgr.origin.x=o.x-stl->_dimx/2.0+((double)(i-1))*bsp+(0.5*stl->_spc);
			cgr.origin.y=o.y-stl->_dimy/2.0;
			cgr.size.width=bsz;
			cgr.size.height=stl->_dimy*(1.0-((double)i)*rdc);
		}
		if(!CGRectIsEmpty(cgr)){
			nsv++;
		}
		CGContextSetLineWidth(ctx,0);
		MMCGContextSetFillColor64(ctx,stl->_fill,_ext->cmyk_get());
		CGContextAddRect(ctx,cgr);
		CGContextDrawPath(ctx,kCGPathFill);
		
		if([_run_tbl isRowSelected:i-1]==YES){
			CGContextSetLineWidth(ctx,1);
			CGContextSetRGBFillColor(ctx,0,0,0,1);
			CGContextBeginPath(ctx);
			if(stl->_onx){
				CGContextMoveToPoint(ctx,cgr.origin.x-5,CGRectGetMidY(cgr));
				CGContextAddLineToPoint(ctx,cgr.origin.x-1,CGRectGetMidY(cgr));
			}
			else{
				CGContextMoveToPoint(ctx,CGRectGetMidX(cgr),cgr.origin.y-4);
				CGContextAddLineToPoint(ctx,CGRectGetMidX(cgr),cgr.origin.y-1);			
			}
			CGContextClosePath(ctx);
			CGContextDrawPath(ctx,kCGPathStroke);
		}
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
//_bTrace_("[vDefPaletteHistoWindowController numberOfRowsInTableView]",true);
	return ((bvDefPaletteHisto*)_ext)->fields().count();
}

// ---------------------------------------------------------------------------
// 
// -----------
-(id)	tableView:(NSTableView*)aTableView 
		objectValueForTableColumn:(NSTableColumn*)aTableColumn 
		row:(NSInteger)rowIndex{
//_bTrace_("[vDefPaletteHistoWindowController tableView objectValueForTableColumn row]",true);
NSString*	nsstr;
char		str[256];
long		fld;
	
	((bvDefPaletteHisto*)_ext)->fields().get(rowIndex+1,&fld);
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
vDefPaletteHistoWindowController	*controller;
NSAutoreleasePool						*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[vDefPaletteHistoWindowController alloc] init];
    [controller setExt:(bStdNSPalettevDef*)ext];
    [localPool release];
    return((void*)controller);
}

