/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/


#ifndef IREFLECTANNOTATION_H_
#define IREFLECTANNOTATION_H_

#include "reflection/annotations/IAnnotation.h"
#include "core/variant/Variant.h"

namespace Reflection {
struct IReflectionVisitor;
class Class;

/**
 *
 */
struct IReflectionAnnotation : public Annotations::IAnnotation {

        virtual ~IReflectionAnnotation () {}
        /**
         * Will acceptt variuous operations on Annotations.
         * @param vis Visitor (tha means a class that implements some particular algorithm on IAnnotation).
         * @param args Additional args (input).
         * @return Output.
         */
        virtual Core::Variant accept (IReflectionVisitor *vis, Class *cls = NULL) = 0;
        virtual void deleteDuplicate () {}

};

} // namespace

#endif /* IREFLECTANNOTATION_H_ */
