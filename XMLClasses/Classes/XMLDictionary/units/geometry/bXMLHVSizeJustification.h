//----------------------------------------------------------------------------
// File : bXMLHVSizeJustification.h
// Project : MacMap
// Purpose : Header file : x&y size justification tag class, used in styles
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
// 22/06/2011 creation.
//----------------------------------------------------------------------------

#ifndef __bHVSizeJustificationElement__
#define __bHVSizeJustificationElement__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMLLowRenderElement.h>
#include <mox_intf/CGUtils.h>

//----------------------------------------------------------------------------

class bHVSizeJustificationElement : public bStdXMLLowRenderElement{
protected:
	bHVSizeJustificationElement 			(	bGenericXMLBaseElement* elt, 
												bGenericMacMapApp* gapp, 
												CFBundleRef bndl );
	virtual ~bHVSizeJustificationElement  	(	);
	
public:
	virtual bool actionstd					(	bGenericGraphicContext* ctx);
	virtual bool actionval					(	bGenericGraphicContext* ctx,
												bStdXMLValueElement* elt,
												bGenericGeoElement* geo);
	
protected:
	virtual bool align						(	bGenericGraphicContext *ctx);
	double	_val;

private:
};

//----------------------------------------------------------------------------

class bHSizeJustificationElement : public bHVSizeJustificationElement{
public:
	bHSizeJustificationElement 				(	bGenericXMLBaseElement* elt, 
												bGenericMacMapApp* gapp, 
												CFBundleRef bndl );
	virtual ~bHSizeJustificationElement  	(	);
	virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
	
protected:
	virtual bool align						(	bGenericGraphicContext *ctx);

private:
};

//----------------------------------------------------------------------------

class bVSizeJustificationElement : public bHVSizeJustificationElement{
public:
	bVSizeJustificationElement 				(	bGenericXMLBaseElement* elt, 
												bGenericMacMapApp* gapp, 
												CFBundleRef bndl );
	virtual ~bVSizeJustificationElement  	(	);
	virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);

protected:
	virtual bool align						(	bGenericGraphicContext *ctx);
	
private:
};

//----------------------------------------------------------------------------

#endif
