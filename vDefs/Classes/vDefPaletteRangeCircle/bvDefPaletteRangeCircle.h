//----------------------------------------------------------------------------
// File : bvDefPaletteRangeCircle.h
// Project : MacMap
// Purpose : Header file : Range circle vdef class
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

#ifndef __bvDefPaletteRangeCircle__
#define __bvDefPaletteRangeCircle__

//----------------------------------------------------------------------------

#include <vdef_lib/bvDefPaletteRange.h>
#include <Carbon/Carbon.h>

//----------------------------------------------------------------------------

class bvDefPaletteRangeCircle : public bvDefPaletteRange{
public:		
	bvDefPaletteRangeCircle					(	bGenericXMLBaseElement* elt, 
												bGenericMacMapApp* gapp, 
												CFBundleRef bndl);
	virtual ~bvDefPaletteRangeCircle		(	);
	virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
	
	virtual bool test						(	bGenericType* tp);
	
	virtual void stl_alloc					(	int idx);

protected:
	virtual void* ccinit					(	);
	
	virtual void stl_free					(	);
	virtual void rebuild_limits				(	);
	virtual bool read						(	);

private:
};

//----------------------------------------------------------------------------

#endif
