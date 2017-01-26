//----------------------------------------------------------------------------
// File : bXMapAssociationWithField.h
// Project : MacMap
// Purpose : Header file : XMap class, concatenate polylines geometries of a network comparing content of a field and class
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
// 22/12/2005 creation.
// 30/06/2016 cocoa intf.
//----------------------------------------------------------------------------
// SCRIPT_COMPATIBLE
//----------------------------------------------------------------------------

#ifndef __bXMapAssociationWithField__
#define __bXMapAssociationWithField__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <std_ext/bXMapStdIntf.h>

//----------------------------------------------------------------------------

#define	kXMapAssociationWithFieldIndexErr				"IndexErr"
#define	kXMapAssociationWithFieldCloneObjectErr			"CloneObjectErr"
#define	kXMapAssociationWithFieldSetVerticesErr			"SetVerticesErr"
#define	kXMapAssociationWithFieldVerticesErr			"VerticesErr"
#define	kXMapAssociationWithFieldObjNotAssociateWarning	"ObjNotAssociatedWarning"

//----------------------------------------------------------------------------

class bXMapAssociationWithField : public bStdXMap{
public:
    bXMapAssociationWithField				(	bGenericXMLBaseElement* elt, 
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bXMapAssociationWithField		(	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
    
    virtual void open						(	int* flags);
    virtual bool edit						(	void* prm);
    virtual bool process					(	int msg,
                                                void* prm);
    virtual bool test						(	void* prm);
    
    associationwithfield_prm get_data       (   ){return _prm;};
    void set_data                           (   associationwithfield_prm prm){_prm=prm;};
    virtual bGenericType* get_type          (	);
    
protected:		
    virtual bool associate					(	);
    virtual bool associate					(	int fhier,
                                                int fass,
                                                double lmin,
                                                double lmax,
                                                bool silent);

private:
    virtual int get_lines					(	bGenericGeoElement* oa,		// Ref object
                                                ivertices* vxsa,			// Ref vertices
                                                int loc,					// Point to check (0 or vxsa->nv-1)
                                                int	aclss,					// Ref class
                                                char* aname,				// Ref name
                                                
                                                bGenericGeoIterator* iter,	// Iterator
                                                bArray& sel,				// Obj List (from selection)
                                                
                                                int hfld,					// Class Field
                                                int nfld,					// Name Field
                                                
                                                double	lmin,				// Min length
                                                double	lmax,				// Max length

                                                bGenericGeoElement** ob);	// Next object

    static int check_line_dist				(	void *o, 
                                                void *prm);
    static int obj_comp						(	const void* a,
                                                const void* b);

    associationwithfield_prm	_prm;
    static int					_sfhier;
};

//----------------------------------------------------------------------------

#endif
