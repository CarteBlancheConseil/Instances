//----------------------------------------------------------------------------
// File : bvDefPaletteQuickSymb.h
// Project : MacMap
// Purpose : Header file : Symbols vdef class
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
// 26/06/2012 creation.
//----------------------------------------------------------------------------

#ifndef __bvDefPaletteQuickSymb__
#define __bvDefPaletteQuickSymb__

//----------------------------------------------------------------------------

#include <vdef_lib/bvDefPaletteQuick.h>
#include <Carbon/Carbon.h>

//----------------------------------------------------------------------------

class bvDefPaletteQuickSymb : public bvDefPaletteQuick{
	public:		
		bvDefPaletteQuickSymb					(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl);
		virtual ~bvDefPaletteQuickSymb			(	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
		
		virtual bool test						(	bGenericType* tp);
		
	
	protected:
		virtual void* ccinit					(	);
		
		virtual void stl_alloc					(	);
		virtual void stl_free					(	);

	private:

	
};

//----------------------------------------------------------------------------

#endif
