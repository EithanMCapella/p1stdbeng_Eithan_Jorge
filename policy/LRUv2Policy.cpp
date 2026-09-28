// policy/LRUv2Policy.cpp — stub; replace with your implementation
#include "LRUv2Policy.h"

namespace bufman {

    void LRUv2Policy::init(std::size_t) {}
    void LRUv2Policy::on_access(std::size_t) {}
    void LRUv2Policy::on_load(std::size_t) {}
    void LRUv2Policy::on_remove(std::size_t) {}
    std::optional<std::size_t> LRUv2Policy::pick_victim(
            const std::vector<std::size_t>& candidates) const {
        // Valid but arbitrary: keeps the harness running. A stub that returns
        // std::nullopt makes the check suite abort partway.
        if (candidates.empty()) {
            return std::nullopt;
        }
        return candidates.front();
    }

    // Private helper declared in the header (move a frame to the MRU front).
    void LRUv2Policy::touch(std::size_t) {}

}
