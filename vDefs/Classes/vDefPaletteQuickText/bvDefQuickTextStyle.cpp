//----------------------------------------------------------------------------
// File : bvDefQuickTextStyle.cpp
// Project : MacMap
// Purpose : C++ source file : Text vdef style class
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
// 28/06/2012 creation.
//----------------------------------------------------------------------------

#include "bvDefQuickTextStyle.h"
#include <limits.h>
#include <Carbon/Carbon.h>

// ---------------------------------------------------------------------------
// Globals
// ------------
bool bvDefQuickTextStyle::_centro=false;

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefQuickTextStyle	::bvDefQuickTextStyle(bGenericMacMapApp* gapp,
										 bGenericType* gtp,
										 int clss)
					:bvDefPaletteQuickStyle(gapp,gtp,clss){
	_field=kOBJ_Name_;
	strcpy(_font,"Geneva");
	_ffont=0;
	_size=0;
	_fsize=0;
	_width=0;
	_fwidth=0;
	
	_backwidth=0;
	_fbackwidth=0;
	_backwidthmaj=0;
	_fbackwidthmaj=0;
	_backheightmaj=0;
	_fbackheightmaj=0;
	
	_backshiftx=0;
	_fbackshiftx=0;
	_backshifty=0;
	_fbackshifty=0;
	
	_rradius=0;
	_frradius=0;
	
	_fill[0]=0;
	_fill[1]=0;
	_fill[2]=0;
	_fill[3]=1;
	_fill[4]=1;
	_ffill=0;
	_stroke[0]=0;
	_stroke[1]=0;
	_stroke[2]=0;
	_stroke[3]=1;
	_stroke[4]=1;
	_fstroke=0;

	_backfill[0]=0;
	_backfill[1]=0;
	_backfill[2]=0;
	_backfill[3]=0;
	_backfill[4]=0;
	_fbackfill=0;
	_backstroke[0]=0;
	_backstroke[1]=0;
	_backstroke[2]=0;
	_backstroke[3]=1;
	_backstroke[4]=1;
	_fbackstroke=0;
	
	_just=0;
	_fjust=0;
	_iltr=0;
	_filtr=0;
	_iwrd=0;
	_fiwrd=0;	
	_angle=0;
	_fangle=0;
	_dec=0;
	_fdec=0;
	_dx=0;
	_fdx=0;
	_dy=0;
	_fdy=0;
	_smooth=false;
	_fsmooth=0;
	_legible=false;
	_flegible=0;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefQuickTextStyle::~bvDefQuickTextStyle(){
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefQuickTextStyle::load(bGenericXMLBaseElement* root){
bGenericXMLBaseElement		*chld,*elt;
char						val[_values_length_max_];
	
	if(!std_load(root)){
		// for new subtypes
		return(false);
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"font")){
		elt->getvalue(_font);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_ffont=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(_font);
		}
	}
	
	if(chld=_gapp->classMgr()->NthElement(_gstl,1,"text")){	
		if(elt=_gapp->classMgr()->NthElement(chld,1,"field")){
			elt->getvalue(val);
			_field=_gtp->fields()->get_index(val);
		}	
	}
	
	if(chld=_gapp->classMgr()->NthElement(_gstl,1,"fill")){	
		if(elt=_gapp->classMgr()->NthElement(chld,1,"red")){
			elt->getvalue(val);
			_fill[0]=matof(val);
			_cc=4;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"green")){
			elt->getvalue(val);
			_fill[1]=matof(val);
			_cc=4;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"blue")){
			elt->getvalue(val);
			_fill[2]=matof(val);
			_cc=4;
		}
		
		if(elt=_gapp->classMgr()->NthElement(chld,1,"cyan")){
			elt->getvalue(val);
			_fill[0]=matof(val);
			_cc=5;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"magenta")){
			elt->getvalue(val);
			_fill[1]=matof(val);
			_cc=5;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"yellow")){
			elt->getvalue(val);
			_fill[2]=matof(val);
			_cc=5;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"black")){
			elt->getvalue(val);
			_fill[3]=matof(val);
			_cc=5;
		}
		
		if(elt=_gapp->classMgr()->NthElement(chld,1,"alpha")){
			elt->getvalue(val);
			if(_cc==4){
				_fill[3]=matof(val);
			}
			else{
				_fill[4]=matof(val);
			}
		}
		
		if(elt=_gapp->classMgr()->NthElement(chld,1,"colorfield16m")){
			elt->getvalue(val);
			_ffill=_gtp->fields()->get_index(val);
		}
	}
	
	if(chld=_gapp->classMgr()->NthElement(_gstl,1,"stroke")){	
		if(elt=_gapp->classMgr()->NthElement(chld,1,"red")){
			elt->getvalue(val);
			_stroke[0]=matof(val);
			_cc=4;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"green")){
			elt->getvalue(val);
			_stroke[1]=matof(val);
			_cc=4;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"blue")){
			elt->getvalue(val);
			_stroke[2]=matof(val);
			_cc=4;
		}
		
		if(elt=_gapp->classMgr()->NthElement(chld,1,"cyan")){
			elt->getvalue(val);
			_stroke[0]=matof(val);
			_cc=5;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"magenta")){
			elt->getvalue(val);
			_stroke[1]=matof(val);
			_cc=5;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"yellow")){
			elt->getvalue(val);
			_stroke[2]=matof(val);
			_cc=5;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"black")){
			elt->getvalue(val);
			_stroke[3]=matof(val);
			_cc=5;
		}
		
		if(elt=_gapp->classMgr()->NthElement(chld,1,"alpha")){
			elt->getvalue(val);
			if(_cc==4){
				_stroke[3]=matof(val);
			}
			else{
				_stroke[4]=matof(val);
			}
		}
		
		if(elt=_gapp->classMgr()->NthElement(chld,1,"colorfield16m")){
			chld->getvalue(val);
			_fstroke=_gtp->fields()->get_index(val);
		}
	}
	
	if(chld=_gapp->classMgr()->NthElement(_gstl,1,"back")){
	}
	else if(chld=_gapp->classMgr()->NthElement(_gstl,1,"bgfill")){
	}
	if(chld){
		if(elt=_gapp->classMgr()->NthElement(chld,1,"red")){
			elt->getvalue(val);
			_backfill[0]=matof(val);
			_cc=4;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"green")){
			elt->getvalue(val);
			_backfill[1]=matof(val);
			_cc=4;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"blue")){
			elt->getvalue(val);
			_backfill[2]=matof(val);
			_cc=4;
		}
		
		if(elt=_gapp->classMgr()->NthElement(chld,1,"cyan")){
			elt->getvalue(val);
			_backfill[0]=matof(val);
			_cc=5;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"magenta")){
			elt->getvalue(val);
			_backfill[1]=matof(val);
			_cc=5;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"yellow")){
			elt->getvalue(val);
			_backfill[2]=matof(val);
			_cc=5;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"black")){
			elt->getvalue(val);
			_backfill[3]=matof(val);
			_cc=5;
		}
		
		if(elt=_gapp->classMgr()->NthElement(chld,1,"alpha")){
			elt->getvalue(val);
			if(_cc==4){
				_backfill[3]=matof(val);
			}
			else{
				_backfill[4]=matof(val);
			}
		}
		
		if(elt=_gapp->classMgr()->NthElement(chld,1,"colorfield16m")){
			elt->getvalue(val);
			_fbackfill=_gtp->fields()->get_index(val);
		}
	}
	
	if(chld=_gapp->classMgr()->NthElement(_gstl,1,"bgstroke")){
		if(elt=_gapp->classMgr()->NthElement(chld,1,"red")){
			elt->getvalue(val);
			_backstroke[0]=matof(val);
			_cc=4;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"green")){
			elt->getvalue(val);
			_backstroke[1]=matof(val);
			_cc=4;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"blue")){
			elt->getvalue(val);
			_backstroke[2]=matof(val);
			_cc=4;
		}
		
		if(elt=_gapp->classMgr()->NthElement(chld,1,"cyan")){
			elt->getvalue(val);
			_backstroke[0]=matof(val);
			_cc=5;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"magenta")){
			elt->getvalue(val);
			_backstroke[1]=matof(val);
			_cc=5;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"yellow")){
			elt->getvalue(val);
			_backstroke[2]=matof(val);
			_cc=5;
		}
		if(elt=_gapp->classMgr()->NthElement(chld,1,"black")){
			elt->getvalue(val);
			_backstroke[3]=matof(val);
			_cc=5;
		}
		
		if(elt=_gapp->classMgr()->NthElement(chld,1,"alpha")){
			elt->getvalue(val);
			if(_cc==4){
				_backstroke[3]=matof(val);
			}
			else{
				_backstroke[4]=matof(val);
			}
		}
		
		if(elt=_gapp->classMgr()->NthElement(chld,1,"colorfield16m")){
			elt->getvalue(val);
			_fbackstroke=_gtp->fields()->get_index(val);
		}
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"size")){
		elt->getvalue(val);
		_size=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fsize=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_size=matof(val);
		}
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"width")){
		elt->getvalue(val);
		_width=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fwidth=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_width=matof(val);
		}
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"bgwidth")){
		elt->getvalue(val);
		_backwidth=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fbackwidth=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_backwidth=matof(val);
		}
	}
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"bgwidthmaj")){
		elt->getvalue(val);
		_backwidthmaj=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fbackwidthmaj=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_backwidthmaj=matof(val);
		}
	}
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"bgheightmaj")){
		elt->getvalue(val);
		_backheightmaj=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fbackheightmaj=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_backheightmaj=matof(val);
		}
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"bgshiftx")){
		elt->getvalue(val);
		_backshiftx=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fbackshiftx=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_backshiftx=matof(val);
		}
	}
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"bgshifty")){
		elt->getvalue(val);
		_backshifty=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fbackshifty=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_backshifty=matof(val);
		}
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"roundedradius")){
		elt->getvalue(val);
		_rradius=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_frradius=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_rradius=matof(val);
		}
	}	
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"centroid")){
		elt->getvalue(val);
		_centro=atoi(val);
	}
	else{
		_centro=false;
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"charspacing")){
		elt->getvalue(val);
		_iltr=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_filtr=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_iltr=matof(val);
		}
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"wordspacing")){
		elt->getvalue(val);
		_iwrd=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fiwrd=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_iwrd=matof(val);
		}
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"decal")){
		elt->getvalue(val);
		_dec=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fdec=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_dec=matof(val);
		}
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"shiftx")){
		elt->getvalue(val);
		_dx=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fdx=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_dx=matof(val);
		}
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"shifty")){
		elt->getvalue(val);
		_dy=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fdy=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_dy=matof(val);
		}
	}
	
	if(_centro){
		if(elt=_gapp->classMgr()->NthElement(_gstl,1,"angle")){
			elt->getvalue(val);
			_angle=matof(val);
			if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
				chld->getvalue(val);
				_fangle=_gtp->fields()->get_index(val);
			}
			if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
				chld->getvalue(val);
				_angle=matof(val);
			}
		}
		if(elt=_gapp->classMgr()->NthElement(_gstl,1,"pointjustification")){
			elt->getvalue(val);
			_just=matof(val);
			if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
				chld->getvalue(val);
				_fjust=_gtp->fields()->get_index(val);
			}
			if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
				chld->getvalue(val);
				_just=matof(val);
			}
		}
	}
	else{
		if(elt=_gapp->classMgr()->NthElement(_gstl,1,"legible")){
			elt->getvalue(val);
			_legible=atoi(val);
			if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
				chld->getvalue(val);
				_flegible=_gtp->fields()->get_index(val);
			}
			if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
				chld->getvalue(val);
				_legible=atoi(val);
			}
		}
		if(elt=_gapp->classMgr()->NthElement(_gstl,1,"smooth")){
			elt->getvalue(val);
			_smooth=atoi(val);
			if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
				chld->getvalue(val);
				_fsmooth=_gtp->fields()->get_index(val);
			}
			if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
				chld->getvalue(val);
				_smooth=atoi(val);
			}
		}
		if(elt=_gapp->classMgr()->NthElement(_gstl,1,"polyjustification")){
			elt->getvalue(val);
			_just=matof(val);
			if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
				chld->getvalue(val);
				_fjust=_gtp->fields()->get_index(val);
			}
			if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
				chld->getvalue(val);
				_just=matof(val);
			}
		}
	}
	
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefQuickTextStyle::dump(bArray& arr, int indent){
	if((_size==0)&&(_fsize==0)){
		return(true);
	}
	if((strlen(_font)==0)&&(_ffont==0)){
		return(true);
	}
// StyleRun & Validity
	if(!std_dump(arr,indent)){
		return(false);
	}
// Render	
char	nm[256];
	
	add_cdesc(arr,indent+2,"render","");
	
	if(	(_backfill[_cc-1]>0)	||
		(_fbackfill!=0)			){
		add_cdesc(arr,indent+3,"bgfill","");
		if(_cc==4){
			add_ddesc(arr,indent+4,"red",_backfill[0],2);
			add_ddesc(arr,indent+4,"green",_backfill[1],2);
			add_ddesc(arr,indent+4,"blue",_backfill[2],2);
			add_ddesc(arr,indent+4,"alpha",_backfill[3],2);
		}
		else if(_cc==5){
			add_ddesc(arr,indent+4,"cyan",_backfill[0],2);
			add_ddesc(arr,indent+4,"magenta",_backfill[1],2);
			add_ddesc(arr,indent+4,"yellow",_backfill[2],2);
			add_ddesc(arr,indent+4,"black",_backfill[3],2);
			add_ddesc(arr,indent+4,"alpha",_backfill[4],2);
		}
		if(_fbackfill){
			_gtp->fields()->get_name(_fbackfill,nm);
			add_cdesc(arr,indent+4,"colorfield16m",nm);
		}
	}
	if(	(	(_fbackwidth>0)				||
			(_backwidth>0)	)			&&
		(	(_backstroke[_cc-1]>0)		||
		(_fbackstroke!=0)		)	){
		   add_cdesc(arr,indent+3,"bgstroke","");
		   if(_cc==4){
			   add_ddesc(arr,indent+4,"red",_backstroke[0],2);
			   add_ddesc(arr,indent+4,"green",_backstroke[1],2);
			   add_ddesc(arr,indent+4,"blue",_backstroke[2],2);
			   add_ddesc(arr,indent+4,"alpha",_backstroke[3],2);
		   }
		   else if(_cc==5){
			   add_ddesc(arr,indent+4,"cyan",_backstroke[0],2);
			   add_ddesc(arr,indent+4,"magenta",_backstroke[1],2);
			   add_ddesc(arr,indent+4,"yellow",_backstroke[2],2);
			   add_ddesc(arr,indent+4,"black",_backstroke[3],2);
			   add_ddesc(arr,indent+4,"alpha",_backstroke[4],2);
		   }
		   if(_fbackstroke){
			   _gtp->fields()->get_name(_fbackstroke,nm);
			   add_cdesc(arr,indent+4,"colorfield16m",nm);
		   }
	   }
	
	add_cdesc(arr,indent+3,"fill","");
	if(_cc==4){
		add_ddesc(arr,indent+4,"red",_fill[0],2);
		add_ddesc(arr,indent+4,"green",_fill[1],2);
		add_ddesc(arr,indent+4,"blue",_fill[2],2);
		add_ddesc(arr,indent+4,"alpha",_fill[3],2);
	}
	else if(_cc==5){
		add_ddesc(arr,indent+4,"cyan",_fill[0],2);
		add_ddesc(arr,indent+4,"magenta",_fill[1],2);
		add_ddesc(arr,indent+4,"yellow",_fill[2],2);
		add_ddesc(arr,indent+4,"black",_fill[3],2);
		add_ddesc(arr,indent+4,"alpha",_fill[4],2);
	}
	if(_ffill){
		_gtp->fields()->get_name(_ffill,nm);
		add_cdesc(arr,indent+4,"colorfield16m",nm);
	}
	
	if((_width>0)||(_fwidth!=0)){
		add_cdesc(arr,indent+3,"stroke","");
		if(_cc==4){
			add_ddesc(arr,indent+4,"red",_stroke[0],2);
			add_ddesc(arr,indent+4,"green",_stroke[1],2);
			add_ddesc(arr,indent+4,"blue",_stroke[2],2);
			add_ddesc(arr,indent+4,"alpha",_stroke[3],2);
		}
		else if(_cc==5){
			add_ddesc(arr,indent+4,"cyan",_stroke[0],2);
			add_ddesc(arr,indent+4,"magenta",_stroke[1],2);
			add_ddesc(arr,indent+4,"yellow",_stroke[2],2);
			add_ddesc(arr,indent+4,"black",_stroke[3],2);
			add_ddesc(arr,indent+4,"alpha",_stroke[4],2);
		}
		if(_fstroke){
			_gtp->fields()->get_name(_fstroke,nm);
			add_cdesc(arr,indent+4,"colorfield16m",nm);
		}
	}
	add_cdesc(arr,indent+3,"dash","");
	
// Geometry
	add_cdesc(arr,indent+2,"stdgeometry","");
	if(!off_dump(arr,indent)){
		return(false);
	}
	
	if(_fsize){
		add_cdesc(arr,indent+3,"size","");
		_gtp->fields()->get_name(_fsize,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_size,2);
	}
	else{
		add_ddesc(arr,indent+3,"size",_size,2);
	}
	
	if(_fwidth){
		add_cdesc(arr,indent+3,"width","");
		_gtp->fields()->get_name(_fwidth,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_width,2);
	}
	else{
		add_ddesc(arr,indent+3,"width",_width,2);
	}
	
// -> NEW
	if(_fbackwidth){
		add_cdesc(arr,indent+3,"bgwidth","");
		_gtp->fields()->get_name(_fbackwidth,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_backwidth,2);
	}
	else{
		add_ddesc(arr,indent+3,"bgwidth",_backwidth,2);
	}
	if(_fbackwidthmaj){
		add_cdesc(arr,indent+3,"bgwidthmaj","");
		_gtp->fields()->get_name(_fbackwidthmaj,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_backwidthmaj,2);
	}
	else{
		add_ddesc(arr,indent+3,"bgwidthmaj",_backwidthmaj,2);
	}
	if(_fbackheightmaj){
		add_cdesc(arr,indent+3,"bgheightmaj","");
		_gtp->fields()->get_name(_fbackheightmaj,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_backheightmaj,2);
	}
	else{
		add_ddesc(arr,indent+3,"bgheightmaj",_backheightmaj,2);
	}
	
	if(_fbackshiftx){
		add_cdesc(arr,indent+3,"bgshiftx","");
		_gtp->fields()->get_name(_fbackshiftx,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_backshiftx,2);
	}
	else{
		add_ddesc(arr,indent+3,"bgshiftx",_backshiftx,2);
	}
	if(_fbackshifty){
		add_cdesc(arr,indent+3,"bgshifty","");
		_gtp->fields()->get_name(_fbackshifty,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_backshifty,2);
	}
	else{
		add_ddesc(arr,indent+3,"bgshifty",_backshifty,2);
	}
	
	if(_frradius){
		add_cdesc(arr,indent+3,"roundedradius","");
		_gtp->fields()->get_name(_frradius,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_rradius,2);
	}
	else{
		add_ddesc(arr,indent+3,"roundedradius",_rradius,2);
	}		
// <- NEW
	
	
	if(_filtr){
		add_cdesc(arr,indent+3,"charspacing","");
		_gtp->fields()->get_name(_filtr,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_iltr,2);
	}
	else{
		add_ddesc(arr,indent+3,"charspacing",_iltr,2);
	}
	
	if(_fiwrd){
		add_cdesc(arr,indent+3,"wordspacing","");
		_gtp->fields()->get_name(_fiwrd,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_iwrd,2);
	}
	else{
		add_ddesc(arr,indent+3,"wordspacing",_iwrd,2);
	}
	
	if(_fdx){
		add_cdesc(arr,indent+3,"shiftx","");
		_gtp->fields()->get_name(_fdx,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_dx,2);
	}
	else if(_dx!=0){
		add_ddesc(arr,indent+3,"shiftx",_dx,2);
	}
	if(_fdy){
		add_cdesc(arr,indent+3,"shifty","");
		_gtp->fields()->get_name(_fdy,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_dy,2);
	}
	else if(_dy!=0){
		add_ddesc(arr,indent+3,"shifty",_dy,2);
	}
	
	if(_centro){
		add_idesc(arr,indent+3,"centroid",1);
		if(_fangle){
			add_cdesc(arr,indent+3,"angle","");
			_gtp->fields()->get_name(_fangle,nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_ddesc(arr,indent+4,"value",_angle,2);
		}
		else{
			add_ddesc(arr,indent+3,"angle",_angle,2);
		}
		if(_fdec){
			add_cdesc(arr,indent+3,"decal","");
			_gtp->fields()->get_name(_fdec,nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_ddesc(arr,indent+4,"value",_dec,2);
		}
		else if(_dec){
			add_ddesc(arr,indent+3,"decal",_dec,2);
		}
	}
	else{
		if(_flegible){
			add_cdesc(arr,indent+3,"legible","");
			_gtp->fields()->get_name(_flegible,nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_idesc(arr,indent+4,"value",_legible);
		}
		else if(_legible!=0){
			add_idesc(arr,indent+3,"legible",1);
		}
		if(_fdec){
			add_cdesc(arr,indent+3,"decal","");
			_gtp->fields()->get_name(_fdec,nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_ddesc(arr,indent+4,"value",_dec,2);
		}
		else if(_dec){
			add_ddesc(arr,indent+3,"decal",_dec,2);
		}
		if(_fsmooth){
			add_cdesc(arr,indent+3,"smooth","");
			_gtp->fields()->get_name(_fsmooth,nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_idesc(arr,indent+4,"value",_smooth);
		}
		else if(_smooth!=0){
			add_idesc(arr,indent+3,"smooth",1);
		}
	}
	
// La police doit être après la taille
	if(_ffont){
		add_cdesc(arr,indent+3,"font","");
		_gtp->fields()->get_name(_ffont,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_cdesc(arr,indent+4,"value",_font);
	}
	else{
		add_cdesc(arr,indent+3,"font",_font);
	}
	
// Le texte doit être à la fin pour que le ATSTextLayout prenne toutes les caractéristiques
	_gtp->fields()->get_name(_field,nm);
	add_cdesc(arr,indent+3,"text","");
	add_cdesc(arr,indent+4,"field",nm);
	
// la justification doit être en dernier car elle utilise ATSTextLayout
	if(_centro){
		if(_fjust){
			add_cdesc(arr,indent+3,"pointjustification","");
			_gtp->fields()->get_name(_fjust,nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_ddesc(arr,indent+4,"value",_just,4);
		}
		else{
			add_ddesc(arr,indent+3,"pointjustification",_just,4);
		}
	}
	else{
		if(_fjust){
			add_cdesc(arr,indent+3,"polyjustification","");
			_gtp->fields()->get_name(_fjust,nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_ddesc(arr,indent+4,"value",_just,4);
		}
		else{
			add_ddesc(arr,indent+3,"polyjustification",_just,4);
		}
	}
	return(true);
}
