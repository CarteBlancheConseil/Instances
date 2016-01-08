//----------------------------------------------------------------------------
// File : bXMLPolyJustification.cpp
// Project : MacMap
// Purpose : C++ source file : justify on polyline tag class, used in styles
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

#include "bXMLPolyJustification.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bPolyJustificationElement	::bPolyJustificationElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
							: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("polyjustification");
	setobjectcompliant(true);
	_val=-1;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bPolyJustificationElement::create(bGenericXMLBaseElement* elt){
	return(new bPolyJustificationElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bPolyJustificationElement::~bPolyJustificationElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bPolyJustificationElement::actionval(	bGenericGraphicContext* ctx,
											bStdXMLValueElement* elt,
											bGenericGeoElement* geo){
	elt->getvalue(geo,&_val);
	if((_val>=0)&&(_val<=1)){
		ctx->setJustification(_val);
		return(justify(ctx));
	}
	else if(_val==2){
		ctx->setJustification(_val);
		return(justify(ctx));
	}
	return(false);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bPolyJustificationElement::actionstd(bGenericGraphicContext* ctx){
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
	if((_val>=0)&&(_val<=1)){
		ctx->setJustification(_val);
		return(justify(ctx));
	}
	if(_val==2){
		ctx->setJustification(_val);
bool	b=justify(ctx);
		return(b);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bPolyJustificationElement::justify(bGenericGraphicContext *ctx){
//_bTrace_("bPolyJustificationElement::justify",true);
bCoreTextInfo* txt=ctx->getText();
	if(!txt){
		return(true);
	}
	
int	n=txt->nGlyphs();
	
	if(n<=0){
		return(true);
	}
	txt->setAlign(_val);
	
int		npts,*offsets,noffsets;
float	*xpts,*ypts;

	ctx->getGeometry(&xpts,&ypts,&npts,&offsets,&noffsets);	
	if(npts<2){
		return(false);
	}

float*	bsex=NULL;
float*	bsey=NULL;
int		bsenpts;
float	d,sz=ctx->getVSize();



#warning A L'OCCASION, RECHERCHER POURQUOI IL Y A DES DEPASSEMENT DE CAPACITE 
#warning ET TRACER LES INDEX DE TABLEAUX
#warning REMETTRE A n+1 QUAND LE PROBLEME SERA RESOLU
float*	x=new float[(n*2)+1];
	if(x==NULL){
		return(false);
	}
float*	y=new float[(n*2)+1];
	if(y==NULL){
		delete x;
		return(false);
	}
float*	z=new float[(n*2)];
	if(z==NULL){
		delete x;
		delete y;
		return(false);
	}
#warning END WARNING
	
int		nl=txt->nLines();
	for(int i=0;i<nl;i++){
		d=((float)((nl-1)-i))*sz;
		if(d!=0){
			XYDecal(xpts,ypts,npts,d,&bsex,&bsey,&bsenpts);
		}
		else{
			bsex=xpts;
			bsey=ypts;
			bsenpts=npts;
		}
		if((bsex==NULL)||(bsey==NULL)){
			continue;
		}
		if(bsenpts<2){
			continue;
		}
		if(!justify_line(	ctx,
							i,
							bsex,
							bsey,
							bsenpts,
							x,
							y,
							z,
							n,
							txt)){
			if(d!=0){
				free(bsex);
				free(bsey);
			}
			n=txt->nGlyphs();
			break;
		}
		if(d!=0){
			free(bsex);
			free(bsey);
		}
	}

//_tm_("before set_glyph_pos");		
	txt->setGlyphPos(x,y,z);

//_tm_("before delete");		

// LE PROBLEME SURVIENT AU DELETE
// DONC ON DOIT AVOIR UN DÉPASSEMENT DE CAPACITE
// SUR UN DES TABLEAUX QUI VIENT ECRASER LE DEBUT DU SUIVANT	
	delete x;
	delete y;
	delete z;

//_tm_("after delete");		

	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bPolyJustificationElement::justify_line(	bGenericGraphicContext* ctx,
												int	line,
												float* bsex,
												float* bsey,
												int nbse,
												float* x,
												float* y,
												float* a,
												int n,
												bCoreTextInfo* txt){
//_bTrace_("bPolyJustificationElement::justify_line",true);
int		i;
int		pk=0;
int		strt;
int		lsz;
float	cf=1;
double	cons=0;

//_tm_("line="+line);
	if(_val==2){// justifié
//_tm_("(_val==2)");
double	pthlen=length(bsex,bsey,nbse);
double	wdt=txt->lineWidth(line);
		cf=pthlen/wdt;// on adapte le coef pour dilater
	}

	strt=txt->lineStart(line,&lsz);
	calcOrigin(bsex,bsey,nbse,txt->lineWidth(line),x,y,strt,&pk,&cons);

//_tm_("plage :"+strt+"->"+(strt+lsz));	
	for(i=strt;i<strt+lsz;i++){
		nextPos(bsex,		// support x
				bsey,		// support y
				nbse,		// nb support
				&pk,		// curseur support
				x,			// positions x
				y,			// positions y
				a,			// positions alpha
				n,			// nb positions
				txt,		// text
				i,			// curseur caractère
				cf,			// coef justification
				&cons);		// portion consommée du segment en cours
//_tm_(i+"->"+pk);
	}
	
	if(strt!=0){
//_tm_("(strt!=0)");
		x[strt-1]=x[strt];
		y[strt-1]=y[strt];
		a[strt-1]=0;
	}
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bPolyJustificationElement::calcOrigin(	float*	xin, 
											float*	yin, 
											int		nin, 
											double	width,
											float*	xout, 
											float*	yout,
											int		strt,
											int*	nout,
											double* crcons){
//_bTrace_("bPolyJustificationElement::calcOrigin",true);
double	w=length(xin,yin,nin)-width;// longueur inocuppée par le texte
	if((w<0)||(_val==0)||(_val==2)){
//_tm_("((w<0)||(_val==0)||(_val==2))");
//_tm_("w="+w+", _val="+_val);
		xout[strt]=xin[0];
		yout[strt]=yin[0];
		(*nout)=0;
		return;
	}
	w*=_val;// justification = distance à laquelle le texte commence
int		i;
float	a;
double	l=0;
	for(i=1;i<nin;i++){// recherche de l'index du point après lequel le texte commence
		l+=length(xin[i-1],yin[i-1],xin[i],yin[i]);
		if(l>=w){
//_tm_("(l>=w)");
			break;
		}
	}
	a=XYVec2Angle(xin[i-1],yin[i-1],xin[i],yin[i]);// angle entre les 2 derniers points
double	d=length(xin[i-1],yin[i-1],xin[i],yin[i]);// distance entre les 2 derniers points
	d-=(l-w);// distance entre le dernier point et le premier point du texte
	xout[strt]=xin[i-1]+d*cos(a);
	yout[strt]=yin[i-1]+d*sin(a);
	(*nout)=i-1;
	(*crcons)=d;
}

// ---------------------------------------------------------------------------
// 
// -----------
void bPolyJustificationElement::nextPos(	float*	xin,		// support x
											float*	yin,		// support y
											int		nin,		// nb support
											int*	crsin,		// curseur support
											float*	xout,		// positions x
											float*	yout,		// positions y
											float*	aout,		// positions alpha
											int		nout,		// nb positions
											bCoreTextInfo* txt,		// text
											int		cglyph,		// curseur caractère
											double	coef,		// coef justification
											double*	crcons){	// portion consommée du segment courant
//_bTrace_("bPolyJustificationElement::nextPos",false);
	if((*crsin)>=nin-1){
//_tm_("((*crsin)>=nin-1)");
		xout[cglyph+1]=0;
		yout[cglyph+1]=0;
		aout[cglyph+1]=0;
		txt->trunc(cglyph-2);
		return;
	}
int		bk=(*crsin);
double	splen=length(xout[cglyph],yout[cglyph],xin[(*crsin)+1],yin[(*crsin)+1]);
double	gw=txt->glyphWidth(cglyph)*coef;
double	len;

//_tm_("ENTREE:(*crcons)="+(*crcons));
//_tm_("gw="+gw+", splen="+splen+", cglyph="+cglyph+", (*crsin)="+(*crsin)+", nin="+nin+", nout="+nout);
//_tm_("out("+xout[cglyph]+";"+yout[cglyph]+"), in("+xin[(*crsin)+1]+";"+yin[(*crsin)+1]+")");

	if(gw>splen){
		do{
			bk++;
			if(bk>=nin){
//_tm_("(bk>=nin)");
				break;
			}
			len=length(xin,yin,bk,bk+1);
			if((splen+len)>gw){
//_tm_("((splen+len)>gw))");
				break;
			}
			splen+=len;
		}
		while(true);
		(*crcons)=0;	// on a changé de segment, on repart avec une conso à 0
		gw-=splen;		// on retire la longueur
	}
	gw+=(*crcons);		// on ajoute la portion consommée	
	if(gw<0){
//_tm_("(gw<0)");
		gw=txt->glyphWidth(cglyph)*coef;
	}
	len=length(xin,yin,bk,bk+1);

//_tm_("SORTIE:(*crcons)="+(*crcons));

//_tm_("SORTIE:xin[bk]="+xin[bk]+", xin[bk+1]="+xin[bk+1]+", gw="+gw+", len="+len);
//_tm_("SORTIE:yin[bk]="+yin[bk]+", yin[bk+1]="+yin[bk+1]+", gw="+gw+", len="+len);

	xout[cglyph+1]=xin[bk]+((xin[bk+1]-xin[bk])*(gw/len));
	yout[cglyph+1]=yin[bk]+((yin[bk+1]-yin[bk])*(gw/len));
	aout[cglyph]=XYVec2Angle(xout[cglyph],yout[cglyph],xout[cglyph+1],yout[cglyph+1]);
	(*crsin)=bk;
	(*crcons)=length(xin[bk],yin[bk],xout[cglyph+1],yout[cglyph+1]);
}


















/*double	alpha=XYVec2Angle(bsex[pk],bsey[pk],bsex[pk+1],bsey[pk+1]);
double	len=length(bsex,bsey,0,pk+1);
double	curlen=	length(bsex,bsey,0,pk)+
				length(bsex[pk],bsey[pk],x[strt],y[strt])+
				txt->glyphWidth(strt)*cf;
double	dx,dy,rx,ry;

	a[strt]=alpha;
	txt->setFirst(strt);
	txt->setOrigin(x[strt],y[strt]);
	txt->setAngle(alpha);
	for(i=strt+1;i<strt+lsz;i++){
		txt->absoluteGlyphPos(&dx,&dy,i,cf);
		x[i]=dx;
		y[i]=dy;
		a[i]=alpha;
trc.msg("(%f;%f;%f)",x[i],y[i],a[i]);
		gw=txt->glyphWidth(i)*cf;
		curlen+=gw;
		if(curlen>len){
trc.msg("curlen(%f)>len(%f)",curlen,len);
			if((i==n-1)&&(_val==1.0)){
				
			}
			else{
				pk++;

				kpk=pk;
				do{
					kpk++;
					if(kpk>=nbse){	
						break;
					}	
					rl=length(bsex,bsey,pk,kpk);
					if(rl>=gw){
						break;
					}
				}
				while(true);
				
				if(rl>gw){
					kpk--;
					rl=length(bsex,bsey,pk,kpk);
					rg=gw-rl;
					rl=length(bsex,bsey,kpk,kpk+1);
					rx=bsex[kpk]+((bsex[kpk+1]-bsex[kpk])*(rg/rl));
					ry=bsex[kpk]+((bsey[kpk+1]-bsey[kpk])*(rg/rl));
				}
				else{
					rx=bsex[kpk];
					ry=bsex[kpk];
				}
								
				//if((pk+1)>=nbse){
					//txt->trunc(i);
					//return(false);
				//	break;
				//}	
//				alpha=XYVec2Angle(bsex[pk],bsey[pk],bsex[pk+1],bsey[pk+1]);
				alpha=XYVec2Angle(bsex[pk],bsey[pk],bsex[kpk],bsey[kpk]);
				
// la dérive se trouve ici, car on ne recale pas sur le linéaire
				dx=bsex[pk]+((curlen-len)*cos(alpha));
				dy=bsey[pk]+((curlen-len)*sin(alpha));
				
				len+=length(bsex[pk],bsey[pk],bsex[pk+1],bsey[pk+1]);
				txt->setOrigin(dx,dy);
				txt->setAngle(alpha);
				txt->setFirst(i+1);
				
				pk=kpk;
			}
		}
	}
	for(;i<strt+lsz;i++){
		x[i]=dx;
		y[i]=dy;
		a[i]=alpha;
	}*/

