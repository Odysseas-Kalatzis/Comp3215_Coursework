#include "Task.h" // Contains Task, std::string.

// Constructor for task.
Task::Task(int compTime, int period, std::string taskName)
{
    m_compTime = compTime;
    m_compLeft = compTime;
    m_period   = period;
    m_deadline = period;
    // Cycle is initially set to 0 as all tasks can be run at time step 0.
    m_cycle    = 0;
    m_taskName = taskName;
}

// This is run when the task is complete. 
// It resets the deadline, cycle and m_compLeft.
void Task::update()
{
    m_deadline += m_period;
    m_cycle += m_period;
    m_compLeft = m_compTime;
}

// This is run when the task is executed.
// It decreases the computations left by 1.
// When m_compLeft reaches 0, task is complete.
void Task::execute()
{
    --m_compLeft;
}
