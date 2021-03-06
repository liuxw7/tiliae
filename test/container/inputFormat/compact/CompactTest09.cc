/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/test/unit_test.hpp>

#include <iostream>
#include "core/Pointer.h"
#include "testHelpers/TestHelpers.h"

#include "container/ContainerFactory.h"
#include "container/inputFormat/compact/CompactMetaService.h"
#include "Conf.h"

/****************************************************************************/

using namespace Core;
using namespace Container;

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (CompactXmlTest09);

/**
 *
 */
BOOST_AUTO_TEST_CASE (test041InitMethod)
{
        BeanFactoryContainer *cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "041-init-method.xml"));

        Variant vB = cont->getBean ("city");
        BOOST_CHECK (ccast <City *> (vB));

        City *cit = vcast <City *> (vB);
        BOOST_CHECK (cit);
        BOOST_CHECK_EQUAL (cit->getName (), "Warszawa_INIT");
}

/**
 * Miałem notatkę, że się wyjebywało na mapie z pustym kluczem (w poprzedniej wersji).
 * Stąd ten test.
 */
BOOST_AUTO_TEST_CASE (test042EmptyMapKey)
{
        BOOST_REQUIRE_THROW (ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "042-map-with-empty-key.xml")), Core::Exception);
}

/**
 * Kolejny błąd, który miałem zapisany : kiedy były 2 beany o
 * tym samym ID, to leciał SegF w poprzedniej wersji.
 */
BOOST_AUTO_TEST_CASE (test043MultipleIdBean)
{
        BOOST_REQUIRE_THROW (ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "043-multiple-id-bean.xml")), Core::Exception);
}

/**
 * Testy, czy da sie tworzyć skalary jako beany i czy da sie używać
 * ich konstruktorów kopiujących.
 */
BOOST_AUTO_TEST_CASE (test045BaseTypesConstructors)
{
        BeanFactoryContainer *cont = ContainerFactory::createAndInit (CompactMetaService::parseFile (PATH + "045-base-types-constructors.xml"));

        Variant vB = cont->getBean ("string1");
        BOOST_CHECK (ccast <std::string> (vB));
        BOOST_CHECK_EQUAL (vcast <std::string> (vB), "");

        vB = cont->getBean ("string2");
        BOOST_CHECK (ccast <std::string> (vB));
        BOOST_CHECK_EQUAL (vcast <std::string> (vB), "testaaa");

        vB = cont->getBean ("int1");
        BOOST_CHECK (ccast <int> (vB));

        vB = cont->getBean ("int2");
        BOOST_CHECK (ccast <int> (vB));
        BOOST_CHECK (vcast <int> (vB) == 6667);
}

BOOST_AUTO_TEST_SUITE_END ();
