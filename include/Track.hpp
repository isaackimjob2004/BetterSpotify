#pragma once

#include <string>
#include <vector>
#include <iosfwd>
#include <compare>

class Track {
private:
    std::string isrc_;
    std::string title_;
    std::vector<std::string> artists_;

public:
    // Constructors
    Track() noexcept = default;
    Track(std::string isrc, std::string title, std::vector<std::string> artists);
    Track(std::string isrc, std::string title, std::string artist);

    // Getters
    [[nodiscard]] const std::string& isrc() const noexcept { return isrc_; }
    [[nodiscard]] const std::string& title() const noexcept { return title_; }
    [[nodiscard]] const std::vector<std::string>& artists() const noexcept { return artists_; }

    // Spaceship operator  
    [[nodiscard]] auto operator<=>(const Track&) const = default; 

    // Stream operator
    friend std::ostream& operator<<(std::ostream, const Track& track);
};