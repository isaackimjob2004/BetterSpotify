#include "Track.hpp"
#include <iostream>
#include <utility>

Track::Track(std::string isrc, std::string title, std::vector<std::string> artists)
    : isrc_(std::move(isrc)), 
      title_(std::move(title)), 
      artists_(std::move(artists)) {}

Track::Track(std::string isrc, std::string title, std::string artist)
    : isrc_(std::move(isrc)),
      title_(std::move(title)),
      artists_{std::move(artist)} {}

std::ostream& operator<<(std::ostream& os, const Track& track) {
    os << "[TRACK " << track.isrc_ << "] \"" << track.title_ << "\" by ";
    if (track.artists_.empty()) {
        os << "Unknown Artist";
    } else {
        for (size_t i = 0; i < track.artists_.size(); ++i) {
            os << track.artists_[i] << (i+1 < track.artists_.size() ? ", " : "");
        }
    }
    return os;
}