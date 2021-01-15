import sys
import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator


def main():
    # The matplotlib plot.
    fig, ax = plt.subplots()
    # Open the file passed in the argument.
    openFile = open(sys.argv[1], "r")

    # Iterate through file lines.
    for line in openFile:
        values = line.split()

        # The current time step.
        timeStep = int(values[0])
        # The name of the task.
        taskName = values[1]
        # The type of log (Executes, Completed, Misses).
        execType = values[2]

        if (execType == "Completed"):
            # Plot completed plot.
            ax.barh(taskName, width=0.15, height=0.025,left=timeStep+1, color='black')
            ax.barh(taskName, width=-0.15, height=0.025,left=timeStep+1, color='black')
        elif (execType == "Misses"):
            # Plot misses plot.
            ax.barh(taskName, width=1, height=0.05,left=timeStep, edgecolor='black', color='r')
        elif (execType == "Executes"):
            # Plot execution plot.
            ax.barh(taskName, width=1, height=0.1,left=timeStep, alpha = 0.4, edgecolor='black', color='b')

    # Set grid in the x direction every 1 x interval.
    #ax.xaxis.set_major_locator(MultipleLocator(1))
    ax.set_axisbelow(False)
    fig.set_size_inches(18.5, 3.5, forward=True)
    plt.grid(color='black')
    plt.show()


if __name__ == "__main__":
    main()

