//
//  functionHeader.hpp
//  BullsNCows


#ifndef functionHeader_h
#define functionHeader_h
#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>






struct BullCow{		//struct som håller värden för gissingar och bulls = B and cows = C  
public:
    int value;
    int B;
    int C;
    BullCow();		//default constructor som skapar en en struct och lägger ett random value 
    void Print();	//print funktion till structen för att göra det lättare att gissa alternativ om man vill använda denna till något annat
    BullCow(std::string& tmp, int& b, int& c);		//constructor till programmet när den skapar gissningar som sedan får bulls and cows av användaren som används till gissningsalgoritmen
};

bool validGuess(std::string& g, std::vector<BullCow>& G);		//kallas av generateGuess() som jämför gissningen och svar med tidigare gissningar och tidigare svar
std::string generateGuess(std::vector<BullCow>& Guesses);		//skapar en gissing utifrån tidigare gissningar
BullCow bullsCows(std::string& g, BullCow& g1);					//kallas av validGuess() som jämför tidigare svar med nya svaret och retunerar en struct
bool checkIfDouples(const std::string& x);						//kollar ifall strängen har 2 av samma siffra
bool bullCowCount(int& value, std::string& y);					//kollar om gissningen och den genererade struct:ens värde är lika
void addToHighscore(const int& score);							//lägger till användaren i en highscore lista
bool checkIfGuessOk(std::string& guess);						//felhantering som kollar ifall gissnignen är godkänd



#endif /* functionHeader_h */
