#include "Collection.h"

namespace seneca {

	Collection::Collection(const std::string& name)
		: m_name(name), m_observer(nullptr) {}

	const std::string& Collection::name() const {
		return m_name;
	}

	size_t Collection::size() const {
		return m_items.size();
	}

	void Collection::setObserver(void (*observer)(const Collection&, const MediaItem&)) {
		m_observer = observer;
	}

	Collection& Collection::operator+=(MediaItem* item) {
		auto it = std::find_if(m_items.begin(), m_items.end(),
			[item](const std::unique_ptr<MediaItem>& current) {
				return current->getTitle() == item->getTitle();
			});
		if (it == m_items.end()) {
			m_items.emplace_back(item);
			if (m_observer) {
				m_observer(*this, *item);
			}
		}
		else {
			delete item; 
		}
		return *this;
	}

	MediaItem* Collection::operator[](size_t idx) const {
		if (idx >= m_items.size()) {
			throw std::out_of_range("Bad index [" + std::to_string(idx) +
				"]. Collection has [" + std::to_string(m_items.size()) + "] items.");
		}
		return m_items[idx].get();
	}

	MediaItem* Collection::operator[](const std::string& title) const {
		auto it = std::find_if(m_items.begin(), m_items.end(),
			[&title](const std::unique_ptr<MediaItem>& item) {
				std::cout << "Comparing " << item->getTitle() << " with " << title << "\n";
				return item->getTitle() == title;
			});

		return it != m_items.end() ? it->get() : nullptr;
	}

	void Collection::removeQuotes() {
		std::for_each(m_items.begin(), m_items.end(),
			[](std::unique_ptr<MediaItem>& item) {
				auto removeQuotesHelper = [](std::string& str) {
					if (!str.empty() && str.front() == '"' && str.back() == '"') {
						str.erase(0, 1); 
						str.pop_back();   
					}
					};

				std::string title = item->getTitle();
				removeQuotesHelper(title);
				item->setTitle(title);

				std::string summary = item->getSummary();
				removeQuotesHelper(summary);
				item->setSummary(summary);
			});
	}



	void Collection::sort(const std::string& field) {
		if (field == "title") {
			std::sort(m_items.begin(), m_items.end(),
				[](const std::unique_ptr<MediaItem>& a, const std::unique_ptr<MediaItem>& b) {
					return a->getTitle() < b->getTitle();
				});
		}
		else if (field == "summary") {
			std::sort(m_items.begin(), m_items.end(),
				[](const std::unique_ptr<MediaItem>& a, const std::unique_ptr<MediaItem>& b) {
					return a->getSummary() < b->getSummary();
				});
		}
		else if (field == "year") {
			std::sort(m_items.begin(), m_items.end(),
				[](const std::unique_ptr<MediaItem>& a, const std::unique_ptr<MediaItem>& b) {
					return a->getYear() < b->getYear();
				});
		}
		else {
			throw "Invalid field [" + field + "].";
		}	
	}



	std::ostream& operator<<(std::ostream& out, const Collection& collection) {
		for (const auto& item : collection.m_items) {
			out << *item;
		}
		return out;
	}




} // namespace seneca
