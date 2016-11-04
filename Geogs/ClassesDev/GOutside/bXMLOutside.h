//----------------------------------------------------------------------------
// File : bXMLOutside.h
// Project : MacMap
// Purpose : Header file : Outside Geog formula class
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
// Outside with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// See the LICENSE.txt file for more information.
//
//----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------
// 26/01/2005 creation.
//----------------------------------------------------------------------------

#ifndef __bXMLOutside__
#define __bXMLOutside__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMLGeog.h>

//----------------------------------------------------------------------------

class bOutsideElement : public bStdXMLGeog{
public:
    bOutsideElement 						(   bGenericXMLBaseElement* elt,
                                                bGenericMacMapApp* gapp,
                                                CFBundleRef bndl );
    virtual ~bOutsideElement				(   );
    virtual bGenericXMLBaseElement* create	(   bGenericXMLBaseElement* elt);
    
    virtual void init						(   void* ctx);
    virtual void reset						(   bStdSolver* ctx);
            
private:
    bool    _full;
    bool    _strict;
};

//----------------------------------------------------------------------------

#endif
