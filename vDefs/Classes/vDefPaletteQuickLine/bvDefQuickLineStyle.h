//----------------------------------------------------------------------------
// File : bvDefQuickLineStyle.h
// Project : MacMap
// Purpose : Header file : Line vdef style class
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

#ifndef __bvDefQuickLineStyle__
#define __bvDefQuickLineStyle__

//----------------------------------------------------------------------------

#include <vdef_lib/bvDefPaletteQuickStyle.h>

//----------------------------------------------------------------------------

class bvDefQuickLineStyle : public bvDefPaletteQuickStyle{
public:
    bvDefQuickLineStyle				(	bGenericMacMapApp* gapp,
                                        bGenericType* gtp,
                                        int clss);
    virtual ~bvDefQuickLineStyle    (	);
    
    virtual bool load				(	bGenericXMLBaseElement* root);
    virtual bool dump				(	bArray& arr, 
                                        int indent);

    double	_width[3];
    int		_fwidth[3];
    double	_stroke[3][5];
    int		_fstroke[3];
    int		_cap[3];
    int		_fcap[3];
    int		_join[3];
    int		_fjoin[3];
    char	_dsh[3][256];
    int		_fdsh[3];
    bool	_smooth[3];
    int		_fsmooth[3];
    double	_dec[3];
    int		_fdec[3];
    bool    _wdec[3];
    double	_limit[3];
    int		_flimit[3];

protected:													

private:
	
};

//----------------------------------------------------------------------------

#endif
