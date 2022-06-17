#include "algorithms/fcfs/fcfs_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

std::queue<std::shared_ptr<Thread>> fcfsQueue;
/*
    Here is where you should define the logic for the FCFS algorithm.
*/

FCFSScheduler::FCFSScheduler(int slice)
{
    if (slice != -1)
    {
        throw("FCFS must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> FCFSScheduler::get_next_thread()
{
    std::shared_ptr<SchedulingDecision> decision(new SchedulingDecision());

    if (!fcfsQueue.empty())
    {
        decision->thread = fcfsQueue.front();

        decision->explanation = ("Selected from " + std::to_string(fcfsQueue.size()) + " threads. Will run to completion of burst.");
        fcfsQueue.pop();
    }
    else
    {
        decision->explanation = "No threads available for scheduling.";
    }
    //choose how to get next thread --> look at get_next_thread
    //ADD EXPLANATION
    // TODO: implement me!
    return decision;
}

void FCFSScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread)
{
    fcfsQueue.push(thread);
    //presumably this is a queue, and get_next_thread pop's first from queue
    // TODO: implement me!
}

size_t FCFSScheduler::size() const
{
    //if size ==0 wtvs
    // TODO: implement me!
    return fcfsQueue.size();
}
