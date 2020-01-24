//----------------------------------------------------------------------------
// File : bvDefVirtualWMSStyle.cpp
// Project : MacMap
// Purpose : C++ source file : WMS vdef style class
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
// 13/07/2013 creation.
//----------------------------------------------------------------------------

#include "bvDefVirtualWMSStyle.h"
#include <limits.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefVirtualWMSStyle::bvDefVirtualWMSStyle(bGenericMacMapApp* gapp)
:bvDefVirtualStyle(gapp){
    _url[0]=0;
    _https=false;
    _usr[0]=0;
    _pwd[0]=0;
	_layer[0]=0;
	strcpy(_style,""/*"default"*/);
	strcpy(_fmt,"image/png");
	_srs=-1;
	_alpha=1;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefVirtualWMSStyle::~bvDefVirtualWMSStyle(){
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefVirtualWMSStyle::load(bGenericXMLBaseElement* root){
	if(!std_load(root)){
		return(false);
	}
bGenericXMLBaseElement*	elt;
	if((elt=_gapp->classMgr()->NthElement(_gstl,1,"wmsraster"))){
        if(elt->countelements()==2){
char                    usrpwd[256];
bGenericXMLBaseElement*	chld=elt->getelement(1);
            chld->getvalue(usrpwd);
char*                   p=strrchr(usrpwd,':');
            p[0]=0;
            p++;
            strcpy(_usr,usrpwd);
            strcpy(_pwd,p);
            chld=elt->getelement(2);
            chld->getvalue(_url);
        }
        else{
            elt->getvalue(_url);
        }
		parse_url();
	}
	else{
		return(false);
	}
char	value[_values_length_max_];
	if((elt=_gapp->classMgr()->NthElement(_gstl,1,"alpha"))){
		elt->getvalue(value);
		_alpha=matof(value);
	}
	else{
		_alpha=1;
	}
	return(true);
}

// ---------------------------------------------------------------------------
// Sample : http://www.geosignal.org/cgi-bin/wmsmap?Service=WMS&Version=1.1.0&Request=GetMap&Layers=Communes&Styles=default&Format=image/png&SRS=EPSG:27582
// ------------
bool bvDefVirtualWMSStyle::dump(bArray& arr, int indent){
	if(_url[0]==0){
		return(false);
	}
	if(!std_dump(arr,indent)){
		return(false);
	}
char	fullurl[2048];
	
	if(_srs>0){
		sprintf(fullurl,
				"http%s://%s?Service=WMS&Version=1.1.1&Layers=%s&Styles=%s&Format=%s&SRS=EPSG:%d",
				(_https?"s":""),_url,_layer,_style,_fmt,_srs);
	}
	else{
		sprintf(fullurl,
				"http%s://%s?Service=WMS&Version=1.1.1&Layers=%s&Styles=%s&Format=%s",
				(_https?"s":""),_url,_layer,_style,_fmt);
	}
    
    
	add_cdesc(arr,indent+2,"render","");
	add_cdesc(arr,indent+3,"fill","");
	add_ddesc(arr,indent+4,"alpha",_alpha,2);
    
    if(strlen(_usr)>0){
        add_cdesc(arr,indent+3,"wmsraster","");
char    usrpwd[256];
        sprintf(usrpwd,"%s:%s",_usr,_pwd);
        add_cdesc(arr,indent+4,"value",usrpwd);
        add_cdesc(arr,indent+4,"value",fullurl);
    }
    else{
        add_cdesc(arr,indent+3,"wmsraster",fullurl);
    }
    
	add_cdesc(arr,indent+2,"screengeometry","");
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bvDefVirtualWMSStyle::parse_url(){
_bTrace_("bvDefVirtualWMSStyle::parse_url",true);
char*	start;
char*	end;
	
	start=strstr(_url,"Layers=");
	if(start){
		start+=strlen("Layers=");
		end=strstr(start,"&");
		if(end==NULL){
			end=start+strlen(start);
		}
		strncpy(_layer,start,end-start);
		_layer[end-start]=0;
	}
	
	start=strstr(_url,"Styles=");
	if(start){
		start+=strlen("Styles=");
		end=strstr(start,"&");
		if(end==NULL){
			end=start+strlen(start);
		}
		strncpy(_style,start,end-start);
		_style[end-start]=0;
	}
	
	start=strstr(_url,"Format=");
	if(start){
		start+=strlen("Format=");
		end=strstr(start,"&");
		if(end==NULL){
			end=start+strlen(start);
		}
		strncpy(_fmt,start,end-start);
		_fmt[end-start]=0;
	}
	
char	buffer[2048];
	start=strstr(_url,"SRS=EPSG:");
	if(start){
		start+=strlen("SRS=EPSG:");
		end=strstr(start,"&");
		if(end==NULL){
			end=start+strlen(start);
		}
		strncpy(buffer,start,end-start);
		buffer[end-start]=0;
		//_srs=atoi(buffer);// On va fixer celui du projet
	}
	
	start=_url+7;
	end=strstr(start,"?");
	
	strncpy(buffer,start,end-start);
	buffer[end-start]=0;
	strcpy(_url,buffer);
	
_tm_(_url);
_tm_(_layer);
_tm_(_style);
_tm_(_fmt);
_tm_(_srs);
}

