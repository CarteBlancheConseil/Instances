//----------------------------------------------------------------------------
// File : bXMapGeometryShift.h
// Project : MacMap
// Purpose : Header file : XMap class, shift polyline and polygon (equal distance in every point)
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
// 17/07/2007 creation.
// 01/07/2016 cocoa intf.
//----------------------------------------------------------------------------
// SCRIPT_COMPATIBLE
//----------------------------------------------------------------------------

#ifndef __bXMapGeometryShift__
#define __bXMapGeometryShift__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>

//----------------------------------------------------------------------------

class bXMapGeometryShift : public bStdXMap{
public:		
    bXMapGeometryShift						(	bGenericXMLBaseElement* elt, 
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bXMapGeometryShift				(	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
    
    virtual void open						(	int* flags);
    virtual bool edit						(	void* prm);
    virtual bool process					(	int msg,
                                                void* prm);
    virtual bool test						(	void* prm);

    double get_data                         (   ){return _dst;};
    void set_data                           (   double d){_dst=d;};
    
protected:		
    
private:
    virtual void shift						(	);
    virtual void shift						(	double d);
    
    double	_dst;
};

//----------------------------------------------------------------------------

#endif
