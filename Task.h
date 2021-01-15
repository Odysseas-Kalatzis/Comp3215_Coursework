#ifndef TASK_H
#define TASK_H

#include <string> // std::string

// Represents the class of a task.
class Task
{

private:
    // Time it takes for the task to compute.
    int m_compTime {};
    // How much computation we have left.
    int m_compLeft {};
    // The intervals of which the deadline and period update.
    int m_period {};
    // When the deadline for completing the computation is.
    int m_deadline {};
    // When we can begin running the computation.
    int m_cycle{};
    std::string m_taskName{};

public: 
    Task(int compTime, int period, std::string taskName);

    int getDeadline() { return m_deadline; }

    int getCycle() { return m_cycle; }
    
    int getPeriod() { return m_period; }
    
    // Updates deadline, cycle and m_compLeft.
    void update();

    // Executes the task, causes m_compLeft to decrease by 1.
    void execute();
    
    // Returns true if task is complete, false otherwise.
    bool isComplete() { return !(m_compLeft); }

    bool missDeadline(int timeStep) { return timeStep > m_deadline; }

    std::string getName() { return m_taskName; }
};

#endif
