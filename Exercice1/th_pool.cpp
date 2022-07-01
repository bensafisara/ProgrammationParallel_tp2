#include "th_pool.h"


th_pool::~th_pool() {}
th_pool::th_pool() : m(),cv(),function_queue(),etat_pool (true){ }


//Chaque thread doit s'exécuter dans la fonction avec
// une boucle , attendant que de nouvelles 
//tâches soient saisies et exécutées.
//Il s'agit d'un while (true) en attente de la file d'attente des tâches pour 
//qu'un thread prend une tache ou si le programme n'est pas terminer

void th_pool::start(){

	std::function<void()> tache;

    while (true)
    {
        
            std::unique_lock<std::mutex> lock(m);
            //si la file de tache n'est pas vide ou la terminaison du groupe est true
            cv.wait(lock, [this](){return !function_queue.empty() || !etat_pool;});
            
              if (!etat_pool && function_queue.empty()){
                //si la file des tache vide et le pool a terminé on sort de la méthode
                           return; }

            // on prend la tache qui est en premier de la queue
            tache = function_queue.front();
            //supprimer la tache du début de la file d'attente
            function_queue.pop();
        

        tache(); 
    }
}



void th_pool::fin()
{     
            std::unique_lock<std::mutex> lock(m);
             etat_pool= false;
            lock.unlock();
            cv.notify_all();
    }



//Il s'agit d'une fonction pour ajouter un travail à la file d'attente
//comme la queue est une section critique on utilise le mutex.
void th_pool::ajouter(std::function<void()> tache){

        std::unique_lock<std::mutex> lock(m);
        function_queue.push(tache);
        m.unlock(); 
        cv.notify_one(); 

}

