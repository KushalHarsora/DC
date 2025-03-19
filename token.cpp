#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

class RaymondTreeToken
{
private:
    struct Process
    {
        int id;
        int parent;
        std::vector<int> children;
        bool hasToken;
        bool isInCS;

        Process(int id) : id(id), parent(-1), hasToken(false), isInCS(false) {}
    };

    std::vector<Process> processes;
    int root;
    int numOfProcesses;
    int maxItr;

public:
    RaymondTreeToken(int numOfProcesses, int maxItr)
    {
        this->numOfProcesses = numOfProcesses;
        this->maxItr = maxItr;

        // Initialize processes
        for (int i = 0; i < numOfProcesses; i++)
        {
            processes.push_back(Process(i));
        }

        // Randomly construct a tree
        constructTree();
    }

    void constructTree()
    {
        // Randomly assign parent-child relationships to simulate a tree structure.
        // For simplicity, we'll make process 0 the root.
        root = 0;
        processes[root].hasToken = true;

        // Randomly assign children (for simplicity, we assume each process can have a random number of children).
        // You could adjust the tree structure or input your own tree.

        // Example tree setup:
        processes[0].children.push_back(1);
        processes[1].parent = 0;
        processes[0].children.push_back(2);
        processes[2].parent = 0;
        processes[1].children.push_back(3);
        processes[3].parent = 1;

        // You can add more specific tree setup or randomize further based on your needs.
    }

    void disp()
    {
        std::cout << "-----------------------------------" << std::endl;
        std::cout << "Processes: ";
        for (auto &process : processes)
        {
            std::cout << process.id << " ";
        }
        std::cout << std::endl;

        std::cout << "Token holders: ";
        for (auto &process : processes)
        {
            if (process.hasToken)
                std::cout << process.id << " ";
        }
        std::cout << std::endl;
        std::cout << "-----------------------------------" << std::endl;
    }

    void solve()
    {
        while (maxItr--)
        {
            for (int i = 0; i < numOfProcesses; i++)
            {
                if (!processes[i].isInCS && processes[i].hasToken)
                {
                    enterCS(i); // If the process has the token, it enters CS
                }
            }
        }
    }

    void enterCS(int processId)
    {
        // Simulate entering the critical section
        std::cout << "Process " << processId << " is entering the critical section." << std::endl;
        processes[processId].isInCS = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate CS work

        std::cout << "Process " << processId << " has finished the critical section." << std::endl;

        // Exit critical section and pass the token to a child
        processes[processId].isInCS = false;
        passToken(processId);
    }

    void passToken(int processId)
    {
        // Pass the token to one of its children or back to the parent if no children.
        if (!processes[processId].children.empty())
        {
            int nextProcess = processes[processId].children[0]; // Pass to the first child
            processes[nextProcess].hasToken = true;
            std::cout << "Process " << processId << " passes the token to Process " << nextProcess << "." << std::endl;
        }
        else if (processes[processId].parent != -1)
        {
            int parentProcess = processes[processId].parent;
            processes[parentProcess].hasToken = true;
            std::cout << "Process " << processId << " passes the token to its parent Process " << parentProcess << "." << std::endl;
        }

        // Set the current process's token to false
        processes[processId].hasToken = false;
    }
};

int main()
{
    int num_of_process, max_iter;
    std::cout << "Enter the number of processes: ";
    std::cin >> num_of_process;
    std::cout << "Enter the number of iterations: ";
    std::cin >> max_iter;

    // start solving
    RaymondTreeToken obj(num_of_process, max_iter);
    obj.disp();
    obj.solve();
    return 0;
}