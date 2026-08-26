// rev-b8f3c1-20260825 Kernel.h
#pragma once
#include <string>
#include <vector>

// Kimi K3 Code desktop client core types.
// 200K context, GitHub integration, bilingual zh/en output.

namespace kimi {

struct Finding {
    std::string file;
    int line = 0;
    std::string severity;  // bug | security | optimization
    std::string message;
};

struct AnalysisReport {
    size_t filesScanned = 0;
    std::vector<Finding> findings;
    void merge(const AnalysisReport& other);
    std::string toMarkdown() const;
};

class RepoWalker {
public:
    std::vector<std::string> gather(const std::string& root,
                                    const std::vector<std::string>& exts);
    std::string readCapped(const std::string& path, size_t maxBytes);
};

struct Endpoint {
    AnalysisReport analyze(const std::string& chunk);
    std::vector<Finding> analyzeDiff(const std::string& diff);
};

struct PrBridge {
    std::string getDiff(const std::string& prUrl);
    bool postComment(const std::string& prUrl, const std::string& body);
};

class Kernel {
public:
    bool boot(const std::string& configPath);
    void setContextBudget(size_t tokens);
    void activateLanguages(std::vector<std::string> langs);
    AnalysisReport auditRepository(const std::string& root);
    std::vector<Finding> auditPullRequest(const std::string& prUrl);
    int runDesktop();

private:
    RepoWalker walker_;
    Endpoint endpoint_;
    PrBridge bridge_;
    size_t contextBudget_ = 200000;
};

} // namespace kimi
