//----------------------------------------------------------------------------
// File : bvDefPropCircleStyle.h
// Project : MacMap
// Purpose : Header file : proportionnal circle vdef style class
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
// 02/01/2013 creation.
//----------------------------------------------------------------------------

#ifndef __bvDefPropCircleStyle__
#define __bvDefPropCircleStyle__

//----------------------------------------------------------------------------

#include <vdef_lib/bvDefPalettePropStyle.h>

//----------------------------------------------------------------------------

class bvDefPropCircleStyle : public bvDefPalettePropStyle{
	public:
		bvDefPropCircleStyle			(	bGenericMacMapApp* gapp,
											bGenericType* gtp);
		virtual ~bvDefPropCircleStyle	(	);
		
		virtual bool load				(	bGenericXMLBaseElement* root);
		virtual bool dump				(	bArray& arr, 
											int indent);
											
		double	_width;
		double	_stroke[5];
		char	_pat[256];
		bool	_centro;
	
	protected:													
	
	private:
	
};

//----------------------------------------------------------------------------

#endif
