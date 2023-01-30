/*Namn: Rickard Karlsson
*Projekt - Bulls and Cows
*Programmet är ett spel som tillåter användaren att spela bulls and cows.
*programmet kan antingen gissa på vad användaren har för siffror alternativ 
*att användaren kan gissa vad programmet har för siffror. 
*när användaren gissar på programmets tal så har man även möjligheten att spara 
*sitt antal gissninger i en highscore lista som visas i en fallande ordning. 
*/
#include "functionHeader.h"




int main(){
    std::vector<BullCow> vecGuess;      //initierar en vector med en struct för att spara gissningar och 
    int val;                            //sammanhängade antal cows och bulls som ges av användaren
    int count = 1;
    int bulls;
    int cows;
    std::string guesses;        //initierar variabler
    BullCow random;     //initierar en klass/struct modell som skapar ett random nummer för alternativ 2
    
    std::cout<<"Welcome to Bulls and Cows!\nFor the program to Guess press 1,\nIf you want to guess press 2 "<<std::endl;
    std::cout<<"and to exit press 3: ";
    std::cin>>val;
    bool correctGuess = false;  //loopbreaker när 4 bulls har hittats
    while(correctGuess == false){
        switch(val)       
        {
            
            case 1 :
                guesses = generateGuess(vecGuess);      //skapar första gissningen som av standard är 1023
                std::cout<<"think of a number between 1023 and 9876 that cant contain any duplicated numbers"<<std::endl;
                while(correctGuess == false){       //loop för att programmet ska fortsätta tills rättgissning är nådd == bulls=4
                    std::cout<<"\nPrograms guess is: "<<guesses<<"\nHow many bulls: ";
                    std::cin>>bulls;        //antal bulls i gissningen
                    while(true){        //denna while-sats är felhantering för inmatningen så att inga bokstäver etc ska kunna läggas in
                        if(std::cin.fail()){
                            std::cout<<"invalid input try again!\nHow many bulls: ";
                            std::cin.clear();
                            std::cin.ignore(1000, '\n');
                            std::cin>>bulls;
                        }else{
                            break;
                        }
                    }
                    std::cout<<"How many cows?: ";
                    std::cin>>cows;     //antal bulls i gissningen
                    while(true){        //denna while-sats är felhantering för inmatningen så att inga bokstäver etc ska kunna läggas in
                        if(std::cin.fail()){
                            std::cout<<"invalid input try again!\nHow many cows: ";
                            std::cin.clear();
                            std::cin.ignore(1000, '\n');
                            std::cin>>cows;
                        }else{
                            break;
                        }
                    }
                    
                    if((bulls == 4) && (cows == 0)){        //ytterligare felhantering för att inte inmatningarna ska bli fel
                        if(count==1){                       //blir det rätt på första försöket så skrivs denna rad ut
                            std::cout<<"\nPROGRAM GUESSED RIGHT ON FIRST TRY!!!"<<std::endl;
                            //std::cin.ignore(1000, '\n');
                            correctGuess = true;        //sätter correctGuess till true
                            //break;                  //bryter ur denna loop som sedan bryter ut ur loopen där switchen är placerad rad:29
                        }else{          //är inte gissningen på första försöket så kommer denna rad.
                        std::cout<<"\nPROGRAM GUESSED RIGHT IN "<<count<<" TRIES!"<<std::endl;  
                        //std::cin.ignore(1000, '\n');
                        correctGuess = true;    //sätter correctGuess till true
                        //break;                  //bryter ur denna loop som sedan bryter ut ur loopen där switchen är placerad rad:29
                        }
                    }else if((bulls+cows)<=4){      //felhantering för att inte gissningarna ska kunna matas över 4 
                    BullCow entity(guesses, bulls, cows);       //är bulls och cows <=4 så läggs antal bulls och cows i en struct tillsammans med gissningen
                    vecGuess.push_back(entity);                 //structen läggs till i vectorn
                    guesses = generateGuess(vecGuess);          //ny gissning skapas utifrån bulls och cows informationen 
                        count++;                                //countern ökas med 1
                        
                    }else{                  //är totalen av bulls and cows över 4 så blir det returnerar programmet invalid input och loopen börjar om
                        std::cout<<"invalid input try again!"<<std::endl;
                        continue;
                    }
                }
                break;
            case 2 :
                random.Print();       //för att veta direkt vad programmet har för nummer så man inte behöver gissa så mkt
                std::cout<<"Please enter a number between 1023 and 9876 \nGuess can't contain duplicated numbers "<<std::endl;
                while(correctGuess==false){     //loop för att programmet ska fortsätta tills rättgissning är nådd == bulls=4
                    std::cout<<"Guess: ";   
                    std::cin.ignore(100, '\n');
                    std::cin>>guesses;
                    if((checkIfGuessOk(guesses) == false) || (checkIfDouples(guesses)==true)){      //felhanterande funktion och funktion som kollar om strängen har mer än 2 av en siffra
                        std::cout<<"ERROR only guess numbers between 1023 and 9876 and no duplicates!\n";
                        std::cout<<"Try again"<<std::endl;      //om den har 2 av samma eller felhanteringsfunktionen retunerar falskt så loopas det om till början för en ny gissning 
                        continue;
                    }else{
                        if(bullCowCount(random.value, guesses) == false){       //kollar om gissingen och det genererade numret är samma
                            count++;        //om inte så denna kod. Då antal gissningar ökas med ett och loopen börjar om
                            continue;
                        }else if(count==1){     //om gissning och det genererade numret är samma samt att count är = 1 så denna kod
                            std::cout<<"\nCongratulation you won on the FIRST try!!!\n\n";
                            correctGuess = true;
                            addToHighscore(count);  //funktion om att lägga till användaren till highscore
                        }else{              //om gissning och det genererade numret är samma samt att count är > 1 så denna kod
                            std::cout<<"\nCongratulation you won!\nIt took you "<<count<<" guesses.\n\n";
                            correctGuess = true;
                            addToHighscore(count);  //funktion om att lägga till användaren till highscore
                        }
                    }
                }
                break;
            case 3 :        //avsluta programmet
                return 0;
            default:        //om inmatningen inte är 1,2 eller 3 så denna kod
                std::cout<<"invalid input try again!"<<std::endl;
                std::cout<<"If you want the program to Guess press 1 \nor if you want to guess press 2: ";
                std::cin>>val;  //nytt val alternativ ges
                continue;   //loopen går vidare
                    
        
            
        }
    }
        
}
