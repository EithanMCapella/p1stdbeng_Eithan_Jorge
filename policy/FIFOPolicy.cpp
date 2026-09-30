#include "FIFOPolicy.h"

#include <algorithm>

namespace bufman
{

void FIFOPolicy::init(std::size_t pool_size)
{
    queue_.clear();
    positions_.clear();
}

void FIFOPolicy::on_access(std::size_t frame)
{
    // FIFO is based on arrival order, not like LRU which accessing the file
    // alters the order.
    (void)frame;
}

void FIFOPolicy::on_load(std::size_t frame)
{
    const auto found = positions_.find(frame);

    if (found != positions_.end())
    {
        queue_.erase(found->second);
        positions_.erase(found);
    }

    queue_.push_back(frame);
    auto position = queue_.end();
    --position;
    positions_[frame] = position;
}

void FIFOPolicy::on_remove(std::size_t frame)
{
    const auto found = positions_.find(frame);
    if (found == positions_.end())
    {
        return;
    }

    queue_.erase(found->second);
    positions_.erase(found);
}

std::optional<std::size_t> FIFOPolicy::pick_victim(
    const std::vector<std::size_t> &candidates) const
{
    for (const size_t frame : queue_)
    {
        if (std::find(candidates.begin(), candidates.end(), frame) != candidates.end())
        {
            return frame;
        }
    }
    return std::nullopt;
}
}