#ifndef UTIL_H
#define UTIL_H
#include <iostream>
#include "pokemon.h"
using namespace std;

void GenericAnimationShort();
bool PokemonStatusConditions(Pokemon& UsedPokemon);
bool PokemonAttackConditions(Pokemon PlayerPokemon, Pokemon OpponentPokemon, string condition);
void PokemonAttackSpecialParameters(Pokemon& PlayerPokemon, Pokemon& OpponentPokemon, string parameter);
void GenericAnimation(char character1, char character2);
#endif