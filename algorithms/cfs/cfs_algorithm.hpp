#ifndef CFS_ALGORITHM_HPP
#define CFS_ALGORITHM_HPP

#include <memory>
#include "algorithms/scheduling_algorithm.hpp"

/*
    FCFSScheduler:
        A representation of a scheduling queue that uses first-come, first-served logic.
        
        This is a derived class from the base scheduling algorithm class.

        You are free to add any member functions or member variables that you
        feel are helpful for implementing the algorithm.
*/

class CFSScheduler : public Scheduler
{
public:
    //==================================================
    //  Member variables
    //==================================================

    // TODO: Add any member variables you may need.
    int minGran;
    double weightTotal;
    //double weight[4]; // = {88761, 29541, 1024, 15};
    //==================================================
    //  Member functions
    //==================================================

    CFSScheduler(int slice = 3);

    std::shared_ptr<SchedulingDecision> get_next_thread();

    void add_to_ready_queue(std::shared_ptr<Thread> thread);

    size_t size() const;
};

#endif
