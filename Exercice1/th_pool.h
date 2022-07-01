#include <queue>
#include <functional>
#include <mutex>
#pragma once
#include <condition_variable>
#include <atomic>
#include <cassert>

class th_pool
{


public:
 //je définit les constructeurs, les méthodes et variables
    th_pool();
    ~th_pool(); 
     
    void ajouter(std::function<void()> tache);
    void start();
    void fin();
   
private:
	std::mutex m;
	std::atomic<bool> etat_pool;
    std::queue<std::function<void()>> function_queue;
    std::condition_variable cv ;
 


};