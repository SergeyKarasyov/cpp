#include <iostream> 
#include <chrono> 
#include <thread> 
        using namespace std::literals::chrono_literals;

        typedef std::chrono::time_point<std::chrono::high_resolution_clock> timepoint; 
int main() { 
         std::cout << "Starting sleep.\n"; 

         timepoint start = std::chrono::high_resolution_clock::now(); 

         std::this_thread::sleep_for(2s); 

         timepoint end = std::chrono::high_resolution_clock::now(); 
         std::chrono::duration<double, std::milli> elapsed = end - 
         start; 
         std::cout << "Slept for: " << elapsed.count() << " ms\n"; 
} 