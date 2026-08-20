#pragma once

#include <string>

class Track {
private:
    std::string isrc;
    std::string title;
    std::string artist; // Assuming there's only one artist for a track. TODO change to dynamic vector

public:
    // Constructor and destructor
    Track(std::string isrc, std::string title, std::string artist);
    ~Track() = default;

    // Getters
    const std::string& get_isrc() const { return isrc; }
    const std::string& get_title() const { return title; }
    const std::string& get_artist() const { return artist; }
};