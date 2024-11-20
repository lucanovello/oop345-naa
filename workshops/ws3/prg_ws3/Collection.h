#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <cctype>
#include <memory>

namespace seneca {

    class MediaItem {
    public:
        virtual const std::string& title() const = 0;
        virtual const std::string& summary() const = 0;
        virtual ~MediaItem() = default;
    };

    class Collection {
        std::string m_name;
        std::vector<std::unique_ptr<MediaItem>> m_items;
        std::function<void(const Collection&, const MediaItem&)> m_observer;
    public:
        Collection(const std::string& name);
        Collection(const Collection&) = delete;
        Collection(Collection&&) = delete;
        Collection& operator=(const Collection&) = delete;
        Collection& operator=(Collection&&) = delete;
        ~Collection() = default;
        const std::string& name() const;
        size_t size() const;
        void setObserver(void (*observer)(const Collection&, const MediaItem&));
        Collection& operator+=(MediaItem* item);
        MediaItem* operator[](size_t idx) const;
        MediaItem* operator[](const std::string& title) const;
        void removeQuotes();
        void sort(const std::string& field);

        friend std::ostream& operator<<(std::ostream& out, const Collection& collection);
    };

} // namespace seneca

#endif // SENECA_COLLECTION_H
