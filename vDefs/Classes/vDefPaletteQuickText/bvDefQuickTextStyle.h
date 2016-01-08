//----------------------------------------------------------------------------
// File : bvDefQuickTextStyle.h
// Project : MacMap
// Purpose : Header file : Text vdef style class
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
// 28/06/2012 creation.
//----------------------------------------------------------------------------

#ifndef __bvDefQuickTextStyle__
#define __bvDefQuickTextStyle__

//----------------------------------------------------------------------------

#include <vdef_lib/bvDefPaletteQuickStyle.h>

//----------------------------------------------------------------------------

class bvDefQuickTextStyle : public bvDefPaletteQuickStyle{
	public:
		bvDefQuickTextStyle				(	bGenericMacMapApp* gapp,
											bGenericType* gtp,
											int clss);
		virtual ~bvDefQuickTextStyle		(	);
		
		virtual bool load				(	bGenericXMLBaseElement* root);
		virtual bool dump				(	bArray& arr, 
											int indent);
		int			_field;
		static bool	_centro;
		
		char		_font[256];
		int			_ffont;
		double		_size;
		int			_fsize;
		double		_width;
		int			_fwidth;
		
		double		_backwidth;
		int			_fbackwidth;
		double		_backwidthmaj;
		int			_fbackwidthmaj;
		double		_backheightmaj;
		int			_fbackheightmaj;
		
		double		_backshiftx;
		int			_fbackshiftx;
		double		_backshifty;
		int			_fbackshifty;
		
		double		_rradius;
		int			_frradius;
		
		double		_fill[5];
		int			_ffill;
		double		_stroke[5];
		int			_fstroke;
		double		_backfill[5];
		int			_fbackfill;
		double		_backstroke[5];
		int			_fbackstroke;
		
		double		_just;
		int			_fjust;
		double		_iltr;
		int			_filtr;
		double		_iwrd;
		int			_fiwrd;		
		double		_angle;
		int			_fangle;
		double		_dec;
		int			_fdec;		
		double		_dx;
		int			_fdx;
		double		_dy;
		int			_fdy;			
		bool		_smooth;
		int			_fsmooth;
		bool		_legible;
		int			_flegible;
	
	protected:													
	
	private:
	
};

//----------------------------------------------------------------------------

#endif
