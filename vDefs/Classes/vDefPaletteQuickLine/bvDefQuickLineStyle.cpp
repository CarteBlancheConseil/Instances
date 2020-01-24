//----------------------------------------------------------------------------
// File : bvDefQuickLineStyle.cpp
// Project : MacMap
// Purpose : C++ source file : Line vdef style class
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
// 27/06/2012 creation.
//----------------------------------------------------------------------------

#include "bvDefQuickLineStyle.h"
#include <limits.h>


// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefQuickLineStyle	::bvDefQuickLineStyle(bGenericMacMapApp* gapp,
										 bGenericType* gtp,
										 int clss)
					:bvDefPaletteQuickStyle(gapp,gtp,clss){
	for(int i=0;i<3;i++){
		_width[i]=0;
		_fwidth[i]=0;
		_stroke[i][0]=0;
		_stroke[i][1]=0;
		_stroke[i][2]=0;
		_stroke[i][3]=1;
		_stroke[i][4]=1;
		_fstroke[i]=0;
		_cap[i]=0;
		_fcap[i]=0;
		_join[i]=0;
		_fjoin[i]=0;
		strcpy(_dsh[i],"");
		_fdsh[i]=0;
		_smooth[i]=false;
		_fsmooth[i]=0;
		_dec[i]=0;
        _fdec[i]=0;
        _wdec[i]=false;
		_limit[i]=0;
		_flimit[i]=0;
	}
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefQuickLineStyle::~bvDefQuickLineStyle(){
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefQuickLineStyle::load(bGenericXMLBaseElement* root){
bGenericXMLBaseElement  *elt,*chld;
char                    val[_values_length_max_];
	
	for(_pass=1;_pass<=3;_pass++){
		if(!std_load(root)){
			// for new subtypes
			continue;
		}
		if(elt=_gapp->classMgr()->NthElement(_gstl,1,"stroke")){
			if(chld=_gapp->classMgr()->NthElement(elt,1,"red")){
				chld->getvalue(val);
				_stroke[_pass-1][0]=matof(val);
				_cc=4;
			}
			if(chld=_gapp->classMgr()->NthElement(elt,1,"green")){
				chld->getvalue(val);
				_stroke[_pass-1][1]=matof(val);
				_cc=4;
			}
			if(chld=_gapp->classMgr()->NthElement(elt,1,"blue")){
				chld->getvalue(val);
				_stroke[_pass-1][2]=matof(val);
				_cc=4;
			}
			
			if(chld=_gapp->classMgr()->NthElement(elt,1,"cyan")){
				chld->getvalue(val);
				_stroke[_pass-1][0]=matof(val);
				_cc=5;
			}
			if(chld=_gapp->classMgr()->NthElement(elt,1,"magenta")){
				chld->getvalue(val);
				_stroke[_pass-1][1]=matof(val);
				_cc=5;
			}
			if(chld=_gapp->classMgr()->NthElement(elt,1,"yellow")){
				chld->getvalue(val);
				_stroke[_pass-1][2]=matof(val);
				_cc=5;
			}
			if(chld=_gapp->classMgr()->NthElement(elt,1,"black")){
				chld->getvalue(val);
				_stroke[_pass-1][3]=matof(val);
				_cc=5;
			}
			
			if(chld=_gapp->classMgr()->NthElement(elt,1,"alpha")){
				chld->getvalue(val);
				if(_cc==4){
					_stroke[_pass-1][3]=matof(val);
				}
				else{
					_stroke[_pass-1][4]=matof(val);
				}
			}
			
			if(chld=_gapp->classMgr()->NthElement(elt,1,"colorfield16m")){
				chld->getvalue(val);
				_fstroke[_pass-1]=_gtp->fields()->get_index(val);
			}
		}
		
		if(elt=_gapp->classMgr()->NthElement(_gstl,1,"cap")){
			elt->getvalue(val);
			_cap[_pass-1]=atoi(val);
			if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
				chld->getvalue(val);
				_fcap[_pass-1]=_gtp->fields()->get_index(val);
			}
			if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
				chld->getvalue(val);
				_cap[_pass-1]=atoi(val);
			}
		}
		
		if(elt=_gapp->classMgr()->NthElement(_gstl,1,"join")){
			elt->getvalue(val);
			_join[_pass-1]=atoi(val);
			if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
				chld->getvalue(val);
				_fjoin[_pass-1]=_gtp->fields()->get_index(val);
			}
			if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
				chld->getvalue(val);
				_join[_pass-1]=atoi(val);
			}
		}
		
		if(elt=_gapp->classMgr()->NthElement(_gstl,1,"dash")){
			elt->getvalue(_dsh[_pass-1]);
			if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
				chld->getvalue(val);
				_fdsh[_pass-1]=_gtp->fields()->get_index(val);
			}
			if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
				chld->getvalue(_dsh[_pass-1]);
			}
		}
		
		if(elt=_gapp->classMgr()->NthElement(_gstl,1,"miterlimit")){
			elt->getvalue(val);
			_limit[_pass-1]=matof(val);
			if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
				chld->getvalue(val);
				_flimit[_pass-1]=_gtp->fields()->get_index(val);
			}
			if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
				chld->getvalue(val);
				_limit[_pass-1]=matof(val);
			}
		}
		
		if(elt=_gapp->classMgr()->NthElement(_gstl,1,"width")){
			elt->getvalue(val);
			_width[_pass-1]=matof(val);
			if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
				chld->getvalue(val);
				_fwidth[_pass-1]=_gtp->fields()->get_index(val);
			}
			if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
				chld->getvalue(val);
				_width[_pass-1]=matof(val);
			}
		}
		
		if(elt=_gapp->classMgr()->NthElement(_gstl,1,"decal")){
			elt->getvalue(val);
			_dec[_pass-1]=matof(val);
            _wdec[_pass-1]=false;
			if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
				chld->getvalue(val);
				_fdec[_pass-1]=_gtp->fields()->get_index(val);
			}
			if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
				chld->getvalue(val);
				_dec[_pass-1]=matof(val);
			}
		}
        else if(elt=_gapp->classMgr()->NthElement(_gstl,1,"widthdecal")){
            elt->getvalue(val);
            _dec[_pass-1]=matof(val);
            _wdec[_pass-1]=true;
            if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
                chld->getvalue(val);
                _fdec[_pass-1]=_gtp->fields()->get_index(val);
            }
            if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
                chld->getvalue(val);
                _dec[_pass-1]=matof(val);
            }
        }
        
		if(elt=_gapp->classMgr()->NthElement(_gstl,1,"smooth")){
			elt->getvalue(val);
			_smooth[_pass-1]=atoi(val);
			if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
				chld->getvalue(val);
				_fsmooth[_pass-1]=_gtp->fields()->get_index(val);
			}
			if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
				chld->getvalue(val);
				_smooth[_pass-1]=atoi(val);
			}
		}
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefQuickLineStyle::dump(bArray& arr, int indent){
char	nm[256];
	
	for(_pass=1;_pass<=3;_pass++){
		if(	(_width[_pass-1]<=0)	&&
		   (_fwidth[_pass-1]==0)	){
			continue;
		}
// StyleRun & Validity
		if(!std_dump(arr,indent)){
			return(false);
		}
// Render
		add_cdesc(arr,indent+2,"render","");
		
		add_cdesc(arr,indent+3,"stroke","");
		if(_cc==4){
			add_ddesc(arr,indent+4,"red",_stroke[_pass-1][0],2);
			add_ddesc(arr,indent+4,"green",_stroke[_pass-1][1],2);
			add_ddesc(arr,indent+4,"blue",_stroke[_pass-1][2],2);
			add_ddesc(arr,indent+4,"alpha",_stroke[_pass-1][3],2);
		}
		else{
			add_ddesc(arr,indent+4,"cyan",_stroke[_pass-1][0],2);
			add_ddesc(arr,indent+4,"magenta",_stroke[_pass-1][1],2);
			add_ddesc(arr,indent+4,"yellow",_stroke[_pass-1][2],2);
			add_ddesc(arr,indent+4,"black",_stroke[_pass-1][3],2);
			add_ddesc(arr,indent+4,"alpha",_stroke[_pass-1][4],2);
		}
		
		if(_fstroke[_pass-1]){
			_gtp->fields()->get_name(_fstroke[_pass-1],nm);
			add_cdesc(arr,indent+4,"colorfield16m",nm);
		}
		
		if(_fcap[_pass-1]){
			add_cdesc(arr,indent+3,"cap","");
			_gtp->fields()->get_name(_fcap[_pass-1],nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_idesc(arr,indent+4,"value",_cap[_pass-1]);
		}
		else{
			add_idesc(arr,indent+3,"cap",_cap[_pass-1]);
		}
		
		if(_fjoin[_pass-1]){
			add_cdesc(arr,indent+3,"join","");
			_gtp->fields()->get_name(_fjoin[_pass-1],nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_idesc(arr,indent+4,"value",_join[_pass-1]);
		}
		else{
			add_idesc(arr,indent+3,"join",_join[_pass-1]);
		}
		
		if(_fdsh[_pass-1]){
			add_cdesc(arr,indent+3,"dash","");
			_gtp->fields()->get_name(_fdsh[_pass-1],nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_cdesc(arr,indent+4,"value",_dsh[_pass-1]);
		}
		else /*if(strlen(_dsh[_pass-1])>0)*/{
			add_cdesc(arr,indent+3,"dash",_dsh[_pass-1]);
		}
		
		if(_flimit[_pass-1]){
			add_cdesc(arr,indent+3,"miterlimit","");
			_gtp->fields()->get_name(_flimit[_pass-1],nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_ddesc(arr,indent+4,"value",_limit[_pass-1],2);
		}
		else if((_join[_pass-1]==kCGLineJoinMiter)&&(_limit[_pass-1]>0)){
			add_ddesc(arr,indent+3,"miterlimit",_limit[_pass-1],2);
		}
		// Geometry
		add_cdesc(arr,indent+2,"stdgeometry","");
		if(!off_dump(arr,indent)){
			return(false);
		}
		
		if(_fwidth[_pass-1]){
			add_cdesc(arr,indent+3,"width","");
			_gtp->fields()->get_name(_fwidth[_pass-1],nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_ddesc(arr,indent+4,"value",_width[_pass-1],2);
		}
		else{
			add_ddesc(arr,indent+3,"width",_width[_pass-1],2);
		}
		
		if(_fdec[_pass-1]){
			add_cdesc(arr,indent+3,_wdec[_pass-1]?"widthdecal":"decal","");
			_gtp->fields()->get_name(_fdec[_pass-1],nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_ddesc(arr,indent+4,"value",_dec[_pass-1],2);
		}
		else if(_dec[_pass-1]!=0){
			add_ddesc(arr,indent+3,_wdec[_pass-1]?"widthdecal":"decal",_dec[_pass-1],2);
		}
		
		if(_fsmooth[_pass-1]){
			add_cdesc(arr,indent+3,"smooth","");
			_gtp->fields()->get_name(_fsmooth[_pass-1],nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_idesc(arr,indent+4,"value",_smooth[_pass-1]);
		}
		else if(_smooth[_pass-1]!=0){
			add_idesc(arr,indent+3,"smooth",1);
		}
		
	}
	return(true);
}

