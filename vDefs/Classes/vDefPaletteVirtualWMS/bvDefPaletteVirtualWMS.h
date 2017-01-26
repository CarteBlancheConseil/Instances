//----------------------------------------------------------------------------
// File : bvDefPaletteVirtualWMS.h
// Project : MacMap
// Purpose : Header file : WMS vdef class (connects to WMS services)
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

#ifndef __bvDefPaletteVirtualWMS__
#define __bvDefPaletteVirtualWMS__

//----------------------------------------------------------------------------

#include <vdef_lib/bvDefPaletteRange.h>
#include <Carbon/Carbon.h>

//----------------------------------------------------------------------------

class bvDefPaletteVirtualWMS : public bStdNSPalettevDef{
public:
    bvDefPaletteVirtualWMS					(	bGenericXMLBaseElement* elt, 
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bvDefPaletteVirtualWMS			(	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
    
    virtual bool test						(	bGenericType* tp);
    
    virtual void stl_alloc					(	);
    virtual bArray&	layers					(	){return(_layers);};
    virtual const char* url_get				(	){return(_url);};
    virtual void url_put					(	char* url){strcpy(_url,url);};
    virtual const char* usr_get				(	){return(_usr);};
    virtual void usr_put					(	char* usr){strcpy(_usr,usr);};
    virtual const char* pwd_get				(	){return(_pwd);};
    virtual void pwd_put					(	char* pwd){strcpy(_pwd,pwd);};
    virtual bool https_get                  (	){return(_https);};
    virtual void https_put					(	bool https){_https=https;};

protected:
    virtual void* ccinit					(	);
    
    virtual void stl_free					(	);

    virtual void make						(	);
    virtual bool read						(	);
    virtual bool write						(	);

private:
    bArray	_layers;
    char	_url[1024];
    char	_usr[256];
    char	_pwd[256];
    bool    _https;
};

//----------------------------------------------------------------------------

#endif
