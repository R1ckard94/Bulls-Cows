//
//  functionHeader.cpp
//  BullsNCows
//
//  Created by Rickard Karlsson

#include "functionHeader.h"


BullCow bullsCows(std::string& g, BullCow& g1){     //funktion som tar in en sträng(ny gisssning) och en bullcow struct
    BullCow tmpStruct;      //skapar en temporär struct som sedan kommer att returneras av funktionen
    int B = 0;
    int C = 0;
    std::string tmp = std::to_string(g1.value);     //sätter värdet ifrån refererade structen till en temporär string så att den kan jämföras i koden
    
    if(g==tmp){     //kollar ifall värdet ifrån refererade structen och strängen är detsamma och tilldelar då samma värden
        
        B = g1.B;       
        C = g1.C;
        tmpStruct.B = B;
        tmpStruct.C = C;        
    }
    
    int i = 0;
    if(g.at(i)==tmp.at(i+1) || g.at(i)==tmp.at(i+2) || g.at(i)==tmp.at(i+3))  { C++; }      
    else if(g.at(i)==tmp.at(i))   { B++; }
    if(g.at(i+1)==tmp.at(i+2) || g.at(i+1)==tmp.at(i+3) || g.at(i+1)==tmp.at(i))  { C++; }
    else if(g.at(i+1)==tmp.at(i+1))   { B++; }
    if(g.at(i+2)==tmp.at(i) || g.at(i+2)==tmp.at(i+1) || g.at(i+2)==tmp.at(i+3))  { C++; }
    else if(g.at(i+2)==tmp.at(i+2))   { B++; }
    if(g.at(i+3)==tmp.at(i) || g.at(i+3)==tmp.at(i+1) || g.at(i+3)==tmp.at(i+2))  { C++; }
    else if(g.at(i+3)==tmp.at(i+3))   { B++; }                                                                
                                                        //funktion som returnerar antal bulls och cows beroende på hur lika gissningen är tidigare gissningar
    tmpStruct.B = B;        //tilldelar den temporära structens bullsvärdet B
    tmpStruct.C = C;        //tilldelar den temporära structens cowssvärdet c
    return tmpStruct;       //returnerar structen 
}


bool validGuess(std::string& g, std::vector<BullCow>& G){       //bool funktion som returnerar sant eller falskt beroende på tidigare gissningar
    for(int i = 0; i!=G.size(); i++){               //loopar igenom den refererade vectorn
        if(bullsCows(g, G[i]).B != G[i].B || bullsCows(g, G[i]).C != G[i].C ){ //kallar funktionen ovan för att avgöra om gissningen bulls-/cows-värde inte är detsamma som tidigare gissningar i syfte om att skapa relevanta gissningar
            return false;   //om det inte stämmer så returnerar funktionen false 
        }else{      
            continue;   //fortsätter vidare i loopen tills vectorn är slut
        }
    }
    return true;    //är svaret "ok" så returneras true
}


std::string generateGuess(std::vector<BullCow>& Guesses){   //funktion som skapar gissningar utifrån en vector med tidigare gissningar och svar
    std::string newGuess;
    if(Guesses.empty()){        //är det första försöket där vectorn är tom så skapas denna standard gissning 
        newGuess = "1023";      //detta är det lägsta numret som ska kunna genereras utan att få upprepade siffror
    }else{
        int value = Guesses[Guesses.size()-1].value;    //eftersom att storleken är 1 mer än positionerna i vectorn så skapas en ny gissning utifrån den senaste gissningen 
        value++;    //värdet ökas till nästa tal
        newGuess = std::to_string(value);   //och görs till en string
        while(checkIfDouples(newGuess) == true){    //kollar ifall det finns mer än 1 av varje siffra i gissningen 
            int value = stoi(newGuess); //sant så skapas en ny gissning utifrån den gamla
            value++;        //som ökas med ett
            if(value>9876){     //skulle gissningen gå till över 9876 så är detta för att användaren har matat in felaktiga svar så att algoritmen spinner vidare till oändlighet 
                std::cout<<"\nYe Cheatin' SCUM!!"<<std::endl;       //därför skapas detta felhanterande meddelande 
                exit(EXIT_FAILURE);                                 //och programmet avslutas
            }
            newGuess = std::to_string(value);       //läggs tillbaka till gissnings-stringen där det fortsätter loop tills loopen returnerar falskt och vi har en gissning utan dubbletter 
            
        }
    }
    
    while(validGuess(newGuess, Guesses) == false){      //loop som körs tills att en giltig gissningar har filtrerats fram 
        int value = stoi(newGuess);         //gissningen läggs till en int
        value++;        //värdet ökas
        newGuess = std::to_string(value);   //läggs sedan till en string
        while(checkIfDouples(newGuess) == true){    //kollar dubletter
            int value = stoi(newGuess);     //gissningen läggs till en int
            value++;    //värdet ökas
            if(value>9876){     //ifall värdet som hela tiden ökas inte avslutas av att rätt gissning har tagits fram så kommer denna felhanterande kod att bli sann
                std::cout<<"\nYe Cheatin' SCUM!!"<<std::endl;   //eftersom att värdet har kommit till en ogiltigt nummer så har användaren matat in fel svar alternativt försökt att fuska 
                std::exit(EXIT_FAILURE);        //programmet avslutas
            }
            newGuess = std::to_string(value);   //läggs sedan till en string
            
        }
        
        
        
    }
    return newGuess;    //returnerar gissnigen
}


BullCow::BullCow(std::string& tmp, int& b, int& c)  //class constructor som tar in 3 värden  
{
    value = stoi(tmp);  
    B = b;
    C = c;          //lägger in värdena tillsammans med en gissning som sedan används av funktionerna
                    //för att ta fram giltiga gissningar
}

