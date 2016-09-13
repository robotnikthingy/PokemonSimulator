#ifndef POKEMON_H
#define POKEMON_H
#include <iostream>
#include "attack.h"
using namespace std;


class Pokemon
{
public:
	Pokemon();
	Pokemon(string name);

	double GetPower();
	int GetDefense();
	int GetHP();
	int GetLevel();
	int GetSpeed();
	string GetName();
	string GetType1();
	string GetType2();
	string GetStatus();
	string GetAttackName(int value);
	string GetAttackType(int value);
	int GetAttackPP(int value);
	int GetStatusCounter();

	void SetAttackPP(int attack, int value);
	void SetAttack(int value);
	void SetDefense(int value);
	void SetHP(int value);
	void SetLevel(int value);
	void SetSpeed(int value);
	void SetName(string value);
	void SetType1(string value);
	void SetType2(string value);
	void SetStatus(string value);
	void SetStatusCounter(int value);

	void AttackOpponent(string value, Pokemon& OpponentPokemon, Pokemon& PlayerPokemon);
	void AIAttackOpponent(Pokemon& OpponentPokemon, Pokemon& PlayerPokemon);

	void Pokemon::Reinitialize(string value);
private:
	double power;
	int defense;
	int hp;
	int level;
	int speed;
	int statuscounter;
	string name;
	string type1;
	string type2;
	string status;

	//pokemon cannot have more than 4 attacks
	Attack Attack1;
	Attack Attack2;
	Attack Attack3;
	Attack Attack4;

};

#endif