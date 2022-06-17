#include "algorithms/cfs/cfs_algorithm.hpp"
#include "utilities/stable_priority_queue/stable_priority_queue.hpp"
#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

Stable_Priority_Queue<std::shared_ptr<Thread>> priorityQueueCFS;

/*
    Here is where you should define the logic for the FCFS algorithm.
*/

CFSScheduler::CFSScheduler(int slice)
{
    if (slice <= 0)
    {
        throw("CFS must have a timeslice > 0");
    }

    weightTotal = 0;
    this->minGran = slice;
    this->time_slice = slice;
}

std::shared_ptr<SchedulingDecision> CFSScheduler::get_next_thread()
{
    std::shared_ptr<SchedulingDecision> decision(new SchedulingDecision());

    double weight[4] = {88761, 29154, 1024, 15};

    if (!priorityQueueCFS.empty())
    {
        decision->thread = priorityQueueCFS.top();
        double genSlice = 48.0 / priorityQueueCFS.size();
        int timeSlice = genSlice * (weight[decision->thread->priority]) / weightTotal;
        if (minGran > timeSlice)
        {
            this->time_slice = minGran;
        }
        else
        {
            this->time_slice = timeSlice;
        }

        int vRunTime = 1024.0 / weight[decision->thread->priority] * decision->thread->runny;
        decision->explanation = ("Selected from " + std::to_string(priorityQueueCFS.size()) + " threads (vruntime = " + std::to_string(int(vRunTime)) + "). Will run for at most " + std::to_string(int(this->time_slice)) + " ticks.");

        weightTotal -= weight[decision->thread->priority];
        priorityQueueCFS.pop();
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

void CFSScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread)
{
    double weight[4] = {88761, 29154, 1024, 15};
    thread->runny += thread->service_time - thread->prevRun;
    thread->prevRun = thread->service_time;
    double vRunTime = (thread->runny) * 1024.0 / weight[thread->priority];

    priorityQueueCFS.push(vRunTime, thread);
    weightTotal += weight[thread->priority];

    //presumably this is a queue, and get_next_thread pop's first from queue
    // TODO: implement me!
}

size_t CFSScheduler::size() const
{
    //if size ==0 wtvs
    // TODO: implement me!
    return priorityQueueCFS.size();
}
