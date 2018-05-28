//----------------------------------------------------------------------------
// File : bvDefRangeLineStyle.h
// Project : MacMap
// Purpose : Header file : Range line vdef style class
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
// 30/08/2012 creation.
//----------------------------------------------------------------------------

#ifndef __bvDefRangeLineStyle__
#define __bvDefRangeLineStyle__

//----------------------------------------------------------------------------

#include <vdef_lib/bvDefPaletteRangeStyle.h>

//----------------------------------------------------------------------------

class bvDefRangeLineStyle : public bvDefPaletteRangeStyle{
public:
    bvDefRangeLineStyle			(	bGenericMacMapApp* gapp,
                                    bGenericType* gtp,
                                    int clss);
    bvDefRangeLineStyle			(	bvDefRangeLineStyle* stl,
                                        int clss);
virtual ~bvDefRangeLineStyle	(	);
    
    virtual bool load			(	bGenericXMLBaseElement* root);
    virtual bool dump			(	bArray& arr, 
                                    int indent);
                                        
    double	_width;
    int		_cap;
    int		_join;
    char	_dsh[256];
    bool	_smooth;
    double	_dec;
    bool	_wdec;
    double	_limit;

protected:													

private:
	
};

//----------------------------------------------------------------------------

#endif
