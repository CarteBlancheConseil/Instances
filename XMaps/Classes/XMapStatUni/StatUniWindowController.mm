//----------------------------------------------------------------------------
// File : StatUniWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap univariate window controller
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
// 18/04/2014 creation.
//----------------------------------------------------------------------------

#import "StatUniWindowController.h"
#import <xmap_lib/StatBrowserView.h>
#import <xmap_lib/MatrixBrowserView.h>
#import <xmap_lib/GraphView.h>
#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation StatUniWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[StatUniWindowController init]",true);
	_anap=(mmx_analysis*)&_ana;
	self=[super init];
_tm_((void*)self);	
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[StatUniWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doCompute:(id)sender{
_bTrace_("[StatUniWindowController doCompute]",true);
	
// Free	
	[self cleanupSheets];
	[self copyColumns];
	
StatBrowserView*	brw=(StatBrowserView*)_brw;
MMsMatrix*			mmx=[brw matrix];
	uni_analysis(mmx,&_ana);
	MMsMatrixFree(mmx);
	
NSBundle*			bndl=[NSBundle bundleWithIdentifier:@"com.cbconseil.xmapstatuni"];
	
// Indicators allocation
	[self initBrowser:@"IndicBrowserView"
			   bundle:bndl
				label:NSLocalizedStringFromTableInBundle(@"indicators",nil,bndl,nil)
			   matrix:_ana.indic];

// Histogram allocation
	[self initGraph:@"HistogramGraphView"
			 bundle:bndl
			  label:NSLocalizedStringFromTableInBundle(@"histogram",nil,bndl,nil)
			 matrix:_ana.data];
	
// Skip to mapping tab
	[_tab selectLastTabViewItem:sender];

// Distribution diagram allocation
	[self initGraph:@"RepDiagramGraphView"
			 bundle:bndl
			  label:NSLocalizedStringFromTableInBundle(@"distributiondiagram",nil,bndl,nil)
			 matrix:_ana.clss];
	
	[self updateUI];
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateUI{	
	[_sav setEnabled:(_ana.indic!=NULL)];
	[_cpt setEnabled:([_brw selectedColumns]->count()==1)];
	
	[super updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(long)analysisType{
	return _kAnalysisUNI;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(NSString*)analysisExt{
	return @"uni";
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)saveToPath:(const char*)fpath
			 name:(const char*)fname{
	return YES;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)loadFromPath:(const char*)fpath
			   name:(const char*)fname
				app:(bGenericMacMapApp*)gapp{
	return YES;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)recoverPanel:(bGenericXMLBaseElement*)root{
_bTrace_("[StatMobWindowController recoverPanel]",true);
bGenericMacMapApp*		gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericXMLBaseElement*	elt=gapp->classMgr()->NthElement(root,1,"sign");
	if(!elt){
		return NO;
	}
char			val[_values_length_max_];
	elt->getvalue(val);
UInt32			sgn=(*(unsigned int*)val);
NSBundle*		bndl=[NSBundle bundleWithIdentifier:@"com.cbconseil.xmapstatuni"];
	
	switch(sgn){
		case kStatBrowserIndicatorPanelContentSignature:
_tm_("kStatBrowserIndicatorPanelContentSignature");
			[self initBrowser:@"IndicBrowserView"
					   bundle:bndl
						label:NSLocalizedStringFromTableInBundle(@"indicators",nil,bndl,nil)
					   matrix:_ana.indic];
			break;
		case kStatGraphHistogramPanelContentSignature:
_tm_("kStatGraphHistogramPanelContentSignature");
			[self initGraph:@"HistogramGraphView"
					 bundle:bndl
					  label:NSLocalizedStringFromTableInBundle(@"histogram",nil,bndl,nil)
					 matrix:_ana.data];
			break;
		case kStatGraphDistribDiagramPanelContentSignature:
_tm_("kStatGraphDistribDiagramPanelContentSignature");
			[self initGraph:@"RepDiagramGraphView"
					 bundle:bndl
					  label:NSLocalizedStringFromTableInBundle(@"distributiondiagram",nil,bndl,nil)
					 matrix:_ana.clss];
			break;
	}
	
	return YES;
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

#pragma mark ---- CPP/Carbon Entry Point ----
