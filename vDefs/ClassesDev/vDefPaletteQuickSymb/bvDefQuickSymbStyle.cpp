//----------------------------------------------------------------------------
// File : bvDefQuickSymbStyle.cpp
// Project : MacMap
// Purpose : C++ source file : Symbols vdef style class
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
// 26/06/2012 creation.
//----------------------------------------------------------------------------

#include "bvDefQuickSymbStyle.h"
#include <limits.h>
#include <Carbon/Carbon.h>
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefQuickSymbStyle::_centro=true;

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefQuickSymbStyle	::bvDefQuickSymbStyle(	bGenericMacMapApp* gapp,
										  bGenericType* gtp,
										  int clss)
					:bvDefPaletteQuickStyle(gapp,gtp,clss){
	_h=0;
	_fh=0;	
	_v=0;
	_fv=0;
	_a=0;
	_fa=0;
	_alpha=1;
	_falpha=0;
	strcpy(_smb,"");
	_fsmb=0;
                        
// -> NEW
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
// <- NEW
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefQuickSymbStyle::~bvDefQuickSymbStyle(){
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefQuickSymbStyle::load(bGenericXMLBaseElement* root){
bGenericXMLBaseElement		*elt,*chld;
char						val[_values_length_max_];
	
	if(!std_load(root)){
// for new subtypes
		return(false);
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"pdfdocument")){
		elt->getvalue(_smb);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fsmb=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(_smb);
		}
	}
	else if(elt=_gapp->classMgr()->NthElement(_gstl,1,"image")){
		elt->getvalue(_smb);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fsmb=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(_smb);
		}
	}
	else if(elt=_gapp->classMgr()->NthElement(_gstl,1,"icon")){
		elt->getvalue(_smb);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fsmb=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(_smb);
		}
	}
	
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"hsize")){
		elt->getvalue(val);
		_h=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fh=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_h=matof(val);
		}
	}
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"vsize")){
		elt->getvalue(val);
		_v=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fv=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_v=matof(val);
		}
	}
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"angle")){
		elt->getvalue(val);
		_a=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_fa=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_a=matof(val);
		}
	}
	if(elt=_gapp->classMgr()->NthElement(_gstl,1,"alpha")){
		elt->getvalue(val);
		_alpha=matof(val);
		if(chld=_gapp->classMgr()->NthElement(elt,1,"field")){
			chld->getvalue(val);
			_falpha=_gtp->fields()->get_index(val);
		}
		if(chld=_gapp->classMgr()->NthElement(elt,1,"value")){
			chld->getvalue(val);
			_alpha=matof(val);
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
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefQuickSymbStyle::dump(bArray& arr, int indent){
char	nm[256];
	if((_h==0)&&(_fh==0)){
		return(true);
	}
	if((_v==0)&&(_fv==0)){
		return(true);
	}
	if((strlen(_smb)==0)&&(_fsmb==0)){
		return(true);
	}
// StyleRun & Validity
	if(!std_dump(arr,indent)){
		return(false);
	}
// Render
	add_cdesc(arr,indent+2,"render","");
	if(GetImageKind(_smb)==kQTFileTypePDF){
		if(_fsmb){
			add_cdesc(arr,indent+3,"pdfdocument","");
			_gtp->fields()->get_name(_fsmb,nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_cdesc(arr,indent+4,"value",_smb);
		}
		else{
			add_cdesc(arr,indent+3,"pdfdocument",_smb);
		}
	}
	else{
		if(_fsmb){
			add_cdesc(arr,indent+3,"image","");
			_gtp->fields()->get_name(_fsmb,nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_cdesc(arr,indent+4,"value",_smb);
		}
		else{
			add_cdesc(arr,indent+3,"image",_smb);
		}
	}
	add_cdesc(arr,indent+3,"fill","");
	if(_falpha){
		add_cdesc(arr,indent+4,"alpha","");
		_gtp->fields()->get_name(_falpha,nm);
		add_cdesc(arr,indent+5,"field",nm);
		add_ddesc(arr,indent+5,"value",_alpha,2);
	}
	else{
		add_ddesc(arr,indent+4,"alpha",_alpha,2);
	}
	
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
    if( (	(_fbackwidth>0)				||
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

    
	// Geometry
	add_cdesc(arr,indent+2,"stdgeometry","");
	if(!off_dump(arr,indent)){
		return(false);
	}
	if(_centro){
		add_idesc(arr,indent+3,"centroid",1);
	}
	
 
    
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

    
    
    if(GetImageKind(_smb)==kQTFileTypePDF){
		if(_fsmb){
			add_cdesc(arr,indent+3,"pdfdocument","");
			_gtp->fields()->get_name(_fsmb,nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_cdesc(arr,indent+4,"value",_smb);
		}
		else{
			add_cdesc(arr,indent+3,"pdfdocument",_smb);
		}
	}
	else{
		if(_fsmb){
			add_cdesc(arr,indent+3,"image","");
			_gtp->fields()->get_name(_fsmb,nm);
			add_cdesc(arr,indent+4,"field",nm);
			add_cdesc(arr,indent+4,"value",_smb);
		}
		else{
			add_cdesc(arr,indent+3,"image",_smb);
		}
	}
	
	if(_fh){
		add_cdesc(arr,indent+3,"hsize","");
		_gtp->fields()->get_name(_fh,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_h,2);
	}
	else{
		add_ddesc(arr,indent+3,"hsize",_h,2);
	}
	if(_fv){
		add_cdesc(arr,indent+3,"vsize","");
		_gtp->fields()->get_name(_fh,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_v,2);
	}
	else{
		add_ddesc(arr,indent+3,"vsize",_v,2);
	}
	if(_fa){
		add_cdesc(arr,indent+3,"angle","");
		_gtp->fields()->get_name(_fa,nm);
		add_cdesc(arr,indent+4,"field",nm);
		add_ddesc(arr,indent+4,"value",_a,2);
	}
	else{
		add_ddesc(arr,indent+3,"angle",_a,2);
	}
	return(true);
}

