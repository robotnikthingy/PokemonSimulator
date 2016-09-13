#include <iostream>
#include <string> 
#include <cstdlib>
#include "debug.h"
#include <windows.h>
#include "pokemon.h"
#include "attack.h"
using namespace std;
//includes misc useful functions



//plays a small rotating thing animation
void GenericAnimationShort()
{
	cout << " ";
	for (int i = 0; i < 2; i++)
	{
		Sleep(250);
		cout << "\b\\" << flush;
		Sleep(250);
		cout << "\b|" << flush;
		Sleep(250);
		cout << "\b/" << flush;
		Sleep(250);
		cout << "\b-" << flush;
	}
	cout << endl;
}

//allows the playing of small custom animations
void GenericAnimation(char character1, char character2)
{
	cout << " ";
	for (int i = 0; i < 3; i++)
	{
		Sleep(250);
		cout << "\b" << character1 << flush;
		Sleep(250);
		cout << "\b" << character2 << flush;
	}
	cout << endl;
}

//Used to apply varius status effect effects to pokemon during battle
bool PokemonStatusConditions(Pokemon& UsedPokemon)
{

	//A pokemon which has fainted obviously cannot attack
	if (UsedPokemon.GetStatus() == "fainted")
		return false;

	//status effects which can stack with other status effects
	if (UsedPokemon.GetStatus() == "Confuse")
	{
		//After 3 turns, there is a 75% chance the pokemon will no longer be confused
		if (UsedPokemon.GetStatusCounter() > 3)
		{
			if(rand() % 100 < 75)
			{
				cout << UsedPokemon.GetName() << " Is no longer counfused" << endl;
				UsedPokemon.SetStatusCounter(0);
				return true;
			}
		}
		else
		{
			{
				cout << UsedPokemon.GetName() << " is confused" << endl;
				GenericAnimation('-','?');

				if (rand() % 100 > 50)
				{
					cout << "it hurt itself in its confusion";
					GenericAnimation('?', '!');
					UsedPokemon.SetHP(UsedPokemon.GetHP() - 10);

					//a pokemon which hurts itself in its confusion cannot attack
					return false;
				}
			}

		}
		return true;
	}




	//status effects which cannot stack

	//A pokemon which is paralzed has a 50% chance of an attack failing due to paralysis
	if (UsedPokemon.GetStatus() == "Paralyze")
	{
		int chance = rand() % 100;

		if (chance > 50)
			cout << UsedPokemon.GetName() << " is paralyed and cant attack " << endl;
		GenericAnimation('{','}');
		cout << endl;
		return false;

	}

	//A pokemon which is frozen cannot attack until it thaws out
	else if (UsedPokemon.GetStatus() == "Freeze")
	{
		if (UsedPokemon.GetStatusCounter() > 3)
		{
			if(rand() % 100 < 75)
			{
				cout << UsedPokemon.GetName() << " Thawed out" << endl;
				UsedPokemon.SetStatusCounter(0);
				return true;
			}
		}

		else
		{
			cout << UsedPokemon.GetName() << " is frozen and cant attack " << endl;
			GenericAnimation('F','*');
			cout << endl;
			return false;
		}
	}

	//A pokemon which is frozen cannot attack unless hit by a fire based attack
	else if (UsedPokemon.GetStatus() == "Sleep")
	{
		if (UsedPokemon.GetStatusCounter() > 3)
		{
			if(rand() % 100 < 75)
			{
				cout << UsedPokemon.GetName() << " Woke up" << endl;
				UsedPokemon.SetStatusCounter(0);
				return true;
			}
		}
		else
		{
		cout << UsedPokemon.GetName() << " is Sleeping and cant attack " << endl;
		GenericAnimation('Z','z');
		cout << endl;
		return false;
		}
	}

	//A pokemon which is burned takes damage every turn, and their attack power decreses every turn as well.
	else if (UsedPokemon.GetStatus() == "Burn")
	{
		cout << UsedPokemon.GetName() << " was hurt by its burn " << endl;
		GenericAnimation('#','=');
		cout << endl;
		UsedPokemon.SetHP(UsedPokemon.GetHP() - 5);
		UsedPokemon.SetAttack(UsedPokemon.GetPower() - 2);
		return true;
	}

	//A pokemon which is poisoned takes a small amount of damage every turn
	else if (UsedPokemon.GetStatus() == "Poison")
	{
		cout << UsedPokemon.GetName() << " was hurt by its poison " << endl;
		GenericAnimation('[',']');
		cout << endl;
		UsedPokemon.SetHP(UsedPokemon.GetHP() - 10);
		return true;
	}

	//a more potent version of poison which doubles the damage it does every turn
	else if (UsedPokemon.GetStatus() == "Toxic")
	{
		int totaldamage = 5 * UsedPokemon.GetStatusCounter();
		cout << UsedPokemon.GetName() << " was hurt by its poison " << endl;
		GenericAnimation('[',']');
		cout << endl;
		UsedPokemon.SetHP(UsedPokemon.GetHP() - totaldamage);
		return true;
	}

	return true;



}


//Some attacks require special contitions in order to work. Conditions are specified in the attack files
bool PokemonAttackConditions(Pokemon PlayerPokemon, Pokemon OpponentPokemon, string condition)
{
	if (condition == "none")
		return true;
	if (condition == "requires_opponent_sleep")
	{
		if (OpponentPokemon.GetStatus() == "Sleep")
			return true;
		else
		{
			cout << "The attack failed" << endl;
			return false;
		}
	}

	return true;
}


//Some attacks have special effects
void PokemonAttackSpecialParameters(Pokemon& PlayerPokemon, Pokemon& OpponentPokemon, string parameter)
{
	//An attack which has this gives the pokemon which used it a small amount of health
	if (parameter == "absorb_small")
	{
		int totalabsorbed = (PlayerPokemon.GetLevel() / 3);
		PlayerPokemon.SetHP(PlayerPokemon.GetHP() + totalabsorbed);
		cout << PlayerPokemon.GetName() << " abosorbed " << totalabsorbed << " HP" << endl;
	}
}