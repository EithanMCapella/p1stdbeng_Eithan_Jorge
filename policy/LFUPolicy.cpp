// policy/LFUPolicy.cpp — stub; replace with your implementation
#include "LFUPolicy.h"

namespace bufman {

    void LFUPolicy::init(std::size_t) {}
    void LFUPolicy::on_access(std::size_t) {}
    void LFUPolicy::on_load(std::size_t) {}
    void LFUPolicy::on_remove(std::size_t) {}
    std::optional<std::size_t> LFUPolicy::pick_victim(
            const std::vector<std::size_t>& candidates) const {
        // Valid but arbitrary: keeps the harness running. A stub that returns
        // std::nullopt makes the check suite abort partway.
        if (candidates.empty()) {
            return std::nullopt;
        }
        return candidates.front();
    }

}
