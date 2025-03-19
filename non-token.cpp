#include <iostream>
#include <vector>
#include <ctime>
#include <thread>
#include <chrono>
#include <mutex>

class Ricart_Agrawala
{
private:
    std::vector<int> process;
    std::vector<bool> isInside;
    std::vector<int> timestamps;
    int start, num_of_process, max_itr;
    std::mutex mtx;

public:
    Ricart_Agrawala(int num_of_process, int max_itr)
    {
        for (int i = 0; i < num_of_process; i++)
        {
            this->process.push_back(i);
            this->isInside.push_back(false);
            this->timestamps.push_back(0);
        }
        std::srand(std::time(0));
        this->start = std::rand() % num_of_process;
        this->num_of_process = num_of_process;
        this->max_itr = max_itr;
    }

    void disp()
    {
        std::cout << "----------------------------------------------x-----------------------------------------------" << std::endl;
        std::cout << "Process: ";
        for (auto i : this->process)
            std::cout << i << " ";
        std::cout << std::endl;
        std::cout << "Is Inside: ";
        for (auto i : this->isInside)
            std::cout << i << " ";
        std::cout << std::endl;
        std::cout << "Start is: " << this->start << std::endl;
        std::cout << "----------------------------------------------x-----------------------------------------------" << std::endl;
    }

    void solve()
    {
        int iter = 1;
        std::cout << "----------------------------------------------x-----------------------------------------------" << std::endl;
        std::cout << "Iteration: " << iter << std::endl;
        std::cout << "The Process " << this->start + 1 << " wants to access the CS." << std::endl;

        // Simulate sending request to all other processes
        for (int i = 0; i < this->num_of_process; i++)
        {
            if (i != this->start && !this->isInside[i])
            {
                request(i);
            }
        }

        // Now process can enter the CS
        enterCS(this->start);
        iter++;
        this->max_itr--;

        while (this->max_itr)
        {
            std::cout << "----------------------------------------------x-----------------------------------------------" << std::endl;
            std::cout << "Iteration: " << iter << std::endl;
            this->start = generate_new_process();
            std::cout << "The Process " << this->start + 1 << " wants to access the CS." << std::endl;

            // Simulate sending request to all other processes
            for (int i = 0; i < this->num_of_process; i++)
            {
                if (i != this->start && !this->isInside[i])
                {
                    request(i);
                }
            }

            // Now process can enter the CS
            enterCS(this->start);
            iter++;
            this->max_itr--;
        }
    }

    void request(int process_id)
    {
        timestamps[start]++;
        std::cout << "The Process " << start + 1 << " requests the CS from Process " << process_id + 1<< std::endl;
        // Wait for the other process to reply
        waitForReply(process_id);
    }

    void waitForReply(int process_id)
    {
        std::cout << "The Process " << process_id + 1 << " has responded to the request from " << start + 1 << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate time delay for reply
    }

    void enterCS(int process_id)
    {
        std::cout << "Process " << process_id + 1 << " has entered the critical section." << std::endl;
        // Simulate the time spent in the critical section
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        // Exit the critical section
        std::cout << "Process " << process_id + 1 << " has exited the critical section." << std::endl;
    }

    int generate_new_process()
    {
        return (std::rand() % this->num_of_process);
    }
};

int main()
{
    int num_of_process, max_itr;
    std::cout << "Enter Number of Processes: ";
    std::cin >> num_of_process;
    std::cout << "Enter Number of Iterations: ";
    std::cin >> max_itr;

    // create object
    Ricart_Agrawala obj(num_of_process, max_itr);
    obj.disp();
    obj.solve();
    return 0;
}
