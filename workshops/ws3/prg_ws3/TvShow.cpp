#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <numeric>
#include "TvShow.h"

namespace seneca {

    void TvShow::display(std::ostream& out) const
    {
        if (g_settings.m_tableView)
        {
            out << "S | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_episodes.size() << " | ";
            out << std::setw(4) << this->getYear() << " | ";
            out << std::left;
            if (g_settings.m_maxSummaryWidth > -1)
            {
                if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << this->getSummary();
                else
                    out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else
                out << this->getSummary();
            out << std::endl;
        }
        else
        {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            for (auto& item : m_episodes)
            {
                out << std::setfill('0') << std::right;
                out << "    " << 'S' << std::setw(2) << item.m_season
                    << 'E' << std::setw(2) << item.m_numberInSeason << ' ';
                if (item.m_title != "")
                    out << item.m_title << '\n';
                else
                    out << "Episode " << item.m_numberOverall << '\n';

                pos = 0;
                while (pos < item.m_summary.size())
                {
                    out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                    pos += g_settings.m_maxSummaryWidth - 8;
                }
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }

    TvShow* TvShow::createItem(const std::string& strShow) {
        if (strShow.empty() || strShow[0] == '#') {
            throw std::invalid_argument("Not a valid show.");
        }

        std::istringstream stream(strShow);
        std::string id, title, yearStr, summary;

        std::getline(stream, id, ',');
        trim(id);
        std::getline(stream, title, ',');
        trim(title);
        std::getline(stream, yearStr, ',');
        trim(yearStr);
        std::getline(stream, summary);
        trim(summary);

        unsigned short year = static_cast<unsigned short>(std::stoi(yearStr));

        return new TvShow(id, title, year, summary);
    }

    template <typename Collection_t>
    void TvShow::addEpisode(Collection_t& col, const std::string& strEpisode) {
        if (strEpisode.empty() || strEpisode[0] == '#') {
            throw std::invalid_argument("Not a valid episode.");
        }

        std::istringstream stream(strEpisode);
        std::string id, numOverallStr, seasonStr, numInSeasonStr, airDate, lengthStr, title, summary;

        std::getline(stream, id, ',');
        trim(id);
        auto it = std::find_if(col.begin(), col.end(), [&](const MediaItem* item) {
            return dynamic_cast<const TvShow*>(item)->m_id == id;
            });

        if (it == col.end()) {
            throw std::invalid_argument("Show not found.");
        }

        const TvShow* show = dynamic_cast<const TvShow*>(*it);

        std::getline(stream, numOverallStr, ',');
        std::getline(stream, seasonStr, ',');
        std::getline(stream, numInSeasonStr, ',');
        std::getline(stream, airDate, ',');
        std::getline(stream, lengthStr, ',');
        std::getline(stream, title, ',');
        std::getline(stream, summary);

        trim(numOverallStr);
        trim(seasonStr);
        trim(numInSeasonStr);
        trim(airDate);
        trim(lengthStr);
        trim(title);
        trim(summary);

        unsigned short numOverall = static_cast<unsigned short>(std::stoi(numOverallStr));
        unsigned short season = seasonStr.empty() ? 1 : static_cast<unsigned short>(std::stoi(seasonStr));
        unsigned short numInSeason = static_cast<unsigned short>(std::stoi(numInSeasonStr));
        unsigned int length = static_cast<unsigned int>(std::stoi(lengthStr));

        TvEpisode episode{ show, numOverall, season, numInSeason, airDate, length, title, summary };
        const_cast<TvShow*>(show)->m_episodes.push_back(episode);
    }

    double TvShow::getEpisodeAverageLength() const {
        if (m_episodes.empty()) return 0.0;

        return std::accumulate(m_episodes.begin(), m_episodes.end(), 0.0,
            [](double sum, const TvEpisode& ep) { return sum + ep.m_length; }) / m_episodes.size();
    }

    std::list<std::string> TvShow::getLongEpisodes() const {
        std::list<std::string> longEpisodes;
        std::copy_if(m_episodes.begin(), m_episodes.end(), std::back_inserter(longEpisodes),
            [](const TvEpisode& ep) { return ep.m_length >= 3600; });

        return longEpisodes;
    }

} // namespace seneca
