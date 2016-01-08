//----------------------------------------------------------------------------
// File : bXMLSubStyle.h
// Project : MacMap
// Purpose : Header file : substyle tag class, used in complex styles
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
// 17/04/2007 creation
//----------------------------------------------------------------------------

#ifndef __bSubStyleElement__
#define __bSubStyleElement__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMLRenderingElement.h>
#include <MacMapSuite/bArray.h>
#include "bSubStyle.h"

//----------------------------------------------------------------------------

class bSubStyleElement : public bStdXMLRenderingElement{
	public:
		bSubStyleElement 						(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl );
		virtual ~bSubStyleElement  				(	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
		
		virtual void init						(	void* ctx);
		
		virtual bool applyforscale				(	bGenericGraphicContext* ctx);
		virtual bool applyforclass				(	bGenericGraphicContext* ctx);
		virtual bool applyforobject				(	bGenericGraphicContext* ctx);
	
	private:
		static bool ocompliant					(	bGenericXMLBaseElement* elt, 
													void* prm,
													int indent);
			
		bSubStyle	_stl;
		bArray		_arr;
};

//----------------------------------------------------------------------------

#endif
