//----------------------------------------------------------------------------
// File : bvDefPalettePieChart.h
// Project : MacMap
// Purpose : Header file : Pie chart vdef class
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

#ifndef __bvDefPalettePieChart__
#define __bvDefPalettePieChart__

//----------------------------------------------------------------------------

#include <std_ext/bStdNSPalettevDef.h>

//----------------------------------------------------------------------------

class bvDefPalettePieChart : public bStdNSPalettevDef{
	public:		
		bvDefPalettePieChart					(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl);
		virtual ~bvDefPalettePieChart			(	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
		
		virtual bool test						(	bGenericType* tp);
		
		virtual void stl_alloc					(	bool);

		virtual void fld_put					(	int fld){_fld=fld;};

		virtual double* strk_get				(	){return(_stroke);};
		virtual void strk_put					(	double* stroke){
													_stroke[0]=stroke[0];
													_stroke[1]=stroke[1];
													_stroke[2]=stroke[2];
													_stroke[3]=stroke[3];
													_stroke[4]=stroke[4];};
	
		virtual double wdth_get					(	){return(_width);};
		virtual void wdth_put					(	double width){_width=width;};

		virtual bArray&	fields					(	){return(_fields);};

		virtual bool prop_get					(	){return(_prop);};
		virtual void prop_put					(	bool prop){_prop=prop;};

	protected:
		virtual void* ccinit					(	);
		
		virtual void stl_free					(	);
	
		virtual void make						(	);
		virtual bool read						(	);
		virtual bool write						(	);

	private:
		bool				_prop;
		bArray				_fields;
		double				_width;
		double				_stroke[5];
	
};

//----------------------------------------------------------------------------

#endif
