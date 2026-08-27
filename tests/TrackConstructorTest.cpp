#include <gtest/gtest.h>
#include "Track.hpp"
#include <string>
#include <optional>
#include <vector>

TEST(TrackConstructorTest, EmptyConstructor) {
    Track track{};

    EXPECT_EQ(track.isrc(), "");
    EXPECT_EQ(track.title(), "");
    EXPECT_EQ(track.artists(), std::vector<std::string>{});
}

TEST(TrackConstructorTest, SingleConstructor) {
    Track track{"USRC17607839", "Under Pressure", "Queen"};

    EXPECT_EQ(track.isrc(), "USRC17607839");
    EXPECT_EQ(track.title(), "Under Pressure");
    EXPECT_EQ(track.artists(), std::vector<std::string>{"Queen"});
}

enum class Expectation {
    Success,
    ThrowsLengthError,
    ThrowsInvalidArgument
};

struct TrackTestCase {
    std::string testName;
    std::string isrc;
    std::string title;
    std::vector<std::string> artists;
    Expectation expectedOutcome;
};

struct TestCaseBuilder {
    static constexpr const char* BASE_ISRC = "USRC17607839";
    static constexpr const char* BASE_TITLE = "Under Pressure";

    static std::vector<std::string> baseArtists() {
        return {"Queen", "David Bowie"};
    }

    static TrackTestCase create(
        std::string name,
        std::optional<std::string> isrc,
        std::optional<std::string> title,
        std::optional<std::vector<std::string>> artists,
        Expectation expected
    ) {
        return TrackTestCase{
            std::move(name),
            isrc.value_or(BASE_ISRC),
            title.value_or(BASE_TITLE),
            artists.value_or(baseArtists()),
            expected
        };
    }
};

// Test fixture
class TrackBCCTest : public ::testing::TestWithParam<TrackTestCase> {};

TEST_P(TrackBCCTest, ExecutesBCCScenario) {
    const auto& tc = GetParam();

    switch (tc.expectedOutcome) {
        case Expectation::Success:
            EXPECT_NO_THROW({
                Track track(tc.isrc, tc.title, tc.artists);
                EXPECT_EQ(track.isrc(), tc.isrc);
                EXPECT_EQ(track.title(), tc.title);
                EXPECT_EQ(track.artists(), tc.artists);
            }) << "Failed on test case: " << tc.testName;
            break;
        
        case Expectation::ThrowsLengthError:
            EXPECT_THROW(
                Track(tc.isrc, tc.title, tc.artists),
                std::length_error
            ) << "Failed on test case: " << tc.testName;
            break;
        
        case Expectation::ThrowsInvalidArgument:
            EXPECT_THROW(
                Track(tc.isrc, tc.title, tc.artists),
                std::invalid_argument
            ) << "Failed on test case: " << tc.testName;
            break;
    }
}

INSTANTIATE_TEST_SUITE_P(
    ConstructorBCCSuite,
    TrackBCCTest,
    ::testing::Values(
        // Base choice
        TestCaseBuilder::create("TC_Base", std::nullopt, std::nullopt, std::nullopt, Expectation::Success),
        // Vary ISRC
        TestCaseBuilder::create("ISRC_Empty", "", std::nullopt, std::nullopt, Expectation::ThrowsLengthError),
        TestCaseBuilder::create("ISRC_TooShort", "USRC1", std::nullopt, std::nullopt, Expectation::ThrowsLengthError),
        TestCaseBuilder::create("ISRC_TooLong", "USRC17607839999", std::nullopt, std::nullopt, Expectation::ThrowsLengthError),
        TestCaseBuilder::create("ISRC_Lowercase", "usrc17607839", std::nullopt, std::nullopt, Expectation::ThrowsInvalidArgument),
        TestCaseBuilder::create("ISRC_Hyphens", "US-RC1-76-078", std::nullopt, std::nullopt, Expectation::ThrowsInvalidArgument),
        // Vary Title
        TestCaseBuilder::create("Title_Empty", std::nullopt, "", std::nullopt, Expectation::ThrowsInvalidArgument),
        TestCaseBuilder::create("Title_TooLong", std::nullopt, std::string(256, 'A'), std::nullopt, Expectation::ThrowsLengthError),
        TestCaseBuilder::create("Title_Utf8Emojis", std::nullopt, "☀️ Sigur Rós", std::nullopt, Expectation::Success),
        TestCaseBuilder::create("Title_WhitespaceOnly", std::nullopt, "   \t\n  ", std::nullopt, Expectation::ThrowsInvalidArgument),
        TestCaseBuilder::create("Title_ControlChars", std::nullopt, "Song\nTitle", std::nullopt, Expectation::ThrowsInvalidArgument),
        // Vary Artists Vector
        TestCaseBuilder::create("Artists_EmptyList", std::nullopt, std::nullopt, std::vector<std::string>{}, Expectation::ThrowsInvalidArgument),
        TestCaseBuilder::create("Artists_SingleArtist", std::nullopt, std::nullopt, std::vector<std::string>{"Queen"}, Expectation::Success),
        TestCaseBuilder::create("Artists_ExceedsMaxCount", std::nullopt, std::nullopt, std::vector<std::string>(51, "Queen"), Expectation::ThrowsLengthError),
        TestCaseBuilder::create("Artists_ContainsEmptyItem", std::nullopt, std::nullopt, std::vector<std::string>{"Queen", ""}, Expectation::ThrowsInvalidArgument),
        TestCaseBuilder::create("Artists_ItemTooLong", std::nullopt, std::nullopt, std::vector<std::string>{std::string(256, 'X')}, Expectation::ThrowsLengthError)
    ),
    [](const ::testing::TestParamInfo<TrackTestCase>& info) {
        return info.param.testName;
    }
);