#include <iostream>
#include <thread>
#include <future>
#include <list>
#include <string>
#include <cmath>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>
using namespace std::chrono;
using namespace std;
#include "md5.h"
#include "md5.cpp" // http://www.zedwood.com/article/cpp-md5-function
/*
- Bensafi Sarra
-Pour compiler : g++ -pthread ForceBrute_.cpp -o try.x 
-Pour Executer : time ./try.x
*/

//hach_Word est un mot de 5 lettres chiffré en md5.
std::string hach_Word = "3ed7dceaf266cafef032b9d5db224717";

void func1(){
    for(char a='a'; a <='f' ; ++a)
    {
       for(char b='a'; b <= 'z' ; ++b)
        {
            for(char c='a'; c <= 'z'; ++c)
            {   
                for(char d='a'; d <= 'z' ; ++d)
                {
                    for(char e='a'; e <= 'z' ; ++e)
                    {
                        
                        std::string  s1 = "";
                        s1 += a;
                        s1 += b; 
                        s1 += c; 
                        s1 += d; 
                        s1 += e; 
                        // appeler la fonction d'hachage ici 
                        // comparer le résultat haché avec la phrase initale (crypté)
                        if (md5(s1)==hach_Word){
                             cout << s1 << " s1 le mot décrypté " << endl;
                            
                        }
                    }
                }
            }
        }
    }
    
}


void func2(){
    for(char a='g'; a <= 'l' ; ++a)
    {
        for(char b='a'; b <= 'z' ; ++b)
        {
            for(char c='a'; c <= 'z'; ++c)
            {   
                for(char d='a'; d <= 'z' ; ++d)
                {
                    for(char e='a'; e <= 'z' ; ++e)
                    {
                        
                        std::string s2 = "";
                        s2 += a;
                        s2 += b; 
                        s2 += c; 
                        s2 += d; 
                        s2 += e; 
                        // appeler la fonction d'hachage ici 
                        // comparer le résultat haché avec la phrase initale (crypté)
                        if (md5(s2)==hach_Word){
                            cout << s2 << " le mot décrypté " << endl;
                            

                        }
                    }
                }
            }
        }
    }
 
}


void func3(){
    for(char a='m'; a <= 'r' ; ++a)
    {
        for(char b='a'; b <= 'z' ; ++b)
        {
            for(char c='a'; c <= 'z'; ++c)
            {   
                for(char d='a'; d <= 'z' ; ++d)
                {
                    for(char e='a'; e <= 'z' ; ++e)
                    {
                        
                        std::string s3 = "";
                        s3 += a;
                        s3 += b; 
                        s3 += c; 
                        s3 += d; 
                        s3 += e; 
                        // appeler la fonction d'hachage ici 
                        // comparer le résultat haché avec la phrase initale (crypté)
                        if (md5(s3)==hach_Word){
                            cout << s3 << " le mot décrypté " << endl;
                            

                        }
                    }
                }
            }
        }
    }

}

void func4(){
    for(char a='s'; a <= 'z' ; ++a)
    {
        for(char b='a'; b <= 'z' ; ++b)
        {
            for(char c='a'; c <= 'z'; ++c)
            {   
                for(char d='a'; d <= 'z' ; ++d)
                {
                    for(char e='a'; e <= 'z' ; ++e)
                    {
                        
                        std::string s4 = "";
                        s4 += a;
                        s4 += b; 
                        s4 += c; 
                        s4 += d; 
                        s4 += e; 
                        // appeler la fonction d'hachage ici 
                        // comparer le résultat haché avec la phrase initale (crypté)
                        if (md5(s4)==hach_Word){
                            cout << s4 << " le mot décrypté " << endl;
                            

                        }
                    }
                }
            }
        }
    }

}

/**main**/
int main(){
/*

le temps d'exécution en utilisant différent nombre de threads en parallèle est le suivant : 
_________________________________________________________
|   4 Threads  |   3 Threadsd  |  2 Threads  | 1 Threads |
----------------------------------------------------------
|   10951842   |   15426653    |  15435729   | 24510432  |
_________________________________________________________


*/



auto start1 = high_resolution_clock::now();
//les deux thread vont effectuer les combinaison en parallèle
std::thread t1(func1);
std::thread t2(func2);
std::thread t3(func3);
std::thread t4(func4);

t1.join();
t2.join();
t3.join();
t4.join();
auto stop1 = high_resolution_clock::now();
auto duration1 = duration_cast<microseconds>(stop1-start1);
std::cout<<"Temps Fonctions 1: " <<duration1.count()<<std::endl;  
return 0;


}