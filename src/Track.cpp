#include "Track.hpp"
#include <utility>

Track::Track(std::string isrc, std::string title, std::string artist)
    : isrc(std::move(isrc)), title(std::move(title)), artist(std::move(artist)) {}