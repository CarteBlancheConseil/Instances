//----------------------------------------------------------------------------
// File : bvDefPieChartStyle.h
// Project : MacMap
// Purpose : Header file : Pie chart vdef style class
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

#ifndef __bvDefPieChartStyle__
#define __bvDefPieChartStyle__

//----------------------------------------------------------------------------

#include <vdef_lib/bvDefPaletteRangeStyle.h>

//----------------------------------------------------------------------------

class bvDefPieChartStyle{
	public:
		bvDefPieChartStyle			(	bGenericMacMapApp* gapp,
										bGenericType* gtp,
										bool prop,
										bArray* arr);
		virtual ~bvDefPieChartStyle	(	);
	
		virtual bool load			(	bGenericXMLBaseElement* root);
		virtual bool dump			(	bArray& arr, 
										int indent);
	
// Std
		int		_fld;// Champ Classe
		int		_idx;
		
		double	_smin;
		double	_smax;
		
		int		_offx;
		int		_offy;
		int		_cc;
		
// Prop
		bool	_prop;
		double	_qref;
		double	_qmax;
		double	_rref;// Rayon
		double	_exp;
		
// Champs
		bArray*	_arr;
		
		double	_width;
		double	_stroke[5];
		double	_fill[5];
		bool	_centro;
		bool	_isstrk;
		
	protected:													
		virtual bool std_load		(	bGenericXMLBaseElement* root);
		virtual bool std_dump		(	bArray& arr, 
											int indent);
		virtual bool prop_load		(	bGenericXMLBaseElement* root);
		virtual bool prop_dump		(	bArray& arr, 
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
