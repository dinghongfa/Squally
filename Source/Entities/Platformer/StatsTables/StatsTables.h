#pragma once
#include <map>

class StatsTables
{
public:
	static int getHealthGainAtLevel(int level);
	static int getHealthGainAtNewLevel(int newLevel);
	static int getManaGainAtLevel(int level);
	static int getManaGainAtNewLevel(int newLevel);
	static int getExpRequiredAtLevel(int level);
	static int calculateEnemyExp(int health, int mana);

protected:

private:
	static const std::map<int, int> HealthGain;
	static const std::map<int, int> ManaGain;
	static const std::map<int, int> ExpRequired;
};