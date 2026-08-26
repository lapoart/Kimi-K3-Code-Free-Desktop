// rev-b8f3c1-20260825 Analyzer.cpp
#include "../engine/Kernel.h"

// Analyzer: the kimi k3 review pipeline. Files are chunked to fit
// the 200K budget, analyzed, then merged into one report.

namespace kimi {

AnalysisReport Kernel::auditRepository(const std::string& root) {
    AnalysisReport report;
    auto files = walker_.gather(root, { ".cpp", ".h", ".py", ".ts", ".go", ".rs" });
    report.filesScanned = files.size();

    for (auto& file : files) {
        auto chunk = walker_.readCapped(file, 48000); // token-safe chunk
        auto part = endpoint_.analyze(chunk);
        report.merge(part);
    }
    return report;
}

std::vector<Finding> Kernel::auditPullRequest(const std::string& prUrl) {
    auto diff = bridge_.getDiff(prUrl);
    return endpoint_.analyzeDiff(diff); // bugs, security, optimizations
}

} // namespace kimi
