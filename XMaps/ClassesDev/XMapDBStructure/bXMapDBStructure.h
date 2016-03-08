//----------------------------------------------------------------------------
// File : bXMapDBStructure.h
// Project : MacMap
// Purpose : Header file : XMap database structure class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2015 Carte Blanche Conseil.
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
// 28/04/2005 creation.
// 02/09/2015 cocoa intf.
//----------------------------------------------------------------------------

#ifndef __bXMapDBStructure__
#define __bXMapDBStructure__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <Carbon/Carbon.h>

//----------------------------------------------------------------------------

class bXMapDBStructure : public bStdXMap{
	public:		
		bXMapDBStructure                        (	bGenericXMLBaseElement* elt,
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl);
		virtual ~bXMapDBStructure               (	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
				
		virtual bool test						(	void* prm);
		virtual bool edit						(	void* prm);
	
		virtual bool process					(	int msg,
													void* prm);
    
		virtual int remove                      (	bGenericType* tp,
													long field);
		virtual int add                         (	bGenericType* tp,
													long kind,
                                                    long len,
                                                    long decs,
                                                    const char* name);
		virtual int modify                      (	bGenericType* tp,
													long field,
                                                    long kind,
                                                    long len,
                                                    long decs,
                                                    const char* name);
        virtual int set_default_value			(	bGenericType* tp,
                                                    long field,
                                                    void* value,
                                                    bool init);
        virtual int set_masked                  (	bGenericType* tp,
                                                    long field,
                                                    bool value);
        virtual int set_delete_protected        (	bGenericType* tp,
                                                    long field,
                                                    bool value);
        virtual int set_write_protected         (	bGenericType* tp,
                                                    long field,
                                                    bool value);
    
	protected:
	
	private:

};

//----------------------------------------------------------------------------

#endif
