#include <iostream>
#include <thread>
#include <mutex>
#include <cmath>

// Create mutex to protect the shared data
std::mutex mtx;

class Thread {
    private:
        int a, b;

    public:
        Thread(int x, int y) : a(x), b(y) {}

        void add(int &result) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::lock_guard<std::mutex> lock(mtx);
            result = a + b;
        }

        void subtract(int &result) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::lock_guard<std::mutex> lock(mtx);
            result = a - b;
        }

        void multiply(int &result) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::lock_guard<std::mutex> lock(mtx);
            result = a * b;
        }

        void divide(double &result) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::lock_guard<std::mutex> lock(mtx);
            if (b != 0) {
                result = static_cast<double>(a) / b;
            } else {
                std::cout << "Division by zero" << std::endl;
                result = 0.0;
            }
        }

        void log(double &result) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::lock_guard<std::mutex> lock(mtx);
            if (a > 0 && b > 0) {
                result = std::log(a) / std::log(b);
            } else {
                std::cout << "Numbers must be positive" << std::endl;
                result = 0.0;
            }
        }

        void gcd(int &result) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::lock_guard<std::mutex> lock(mtx);
            int x = a, y = b;
            while (y != 0) {
                int temp = y;
                y = x % y;
                x = temp;
            }
            result = x;
        }
};

int main() {
    int m, n;
    std::cout << "Enter first number: ";
    std::cin >> m;
    std::cout << "Enter second number: ";
    std::cin >> n;

    Thread obj(m, n);
    int add_res, sub_res, mul_res, gcd_res;
    double div_res, log_res;

    // Create threads for each operation
    std::thread t1(&Thread::add, &obj, std::ref(add_res));
    std::thread t2(&Thread::subtract, &obj, std::ref(sub_res));
    std::thread t3(&Thread::multiply, &obj, std::ref(mul_res));
    std::thread t4(&Thread::divide, &obj, std::ref(div_res));
    std::thread t5(&Thread::log, &obj, std::ref(log_res));
    std::thread t6(&Thread::gcd, &obj, std::ref(gcd_res));

    // Wait for all threads to finish
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();

    // Output results
    std::cout << "\nThe Output is: \n";
    std::cout << "Addition: " << add_res << std::endl;
    std::cout << "Subtraction: " << sub_res << std::endl;
    std::cout << "Multiplication: " << mul_res << std::endl;
    std::cout << "Division: " << div_res << std::endl;
    std::cout << "Logarithm of " << m << " base " << n << " is: " << log_res << std::endl;
    std::cout << "GCD of " << m << " and " << n << ": " << gcd_res << std::endl;

    return 0;
}