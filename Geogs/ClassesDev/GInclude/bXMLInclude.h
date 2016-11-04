//----------------------------------------------------------------------------
// File : bXMLInclude.h
// Project : MacMap
// Purpose : Header file : Include Geog formula class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2006 Carte Blanche Conseil.
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
// 15/03/2006 creation.
//----------------------------------------------------------------------------

#ifndef __bXMLInclude__
#define __bXMLInclude__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMLGeog.h>

//----------------------------------------------------------------------------

class bIncludeElement : public bStdXMLGeog{
public:		
    bIncludeElement 						(	bGenericXMLBaseElement* elt, 
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl );
    virtual ~bIncludeElement				(	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
    
    virtual void init						(	void* ctx);
    static int process_for_surf				(	void* o, 
                                                void* prm);
    static int process_for_line				(	void* o, 
                                                void* prm);
    
private:
    bool					_full;
    bool					_strict;
    bSelectSolver*			_ctx;
    bGenericGeoElement*		_ref;
    ivx_rect				_vxr;
};

//----------------------------------------------------------------------------

#endif
