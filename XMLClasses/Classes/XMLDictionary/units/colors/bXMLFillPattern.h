//----------------------------------------------------------------------------
// File : bXMLFillPattern.h
// Project : MacMap
// Purpose : Header file : fill pattern tag class, used in styles
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
// 30/05/2006 creation.
//----------------------------------------------------------------------------

#ifndef __bFillPatternElement__
#define __bFillPatternElement__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMLLowRenderElement.h>

//----------------------------------------------------------------------------

class bFillPatternElement : public bStdXMLLowRenderElement{
	public:
		bFillPatternElement 					(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl );
		virtual ~bFillPatternElement  			(	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
		
		virtual void init						(	void* ctx);

		virtual bool actionstd					(	bGenericGraphicContext* ctx);
		virtual bool actionval					(	bGenericGraphicContext* ctx,
													bStdXMLValueElement* elt,
													bGenericGeoElement* geo);
	
	private:
		char			_last[_values_length_max_];
		void*			_data;
		int				_sz;
		bGenericType*	_tp;
};

//----------------------------------------------------------------------------

#endif
