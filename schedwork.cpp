#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool backtrack(size_t day, size_t slot, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, std::vector<size_t>& shiftsUsed);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    size_t numDays = avail.size(); //number of days
    size_t numWorkers = avail[0].size(); //number of possible workers

    //set sched row = days, col = workers
    sched.assign(numDays, std::vector<Worker_T>());

    //track shifts used on each worker
    std::vector<size_t> shiftsUsed(numWorkers, 0);

    bool helper = backtrack(0, 0, avail, dailyNeed, maxShifts, sched, shiftsUsed);

    return helper;
}

bool backtrack(
    size_t day, 
    size_t slot, 
    const AvailabilityMatrix& avail, 
    const size_t dailyNeed, 
    const size_t maxShifts, 
    DailySchedule& sched, 
    std::vector<size_t>& shiftsUsed)
{
    size_t numDays = avail.size();
    size_t numWorkers = avail[0].size(); 

    if(day == numDays){
        //we have checked all days 
        return true;
    }

    if(slot == dailyNeed){
        //that days slots are filled up
        return backtrack(day + 1, 0, avail, dailyNeed, maxShifts, sched, shiftsUsed); //move to next day 
    }

    //loop from 0 to numWorkers - 1 X
    //check avail[day][w] if true X
    //check shiftsUsed[w] < maxShifts X
    //make sure w is not in sched[day], use std::find X
    //if good put w into sched[day], push_back(w)
    //increment shiftsUsed[w]
    //then need to recurse day, slot + 1 <-- track slots taken
    //if it returns true then we return true / found solution 
    //

    for(size_t w = 0; w < numWorkers; ++w){
        if(avail[day][w] == true){
            if(shiftsUsed[w] < maxShifts){
                if(std::find(sched[day].begin(), sched[day].end(), w) != sched[day].end()){
                    //w was scheduled this day -> skip
                    continue;
                }
                    sched[day].push_back(w);
                    shiftsUsed[w]++;

                    if(backtrack(day, slot + 1, avail, dailyNeed, maxShifts, sched, shiftsUsed)){ //track slots
                        return true; 
                    }else{
                        shiftsUsed[w]--;
                        sched[day].pop_back();
                    }
            }
        }
    }

    return false;
}
