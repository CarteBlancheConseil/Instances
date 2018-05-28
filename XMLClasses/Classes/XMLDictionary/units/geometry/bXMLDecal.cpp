//----------------------------------------------------------------------------
// File : bXMLDecal.cpp
// Project : MacMap
// Purpose : C++ source file : shift tag class, used in styles
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
// 15/11/2017 ajout widthdecal.
//----------------------------------------------------------------------------

#include "bXMLDecal.h"
#include "math.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bDecalElement	::bDecalElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
				: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("decal");
	setobjectcompliant(true);
	_val=0;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bDecalElement::create(bGenericXMLBaseElement* elt){
	return(new bDecalElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bDecalElement::~bDecalElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bDecalElement::actionval(	bGenericGraphicContext* ctx,
								bStdXMLValueElement* elt,
								bGenericGeoElement* geo){
	elt->getvalue(geo,&_val);
	if(_val!=0){
		return(decal(ctx));
	}
	return(false);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bDecalElement::actionstd(bGenericGraphicContext* ctx){
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
	if(_val!=0){
		return(decal(ctx));
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bDecalElement::decal(bGenericGraphicContext *ctx){
double	v;
int		npts,*offsets,noffsets,nbuf;
float	*xpts,*ypts,*xbuf,*ybuf;
	
	ctx->getGeometry(&xpts,&ypts,&npts,&offsets,&noffsets);

	if(npts<1){
		return(true);
	}
	if(npts==1){
double	a=ctx->getAngle();
		a+=(M_PI/2.0);
		v=_val*ctx->getUnitCoef()*ctx->getFixConv();
		XYNewPos(xpts[0],ypts[0],v,a,&xpts[0],&ypts[0]);
		return(true);
	}
	
int		nnewpts=0,*newoffsets,nnewoffsets;
float	*newxpts,*newypts;
	
	newxpts=NULL;
	newypts=NULL;
	newoffsets=NULL;
	
	v=_val*ctx->getUnitCoef()*ctx->getFixConv();

	nnewoffsets=noffsets;
	newoffsets=(int*)malloc(nnewoffsets*sizeof(int));
	if(!newoffsets){
		return(true);
	}
	newoffsets[0]=0;
	
	for(int i=0;i<noffsets-1;i++){

		xbuf=NULL;
		ybuf=NULL;
		nbuf=0;

		XYDecal(&xpts[offsets[i]],&ypts[offsets[i]],offsets[i+1]-offsets[i],v,&xbuf,&ybuf,&nbuf);
		if(!xbuf){
			continue;
		}
		if(!ybuf){
			continue;
		}
		if(nbuf==0){
			continue;
		}
		
		if(!newxpts){
			newxpts=xbuf;
			newypts=ybuf;
			nnewpts=nbuf;
		}
		else{
			newxpts=(float*)realloc(newxpts,(nnewpts+nbuf)*sizeof(float));
			if(!newxpts){
				break;
			}
			newypts=(float*)realloc(newypts,(nnewpts+nbuf)*sizeof(float));
			if(!newypts){
				break;
			}
			memmove(&newxpts[nnewpts],xbuf,nbuf*sizeof(float));
			memmove(&newypts[nnewpts],ybuf,nbuf*sizeof(float));
			
			nnewpts+=nbuf;
			free(xbuf);
			xbuf=NULL;
			free(ybuf);
			ybuf=NULL;
		}
		
		newoffsets[i+1]=nnewpts;
	}
	
	if((newxpts)&&(newypts)&&(newoffsets)){
		ctx->setGeometry(newxpts,newypts,nnewpts,newoffsets,nnewoffsets);
	}
	
	if(newxpts){
		free(newxpts);
	}
	if(newypts){
		free(newypts);
	}
	if(newoffsets){
		free(newoffsets);
	}
	return(true);
}


// ---------------------------------------------------------------------------
// Constructeur
// ------------
bWidthDecalElement	::bWidthDecalElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
                    : bDecalElement(elt,gapp,bndl){
    setclassname("widthdecal");
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bWidthDecalElement::create(bGenericXMLBaseElement* elt){
    return(new bWidthDecalElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bWidthDecalElement::~bWidthDecalElement(){
}

// ---------------------------------------------------------------------------
//
// -----------
bool bWidthDecalElement::actionval(	bGenericGraphicContext* ctx,
                                    bStdXMLValueElement* elt,
                                    bGenericGeoElement* geo){
double  d;
double  w=ctx->getWidth();
    w/=ctx->getFixConv();
    w/=ctx->getUnitCoef();
    w/=2.0;

    elt->getvalue(geo,&d);
    
    if(d==0){
        _val=0;
    }
    else if(d<0){
        _val=-(w-d);
    }
    else{
        _val=w+d;
    }
    if(_val!=0){
        return(decal(ctx));
    }
    return(false);
}

// ---------------------------------------------------------------------------
//
// -----------
bool bWidthDecalElement::actionstd(bGenericGraphicContext* ctx){
double  d;
double  w=ctx->getWidth();
    w/=ctx->getFixConv();
    w/=ctx->getUnitCoef();
    w/=2.0;
    
    if(_elts.count()>0){
bStdXMLValueElement*	elt=find_value();
        if(elt==NULL){
            return(true);
        }
        elt->getvalue(NULL,&d);
    }
    else{
char	val[_values_length_max_];
        getvalue(val);
        d=atof(val);
    }
    
    if(d==0){
        _val=0;
    }
    else if(d<0){
        _val=-(w-d);
    }
    else{
        _val=w+d;
    }
    
    if(_val!=0){
        return(decal(ctx));
    }
    return(true);
}

