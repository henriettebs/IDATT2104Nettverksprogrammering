#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

class Workers {
private:
    vector<thread> threads;
    list<function<void ()>> tasks;
    mutex tasks_mutex;
    condition_variable tasks_cv;
    int thread_count;
    bool join_called;


public:
     Workers(int threads) {
        thread_count = threads;
        join_called = true;
    }

     /**
      * Creates internal threads and run them
      */
    void start(){
        if(!join_called){
            /** Worker class has already started. Ignore duplicate call. */
            return;
        }
        /** Make threads wait if task list is empty */
        join_called = false;

        for(int i = 0; i < thread_count; i++){
            threads.emplace_back([i, this] {
                while(true){
                    function<void()> task;
                    {
                        /** The mutex gets locked automatically. */
                        unique_lock<mutex> lock(tasks_mutex);

                        /** Waits in loop for tasks to come in, and then release lock. */
                        while(tasks.empty()){
                            cout << "Thread " << to_string(i) << ": No tasks to work on. \n";
                            if(join_called) return;
                            cout << "Thread " << to_string(i) << ": Going to sleep. \n";
                            tasks_cv.wait(lock);
                            cout << "Thread " << to_string(i) << ": Got woken up. \n";
                        }

                        /** Pop the first task and then release the lock */
                        task = *tasks.begin();
                        tasks.pop_front();

                        /** When we exit the function task, the unique_lock is destroyed and mutex gets released. */
                    }
                    if(task) {
                        /** Run the task, if we ever retrieved one. */
                        cout << "Thread " << to_string(i) << ": Running task. \n";
                        task();
                    }
                }
            });
        }
    }


    /**
     * Adds a function to run.
     */
    void post(const function<void()>& f){
        unique_lock<mutex> lock(tasks_mutex);
        tasks.emplace_back(f);

        /** Notifies a worker thread that there are new tasks available */
        tasks_cv.notify_one();
    }

     /**
      * Adds a function to run after given amount of time
      */
    void post_timeout(const function<void()>& f, long timeout_ms){
        post([&f, timeout_ms] {
            this_thread::sleep_for(chrono::milliseconds(timeout_ms));
            f();
        });
    }

    /**
     * Stop-method to join internal threads that were created
     */
    void stop(){

         tasks_cv.notify_all();
         for(auto &thread: threads) thread.join();
     }
};


int main() {
    Workers worker_threads(4);
    Workers event_loop(1);

    worker_threads.start();
    event_loop.start();

    worker_threads.post([] {
        cout << "Function 1 running. \n";
    });
    worker_threads.post([] {
        cout << "Function 2 running. \n";
    });
    worker_threads.post([] {
        cout << "Function 3 running. \n";
    });
    worker_threads.post_timeout([] {
        cout << "Function 4 running. \n";
    }, 3000);

    cout << "Calling stop(): \n";
    worker_threads.stop();
    event_loop.stop();

    return 0;
}
