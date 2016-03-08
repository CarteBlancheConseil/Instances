//----------------------------------------------------------------------------
// File : bXMapPrefs.h
// Project : MacMap
// Purpose : Header file : XMap classe, preferences
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2016 Carte Blanche Conseil.
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
// 18/06/2007 creation.
// 25/02/2016 cocoa intf.
//----------------------------------------------------------------------------

#ifndef __bXMapPrefs__
#define __bXMapPrefs__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <std_ext/bXMapStdIntf.h>
#include <Carbon/Carbon.h>

//----------------------------------------------------------------------------

#define	kXMapPrefsMessageID		"Prefs"
#define	kXMapPrefsMsgFillField	"FillField"
#define	kXMapPrefsMsgWithValue	"WithValue"
#define	kXMapPrefsMsgWithCalc	"WithCalc"
#define	kXMapPrefsMsgWithField	"WithField"

#define	kXMapPrefsErrorCode		-1

//----------------------------------------------------------------------------

class bXMapPrefs : public bStdXMap{
public:
    bXMapPrefs                           (	bGenericXMLBaseElement* elt,
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bXMapPrefs                  (	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
            
    virtual bool edit						(	void* prm);
    
    virtual bool process					(	int msg,
                                                void* prm);

protected:

private:
    
};

//----------------------------------------------------------------------------

#endif
