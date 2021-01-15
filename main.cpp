#include "Task.h" // Contains Task, std::string and std::get_line
#include "Sched.h" // For sched, enum SchedType (EDF, RMS).
#include <fstream> // For std::ifstream and std::ofstream
#include <iostream> // For std::cin and std::cout
#include <vector> // For std::vector
#include <cstddef> // For std::size_t
#include <numeric> // For std::lcm

int main(int argc, char *argv[])
{
    // Vector containing all of our tasks for EDF.
    std::vector<Task> tasksEDF {};
    // Vector containing all of our tasks for RMS.
    std::vector<Task> tasksRMS {};

    // String containing the name of the file.
    std::string fileName {};

    while (argc == 1) {
        std::cout << "Filename of .txt format required to load tasks." << '\n';

        // Get the file name.
        std::getline(std::cin, fileName);
    }
    
    // More than 1 argument passed to main, get file name.
    if (argc > 1) {
        fileName = argv[1];
    }

    // Read the .txt file.
    std::ifstream readFile(fileName);
    
    // line to get contents of line, lineNum to get line number.
    std::string line {};
    int lineNum {0};
    // Getting line by line the contents of the file.
    while (std::getline (readFile, line)) {
        // Update lineNum.
        ++lineNum;

        // Get the number of tasks to create vector of right size.
        if (lineNum > 1){
            // Getting the task name.
            std::size_t firstWord = line.find_first_of(" ");
            std::string taskName = line.substr(0, firstWord);
            
            // Updating line to contain everything but the first word.
            line = line.substr(line.find(" ") + 1);
            // Getting the next word which is the compTime, assigning it to int.
            firstWord = line.find_first_of(" ");
            std::string word = line.substr(0, firstWord);
            int compTime = std::stoi(word);

            // Updating line to contain everything but the first word.                   
            line = line.substr(line.find(" ") + 1);                                      
            // Getting the next word which is the period, assigning it to int.         
            firstWord = line.find_first_of(" ");                                         
            word = line.substr(0, firstWord);                                
            int period = std::stoi(word);

            // Creating the task and adding it to the vector tasks for EDS and RMS.
            Task task {compTime, period, taskName};
            tasksEDF.push_back(task);
            tasksRMS.push_back(task);
        }
    }
    // Close the file
    readFile.close();

    // Find lowest common multiple amongst the periods of tasks.
    int totalTimeSteps {1};
    // Makes no difference to use tasksRMS instead of tasksEDF.
    for (Task& task : tasksEDF) {
        totalTimeSteps = std::lcm(totalTimeSteps, task.getPeriod());
    }
    
    // Get filename to write results.
    std::size_t fileFirstWord = fileName.find_first_of(".");

    // EDF file name.
    std::string edfResults = fileName.substr(0, fileFirstWord);
    edfResults.append("EDF.txt");
    // Create a text file to write results.
    std::ofstream edfWriteFile(edfResults);
    // Write to the file.
    edfWriteFile << Sched(totalTimeSteps, tasksEDF, SchedType::EDF);
    // Close the file.
    edfWriteFile.close();
    
    // RMS file name.
    std::string rmsResults = fileName.substr(0, fileFirstWord);
    rmsResults.append("RMS.txt");
    // Create a text file to write results.
    std::ofstream rmsWriteFile(rmsResults);
    // Write to the file.
    rmsWriteFile << Sched(totalTimeSteps, tasksRMS, SchedType::RMS);
    // Close the file.
    rmsWriteFile.close();
    
}
