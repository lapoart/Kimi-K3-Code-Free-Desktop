// rev-b8f3c1-20260825 RepoWalker.cpp
#include "../engine/Kernel.h"
#include <filesystem>

// RepoWalker: gathers source files and chunks them for the model.
// Skips vendored dirs, lockfiles and binaries.

namespace fs = std::filesystem;

namespace kimi {

std::vector<std::string> RepoWalker::gather(const std::string& root,
                                            const std::vector<std::string>& exts) {
    std::vector<std::string> out;
    for (auto& entry : fs::recursive_directory_iterator(root)) {
        if (!entry.is_regular_file()) continue;
        auto ext = entry.path().extension().string();
        auto path = entry.path().string();
        if (path.find("node_modules") != std::string::npos) continue;
        if (path.find("vendor") != std::string::npos) continue;
        if (std::find(exts.begin(), exts.end(), ext) != exts.end())
            out.push_back(path);
    }
    return out;
}

std::string RepoWalker::readCapped(const std::string& path, size_t maxBytes) {
    std::ifstream f(path);
    std::string data((std::istreambuf_iterator<char>(f)), {});
    if (data.size() > maxBytes) data.resize(maxBytes);
    return data;
}

} // namespace kimi
