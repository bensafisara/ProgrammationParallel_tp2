#include "th_pool.h"
#include "th_pool.cpp"
#include <string>
#include <iostream>
#include <mutex>
#include <cmath>
#include <functional>
#include <thread>
#include <vector>
//Déclaration
th_pool pool;
int p=0;
float somme=0;
std::mutex mtx_Approxi;
std::mutex m1;

/*
- Bensafi Sarra
-Pour compiler : g++ -pthread main_Thpool.cpp -o thP.x
-Pour Executer : ./thP.x
*/

//Fonction Utile pour l'approximation pow et Facto
float Pow(int x, unsigned int y)
{
    if (y == 0)
        return 1;
    else if (y % 2 == 0)
        return Pow(x, y / 2) * Pow(x, y / 2);
    else
        return x * Pow(x, y / 2) * Pow(x, y / 2);
}

float Facto(int n)
{
    if (n == 0)
        return 1;
    return n * Facto(n - 1);
}



//main et appelle des fonctions
int main()
{
    std::cout << "Debut" << std::endl;
    int numThreads = std::thread::hardware_concurrency();
    std::cout << "num threads = " << numThreads << std::endl;
    std::vector<std::thread> threadpool;
    for (int i = 0; i < numThreads; i++){
        threadpool.push_back(std::thread(&th_pool::start, &pool));  
    }

    for (p = 0; p < 6 ; ++p){

        m1.lock();
        pool.ajouter([&](){somme = somme + (Pow(-1,p)/Facto(p));}); 
        m1.unlock();

        //attendre que toutes les taches soient achevées.
         std::this_thread::sleep_for (std::chrono::seconds(1));}

    pool.fin();

    for (int i = 0; i < threadpool.size(); i++){
           threadpool.at(i).join();
        }

    //Approximation   
    std::cout << "Approximation =  " << somme<< std::endl; 
   
}