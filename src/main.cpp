#include <iostream>
#include <string>
#include <filesystem>
#include <git2.h>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

using json = nlohmann::json;

// do i need more free fncs in this?
#define CHECK_GIT(api_call, repo_ptr, step_name) \
    if ((api_call) < 0) { \
        const git_error* e = git_error_last(); \
        std::cerr << "[Error] " << step_name << " failed: " << (e ? e->message : "Unknown") << "\n"; \
        if (repo_ptr) git_repository_free(repo_ptr); \
        git_libgit2_shutdown(); \
        return 1; \
    }

int main() {
    std::string base_path = "./mock_playlist_repo";
    std::string repo_path = base_path + "/repo_1.git";

    // Clean up previous run before starting
    if (std::filesystem::exists(base_path)) {
        std::filesystem::remove_all(base_path);
    }

    // Initialize libgit2
    git_libgit2_init();
    
    // Init a new repo
    git_repository* repo = nullptr;
    CHECK_GIT(git_repository_init(&repo, repo_path.c_str(), 1), repo, "REPO INIT");
    std::cout << "[Success] Bare repo initialized succesfully.\n";

    // Create JSON str for each track
    json track1 = {
        {"isrc", "one"},
        {"title", "song one"},
        {"artist", "artist one"}
    };

    json track2 = {
        {"isrc", "two"},
        {"title", "song two"},
        {"artist", "artist two"}
    };

    std::string playlist = track1.dump() + "\n" + track2.dump() + "\n";

    // Create Git Blob
    git_oid blob_oid;
    CHECK_GIT(git_blob_create_from_buffer(&blob_oid, repo, playlist.data(), playlist.size()), repo, "CREATE BLOB");
    std::cout << "[Success] Created blob for playlist (Size: " << playlist.size() << " bytes)\n";

    // Tree build and insert
    git_treebuilder* bld = nullptr;
    CHECK_GIT(git_treebuilder_new(&bld, repo, nullptr), repo, "CREATE TREE");
    CHECK_GIT(git_treebuilder_insert(nullptr, bld, "playlist.jsonl", &blob_oid, GIT_FILEMODE_BLOB), repo, "INSERT BLOB INTO TREE");

    // Write tree to db
    git_oid tree_id;
    CHECK_GIT(git_treebuilder_write(&tree_id, bld), repo, "WRITE TREE");
    git_treebuilder_free(bld);
    std::cout << "[Success] Tree built and written to DB.\n";

    // Get signature and tree obj
    git_signature* sign = nullptr;
    CHECK_GIT(git_signature_now(&sign, "User", "UserName@gmail.com"), repo, "GET SIGNATURE");

    git_tree* tree = nullptr;
    CHECK_GIT(git_tree_lookup(&tree, repo, &tree_id), repo, "TREE LOOKUP");

    // Commit
    git_oid commit_id;
    CHECK_GIT(git_commit_create_v(&commit_id, repo, "HEAD", sign, sign, nullptr, "added two tracks", tree, 0), repo, "COMMIT CREATION");
    std::cout << "[Success] Commit succesful! Hash: " << git_oid_tostr_s(&commit_id) << "\n";

    // Clean up memory
    git_signature_free(sign);
    git_tree_free(tree);
    git_repository_free(repo);
    git_libgit2_shutdown();

    std::cout << "[Cleanup] Deleting " << base_path << "...\n";
    std::filesystem::remove_all(base_path);
    std::cout << "Done!\n";

    return 0;
}