/*****************************************************************************
*
* PyObjCryst        by DANSE Diffraction group
*                   Simon J. L. Billinge
*                   (c) 2009 Trustees of the Columbia University
*                   in the City of New York.  All rights reserved.
*
* File coded by:    Chris Farrow
*
* See AUTHORS.txt for a list of people who contributed.
* See LICENSE.txt for license information.
*
******************************************************************************
*
* $Id$
*
*****************************************************************************/

#include <boost/python.hpp>
#include <boost/python/module.hpp>

void wrap_asymmetricunit();
void wrap_atom();
void wrap_crystal();
void wrap_general();
void wrap_globalscatteringpower();
void wrap_io();
void wrap_molatom();
void wrap_molbond();
void wrap_molbondangle();
void wrap_moldihedralangle();
void wrap_molecule();
void wrap_objregistry();
void wrap_polyhedron();
void wrap_quaternion();
void wrap_refinableobj();
void wrap_refinableobjclock();
void wrap_refinablepar();
void wrap_refobjopt();
void wrap_refpartype();
void wrap_registerconverters();
void wrap_restraint();
void wrap_rigidgroup();
void wrap_scatterer();
void wrap_scatteringcomponent();
void wrap_scatteringcomponentlist();
void wrap_scatteringpower();
void wrap_scatteringpoweratom();
void wrap_scatteringpowersphere();
void wrap_spacegroup();
void wrap_stretchmode();
void wrap_unitcell();
void wrap_zatom();
void wrap_zpolyhedron();
void wrap_zscatterer();

// Wrappers must be called according to inheritance hierarchy
BOOST_PYTHON_MODULE(_pyobjcryst)
{
    // General stuff
    wrap_general();
    wrap_io();
    wrap_objregistry();
    wrap_quaternion();
    wrap_refinableobjclock();
    wrap_refobjopt();
    wrap_refpartype();
    wrap_registerconverters();


    // Core objects
    wrap_restraint();
    wrap_refinablepar();
    wrap_refinableobj();

    // Other base classes
    wrap_scatterer();
    wrap_scatteringpower();
    wrap_zscatterer();
    wrap_unitcell();

    // Other stuff in no particular order.
    wrap_asymmetricunit();
    wrap_atom();
    wrap_crystal();
    wrap_globalscatteringpower();
    wrap_molatom();
    wrap_molbond();
    wrap_molbondangle();
    wrap_moldihedralangle();
    wrap_molecule();
    wrap_polyhedron();
    wrap_rigidgroup();
    wrap_scatteringcomponent();
    wrap_scatteringcomponentlist();
    wrap_scatteringpoweratom();
    wrap_scatteringpowersphere();
    wrap_spacegroup();
    wrap_stretchmode();
    wrap_zatom();
    wrap_zpolyhedron();

}

