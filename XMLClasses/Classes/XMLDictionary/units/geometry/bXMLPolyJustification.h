//----------------------------------------------------------------------------
// File : bXMLPolyJustification.h
// Project : MacMap
// Purpose : Header file : justify on polyline tag class, used in styles
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
// 16/12/2003 creation.
//----------------------------------------------------------------------------

#ifndef __bPolyJustificationElement__
#define __bPolyJustificationElement__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMLLowRenderElement.h>
#include <mox_intf/CGUtils.h>
//#include <mox_intf/bCoreTextInfo.h>

//----------------------------------------------------------------------------

class bPolyJustificationElement : public bStdXMLLowRenderElement{
	public:
		bPolyJustificationElement 				(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl );
		virtual ~bPolyJustificationElement  	(	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
		
		virtual bool actionstd					(	bGenericGraphicContext* ctx);
		virtual bool actionval					(	bGenericGraphicContext* ctx,
													bStdXMLValueElement* elt,
													bGenericGeoElement* geo);
		
	protected:
		bool justify							(	bGenericGraphicContext *ctx);
		bool justify_line						(	bGenericGraphicContext* ctx,
													int	line,
													float* bsex,
													float* bsey,
													int nbse,
													float* x,
													float* y,
													float* a,
													int na,
													bCoreTextInfo* txt);
													
		void calcOrigin							(	float *xin, 
													float *yin, 
													int nin, 
													double width,
													float *xout, 
													float *yout, 
													int strt, 
													int *nout,
													double*	crcons);
		
		void nextPos							(	float*	xin,		// support x
													float*	yin,		// support y
													int		nin,		// nb support
													int*	crsin,		// curseur support
													float*	xout,		// positions x
													float*	yout,		// positions y
													float*	aout,		// positions alpha
													int		nout,		// nb positions
													bCoreTextInfo* txt,	// text
													int		cglyph,		// curseur caractère
													double	coef,		// coef justification
													double*	crcons);	// portion consommée du segment courant
													
		double	length							(	float x1, 
													float y1, 
													float x2, 
													float y2);
		double length							(	float *x, 
													float *y, 
													int start, 
													int end);
		double length							(	float *x, 
													float *y, 
													int n);	
	private:
		double	_val;
};

//----------------------------------------------------------------------------

#define	sqr(x) ((x)*(x))

//----------------------------------------------------------------------------
// 
// -----------
inline double bPolyJustificationElement::length(	float x1, 
													float y1, 
													float x2, 
													float y2){
	return(sqrt(sqr(x2-x1)+sqr(y2-y1)));											
}

//----------------------------------------------------------------------------
// 
// -----------
inline double bPolyJustificationElement::length(	float *x, 
													float *y, 
													int start, 
													int end){
int		i;
double	len=0;
	for(i=start+1;i<=end;i++){
		len+=length(x[i-1],y[i-1],x[i],y[i]);
	}
	return(len);										
}

//----------------------------------------------------------------------------
// 
// -----------
inline double bPolyJustificationElement::length(	float *x, 
													float *y, 
													int n){
	return(length(x,y,0,n-1));									
}

//----------------------------------------------------------------------------

#endif
