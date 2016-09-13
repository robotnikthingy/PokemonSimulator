#ifndef ATTACK_H
#define ATTACK_H
#include <iostream>

using namespace std;

class Attack
{
public:
	Attack();
	Attack(string name);

	double GetPower();
	int GetAccuracy();
	string GetEffect();
	int GetEffectChance();
	int GetPP();
	string GetName();
	string GetType();
	string GetCondition();
	string GetSpecialParameter();

	void SetPower(int value);
	void SetAccuracy(int value);
	void SetEffect(string value);
	void SetEffectChance(int value);
	void SetPP(int value);

	void initialize(string value);
private:
	string type;
	string name;
	string condition;
	string SpecialParameter;
	double power;
	int accuracy;
	string effect;
	int effectchance;
	int pp;
};

#endif