#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include <list>
#include <string>
#include <iomanip>
#include <vector>
#include "mediaItem.h"
#include "Settings.h"

namespace seneca {

    class TvShow;

    struct TvEpisode {
        const TvShow* m_show{}; 
        unsigned short m_numberOverall{};
        unsigned short m_season{};
        unsigned short m_numberInSeason{};
        std::string m_airDate{};
        unsigned int m_length{};
        std::string m_title{};
        std::string m_summary{};
    };


    class TvShow : public MediaItem {
        std::string m_id;
        std::vector<TvEpisode> m_episodes;
        TvShow(const std::string& id, const std::string& title, unsigned short year, const std::string& summary)
            : MediaItem(title, summary, year), m_id(id) {} 
    public:
        void display(std::ostream& out) const override;
        static TvShow* createItem(const std::string& strShow);
        template <typename Collection_t>
        static void addEpisode(Collection_t& col, const std::string& strEpisode) {
            if (strEpisode.empty() || strEpisode[0] == '#') {
                throw "Not a valid episode.";
            }

            std::istringstream stream(strEpisode);
            std::string id, numOverallStr, seasonStr, numInSeasonStr, airDate, lengthStr, title, summary;

            std::getline(stream, id, ',');
            trim(id);

            const TvShow* show = nullptr;
            for (size_t i = 0; i < col.size(); ++i) {
                const TvShow* currentShow = dynamic_cast<const TvShow*>(col[i]);
                if (currentShow && currentShow->m_id == id) {
                    show = currentShow;
                    break;
                }
            }

            if (show == nullptr) {
                throw std::invalid_argument("Show not found.");
            }

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



        double getEpisodeAverageLength() const;
        std::list<std::string> getLongEpisodes() const;

        friend std::ostream& operator<<(std::ostream& out, const TvShow& show);
    };

} // namespace seneca

#endif // SENECA_TVSHOW_H


