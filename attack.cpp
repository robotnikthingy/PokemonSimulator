#include "attack.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string> 
#include "debug.h"

Attack::Attack()
{
	power = 0;
	accuracy = 0;
	string effect;
	int effectchance;
	int pp;

}

Attack::Attack(string value)
{
	//load up attack from the attack folder
	string attackfilename = "attacks\/" + value += ".txt";
	ifstream input(attackfilename);

	input >> name >> power >> accuracy >> effect >> effectchance >> pp >> type >> condition >> SpecialParameter;
}

int Attack::GetAccuracy()
{
	return accuracy;
}

string Attack::GetEffect()
{
	return effect;
}

int Attack::GetEffectChance()
{
	return effectchance;
}

double Attack::GetPower()
{
	return power;
}

int Attack::GetPP()
{
	return pp;
}

string Attack::GetName()
{
	return name;
}

void Attack::SetAccuracy(int value)
{
	accuracy = value;
}

void Attack::SetEffect(string value)
{
	effect = value;
}

void Attack::SetEffectChance(int value)
{
	effectchance = value;
}

void Attack::SetPower(int value)
{
	power = value;
}

void Attack::SetPP(int value)
{
	pp = value;
}

void Attack::initialize(string value)
{
	DebugOutput("Attack::initialize");
	string attackfilename = value += ".txt";
	ifstream input(attackfilename);

	input >> name >> power >> accuracy >> effect >> effectchance >> pp >> type >> condition >> SpecialParameter;

	input.close();
}

string Attack::GetType()
{
	return type;
}

string Attack::GetSpecialParameter()
{
	return SpecialParameter;
}

string Attack::GetCondition()
{
	return condition;
}