#include <future>
#include <deque>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <vector>


/* Bensafi Sarra 
 To compile : g++ -pthread mainPipe.cpp -o p.x
 To execute  : ./p.x 
 */


//Fonction qui transforme en miniscule
std::string miniscule(std::future<std::string>&& future_input){
 //std::future nous aide récupérer une valeur qui vous a été promise 
    const auto input = future_input.get();
    std::string s = input;
    std::transform(s.begin(), s.end(), s.begin(),
       [](unsigned char c){ return std::tolower(c); }
    );
    std::cout << "miniscule a fini...chaine en miniscule :    " << s <<std::endl;
    // je retourne un objet qui sera transformé
   // en un objet futur dans le main par std::async
    return s;}

//Fonction qui sépare les tokens
std::vector<std::string> Tokkenise(std::future<std::string>&& future_input){

    // la valeur std::future qui sera la sortie de la fonction précédente
    const auto input = future_input.get();
    std::string s = input;
    std::vector<std::string> v;
    std::string Tokken = "";

    for(int i=0;i<s.length();++i){
        if(s[i]==' '){
            v.push_back(Tokken);
            Tokken = "";
        }
        else{
            Tokken.push_back(s[i]);
        }
    }

    if(Tokken!=""){
        v.push_back(Tokken);
    }
    
    std::cout << "Tokkenise a fini...taille vecteur sortie    " << v.size() <<std::endl;
    return v;}

//Fonction qui supprime la ponctuation
std::vector<std::string> SuppPonct(std::future<std::vector<std::string>>&& future_input){
    
    const auto input = future_input.get();
    std::vector<std::string> v = input; 
    std::vector<std::string> vectorResult;

    for(int i=0;i<v.size();++i){
        std::string s= input[i];
        s.erase(remove_if(s.begin(), s.end(), ::ispunct), s.end()); 
        vectorResult.push_back(s); }


    std::cout << "SuppPonct a fini...taille vecteur sortie    " <<vectorResult.size() <<std::endl;
    return vectorResult;
}


//Foction qui remplace les nombres ex:  10 par dix
std::vector<std::string> Nombre(std::future<std::vector<std::string>>&& future_input){
    const auto input = future_input.get();
    std::vector<std::string> v = input;
    std::unordered_map<std::string, std::string> map;
    map["dix"]="10";
    map["neuf"]="9";
    map["huit"]="8";
    map["sept"]="7";
    map["six"]="6";
    map["cinq"]="5";
    map["quatre"]="4";
    map["trois"]="3";
    map["deux"]="2";
    map["un"]="1";

    for(auto& elm: map){
     for (int i = 0; i < v.size(); ++i)
	  {
	    if(elm.second.compare(v[i])==0){
	     
	    v[i]= elm.first;

	    }}}
	  
 std::cout<<"Nombre a fini...taille vecteur sortie    " << v.size() <<std::endl;

 return v;
}




//Afficher le résultat
void Afficher(std::future<std::vector<std::string>>&& future_input, const std::chrono::time_point<std::chrono::high_resolution_clock>& start_time){
    
    const auto input = future_input.get();
    std::string Res = ""; 
    std::vector<std::string> v = input; 
    for(int i=0;i<v.size();++i){
        std::string s= "<" + v[i] +">";
        Res += s; 
        s =""; }

    // Cela nous permet de  voir ce que nous avons obtenu  
    std::cout << "   sortie: '" << Res << "' termine à " <<
    std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time).count() << std::endl;
    // Afin d'avoir un affichage régulier on bloquele pipeline pendant quelque seconde.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}



int main()
{
    /* j'ai utiliser les futur et promise avec la fonction std:async.
       Elle exécute une fonction dans un nouveau thread crée automatiquement. 
       Et passe l'objet std:promise au thread et retourne un std:futur contenant le résultat.
    */

    //Le moment de commencer.
    const auto start_time = std::chrono::high_resolution_clock::now();
    size_t nbFoctions = 4;

	//Nous devons garder la trace des objets futurs pour les traitement qui suivent  
    //pour le traitement de notre chaine de caractère
    std::deque<std::future<void>> visualize_futures;

    
    // La phrase qui sera normalisé
    std::cout << " La phrase qui sera normalisé  => " <<"INPUT _String! Un texte est uNE série orale , écriTE, de mots! ?est 9 km , à écolE E 10."<< std::endl;
    auto input_str = std::string("INPUT _String! Un texte est uNE série orale , écriTE, de mots! ?est 9 km , à écolE E 10.") ;
    
    /*l'entrée sera considérer comme un objet futur qui sera promis à la fonction.
      la fonctions retourne une valeur qui à son tour sera 
      un nouvel objet futur puisque c'est la sortie de std::async.*/

    std::promise< std::string>  promise_0;
    promise_0.set_value( input_str);
    auto future_0 = promise_0.get_future();

    //Lancer la première étape du pipeline. 
    auto future_1 = std::async(std::launch::async, &miniscule, std::move(future_0));
    // lancer l'étapes prochaine après obtention du futur objet de chaque étape précédente
    auto future_2 = std::async(std::launch::async, &Tokkenise, std::move(future_1));
    auto future_3 = std::async(std::launch::async, &SuppPonct, std::move(future_2));
    auto future_4 = std::async(std::launch::async, &Nombre, std::move(future_3));

    //Afficher la chaine de caractères à sa sortie
    auto future_vis = std::async(std::launch::async, &Afficher, std::move(future_4),std::ref(start_time));
    visualize_futures.push_back(std::move(future_vis));

    return 0;
}
