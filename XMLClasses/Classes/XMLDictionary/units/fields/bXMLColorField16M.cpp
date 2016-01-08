//----------------------------------------------------------------------------
// File : bXMLColorField16M.cpp
// Project : MacMap
// Purpose : C++ source file : 16.000.000 color field tag class, used in styles
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
// 04/07/2007 creation.
//----------------------------------------------------------------------------

#include "bXMLColorField16M.h"
#include <MacMapSuite/C_Utils.h>

// ---------------------------------------------------------------------------
// Field
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bColorField16MElement	::bColorField16MElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
						: bStdXMLRenderingElement(elt,gapp,bndl){
	setclassname("colorfield16m");
	setobjectcompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bColorField16MElement::create(bGenericXMLBaseElement* elt){
	return(new bColorField16MElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bColorField16MElement::~bColorField16MElement(){
}

// ---------------------------------------------------------------------------
// Action
// -----------
bool bColorField16MElement::action(bGenericGraphicContext *ctx){
bGenericGeoElement	*geo=ctx->getCurElement();
char				color[256]="RGB:0;0;0;1";

	if(geo){
		geo->getValue(_cfvalue,color);
	}
	strupper(color);
char	*cp,*addr;
int		x=1;
	if(strstr(color,"RGB")){
float	r,g,b,a;
		r=0;
		g=0;
		b=0;
		a=1;
		cp=color+4;
		addr=strtok(cp,";");
		while(addr){
			switch(x){
				case 1:
					r=atof(addr)/100.0;
					break;
				case 2:
					g=atof(addr)/100.0;
					break;
				case 3:
					b=atof(addr)/100.0;
					break;
				case 4:
					a=atof(addr)/100.0;
					break;
			}
			addr=strtok(NULL,";");
			if(addr==NULL){
				break;
			}
			x++;
			if(x>4){
				break;
			}
		}
		ctx->setRed(r);
		ctx->setGreen(g);
		ctx->setBlue(b);
		ctx->setAlpha(a);
	}
	else if(strstr(color,"CMYK")){
float	c,m,y,k,a;
		c=0;
		m=0;
		y=0;
		k=0;
		a=1;
		cp=color+5;
		addr=strtok(cp,";");
		while(addr){
			switch(x){
				case 1:
					c=atof(addr)/100.0;
					break;
				case 2:
					m=atof(addr)/100.0;
					break;
				case 3:
					y=atof(addr)/100.0;
					break;
				case 4:
					k=atof(addr)/100.0;
					break;
				case 5:
					a=atof(addr)/100.0;
					break;
			}
			addr=strtok(NULL,";");
			if(addr==NULL){
				break;
			}
			x++;
			if(x>5){
				break;
			}
		}
		ctx->setCyan(c);
		ctx->setMagenta(m);
		ctx->setYellow(y);
		ctx->setBlack(k);
		ctx->setAlpha(a);
	}
	else{
		//return(false);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// Field
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bv160ColorFieldElement	::bv160ColorFieldElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
						: bColorField16MElement(elt,gapp,bndl){
	setclassname("v160colorfield");
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bv160ColorFieldElement::create(bGenericXMLBaseElement* elt){
	return(new bv160ColorFieldElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bv160ColorFieldElement::~bv160ColorFieldElement(){
}
