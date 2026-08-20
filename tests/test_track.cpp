#include <gtest/gtest.h>
#include "Track.hpp"

TEST(TrackTest, InitializationAndGetters) {
    Track track("isrc", "song name", "artist name");

    EXPECT_EQ(track.get_isrc(), "isrc");
    EXPECT_EQ(track.get_title(), "song name");
    EXPECT_EQ(track.get_artist(), "artist name");
}

TEST(TrackTest, HandlesEmptyFields) {
    Track track("", "", "");

    EXPECT_TRUE(track.get_isrc().empty());
    EXPECT_TRUE(track.get_title().empty());
    EXPECT_TRUE(track.get_artist().empty());
}