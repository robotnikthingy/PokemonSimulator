#include "pokemon.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string> 
#include "debug.h"
#include <windows.h>
#include "util.h"

Pokemon::Pokemon()
{
	power = 0;
	defense = 0;
	hp = 0;
	level = 0;
	speed = 0;
	name = "empty";
	type1 = "Normal";
	type2 = "Normal";

}

Pokemon::Pokemon(string value)
{
	DebugOutput("Pokemon::Pokemon");
	string attacknumber1;
	string attacknumber2;
	string attacknumber3;
	string attacknumber4;

	//load up pokemon from the attack folder
	string filename = "pokemon\/" + value += ".txt";
	ifstream input(filename);

	if (input.fail())
		cout << "invalid pokemon, please try again" << endl;
	//This is where the program does not work, for some reason wont read attacks or something from file
	//Nevermind, solved. Refer to page 495 of book if it happens again
	input >> name >> hp >> power >> defense >> speed >> level >> type1 >> type2 >> attacknumber1 >> attacknumber2 >> attacknumber3 >> attacknumber4;

	input.close();

	Attack1.initialize(attacknumber1);
	Attack2.initialize(attacknumber2);
	Attack3.initialize(attacknumber3);
	Attack4.initialize(attacknumber4);

	status = "none";
	statuscounter = 0;
}

double Pokemon::GetPower()
{
	return power;
}

int Pokemon::GetDefense()
{
	return defense;
}

int Pokemon::GetHP()
{
	return hp;
}

int Pokemon::GetLevel()
{
	return level;
}

int Pokemon::GetSpeed()
{
	return speed;
}
string Pokemon::GetName()
{
	return name;
}
string Pokemon::GetType1()
{
	return type1;
}

string Pokemon::GetType2()
{
	return type2;
}

void Pokemon::SetAttack(int value)
{
	power = value;
}

void Pokemon::SetDefense(int value)
{
	defense = value;
}

void Pokemon::SetHP(int value)
{
	hp = value;
}

void Pokemon::SetLevel(int value)
{
	level = value;
}

void Pokemon::SetSpeed(int value)
{
	speed = value;
}

void Pokemon::SetName(string value)
{
	name = value;
}

void Pokemon::SetType1(string value)
{
	type1 = value;
}

void Pokemon::SetType2(string value)
{
	type2 = value;
}


