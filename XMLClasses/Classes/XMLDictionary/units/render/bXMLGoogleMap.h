//----------------------------------------------------------------------------
// File : bXMLGoogleMap.h
// Project : MacMap
// Purpose : Header file : google tiling service tag class, used in styles
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
// 28/02/2014 creation.
//----------------------------------------------------------------------------

#ifndef __bGoogleMapElement__
#define __bGoogleMapElement__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMLLowRenderElement.h>
#include <MacMapSuite/bStdProj.h>
#include <MacMapSuite/wgs84.h>
#include <MacMapSuite/bStdTable.h>

//----------------------------------------------------------------------------

class bGoogleMapElement : public bStdXMLLowRenderElement{
public:
	bGoogleMapElement						(	bGenericXMLBaseElement* elt, 
												bGenericMacMapApp* gapp, 
												CFBundleRef bndl);
	virtual ~bGoogleMapElement				(	);
	virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);

	virtual void init						(	void* ctx);
	
	virtual bool actionstd					(	bGenericGraphicContext* ctx);

private:
	char			_last[_values_length_max_];
	void*			_data;
	size_t			_sz;
	
	bStdProj*		_fromp;
	wgs84			_wgs;
};

//----------------------------------------------------------------------------

#endif
