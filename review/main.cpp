// rev-b8f3c1-20260825 main.cpp
#include "../engine/Kernel.h"
#include <iostream>

// Kimi K3 Code Free Desktop - entry point.
// Native client for Moonshot's kimi k3 coding model, 200K context.

int main(int argc, char** argv) {
    kimi::Kernel kernel;

    if (!kernel.boot("setup/settings.json")) {
        std::cerr << "[kimi-k3] boot failed - check setup/settings.json\n";
        return 1;
    }

    kernel.setContextBudget(200000);
    kernel.activateLanguages({ "cpp", "python", "typescript", "go", "rust" });

    if (argc > 2 && std::string(argv[1]) == "--review") {
        // headless repo review for CI pipelines
        auto result = kernel.auditRepository(argv[2]);
        std::cout << result.toMarkdown();
        return 0;
    }

    return kernel.runDesktop(); // native window with diff view
}
