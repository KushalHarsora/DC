#include <bits/stdc++.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024
#define SLEEP_TIME 10

class IPC {

    private:
        key_t key;

    public:
        IPC()
        {
            // generate a unique for shared memory
            this->key = ftok("shmfile", 65);

            // create a shared memory segment
            int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
            if (shmid == -1) 
            {
                std::cerr << "Shared Memory creation Failed!!" << std::endl;
                return;
            }

            // attach the shared memory to process's address space
            int* data = (int*) shmat(shmid, nullptr, 0);
            if (data == (int*) -1)
            {
                std::cerr << "Failed to attach the shared memory" << std::endl;
                return;
            }

            std::cout << "Writing data in shared memory..." << std::endl;
            int num = 10;
            *data = num;

            if (data)
                std::cout << "Data written to shared memory: " << *data << std::endl;
            else
                std::cout << "Data written failed!!" << std::endl;
            
            // allow the reader process to execute
            this->reader();
            
            // log the shared data
            std::cout << "The data received is: " << *data << std::endl;

            // timer
            std::cout << "The Data will be removed from shared memory in: " << std::endl;
            int i = SLEEP_TIME;
            while(i > 0)
            {
                std::cout << i << "s" << std::endl;
                sleep(1);
                i--;
            }

            // remove the data from shared memory
            shmdt(data);
            std::cout << "Data removed from shared memory" << std::endl;
        }

        void reader()
        {
            // generate a unique for shared memory
            this->key = ftok("shmfile", 65);

            // create a shared memory segment
            int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
            if (shmid == -1) 
            {
                std::cerr << "Shared Memory creation Failed!!" << std::endl;
                return;
            }

            // attach the shared memory to process's address space
            int* data = (int*) shmat(shmid, nullptr, 0);
            if (data == (int*) -1)
            {
                std::cerr << "Failed to attach the shared memory" << std::endl;
                return;
            }

            std::cout << "Reading data from shared memory..." << std::endl;
            std::cout << "The Data is " << *data << std::endl;

            *data += 10;

            std::cout << "Updated Data is: " << *data << std::endl;           
            return;
        }

};

int main()
{
    IPC object;
    return 0;
}