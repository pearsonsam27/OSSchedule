#include "algorithms/priority/priority_algorithm.hpp"
#include "utilities/stable_priority_queue/stable_priority_queue.hpp"
#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

Stable_Priority_Queue<std::shared_ptr<Thread>> priorityQueue;
int priorityArrayU[4] = {0, 0, 0, 0};
int priorityArrayV[4] = {0, 0, 0, 0};
/*
    Here is where you should define the logic for the FCFS algorithm.
*/

PRIORITYScheduler::PRIORITYScheduler(int slice)
{
    if (slice != -1)
    {
        throw("Priority must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> PRIORITYScheduler::get_next_thread()
{
    std::shared_ptr<SchedulingDecision> decision(new SchedulingDecision());

    if (!priorityQueue.empty())
    {
        decision->thread = priorityQueue.top();
        priorityArrayV[decision->thread->priority] -= 1;
        decision->explanation = ("[S: " + std::to_string(priorityArrayU[0]) + " I: " + std::to_string(priorityArrayU[1]) + " N: " + std::to_string(priorityArrayU[2]) + " B: " + std::to_string(priorityArrayU[3]) + "] -> [S: " + std::to_string(priorityArrayV[0]) + " I: " + std::to_string(priorityArrayV[1]) + " N: " + std::to_string(priorityArrayV[2]) + " B: " + std::to_string(priorityArrayV[3]) + "]. Will run to completion of burst.");
        priorityQueue.pop();
        priorityArrayU[decision->thread->priority] -= 1;
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

void PRIORITYScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread)
{
    priorityQueue.push(thread->priority, thread);
    priorityArrayU[thread->priority] += 1;
    priorityArrayV[thread->priority] += 1;
    //presumably this is a queue, and get_next_thread pop's first from queue
    // TODO: implement me!
}

size_t PRIORITYScheduler::size() const
{
    //if size ==0 wtvs
    // TODO: implement me!
    return priorityQueue.size();
}