void Pokemon::AttackOpponent(string value, Pokemon& OpponentPokemon, Pokemon& PlayerPokemon)
{
	DebugOutput("Pokemon::AttackOpponent");
	int TotalDamage;
	int attackPower;
	int attacknumber;
	int attackaccuracy;
	string statuseffect;
	int statuseffectchance;
	string condition;
	string specialparameter;
	string attackname = value;

	bool ispickattackfinished = false;

	do{
		if (value != "none")
		{
			if (value == Attack1.GetName())
			{
				if (GetAttackPP(1) == 0)
					cout << "that attack has no power left" << endl;
				else
				{
					attackPower = Attack1.GetPower();
					attacknumber = 1;
					statuseffect = Attack1.GetEffect();
					statuseffectchance = Attack1.GetEffectChance();
					attackaccuracy = Attack1.GetAccuracy();
					condition = Attack1.GetCondition();
					specialparameter = Attack1.GetSpecialParameter();
					ispickattackfinished = true;
				}
			}
			else if (value == Attack2.GetName())
			{
				if (GetAttackPP(2) == 0)
					cout << "that attack has no power left" << endl;
				else
				{
					attackPower = Attack2.GetPower();
					attacknumber = 2;
					statuseffect = Attack2.GetEffect();
					statuseffectchance = Attack2.GetEffectChance();
					attackaccuracy = Attack2.GetAccuracy();
					condition = Attack2.GetCondition();
					specialparameter = Attack2.GetSpecialParameter();
					ispickattackfinished = true;
				}

			}
			else if (value == Attack3.GetName())
			{
				if (GetAttackPP(3) == 0)
					cout << "that attack has no power left" << endl;
				else
				{
					attackPower = Attack3.GetPower();
					attacknumber = 3;
					statuseffect = Attack3.GetEffect();
					statuseffectchance = Attack3.GetEffectChance();
					attackaccuracy = Attack3.GetAccuracy();
					condition = Attack3.GetCondition();
					specialparameter = Attack3.GetSpecialParameter();
					ispickattackfinished = true;
				}
			}
			else if (value == Attack4.GetName())
			{
				if (GetAttackPP(4) == 0)
					cout << "that attack has no power left" << endl;
				else
				{
					attackPower = Attack4.GetPower();
					attacknumber = 4;
					statuseffect = Attack4.GetEffect();
					statuseffectchance = Attack4.GetEffectChance();
					attackaccuracy = Attack4.GetAccuracy();
					condition = Attack4.GetCondition();
					specialparameter = Attack4.GetSpecialParameter();
					ispickattackfinished = true;
				}
			}
			else
				cout << "invalid attack" << endl;
		}
	} while (ispickattackfinished == false);

	//calculate attack damage
	TotalDamage = (attackPower * (power/ 100) * ((level / 100) + 1)) - (OpponentPokemon.GetDefense() * 0.2);
	//calculate type bonus, which occurs when a pokemon uses an attack with the same type as the type of the pokemon using it
	if (PlayerPokemon.GetAttackType(attacknumber) == PlayerPokemon.GetType1() || PlayerPokemon.GetAttackType(attacknumber) == PlayerPokemon.GetType2())
		TotalDamage = TotalDamage * 1.25;

	//set attack pp (pp basically is how much times an attack can be used)
	SetAttackPP(attacknumber,GetAttackPP(attacknumber) - 1);

	//Some attacks do not do any damage, so try to make it stay that way
	if (attackPower == 0)
		TotalDamage = 0;


	//determine if the pokemon is even able to attack and apply damage
	//Also apply negative effects from other statuses

	if (PokemonStatusConditions(PlayerPokemon) == true && PokemonAttackConditions(PlayerPokemon, OpponentPokemon, condition) == true)
	{
		cout << "your " << name << " used " << attackname << endl;
		GenericAnimationShort();
		int accuracychance = rand() % 100;

		if (attackaccuracy > accuracychance)
		{

			//Check if the attack is a critical hit. all attacks have a 10% chance of doing a critical hit, which doubles the damage.
			if (rand() % 100 < 10)
			{
				cout << "Critical hit!" << endl;
				TotalDamage == TotalDamage * 2;
			}

			cout << "your " << name << " did " << TotalDamage << " damage" << endl;
			//apply the damage
			OpponentPokemon.SetHP(OpponentPokemon.GetHP() - TotalDamage);

			//apply any special parameters
			PokemonAttackSpecialParameters(PlayerPokemon, OpponentPokemon, specialparameter);

			if (statuseffect != "none")
			{
				int chance = rand() % 100;
				if (chance <= statuseffectchance)
				{
					OpponentPokemon.SetStatus(statuseffect);
					cout << OpponentPokemon.GetName() << " has been effected with " << statuseffect;
					GenericAnimation('!','_');
					cout << endl;
				}
			}
		}
		else
			cout << name << " missed" << endl;
	}
	else
		

	if (PlayerPokemon.GetStatus() != "none")
		statuscounter++;

	if (OpponentPokemon.GetHP() <= 0)
		OpponentPokemon.SetStatus("fainted");
			GenericAnimationShort();
}


