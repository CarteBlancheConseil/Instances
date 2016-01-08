//----------------------------------------------------------------------------
// File : bvDefPaletteUltra.h
// Project : MacMap
// Purpose : Header file : Ultra vdef class (edits all styles in an XML mode)
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
// 12/08/2013 creation.
//----------------------------------------------------------------------------

#ifndef __bvDefPaletteUltra__
#define __bvDefPaletteUltra__

//----------------------------------------------------------------------------

#include <vdef_lib/bvDefPaletteRange.h>
#include <Carbon/Carbon.h>

//----------------------------------------------------------------------------

class bvDefPaletteUltra : public bStdNSPalettevDef{
	public:		
		bvDefPaletteUltra						(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl);
		virtual ~bvDefPaletteUltra				(	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
		
		virtual bool test						(	bGenericType* tp);
		
		virtual char* txt_get					(	);
		virtual long siz_get					(	);
		virtual void txt_put					(	char* txt,
													long sz);

	protected:
		virtual void* ccinit					(	);
			
		virtual void make						(	);
		virtual bool read						(	);
		virtual bool write						(	);

	private:
		char*	_xml;
		long	_sz;
};

//----------------------------------------------------------------------------

#endif
