//----------------------------------------------------------------------------
// File : bXMapStringProcessing.h
// Project : MacMap
// Purpose : Header file : XMap class, string formating utility
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
// 28/05/2009 creation.
// 19/02/2016 cocoa intf.
//----------------------------------------------------------------------------
// SCRIPT_COMPATIBLE
//----------------------------------------------------------------------------

#ifndef __bXMapStringProcessing__
#define __bXMapStringProcessing__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <std_ext/bXMapStdIntf.h>

//----------------------------------------------------------------------------

#define kXMapStringProcessingMessageID			"StringProcessing"
#define kXMapStringProcessingProcessMessageID	"Processing"
#define kXMapStringProcessingErrorsOccursID		"ErrorsOccurs"
#define kXMapStringProcessingReadLogID			"ReadLog"

//----------------------------------------------------------------------------

class bXMapStringProcessing : public bStdXMap{
public:
    bXMapStringProcessing                   (	bGenericXMLBaseElement* elt,
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bXMapStringProcessing          (	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
            
    virtual void open						(	int* flags);
    virtual bool edit						(	void* prm);
    
    virtual bool process					(	int msg,
                                                void* prm);
    virtual bool test						(	void* prm);

    virtual void get_params                 (	strprocess_prm* prm);
    virtual void set_params                 (	strprocess_prm prm);
    virtual bGenericType* get_type          (	);

protected:

private:
    virtual bool process_str				(	);
    virtual bool process_str				(	bool dummy);
    virtual bool process_str				(	strprocess_prm* prm,
                                                bool silent);
    
    bArray			_arr;
    strprocess_prm	_prm;
};

//----------------------------------------------------------------------------

#endif
