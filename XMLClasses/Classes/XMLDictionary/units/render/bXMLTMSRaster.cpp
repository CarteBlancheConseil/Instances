//----------------------------------------------------------------------------
// File : bXMLTMSRaster.cpp
// Project : MacMap
// Purpose : C++ source file : generic tiling service tag class, used in styles
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
// 28/02/2014 creation.
//----------------------------------------------------------------------------

#include "bXMLTMSRaster.h"
#include <MacMapSuite/bTrace.h>
#include <MacMapSuite/bStdFile.h>
#include <MacMapSuite/bStdDirectory.h>
#include <MacMapSuite/mmurl.h>
#include <MacMapSuite/bString.h>
#include <MacMapSuite/C_Utils.h>
#include <mox_intf/bitmap_utils.h>
#include <mox_intf/ext_utils.h>
#include <mox_intf/CGUtils.h>
#include <mox_intf/NSOpenSavePanelWrappers.h>

// ---------------------------------------------------------------------------
// 
// ------------

#ifdef __LITTLE_ENDIAN__
#define kPNGSignature				'PNG '
#else
#define kPNGSignature				' GNP'
#endif

#ifdef __LITTLE_ENDIAN__
#define kJPGSignature				'JPEG'
#else
#define kJPGSignature				'GEPJ'
#endif

#define kImgSize	256

// ---------------------------------------------------------------------------
// 
// ------------
static int long2tilex(double lon, int z){ 
	return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z))); 
}

