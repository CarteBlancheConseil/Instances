//----------------------------------------------------------------------------
// File : bvDefPropRectStyle.h
// Project : MacMap
// Purpose : Header file : proportionnal rectangle vdef style class
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
// 28/01/2013 creation.
//----------------------------------------------------------------------------

#ifndef __bvDefPropRectStyle__
#define __bvDefPropRectStyle__

//----------------------------------------------------------------------------

#include <vdef_lib/bvDefPalettePropStyle.h>

//----------------------------------------------------------------------------

class bvDefPropRectStyle : public bvDefPalettePropStyle{
	public:
		bvDefPropRectStyle			(	bGenericMacMapApp* gapp,
										bGenericType* gtp);
		virtual ~bvDefPropRectStyle	(	);
		
		virtual bool load			(	bGenericXMLBaseElement* root);
		virtual bool dump			(	bArray& arr, 
										int indent);
											
		double	_rat;
		double	_width;
		double	_stroke[5];
		char	_pat[256];
		double	_rradius;
		bool	_centro;
	
	protected:													
	
	private:
	
};

//----------------------------------------------------------------------------

#endif
