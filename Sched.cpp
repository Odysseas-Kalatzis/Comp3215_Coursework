#include "Sched.h" // Contains Task, std::string, std::to_string and std::vector
#include <cstddef> // For std::size_t
#include <limits> // For std::numeric_limits

std::string Sched(int totalTimeSteps, std::vector<Task>& tasksSched, SchedType sType)
{
    std::string output {};
    
    // Iterating through time timesteps.
    for (int timeStep { 0 }; timeStep < totalTimeSteps; ++timeStep) {
        // Get all deadline misses to output.
        output.append(getMissedTasks(timeStep, tasksSched));
        
        // Getting the task with the earliest deadline / period.
        Task *schedTask = getSchedTask(timeStep, tasksSched, sType);

        // We have task to execute.
        if (schedTask) {
            // Executing the task.
            schedTask->execute();
            // Writing to output that task was executed. 
            output.append(std::to_string(timeStep));
            output.append(" ");
            output.append(schedTask->getName());
            output.append(" Executes\n");

            // Checking to see if task is complete.
            if (schedTask->isComplete()) {
                // Updating deadline, cycle and compLeft.
                schedTask->update();

                // Writting to output that task was completed.
                output.append(std::to_string(timeStep));
                output.append(" ");
                output.append(schedTask->getName());
                output.append(" Completed\n");
            }

            // Setting schedTask to nullptr.
            schedTask = nullptr;
        }
        /* schedTask is assigned to nullptr, means no task will execute.
         * This can happen because all tasks have completed and their
         * cycles is greater than the current time step.
         */
        else {
            output.append(std::to_string(timeStep));
            output.append(" No Tasks Executed\n");
        }
    }

    return output;
}

// Used to get a pointer to the task with smallest deadline / period.
Task* getSchedTask(int timeStep, std::vector<Task>& tasksSched, SchedType sType)
{
    // Return a pointer of the task with the earliest deadline / cycle.
    Task *schedTask = nullptr;
    int smallestSched { std::numeric_limits<int>::max() };

    for (Task& task : tasksSched) {
        // Make sure task is ready to be executed.
        if (timeStep >= task.getCycle()) {
            // EDF Scheduling.
            if (sType == SchedType::EDF) {
                // Check to see if task has earlier deadline than current min.
                if (smallestSched > task.getDeadline()) {
                    schedTask = &task;
                    smallestSched = task.getDeadline();
                }
            }
            // RMS Scheduling.
            else {
                // Check to see if task has earlier period than current min.
                if (smallestSched > task.getPeriod()) {
                    schedTask = &task;
                    smallestSched = task.getPeriod();
                }
            }

        }
    }

    return schedTask;
}

// Returns a string of all tasks that missed a deadline.
std::string getMissedTasks(int timeStep, std::vector<Task>& tasksSched)
{
    std::string outputMisses {};

    for (Task& task : tasksSched) {
        // Checking to see if task missed the deadline.
        if (timeStep >= task.getDeadline()) {
            outputMisses.append(std::to_string(timeStep));
            outputMisses.append(" ");
            outputMisses.append(task.getName());
            outputMisses.append(" Misses\n");
        }
    }

    return outputMisses;
}
