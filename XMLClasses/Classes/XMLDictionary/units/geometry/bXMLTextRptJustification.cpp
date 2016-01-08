//----------------------------------------------------------------------------
// File : bXMLTextRptJustification.cpp
// Project : MacMap
// Purpose : C++ source file : text repeat and justify tag class, used in styles
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
// 22/02/2012 creation.
//----------------------------------------------------------------------------

#include "bXMLTextRptJustification.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bTextRptJustificationElement::bTextRptJustificationElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
							: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("textrptjustification");
	setobjectcompliant(true);
	_val=-1;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bTextRptJustificationElement::create(bGenericXMLBaseElement* elt){
	return(new bTextRptJustificationElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bTextRptJustificationElement::~bTextRptJustificationElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bTextRptJustificationElement::actionval(bGenericGraphicContext* ctx,
                                             bStdXMLValueElement* elt,
                                             bGenericGeoElement* geo){
	elt->getvalue(geo,&_val);
	return(rpt(ctx));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bTextRptJustificationElement::actionstd(bGenericGraphicContext* ctx){
	if(_elts.count()>0){
bStdXMLValueElement*	elt=find_value();
		if(elt==NULL){
			return(true);
		}
		elt->getvalue(NULL,&_val);
	}
	else{
char	val[_values_length_max_];
		getvalue(val);
		_val=atof(val);		
	}
	
	return(rpt(ctx));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bTextRptJustificationElement::rpt(bGenericGraphicContext *ctx){
bCoreTextInfo* txt=ctx->getText();
	if(!txt){
		return(true);
	}
	
int		npts,*offsets,noffsets;
float	*xpts,*ypts;

	ctx->getGeometry(&xpts,&ypts,&npts,&offsets,&noffsets);	
	if(npts<2){
		return(false);
	}

double	tlen=txt->textWidth();
double	r,llen=0;
	for(long i=0;i<noffsets-1;i++){
		if(offsets[i+1]-offsets[i]>1){
			r=length(&xpts[offsets[i]],&ypts[offsets[i]],offsets[i+1]-offsets[i]);
			if(r>llen){
				llen=r;
			}
		}
	}
	
	r=floor(llen/tlen);
	if(r<2){
		return(true);
	}
	
char*	t=(char*)malloc(txt->nGlyphs()*(int)r+1);
	
	t[0]=0;
	for(long i=0;i<r;i++){
		strcat(t,txt->text());
	}
	ctx->setText(t);
	free(t);
	
	return(true);
}

