#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <string>
#include <sstream>
#include <iomanip>
#include "mediaItem.h"
#include "settings.h"

namespace seneca {

    class Book : public MediaItem {
        std::string m_author{};
        std::string m_country{};
        double m_price{};
        Book(const std::string& author, const std::string& title, const std::string& country,
            double price, const std::string& summary, unsigned short year)
            : MediaItem(title, summary, year), m_author{ author }, m_country{ country }, m_price{ price } {}
    public:
        void display(std::ostream& out = std::cout) const override;
        static Book* createItem(const std::string& strBook);
    };

} // namespace seneca

#endif // SENECA_BOOK_H