// ---------------------------------------------------------------------------
// 
// ------------
static int lat2tiley(double lat, int z){
	return (int)(floor((1.0 - log( tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0, z))); 
}

// ---------------------------------------------------------------------------
// 
// ------------
static double tilex2long(int x, int z){
	return x / pow(2.0, z) * 360.0 - 180;
}

// ---------------------------------------------------------------------------
// 
// ------------
static double tiley2lat(int y, int z){
double n = M_PI - 2.0 * M_PI * y / pow(2.0, z);
	return 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
}

// ---------------------------------------------------------------------------
// Destruction de l'offscreen
// ------------
static void ReleaseBitmap(CGContextRef ctx){
	if(ctx==NULL){
		return;
	}
CGColorSpaceRef	clr=CGBitmapContextGetColorSpace(ctx);
	if(clr){
		CGColorSpaceRelease(clr);
	}
void*			data=CGBitmapContextGetData(ctx);
	if(data){
		free(data);
	}
	CGContextRelease(ctx);
}

// ---------------------------------------------------------------------------
// Vérification et création si nécessaire des dossiers de cache
// ------------
static bool CheckCache(int zoom, const char* dir){
_bTrace_("CheckCache",false);
// Accès au dossier "Cache" (du user library)
char	path[PATH_MAX*3];
    if(!NSGetUserCachePath(cNSUTF8StringEncoding,path)){
        return(false);
    }
	strcat(path,"/");
bStdUTF8Directory	abs(path);
	if(abs.status()){
		return(false);
	}
	
mode_t	msk=S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH;
	
// Accès au dossier de cache de MacMap®
bString			fstr("com.cbconseil.macmap/");
bStdDirectory	root(fstr.string());
	if(root.status()){
		if(mkdir(fstr.string(),msk)){
_te_("mkdir failed for "+fstr.string());
			return(false);
		}
		if(chdir(fstr.string())){
_te_("chdir failed for "+fstr.string());
			return(false);
		}			
	}
	
	// Accès au dossier
	fstr.reset();
	fstr+dir+"/";
	bStdDirectory	gm(fstr.string());
	if(gm.status()){
		if(mkdir(fstr.string(),msk)){
_te_("mkdir failed for "+fstr.string());
			return(false);
		}
		if(chdir(fstr.string())){
_te_("chdir failed for "+fstr.string());
			return(false);
		}
	}
	
// Accès au dossier du zoom
	fstr.reset();
	fstr+"Z"+zoom;
	bStdDirectory	zdr(fstr.string());
	if(zdr.status()){
		if(mkdir(fstr.string(),msk)){
_te_("mkdir failed for "+fstr.string());
			return(false);
		}
		if(chdir(fstr.string())){
_te_("chdir failed for "+fstr.string());
			return(false);
		}			
	}
	return(true);
}


// ---------------------------------------------------------------------------
// Chargement d'une image en cache, si possible, via requête http sinon
// En cas de requête, l'image est enregistrée en cache
// ------------
static void* GetImage(int zoom, const char* url, const char* cache, int imgsign, d2dvertex wgs, size_t* sz){
_bTrace_("GetImage",false);
void*		data=NULL;
char		path[PATH_MAX*3]="";
	
    if(NSGetUserCachePath(cNSUTF8StringEncoding,path)){
        strcat(path,"/com.cbconseil.macmap/");
        strcat(path,cache);
    }

int				tilex=long2tilex(wgs.x,zoom);
int				tiley=lat2tiley(wgs.y,zoom);
bStdDirectory	abs(path);
char			buf[256];
		
	switch(imgsign){
		case kPNGSignature:
			sprintf(buf,"/img_%d_%d.png",tilex,tiley);
			break;
		case kJPGSignature:
			sprintf(buf,"/img_%d_%d.jpg",tilex,tiley);
			break;
		default:
			sprintf(buf,"/img_%d_%d.rif",tilex,tiley);
			break;
	}	
	
bString			str("Z");
	str+zoom+buf;
//__trc__.msg(str);
bStdFile		imgr(str.string(),"rb");
	if(!imgr.status()){
		imgr.mount((char**)&data,(int*)sz);
	}
	if(imgr.status()||((*sz)<=0)){
char	req[PATH_MAX*3];
		strncpy(req,url,PATH_MAX*3);
char	buf[256];
		sprintf(buf,"%d",zoom);
		strrep(req,"##z##",buf);
		sprintf(buf,"%d",tilex);
		strrep(req,"##x##",buf);
		sprintf(buf,"%d",tiley);
		strrep(req,"##y##",buf);
_tm_(req);
		if(mmurl_get(req,NULL,NULL,&data,sz)!=0){
_te_("mmurl_get failed : "+req);
			return(NULL);
		}
bStdFile	imgw(str.string(),"wb");
		imgw.write(data,*sz);
	}
	return(data);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bTMSRasterElement	::bTMSRasterElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
						: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("tmsraster");
	setobjectcompliant(false);
	setclasscompliant(true);
	_data=NULL;
	_sz=0;
	_fromp=NULL;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bTMSRasterElement::create(bGenericXMLBaseElement* elt){
	return(new bTMSRasterElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bTMSRasterElement::~bTMSRasterElement(){
}

// ---------------------------------------------------------------------------
// Init
// -----------
void bTMSRasterElement::init(void *ctx){
	if(_data){
		free(_data);
		_data=NULL;
	}
	_last[0]=0;
	_sz=0;
	bStdXMLLowRenderElement::init(ctx);
	if(_fromp==NULL){
bool	init=false;
		_fromp=new bStdProj(_gapp->document()->srid(),&init);
		if(!init){
			delete _fromp;
			_fromp=NULL;
		}
	}

	_url[0]=0;
	_cache[0]=0;
	_ext[0]=0;
bStdXMLValueElement*	elt;
	if(_elts.get(1,&elt)){
		elt->getvalue(_url);
	}
	if(_elts.get(2,&elt)){
		elt->getvalue(_cache);
	}
	if(_elts.get(3,&elt)){
		elt->getvalue(_ext);
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bTMSRasterElement::actionstd(bGenericGraphicContext* ctx){
_bTrace_("bTMSRasterElement::actionstd",false);
	if(_data){
		free(_data);
		_data=NULL;
	}
	_sz=0;

	if(_fromp){
dvertices		dvxs={_2D_VX,1,0,NULL};
bGenericUnit*	scl=_gapp->scaleMgr()->get();
char			name[256];
		scl->long_name(name);
int				zoom=atoi(name);
ivx_rect		vr;
i2dvertex		vxo;
CGPoint			cgpa,cgpb;
int				nh,nv;
size_t			gsz;
void			*gdata;
CGSize			dim;
int				tilexBL,tileyBL,tilexTR,tileyTR;
int				imgsign=0;		
char			buf[_values_length_max_];
		
		strcpy(buf,_ext);
		strupper(buf);
		if(strstr(buf,".PNG")){
			imgsign=kPNGSignature;
		}
		else if(strstr(buf,".JPG")){
			imgsign=kJPGSignature;
		}
		else if(strstr(buf,".TIF")){
			imgsign=0;
		}

		if(!CheckCache(zoom,_cache)){
_te_("CheckCache failed for zoom "+zoom);
			return(true);
		}

        switch(ctx->signature()){
            case kCtxGraphicContext:
                _gapp->mapIntf()->screenBounds(&vr);
                break;
            default:
                vr=*(_gapp->printMgr()->get_print_area());
                break;
        }
        
		if(!ivr_ok(&vr)){
_te_("NULL area");
			return(true);
		}

CGRect	box=ctx->get_box();

		vxo.h=vr.left;
		vxo.v=vr.bottom;
		_gapp->locConverter()->convert(&dvxs.vx.vx2[0],&vxo);
		_wgs.transform(*_fromp,&dvxs);
		tilexBL=long2tilex(dvxs.vx.vx2[0].x,zoom);
		tileyBL=lat2tiley(dvxs.vx.vx2[0].y,zoom);

		dvxs.vx.vx2[0].x=tilex2long(tilexBL,zoom);
		dvxs.vx.vx2[0].y=tiley2lat(tileyBL,zoom);
		_fromp->transform(_wgs,&dvxs);
		_gapp->locConverter()->convert(&cgpa,&dvxs.vx.vx2[0]);
		cgpa.x-=(kImgSize/2);
		cgpa.y-=(kImgSize/2);
		
		vxo.h=vr.right;
		vxo.v=vr.top;
		_gapp->locConverter()->convert(&dvxs.vx.vx2[0],&vxo);
		_wgs.transform(*_fromp,&dvxs);
		tilexTR=long2tilex(dvxs.vx.vx2[0].x,zoom);
		tileyTR=lat2tiley(dvxs.vx.vx2[0].y,zoom);
		
		nh=tilexTR-tilexBL;
		nv=tileyBL-tileyTR;
		dim.width=(nh+2)*kImgSize;
		dim.height=(nv+1)*kImgSize;
		
CGContextRef	ctx=CreateBitmapContextWithSize(box.size.width,box.size.height);
		if(!ctx){
_te_("MakeBitmap failed");
			return(true);
		}
CGRect	cgr;
		cgr.origin=cgpa;
		cgr.size.width=kImgSize;
		cgr.size.height=kImgSize;
		for(int i=0;i<=nv;i++){
			for(int j=1;j<=nh+1;j++){
                cgpb.x=cgpa.x+j*kImgSize;
				cgpb.y=cgpa.y+i*kImgSize;
				
				_gapp->locConverter()->convert(&dvxs.vx.vx2[0],&cgpb);
				_wgs.transform(*_fromp,&dvxs);
				gdata=GetImage(zoom,_url,_cache,imgsign,dvxs.vx.vx2[0],&gsz);

				cgpb.x+=(kImgSize/2);
				cgpb.y+=(kImgSize/2);
				
				if(gdata){
CGImageRef			img=CGImageCreateFromData(gdata,gsz,imgsign);
					if(img){
// Dessin dans l'offscreen
						cgr.origin=cgpb;
						cgr.origin.x-=kImgSize;
						cgr.origin.y-=kImgSize;
						CGContextDrawImage(ctx,cgr,img);
						free(gdata);
						CGImageRelease(img);
					}
					else{
_te_("CGImageCreateFromData failed");
					}
				}
				else{
_te_("GetImage failed");
				}
            }
		}
		
		(void)CGBitmapContextGetOutputData(ctx,kQTFileTypePNG,72,5,&_data,&_sz);
// Libération de l'offscreen
		ReleaseBitmap(ctx);
	}
	
	if(_data==NULL){
_te_("NULL data");
		ctx->setImage(NULL,0,"");
		return(objectcompliant());
	}
	ctx->setImage(_data,_sz,"MapQuest_raster.png");
	return(true);
}
