//----------------------------------------------------------------------------
// File : bvDefHistoStyle.h
// Project : MacMap
// Purpose : Header file : Histogram vdef style class
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
// 09/07/2013 creation.
//----------------------------------------------------------------------------

#ifndef __bvDefHistoStyle__
#define __bvDefHistoStyle__

//----------------------------------------------------------------------------

#include <vdef_lib/bvDefPaletteRangeStyle.h>

//----------------------------------------------------------------------------

class bvDefHistoStyle{
	public:
		bvDefHistoStyle				(	bGenericMacMapApp* gapp,
										bGenericType* gtp,
										bArray* arr);
		virtual ~bvDefHistoStyle	(	);
	
		virtual bool load			(	bGenericXMLBaseElement* root);
		virtual bool dump			(	bArray& arr, 
										int indent);
	
		virtual bool is_back		(	){return(_isback);};
	
// Std
		int		_fld;// Champ Classe
		int		_idx;
		
		double	_smin;
		double	_smax;
		
		int		_offx;
		int		_offy;
		int		_cc;
		
// Dimension
		double	_dimx;
		double	_dimy;
		double	_dx;
		double	_dy;

// Valeurs Min/Max
		double	_vmin;
		double	_vmax;
// Espacement
		double	_spc;
// Orientation
		bool	_onx;
	
// Champs
		bArray*	_arr;
		
		double	_width;
		double	_stroke[5];
		double	_fill[5];
	
		bool	_centro;
	
		bool	_isback;
		
	protected:													
		virtual bool std_load		(	bGenericXMLBaseElement* root);
		virtual bool std_dump		(	bArray& arr, 
										int indent);
		virtual bool off_load		(	bGenericXMLBaseElement* root);
		virtual bool off_dump		(	bArray& arr, 
										int indent);
		
		virtual void find_stylerun	(	bGenericXMLBaseElement* root);
		
		bGenericXMLBaseElement*	_gstl;
		bGenericMacMapApp*		_gapp;
		bGenericType*			_gtp;
		
	private:
		static bool test_stylerun	(	bGenericXMLBaseElement *root, 
										void *prm,
										int indent);
	
	
};

//----------------------------------------------------------------------------

#endif
