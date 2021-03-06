/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BOOK_H_
#define BOOK_H_

#include <string>
#include "reflection/Reflection.h"
#include "core/Pointer.h"
#include "core/IToStringEnabled.h"
#include "Author.h"

class Book : public Core::IToStringEnabled {
public:
        REFLECTION_CONSTRUCTOR_ (void)

        Book () : author (NULL) {}
        virtual ~Book () {}

        std::string const &getIsbn () const { return isbn; }
        REFLECTION_METHOD (setIsbn) void setIsbn (std::string const &s) { isbn = s; }

        std::string const &getTitle () const { return title; }
        REFLECTION_METHOD (setTitle) void setTitle (std::string const &s) { title = s; }

        Author *getAuthor () const { return author; }
        REFLECTION_METHOD (setAuthor) void setAuthor (Author *a) { author = a; }

        std::string toString () const { return "Book [" + getTitle () + ", " + getAuthor()->toString () + "]"; }

private:

        std::string title;
        std::string isbn;
        Author *author;

        REFLECTION_END (Book)
};

typedef std::vector <Book *> BookVector;
REFLECTION_COLLECTION (BookVector)

#	endif /* BOOK_H_ */
