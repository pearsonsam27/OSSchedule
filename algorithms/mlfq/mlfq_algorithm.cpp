#include "algorithms/mlfq/mlfq_algorithm.hpp"
#include "utilities/stable_priority_queue/stable_priority_queue.hpp"
#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

Stable_Priority_Queue<std::shared_ptr<Thread>> priorityQueueArray[10];
/*
    Here is where you should define the logic for the FCFS algorithm.
*/

MLFQScheduler::MLFQScheduler(int slice)
{
    if (slice <= 0)
    {
        throw("MLFQ must have a timeslice > 0");
    }
    this->time_slice = slice;
}

std::shared_ptr<SchedulingDecision> MLFQScheduler::get_next_thread()
{
    std::shared_ptr<SchedulingDecision> decision(new SchedulingDecision());

    for (int i = 0; i < 10; i++)
    {
        if (!priorityQueueArray[i].empty())
        {
            decision->thread = priorityQueueArray[i].top();
            std::string prior = "";
            if (decision->thread->priority == 0)
            {
                prior.append("SYSTEM");
            }
            else if (decision->thread->priority == 1)
            {
                prior.append("INTERACTIVE");
            }
            else if (decision->thread->priority == 2)
            {
                prior.append("NORMAL");
            }
            else if (decision->thread->priority == 3)
            {
                prior.append("BATCH");
            }

            decision->explanation = ("Selected from queue " + std::to_string(i) + " (priority = " + prior + ", runtime = " + std::to_string(decision->thread->previousRun) + "). Will run for at most " + std::to_string(int(pow(2, i))) + " ticks.");
            priorityQueueArray[i]
                .pop();

            this->time_slice = int(pow(2, i));
            break;
        }
        if (i == 9)
        {
            decision->explanation = "No threads available for scheduling.";
        }
    }
    return decision;
}

//SchedulingDecision->explanation = "No threads available for scheduling.";
//choose how to get next thread --> look at get_next_thread
//ADD EXPLANATION
// TODO: implement me!

void MLFQScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread)
{

    int intervals[10] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
    for (int i = thread->prevQueue; i < 10; i++)
    {
        thread->previousRun += thread->service_time - thread->prevRun;
        thread->prevRun = thread->service_time;
        if (thread->previousRun >= intervals[i] && i != 9)
        {
            thread->previousRun = 0;
            thread->prevQueue = i + 1;
            priorityQueueArray[i + 1].push(thread->priority, thread);
            break;
        }
        else if (thread->previousRun < intervals[i])
        {
            thread->prevQueue = i;
            priorityQueueArray[i].push(thread->priority, thread);
            break;
        }
        else if (i == 9)
        {
            thread->prevQueue = 9;
            priorityQueueArray[9].push(thread->priority, thread);
            break;
        }
    }

    //presumably this is a queue, and get_next_thread pop's first from queue
    // TODO: implement me!
}

size_t MLFQScheduler::size() const
{
    //if size ==0 wtvs
    // TODO: implement me!
    return priorityQueueArray[0].size();
}