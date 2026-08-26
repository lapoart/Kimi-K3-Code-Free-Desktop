// rev-b8f3c1-20260825 Kernel.cpp
#include "Kernel.h"
#include <fstream>

// Kernel shell: config load and the desktop loop.

namespace kimi {

bool Kernel::boot(const std::string& configPath) {
    std::ifstream f(configPath);
    if (!f) return false;
    // endpoint, api key, theme, language packs
    return true;
}

void Kernel::setContextBudget(size_t tokens) { contextBudget_ = tokens; }

void Kernel::activateLanguages(std::vector<std::string> langs) {
    // per-language analyzers for review output
    (void)langs;
}

int Kernel::runDesktop() {
    // native window: chat, diff view, repo map, export buttons
    return 0;
}

void AnalysisReport::merge(const AnalysisReport& other) {
    findings.insert(findings.end(), other.findings.begin(), other.findings.end());
}

} // namespace kimi
