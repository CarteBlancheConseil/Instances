//----------------------------------------------------------------------------
// File : bXMLPropSize.h
// Project : MacMap
// Purpose : Header file : proportionnal size tag class, used in styles
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
// Proportionnalité à une surface
//----------------------------------------------------------------------------
// 27/03/2007 creation.
// pour passer d'un rayon de cercle à un coté de carré
// à surface constante, multiplier par racine(Pi)
//----------------------------------------------------------------------------

#ifndef __bPropSizeElement__
#define __bPropSizeElement__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMLLowRenderElement.h>

//----------------------------------------------------------------------------

class bPropSizeElement : public bStdXMLLowRenderElement{
	public:
		bPropSizeElement						(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl );
		virtual ~bPropSizeElement				(	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
		
		virtual void init						(	void* ctx);
		virtual bool action						(	bGenericGraphicContext *ctx);
		
	private:
		double	_qref;// = min
		double	_qmax;
		double	_rref;
		double	_exp;
		double	_rat;
		double	_r;
		double	_iq,_ir;
};

//----------------------------------------------------------------------------

#endif
