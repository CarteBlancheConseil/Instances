//----------------------------------------------------------------------------
// File : bvDefPalettePropRect.h
// Project : MacMap
// Purpose : Header file : proportionnal rectangle vdef class
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

#ifndef __bvDefPalettePropRect__
#define __bvDefPalettePropRect__

//----------------------------------------------------------------------------

#include <vdef_lib/bvDefPaletteProp.h>


//----------------------------------------------------------------------------

class bvDefPalettePropRect : public bvDefPaletteProp{
	public:		
		bvDefPalettePropRect					(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl);
		virtual ~bvDefPalettePropRect			(	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
		
		virtual bool test						(	bGenericType* tp);
		
		virtual void stl_alloc					(	);

	protected:
		virtual void* ccinit					(	);
		
		virtual void stl_free					(	);
		virtual bool read						(	);

	private:

	
};

//----------------------------------------------------------------------------

#endif
