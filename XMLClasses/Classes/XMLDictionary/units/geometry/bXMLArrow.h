//----------------------------------------------------------------------------
// File : bXMLArrow.h
// Project : MacMap
// Purpose : Header file : arrow tag class, used in styles
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
// 21/12/2005 creation.
//----------------------------------------------------------------------------

#ifndef __bArrowElement__
#define __bArrowElement__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMLLowRenderElement.h>

//----------------------------------------------------------------------------

class bArrowElement : public bStdXMLLowRenderElement{
	public:
		bArrowElement							(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl );
		virtual ~bArrowElement  				(	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
		
		virtual void init						(	void* ctx);
		
		virtual bool actionstd					(	bGenericGraphicContext* ctx);
		virtual bool actionval					(	bGenericGraphicContext* ctx,
													bStdXMLValueElement* elt,
													bGenericGeoElement* geo);
	
	protected:
		virtual bool make_arrow					(	bGenericGraphicContext* ctx);
		virtual bool make_arrow					(	float* xpts, 
													float* ypts, 
													int npts, 
													float sz, 
													float* xout, 
													float* yout);

		double	length							(	float x1, 
													float y1, 
													float x2, 
													float y2);
		double length							(	float *x, 
													float *y, 
													int n);	
	
		double	_dr;
		
};

//----------------------------------------------------------------------------

#define	sqr(x) ((x)*(x))

//----------------------------------------------------------------------------
// 
// -----------
inline double bArrowElement::length(	float x1, 
										float y1, 
										float x2, 
										float y2){
	return(sqrt(sqr(x2-x1)+sqr(y2-y1)));											
}

//----------------------------------------------------------------------------
// 
// -----------
inline double bArrowElement::length(	float *x, 
										float *y, 
										int n){
long	i;
double	len=0;
	for(i=1;i<n;i++){
		len+=length(x[i-1],y[i-1],x[i],y[i]);
	}
	return(len);										
}

//----------------------------------------------------------------------------

#endif
