//----------------------------------------------------------------------------
// File : bGeogGInclude.h
// Project : MacMap
// Purpose : Header file : Include Geog interface class
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
// 15/03/2006 creation.
//----------------------------------------------------------------------------

#ifndef __bGeogGInclude__
#define __bGeogGInclude__

//----------------------------------------------------------------------------

#include <std_ext/bStdGeog.h>

//----------------------------------------------------------------------------

enum{
	kGeogGIncludeSignature			='GInc',
	kGeogGIncludeFullyID			=1,
	kGeogGIncludeFullyCmd			='full',
	kGeogGIncludePartlyID			=2,
	kGeogGIncludePartlyCmd			='part',
	kGeogGIncludeStrictlyID			=3,
	kGeogGIncludeStrictlyCmd		='strc'
};

#define kGeogGIncludeMsgFully		"fully"
#define kGeogGIncludeMsgPartly		"partly"
#define kGeogGIncludeMsgStrictly	"strictly"

#define GIncludeSignature			'ginc'

//----------------------------------------------------------------------------

class bGeogGInclude : public bStdGeog {
	public:		
		bGeogGInclude							(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl);
		virtual ~bGeogGInclude					(	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);

		virtual void open						(	int* flags);
		virtual void close						(	);

		virtual bool event						(	EventRef evt);
		virtual bool edit						(	WindowRef wd, 
													Rect* r);
		virtual void end_edit					(	);
		virtual void hide						(	);
		virtual void show						(	);
		virtual void get_params					(	bArray* arr, 
													int indent);
		virtual void put_params					(	bGenericXMLBaseElement* root);

	protected:
	
	private:
		ControlRef	_cfull;
		ControlRef	_cpart;
		ControlRef	_cstrict;
		bool		_full;
		bool		_strict;
};

//----------------------------------------------------------------------------

#endif
