// policy/LFUPolicy.cpp — stub; replace with your implementation
#include "LFUPolicy.h"

#include <algorithm>
#include <limits>

namespace bufman {

    void LFUPolicy::init(std::size_t pool_size) {
        buckets_.clear();
        slots_.clear();
        min_freq_ = 0;
    }

    void LFUPolicy::on_access(std::size_t frame) {
        auto it = slots_.find(frame);
        if (it == slots_.end()) {
            return;
        }

        std::size_t freq = it->second.count;
        auto &old = buckets_[freq];
        old.erase(it->second.pos);

        if (old.empty()) {
            buckets_.erase(freq);
            if (min_freq_ == freq) {
                ++min_freq_;
            }
        }

        auto &next = buckets_[freq + 1];
        next.push_front(frame);
        it->second = {freq + 1, next.begin()};
    }

    void LFUPolicy::on_load(std::size_t frame) {
        buckets_[1].push_front(frame);
        slots_[frame] = {1, buckets_[1].begin()};
        min_freq_ = 1;
    }

    void LFUPolicy::on_remove(std::size_t frame)
    {
        auto it = slots_.find(frame);
        if (it == slots_.end()) {
            return;
        }

        std::size_t freq = it->second.count;
        buckets_[freq].erase(it->second.pos);

        if (buckets_[freq].empty()) {
            buckets_.erase(freq);
        }

        slots_.erase(it);

        min_freq_ = 0;
        for (const auto &[count, bucket] : buckets_) {
            if (min_freq_ == 0 || count < min_freq_) {
                min_freq_ = count;
            }
        }
    }

    std::optional<std::size_t> LFUPolicy::pick_victim(
    const std::vector<std::size_t>& candidates) const {

        if (candidates.empty()) {
            return std::nullopt;
        }

        std::size_t freq = std::numeric_limits<std::size_t>::max();

        for (auto frame : candidates) {
            auto it = slots_.find(frame);
            if (it != slots_.end()) {
                freq = std::min(freq, it->second.count);
            }
        }

        auto bucket = buckets_.find(freq);
        if (bucket == buckets_.end()) {
            return std::nullopt;
        }

        // Back = least recently used.
        for (auto it = bucket->second.rbegin(); it != bucket->second.rend(); ++it) {
            if (std::find(candidates.begin(), candidates.end(), *it)
                != candidates.end()) {
                return *it;
            }
        }

        return std::nullopt;
    }
}
