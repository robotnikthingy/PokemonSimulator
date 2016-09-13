#include <iostream>
#include <cstdlib>
#include <string>
#include "pokemon.h"
#include "attack.h"
#include <windows.h>
#include <ctime>

using namespace std;

int main()
{
	string playerpokemonname;
	string aipokemonname;
	string randomlevels;
	bool continueplaying = true;

	srand(time(0));

	cout << "do you want pokemon with random levels? y/n" << endl;
	cin >> randomlevels;
	system("cls");
	cout << "enter the name of your pokemon" << endl;
	cin >> playerpokemonname;
	system("cls");
	cout << "enter the name of the AI pokemon" << endl;
	cin >> aipokemonname;


	Pokemon playerpokemon(playerpokemonname);
	Pokemon AIpokemon(aipokemonname);

	//the option for random levels adds some variety
	if (randomlevels == "y")
	{
		playerpokemon.SetLevel(rand() % 100);
		AIpokemon.SetLevel(rand() % 100);
	}
	system("cls");

	//the battle starts here
while(continueplaying == true)
{

	while(playerpokemon.GetStatus() != "fainted" || AIpokemon.GetStatus() != "fainted" )
	{
		//Basic UI stuff
		cout << "[" << playerpokemon.GetName() << "]" << "                        " << "[" << AIpokemon.GetName() << "]" << endl;
		cout << "[Level: " << playerpokemon.GetLevel() << "]                      [Level: " << AIpokemon.GetLevel() << "]" << endl;
		cout << "[HP] " << playerpokemon.GetHP() << "                          " << "[HP] " << AIpokemon.GetHP() << endl;
		cout << "[Status: " << playerpokemon.GetStatus() << "]                    [Status: " << AIpokemon.GetStatus() << "]" << endl;
		cout << endl;

		string attack;
		cout << "choose attack to use: " << endl;
		cout << playerpokemon.GetAttackName(1) << " " << playerpokemon.GetAttackPP(1) << endl;
		cout << playerpokemon.GetAttackName(2) << " " << playerpokemon.GetAttackPP(2) <<endl;
		cout << playerpokemon.GetAttackName(3) << " " << playerpokemon.GetAttackPP(3) <<endl;
		cout << playerpokemon.GetAttackName(4) << " " << playerpokemon.GetAttackPP(4) << endl;
		cin >> attack;

		system("cls");
		if (playerpokemon.GetSpeed() > AIpokemon.GetSpeed())
		{
			playerpokemon.AttackOpponent(attack, AIpokemon, playerpokemon);
			AIpokemon.AIAttackOpponent(playerpokemon, AIpokemon);
		}
		else
		{
			AIpokemon.AIAttackOpponent(playerpokemon, AIpokemon);
			playerpokemon.AttackOpponent(attack, AIpokemon, playerpokemon);

		}
		system("cls");

		//Check if either pokemon has fainted. A pokemon faints when they have 0 or less HP
		if(playerpokemon.GetStatus() == "fainted")
		{
			cout << "your pokemon fainted" << endl;
			break;
		}
		else if(AIpokemon.GetStatus() == "fainted")
		{
			cout << "your opponents pokemon fainted" << endl;
			cout << "your " << playerpokemon.GetName() << " gained " << AIpokemon.GetLevel() * 4 << " xp!" << endl;
			break;
		}
	}

	if (AIpokemon.GetStatus() == "fainted")
	{
		char choice;
		cout << " do you want to keep battling? y/n" << endl;
		cin >> choice;
		if (choice == 'y')
		{
			string pokemonname;
			cout << "enter name of opponent pokemon" << endl;
			cin >> pokemonname;

			AIpokemon.Reinitialize(pokemonname);
				system("cls");
		}
		else
		{
				system("cls");
			cout << "You won, thanks for playing!" << endl;
			break;
		}
		
	}
	else if (playerpokemon.GetStatus() == "fainted")
	{
		char choice;
		cout << " do you want to send out another pokemon? y/n" << endl;
		cin >> choice;
		if (choice == 'y')
		{
			string pokemonname;
			cout << "enter name of the pokemon" << endl;
			cin >> pokemonname;

			playerpokemon.Reinitialize(pokemonname);
				system("cls");
		}
		else
		{
				system("cls");
			cout << "thanks for playing!" << endl;
			break;
		}
	}
	}
	return 0;
}

