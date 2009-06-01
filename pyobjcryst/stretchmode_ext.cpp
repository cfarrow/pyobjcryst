/*****************************************************************************
*
* pyobjcryst        by DANSE Diffraction group
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
* boost::python bindings to ObjCryst::StretchMode and its derivatives.  
*
* Note that all indices are zero-based.
* 
* Changes from ObjCryst++
*
* $Id$
*
*****************************************************************************/

#include "RefinableObj/RefinableObj.h"
#include "ObjCryst/Molecule.h"
#include "ObjCryst/Crystal.h"
#include "ObjCryst/ScatteringPower.h"

#include <boost/utility.hpp>
#include <boost/python.hpp>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/args.hpp>
#include <boost/python/make_constructor.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <map>
#include <algorithm>

#include "helpers.hpp"

namespace bp = boost::python;
using namespace boost::python;
using namespace ObjCryst;


namespace {

typedef std::set<MolAtom*> MolAtomSet;

class StretchModeWrap : public StretchMode, 
                        public wrapper<StretchMode>
{
    public:

    StretchModeWrap() : StretchMode() {}
    StretchModeWrap(const StretchModeWrap& sm) : StretchMode(sm) {}

    // Pure virtual
    
    void CalcDeriv(const bool derivllk=true)
    {
        this->get_override("CalcDeriv")(derivllk);
    }

    void Stretch(const float change)
    {
        this->get_override("Stretch")(change);
    }

    void RandomStretch(const float change)
    {
        this->get_override("RandomStretch")(change);
    }

};

// These gives us a way to add an atom to a stretch mode
void _AddAtomSMBL(StretchModeBondLength& mode, MolAtom& a)
{
    mode.mvTranslatedAtomList.insert(&a);
}

void _AddAtomsSMBL(StretchModeBondLength& mode, bp::object& l)
{
    for(size_t i=0; i < len(l); ++i)
    {
        MolAtom* a = extract<MolAtom*>(l[i]);
        mode.mvTranslatedAtomList.insert(a);
    }
}

void _AddAtomsSetSMBL(StretchModeBondLength& mode, MolAtomSet& l)
{

    MolAtomSet::const_iterator p;
    for(p = l.begin(); p != l.end(); ++p)
    {
        mode.mvTranslatedAtomList.insert(*p);
    }
}

// This one is for the angle modes
template <class T>
void _AddAtom(T& mode, MolAtom& a)
{
    mode.mvRotatedAtomList.insert(&a);
}

template <class T>
void _AddAtoms(T& mode, bp::object& l)
{
    for(size_t i=0; i < len(l); ++i)
    {
        MolAtom* a = extract<MolAtom*>(l[i]);
        mode.mvRotatedAtomList.insert(a);
    }
}

template <class T>
void _AddAtomsSet(T& mode, MolAtomSet& l)
{

    MolAtomSet::const_iterator p;
    for(p = l.begin(); p != l.end(); ++p)
    {
        mode.mvRotatedAtomList.insert(*p);
    }
}

} // namespace


BOOST_PYTHON_MODULE(_stretchmode)
{

    class_<StretchModeWrap, boost::noncopyable> ("StretchMode", no_init )
        .def("CalcDeriv", pure_virtual(&StretchMode::CalcDeriv), 
            (bp::arg("derivllk")=true))
        .def("Stretch", pure_virtual(&StretchMode::Stretch),
            (bp::arg("amplitude")))
        .def("RandomStretch", pure_virtual(&StretchMode::RandomStretch),
            (bp::arg("amplitude")))
        ;

    class_<StretchModeBondLength, bases<StretchMode> >
        ("StretchModeBondLength", 
        init<MolAtom&, MolAtom&, MolBond*>()
        [with_custodian_and_ward<1,2,
            with_custodian_and_ward<1,3,
                with_custodian_and_ward<1,4> > >()])
        .def("AddAtom", &_AddAtomSMBL,
            with_custodian_and_ward<1,2>())
        .def("AddAtoms", &_AddAtomsSMBL,
            with_custodian_and_ward<1,2>())
        .def("AddAtoms", &_AddAtomsSetSMBL,
            with_custodian_and_ward<1,2>())
        ;

    class_<StretchModeBondAngle, bases<StretchMode> >
        ("StretchModeBondAngle", 
        init<MolAtom&, MolAtom&, MolAtom&, MolBondAngle*>()
        [with_custodian_and_ward<1,2,
            with_custodian_and_ward<1,3,
                with_custodian_and_ward<1,4,
                    with_custodian_and_ward<1,5> > > >()])
        .def("AddAtom", &_AddAtom<StretchModeBondAngle>,
            with_custodian_and_ward<1,2>())
        .def("AddAtoms", &_AddAtoms<StretchModeBondAngle>,
            with_custodian_and_ward<1,2>())
        .def("AddAtoms", &_AddAtomsSet<StretchModeBondAngle>,
            with_custodian_and_ward<1,2>())
        ;

    class_<StretchModeTorsion, bases<StretchMode> >
        ("StretchModeTorsion", 
        init<MolAtom&, MolAtom&, MolDihedralAngle*>()
        [with_custodian_and_ward<1,2,
            with_custodian_and_ward<1,3,
                with_custodian_and_ward<1,4> > >()])
        .def("AddAtom", &_AddAtom<StretchModeBondAngle>,
            with_custodian_and_ward<1,2>())
        .def("AddAtoms", &_AddAtoms<StretchModeBondAngle>,
            with_custodian_and_ward<1,2>())
        .def("AddAtoms", &_AddAtomsSet<StretchModeBondAngle>,
            with_custodian_and_ward<1,2>())
        ;

    class_<StretchModeTwist, bases<StretchMode> >
        ("StretchModeTwist", 
        init<MolAtom&, MolAtom&>()
        [with_custodian_and_ward<1,2,
            with_custodian_and_ward<1,3> >()])
        .def("AddAtom", &_AddAtom<StretchModeBondAngle>,
            with_custodian_and_ward<1,2>())
        .def("AddAtoms", &_AddAtoms<StretchModeBondAngle>,
            with_custodian_and_ward<1,2>())
        .def("AddAtoms", &_AddAtomsSet<StretchModeBondAngle>,
            with_custodian_and_ward<1,2>())
        ;
}
