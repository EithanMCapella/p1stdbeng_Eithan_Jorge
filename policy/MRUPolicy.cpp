// policy/MRUPolicy.cpp — stub; replace with your implementation
#include "MRUPolicy.h"

namespace bufman {

    void MRUPolicy::init(std::size_t) {}
    void MRUPolicy::on_access(std::size_t) {}
    void MRUPolicy::on_load(std::size_t) {}
    void MRUPolicy::on_remove(std::size_t) {}
    std::optional<std::size_t> MRUPolicy::pick_victim(
            const std::vector<std::size_t>& candidates) const {
        // Valid but arbitrary: keeps the harness running. A stub that returns
        // std::nullopt makes the check suite abort partway.
        if (candidates.empty()) {
            return std::nullopt;
        }
        return candidates.front();
    }

    // Private helper declared in the header (move a frame to the MRU front).
    void MRUPolicy::touch(std::size_t) {}

}
