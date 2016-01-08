//----------------------------------------------------------------------------
// File : bXMLPropColor.h
// Project : MacMap
// Purpose : Header file : proportionnal color tag class, used in styles
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
// 30/06/2008 creation.
//----------------------------------------------------------------------------

#ifndef __bPropColorElement__
#define __bPropColorElement__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMLLowRenderElement.h>

//----------------------------------------------------------------------------

class bPropColorElement : public bStdXMLLowRenderElement{
	public:
		bPropColorElement						(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl );
		virtual ~bPropColorElement				(	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
		
		virtual void init						(	void* ctx);
		virtual bool action						(	bGenericGraphicContext *ctx);
		
	private:
		double				_qmin;
		double				_qmax;
		double				_x;
		int					_ncc;
		float				_cmin[5];
		float				_cmax[5];
		float				_c[5];
};

//----------------------------------------------------------------------------

#endif
