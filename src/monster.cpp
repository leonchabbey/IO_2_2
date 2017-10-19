#include "monster.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include "json.hpp"
#include "defines.h"

using json = nlohmann::json;

enum class Race {
	ORC,
	GOBLIN,
	TROLL,
	LENGTH
};

struct RaceConfig {
	std::string name;
	std::string fileName;
};


RaceConfig getRaceConfig(Race& race) {
	RaceConfig raceConfig;
	switch (race) {
	case Race::ORC:
		raceConfig.name = "Orc";
		raceConfig.fileName = "orc.png";
		break;
	case Race::GOBLIN:
		raceConfig.name = "Goblin";
		raceConfig.fileName = "goblin.png";
		break;
	case Race::TROLL:
		raceConfig.name = "Troll";
		raceConfig.fileName = "troll.png";
		break;
	}
	return raceConfig;
}

/////////////////////////////
/////// Monster Class ///////
/////////////////////////////

Monster::Monster(std::string filePath) {
	std::ifstream i(filePath);
	json data;
	i >> data;

	if (validateRace(data["race"] - 1))
		race = Race(data["race"] - 1);
	else {
		race = Race(0);
		std::cout << "Race not valid, therefore using default '" << getRaceConfig(race).name << "'" << std::flush;
	}

	health = data["health"];
	attackPower = data["attackPower"];
	defensivePower = data["defensivePower"];
	speed = data["speed"];

	std::string textureName = getRaceConfig(race).fileName;

	texture.loadFromFile(IMG_FOLDER_PATH + textureName);
	sprite.setTexture(texture);
	sprite.scale(1,1);
	sprite.setPosition(0.f, 50.f);
	setHealthUI();
}

void Monster::attack(Monster& enemy) {

	sprite.move(1.f, 2.f);

	/*double damageTaken = attackPower - enemy.defensivePower;

	if (damageTaken <= 0)
		damageTaken = 1;

	enemy.health -= damageTaken;
	
	if (enemy.health <= 0)
		enemy.health = 0;

	std::cout << "The " << getRaceConfig(race).name << " attacks! The " 
		<< getRaceConfig(enemy.race).name << " lost " << damageTaken << " HP.\n";*/
}

void Monster::setHealthUI() {
	std::string fontPath = std::string(FONT_FOLDER_PATH) + std::string(DEFAULT_FONT);

	if (!font.loadFromFile(fontPath))
	{
		std::cout << "ERROR: Cannot load font" << std::flush;
	}

	healthUI.setFont(font);
	healthUI.setCharacterSize(24);
	healthUI.setFillColor(sf::Color::Red);
}

sf::Sprite& Monster::getSprite() {
	return sprite;
}

bool Monster::validateRace(int chosenRace) {
	return chosenRace < (int)Race::LENGTH && chosenRace >= 0;
}

void Monster::update() {
	healthUI.setString(std::to_string((int)health) + " HP");
}

void Monster::draw(sf::RenderWindow& window) {
	window.draw(healthUI);
	window.draw(sprite);
}

Monster::~Monster() {
}
