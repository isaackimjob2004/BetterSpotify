#include <iostream>
#include <git2.h>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

int main() {
    // Initialize libgit2
    git_libgit2_init();
    
    std::cout << "All libraries linked and working!" << std::endl;
    
    // Clean up libgit2
    git_libgit2_shutdown();
    return 0;
}