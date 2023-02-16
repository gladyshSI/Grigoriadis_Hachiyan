#include "map_heap.h"

void MapHeap::add(size_t id, double val)
{
    double new_value = val;
    
    if(_mp.count(id) > 0)
    {
        double old_value = _mp.at(id);
        new_value += old_value;
        _set.erase({-old_value, id});
    }
    _mp[id] = new_value;
    _set.emplace(-new_value, id);
}

double MapHeap::max() const
{
    return -_set.begin()->first;
}