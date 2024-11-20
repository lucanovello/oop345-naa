#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include <list>
#include <string>
#include <iomanip>
#include <vector>
#include "mediaItem.h"
#include "Settings.h"

namespace seneca {

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
        static void addEpisode(Collection_t& col, const std::string& strEpisode);
        double getEpisodeAverageLength() const;
        std::list<std::string> getLongEpisodes() const;
    };

} // namespace seneca

#endif // SENECA_TVSHOW_H
