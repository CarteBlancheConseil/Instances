//----------------------------------------------------------------------------
// File : bXMLSmooth.h
// Project : MacMap
// Purpose : Header file : smooth polyline tag class, used in styles
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
// 02/04/2003 creation.
//----------------------------------------------------------------------------

#ifndef __XMLSMOOTHCLASSE__
#define __XMLSMOOTHCLASSE__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMLLowRenderElement.h>

// ---------------------------------------------------------------------------

typedef struct curve{
	float	startx;
	float	starty;
	float	controlx;
	float	controly;
	float	endx;
	float	endy;
}curve;

//----------------------------------------------------------------------------

class bSmoothElement : public bStdXMLLowRenderElement{
	public:
		bSmoothElement 							(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl );
		virtual ~bSmoothElement  				(	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
				
		virtual bool actionstd					(	bGenericGraphicContext* ctx);
		virtual bool actionval					(	bGenericGraphicContext* ctx,
													bStdXMLValueElement* elt,
													bGenericGeoElement* geo);
	
	protected:
		bool smooth								(	bGenericGraphicContext* ctx);
		bool smooth_one							(	float* xpts,
													float* ypts,
													float* newxpts,
													float* newypts,
													int npts,
													int* gcurs);
		void mid								(	float *x, 
													float *y, 
													float x1, 
													float y1, 
													float x2, 
													float y2);
		void makecurve							(	float *xpts, 
													float *ypts, 
													int npts, 
													int *cur, 
													curve *crv, 
													int level, 
													float *lastx, 
													float *lasty);
};

// ---------------------------------------------------------------------------
// 
// ------------
inline void	bSmoothElement::mid(	float *x, 
									float *y, 
									float x1, 
									float y1, 
									float x2, 
									float y2){
	(*x)=(x1+x2)/2.0;
	(*y)=(y1+y2)/2.0;
}


//----------------------------------------------------------------------------

#endif