void Pokemon::AIAttackOpponent(Pokemon& OpponentPokemon, Pokemon& PlayerPokemon)
{
	//Used to calculoate damage and pick an attack for the AI to use. Also contains the simple AI
	DebugOutput("AIAttackOpponent");

	int TotalDamage;
	int attackPower;
	int damagetodeal;
	int value;
	string attackname = "none";
	int attackaccuracy;
	string statuseffect;
	string condition;
	string specialparameter;
	int statuseffectchance;

	do
	{
		value = rand() % 4;
		if (value == 1)
		{
			attackname =Attack1.GetName();
			attackPower = Attack1.GetPower();
			statuseffect = Attack1.GetEffect();
			statuseffectchance = Attack1.GetEffectChance();
			attackaccuracy = Attack1.GetAccuracy();
			condition = Attack1.GetCondition();
			specialparameter = Attack1.GetSpecialParameter();
		}
		else if (value == 2)
		{
			attackname =Attack2.GetName();
			attackPower = Attack2.GetPower();
			statuseffect = Attack2.GetEffect();
			statuseffectchance = Attack2.GetEffectChance();
			attackaccuracy = Attack2.GetAccuracy();
			condition = Attack2.GetCondition();
			specialparameter = Attack2.GetSpecialParameter();
		}
		else if (value == 3)
		{
			attackname =Attack3.GetName();
			attackPower = Attack3.GetPower();
			statuseffect = Attack3.GetEffect();
			statuseffectchance = Attack3.GetEffectChance();
			attackaccuracy = Attack3.GetAccuracy();
			condition = Attack3.GetCondition();
			specialparameter = Attack3.GetSpecialParameter();
		}
		else if (value == 4)
		{
			attackname =Attack4.GetName();
			attackPower = Attack4.GetPower();
			statuseffect = Attack4.GetEffect();
			statuseffectchance = Attack4.GetEffectChance();
			attackaccuracy = Attack4.GetAccuracy();
			condition = Attack4.GetCondition();
			specialparameter = Attack4.GetSpecialParameter();
		}
		else if (value >= 5)
			attackname = "none";

		if (attackname != "none")
			break;
	} while(attackname == "none");

	//calculate attack damage
	TotalDamage = (attackPower * (power/ 100) * ((level / 100) + 1)) - (OpponentPokemon.GetDefense() * 0.2);

	if (PlayerPokemon.GetAttackType(value) == PlayerPokemon.GetType1() || PlayerPokemon.GetAttackType(value) == PlayerPokemon.GetType2())
		TotalDamage = TotalDamage * 1.25;

	//set attack pp
	SetAttackPP(value,GetAttackPP(value) - 1);

	//Some attacks do not do any damage, so try to make it stay that way
	if (attackPower == 0)
		TotalDamage = 0;

	if (PokemonStatusConditions(PlayerPokemon) == true && PokemonAttackConditions(PlayerPokemon, OpponentPokemon, condition) == true)
	{
		cout << "The opponents " << name << " used " << attackname << endl;
		GenericAnimationShort();
		int accuracychance = rand() % 100;

		if (attackaccuracy > accuracychance)
		{

			//Check if the attack is a critical hit. all attacks have a 10% chance of doing a critical hit, which doubles the damage.
			if (rand() % 100 < 10)
			{
				cout << "Critical hit!" << endl;
				TotalDamage == TotalDamage * 2;
			}

			cout << "the opponents " << name << " did " << TotalDamage << " damage" << endl;
			

			OpponentPokemon.SetHP(OpponentPokemon.GetHP() - TotalDamage);

			//apply any special parameters
			PokemonAttackSpecialParameters(PlayerPokemon, OpponentPokemon, specialparameter);
			if (statuseffect != "none")
			{
				int chance = rand() % 100;
				if (chance <= statuseffectchance)
				{
					OpponentPokemon.SetStatus(statuseffect);
					cout << OpponentPokemon.GetName() << " has been effected with " << statuseffect << endl;
					GenericAnimation('!','_');
					cout << endl;
				}
			}
		}
		else
			cout << name << " missed" << endl;
	}

	if (PlayerPokemon.GetStatus() != "none")
		statuscounter++;

	if (OpponentPokemon.GetHP() <= 0)
		OpponentPokemon.SetStatus("fainted");
			GenericAnimationShort();
}

string Pokemon::GetAttackName(int value)
{
	DebugOutput("Pokemon::GetAttackName, the value is");
	if (value == 1)
		return Attack1.GetName();
	else if (value == 2)
		return Attack2.GetName();
	else if (value == 3)
		return Attack3.GetName();
	else if (value == 4)
		return Attack4.GetName();
	else
		return "invalid";
}


string Pokemon::GetStatus()
{
	return status;
}

void Pokemon::SetStatus(string value)
{
	status = value;
}


int Pokemon::GetAttackPP(int value)
{
	if (value == 1)
		return Attack1.GetPP();
	else if (value == 2)
		return Attack2.GetPP();
	else if (value == 3)
		return Attack3.GetPP();
	else if (value == 4)
		return Attack4.GetPP();
	else
		return 0;
}

void Pokemon::SetAttackPP(int attack, int value)
{
	if (attack == 1)
		Attack1.SetPP(value);
	else if (attack == 2)
		Attack2.SetPP(value);
	else if (attack == 3)
		Attack3.SetPP(value);
	else if (attack == 4)
		Attack4.SetPP(value);
}

void Pokemon::Reinitialize(string value)
{
	//used to set up new pokemon if the player wants to keep playeing
	DebugOutput("Pokemon::Pokemon");
	string attacknumber1;
	string attacknumber2;
	string attacknumber3;
	string attacknumber4;

	//load up pokemon from the attack folder
	string filename = "pokemon\/" + value += ".txt";
	ifstream input(filename);

	if (input.fail())
		cout << "invalid pokemon, please try again" << endl;
	//This is where the program does not work, for some reason wont read attacks or something from file
	//Nevermind, solved. Refer to page 495 of book if it happens again
	input >> name >> hp >> power >> defense >> speed >> level >> type1 >> type2 >> attacknumber1 >> attacknumber2 >> attacknumber3 >> attacknumber4;

	input.close();

	Attack1.initialize(attacknumber1);
	Attack2.initialize(attacknumber2);
	Attack3.initialize(attacknumber3);
	Attack4.initialize(attacknumber4);

	status = "none";
}

string Pokemon::GetAttackType(int value)
{
		if (value == 1)
		return Attack1.GetType();
	else if (value == 2)
		return Attack2.GetType();
	else if (value == 3)
		return Attack3.GetType();
	else if (value == 4)
		return Attack4.GetType();
	else
		return "none";
}

int Pokemon::GetStatusCounter()
{
	return statuscounter;
}

void Pokemon::SetStatusCounter(int value)
{
	statuscounter = value;
}