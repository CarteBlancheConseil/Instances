//----------------------------------------------------------------------------
// File : bvDefQuickRectStyle.h
// Project : MacMap
// Purpose : Header file : Rectangle vdef style class
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
// 25/06/2012 creation.
//----------------------------------------------------------------------------

#ifndef __bvDefQuickRectStyle__
#define __bvDefQuickRectStyle__

//----------------------------------------------------------------------------

#include <vdef_lib/bvDefPaletteQuickStyle.h>

//----------------------------------------------------------------------------

class bvDefQuickRectStyle : public bvDefPaletteQuickStyle{
	public:
		bvDefQuickRectStyle				(	bGenericMacMapApp* gapp,
											bGenericType* gtp,
											int clss);
		virtual ~bvDefQuickRectStyle	(	);
		
		virtual bool load				(	bGenericXMLBaseElement* root);
		virtual bool dump				(	bArray& arr, 
											int indent);
											
		double		_width;
		int			_fwidth;
		double		_stroke[5];
		int			_fstroke;
		double		_fill[5];
		char		_pat[256];
		int			_ffill;
		double		_h;
		int			_fh;
		double		_v;
		int			_fv;
		double		_rradius;
		int			_frradius;
		static bool	_centro;
	
	protected:													
	
	private:
	
};

//----------------------------------------------------------------------------

#endif