BullCow::BullCow(){     //default constructor som skapar en entitet med ett random värde 
    int a,b,c,d;
    a = 0;
    srand (time(NULL));
    
    while(a==0 || a==b || a==c || a==d || b==c || b==d || c==d){    //en algoritm som kommer loopar fram random nummer tills att den får fram 4 olika nummer där a!=0
        a = rand() % 9;
        b = rand() % 9;
        c = rand() % 9;
        d = rand() % 9;
    }
    value = ((a*1000)+(b*100)+(c*10)+d);    //och sedan lägger värdena till value 
}

void BullCow::Print(){      //enkel printfunktion för att visa värdet på bullcow entitet
    std::cout<<value<<std::endl;
}


bool bullCowCount(int& value, std::string& userGuess){ //funktion som tar in två värden för att användaren ska kunna gissa numret som programmet tagit fram 
    std::string programValue = std::to_string(value);
    int bulls = 0;
    int cows = 0;
    for(int i = 0; i != programValue.length(); i++)    //for loop som kollar värdet på två strings för att se hur dom stämmer överens med varandra
    {
        size_t pos = programValue.find(userGuess[i]);  //size_t pos för att hitta indexet och kolla om den finns i programmets värde
        if (pos == i)   //jämnför om index finns på "rätt" plats i strängen
            ++bulls;    //ökar bulls
        else if (pos != std::string::npos)  //finns index i strängen men inte på jämnförda positionen
            ++cows;     //ökar cows
    }
    if(bulls==4){   //om 4 bulls betyder det att man har gissat rätt
        return true;    //true skickas tillbaka
    }
    else{   //om inte så får användaren info om hur många bulls and cows dom fått
        std::cout<<"Your guess got "<<bulls<<" bulls and "<<cows<<" cows!\n";
        return false;   //false ges tillbaka och användaren får fortsätta att gissa 
    }
}

bool checkIfDouples(const std::string& s){  //kollar om en string har dubletter
    
    for (int i = 0; i != s.length(); i++)
      {
          for (int j = i + 1; j != s.length(); j++) //nästlar for loops med andra positionen för "j"
          {
              if (s[i] == s[j]) //om två index är lika så betyder det att det finns dubletter
              {
                  return true;  
              }
          }
          
      }
    
      
    return false;
     
}

void addToHighscore(const int& score){  //highscore funktion
    std::vector<std::pair<std::string, int>> v; //ny vector skapas med pair för att hålla reda på namn och deras score
    std::string name;
    std::string tmp;
    int number;
    char answer;
    std::cout<<"do you want to add your name to the highscore?\nY=yes, N=no:";
    std::cin>>answer;   //användaren får möjlighet att lägga till sitt resultat till highscore eller inte
    if(answer=='y' || answer=='Y'){ 
        std::ifstream inFile("highscore.txt");  //läser in/skapar ny fil med detta namn
        std::cin.ignore(1000, '\n');    //rensar cin
        std::cout<<"your name?: ";  
        std::getline(std::cin, name);   //användaren matar in sitt namn
        v.push_back(make_pair(name, score));    //en pair skapas med namnet och användarens score, som sedan läggs till vectorn
        while(inFile>>tmp){     //while loop för att läsa in tidigare scores(om det existerar) till vectorn
            inFile.ignore(100,'-'); //tmp för namn
            inFile>>number; //score
            if(!tmp.empty()){   //filterar ifall inget namn finns. så skapas inget vector pair.
                v.push_back(make_pair(tmp, number));
            }
        }
        inFile.close(); //stäng filen
        sort(v.begin(), v.end(), [](std::pair<std::string, int>& a, std::pair<std::string, int>& b) { return a.second < b.second; });
                //sort funktion som tar en lambda funktion och sorterar listan på score så att den hamnar i en fallande ordning baserat på score.        
        std::cout<<"\nCurrent highscore list!"<<std::endl<<std::endl;
        for(int i = 0; i < v.size(); i++){  //printar ut uppdaterad highscore listan med tidigare highscores
            std::cout<<v[i].first<<" :: "<<v[i].second<<std::endl;
        }
        std::ofstream writeToFile("highscore.txt", std::ofstream::out | std::ofstream::trunc);  //tar bort tidigare info i filen och öppnar för att skriva till
        for(int i = 0; i < v.size(); i++){  //loop som skriver till filen i fallande ordning
            writeToFile<<v[i].first<<" - "<<v[i].second<<std::endl;     //namn först tillsammans med score brevid
        }
        std::cout<<"\nThank you for playing!\n\n";
    }else{ //om man inte vill lägga till highscore
        std::cout<<"\nThank you for playing!\n\n";
    }
    
    
}

bool checkIfGuessOk(std::string& guess){    //felhanterande funktion för att inte användaren ska kunna skriva in annat än 4 siffror
    int number;
    if(!guess.empty()){ //kollar om gissnigen är tom
        if(guess.size() == 4){  //kollar ifall gissningen är rätt storlek
            if(std::stringstream(guess)>>number){   //gissningen läses in via stringstream för att filtrera bort andra karaktärer som inte kan finnas i en INT 
                if(number>=1023 && number<=9876)    //kollar om gissningen är giltig
                    return true;    
            }else{      //om inte så får användaren ge en ny gissning
                return false;
            }
        }else{      //om inte så får användaren ge en ny gissning
            return false;
        }
        
        
    }else{      //om inte så får användaren ge en ny gissning
        return false;
    }   
    //om inte så får användaren ge en ny gissning
    return false;
}
