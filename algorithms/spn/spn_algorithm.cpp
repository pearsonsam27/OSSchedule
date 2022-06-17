#include "algorithms/spn/spn_algorithm.hpp"
#include "utilities/stable_priority_queue/stable_priority_queue.hpp"
#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

Stable_Priority_Queue<std::shared_ptr<Thread>> spnQueue;
/*
    Here is where you should define the logic for the FCFS algorithm.
*/

SPNScheduler::SPNScheduler(int slice)
{
    if (slice != -1)
    {
        throw("SPN must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> SPNScheduler::get_next_thread()
{
    std::shared_ptr<SchedulingDecision> decision(new SchedulingDecision());

    if (!spnQueue.empty())
    {
        decision->thread = spnQueue.top();

        decision->explanation = ("Selected from " + std::to_string(spnQueue.size()) + " threads. Will run to completion of burst.");
        spnQueue.pop();
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

void SPNScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread)
{
    spnQueue.push(thread->bursts.front()->length, thread);
    //presumably this is a queue, and get_next_thread pop's first from queue
    // TODO: implement me!
}

size_t SPNScheduler::size() const
{
    //if size ==0 wtvs
    // TODO: implement me!
    return spnQueue.size();
}
