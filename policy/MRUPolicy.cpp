#include "MRUPolicy.h"

#include <algorithm>

namespace bufman {
    // order_ is recency ranking
    //positions_[f] is the bookmark pointint at frame f node in the list.
    // order_.end() is an untracked frame or none

    // Empties list and sets all elements to end()
    void MRUPolicy::init(std::size_t pool_size) {
        order_.clear();
        positions_.assign(pool_size, order_.end());
        // In C++, the vector assign() is a built-in method used to assign the new values
        // to the given vector by replacing old ones. It also modifies the size of the vector
        // according to the given number of elements.
    }

    void MRUPolicy::touch(std::size_t frame) {
        if (positions_[frame] != order_.end()) {
            order_.erase(positions_[frame]);
        }
        order_.push_front(frame);
        positions_[frame] = order_.begin();
    }

    void MRUPolicy::on_access(std::size_t frame) {
        touch(frame);
    }

    void MRUPolicy::on_load(std::size_t frame) {
        touch(frame);
    }
    void MRUPolicy::on_remove(std::size_t frame) {
        if (positions_[frame] != order_.end()) {
            order_.erase(positions_[frame]);
            positions_[frame] = order_.end();
        }
    }
    //rbegin & rend are reverse iterators in LRU so they go from the end to the front
    // for MRU we want to go from the start to the end so we use the normal begin and end
    std::optional<std::size_t> MRUPolicy::pick_victim(
        const std::vector<std::size_t>& candidates) const {
        for (auto it = order_.begin(); it != order_.end(); ++it) {
            if (std::find(candidates.begin(), candidates.end(), *it) != candidates.end()) {
                return *it;
            }
        }
        return std::nullopt;
    }

}
