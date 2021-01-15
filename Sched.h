#ifndef Sched_H
#define Sched_H

#include "Task.h" // Contains Task, std::string
#include <vector> // For std::vector

// Creating enum that determines the type of execution for the scheduler.
enum class SchedType {
    EDF,
    RMS
};

std::string Sched(int totalTimeSteps, std::vector<Task>& tasksSched, SchedType sType);

Task* getSchedTask(int timeStep, std::vector<Task>& tasksSched, SchedType sType);

std::string getMissedTasks(int timeStep, std::vector<Task>& tasksSched);

#endif
