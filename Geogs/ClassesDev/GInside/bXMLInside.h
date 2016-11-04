//----------------------------------------------------------------------------
// File : bXMLInside.h
// Project : MacMap
// Purpose : Header file : Inside Geog formula class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2005 Carte Blanche Conseil.
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
// Inside with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// See the LICENSE.txt file for more information.
//
//----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------
// 26/01/2005 creation.
//----------------------------------------------------------------------------

#ifndef __bXMLInside__
#define __bXMLInside__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMLGeog.h>

//----------------------------------------------------------------------------

class bInsideElement : public bStdXMLGeog{
public:		
    bInsideElement							(	bGenericXMLBaseElement* elt, 
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl );
    virtual ~bInsideElement					(	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
    
    virtual void init						(	void* ctx);
    static int process						(	void* o, 
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
