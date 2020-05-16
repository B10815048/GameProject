#include "Management.h"
#include <sstream>

void Management::Heal(User& user, std::string command)
{
	int value;
	std::stringstream ss;
	ss << command;
	ss >> value;
	user.HP += value;
	for (int i = 0; i < this->user.size(); i++)
	{
		if (this->user[i].name == user.name)			
		{
			if (this->user[i].HP < user.HP)
				user.HP = this->user[i].HP;
			std::cout << user.Icon << " heal " << value << ", now hp is " << user.HP << std::endl;
			break;
		}
	}
}

void Management::Heal(Enemy& enemy, std::string command)
{
	int value;
	std::stringstream ss;
	ss << command;
	ss >> value;
	enemy.HP[enemy.Type] += value;
	for (int i = 0; i < this->enemy.size(); i++)
	{
		if (this->enemy[i].name == enemy.name)
		{
			if (this->enemy[i].HP[this->enemy[i].Type] < enemy.HP[enemy.Type])
				enemy.HP[enemy.Type] = this->enemy[i].HP[this->enemy[i].Type];
			std::cout << enemy.Icon << " heal " << value << ", now hp is " << enemy.HP[enemy.Type] << std::endl;
		}
	}
}

void Management::Shield(Creature& creature, std::string command)
{
	int value;
	std::stringstream ss;
	ss << command;
	ss >> value;
	creature.Shield += value;
	std::cout << creature.Icon << " shield " << value << ", this turn" << std::endl;
}