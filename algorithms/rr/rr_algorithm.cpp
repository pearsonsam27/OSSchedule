#include "algorithms/rr/rr_algorithm.hpp"
//#include "utilities/stable_priority_queue/stable_priority_queue.hpp"
#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

std::queue<std::shared_ptr<Thread>> rrQueue;
/*
    Here is where you should define the logic for the FCFS algorithm.
*/

RRScheduler::RRScheduler(int slice)
{
    if (slice <= 0)
    {
        throw("RR must have a timeslice > 0");
    }
    this->time_slice = slice;
}

std::shared_ptr<SchedulingDecision> RRScheduler::get_next_thread()
{
    std::shared_ptr<SchedulingDecision> decision(new SchedulingDecision());

    if (!rrQueue.empty())
    {
        decision->thread = rrQueue.front();

        decision->explanation = ("Selected from " + std::to_string(rrQueue.size()) + " threads. Will run for at most " + std::to_string(this->time_slice) + " ticks.");
        rrQueue.pop();
    }
    else
    {
        decision->explanation = "No threads available for scheduling.";
    }
    //SchedulingDecision->explanation = "No threads available for scheduling.";
    //choose how to get next thread --> look at get_next_thread
    //ADD EXPLANATION
    // TODO: implement me!
    return decision;
}

void RRScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread)
{
    rrQueue.push(thread);
    //presumably this is a queue, and get_next_thread pop's first from queue
    // TODO: implement me!
}

size_t RRScheduler::size() const
{
    //if size ==0 wtvs
    // TODO: implement me!
    return rrQueue.size();
}
