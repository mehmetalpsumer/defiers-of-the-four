//-----------------------------------------------------------------
// Demon Object
// C++ Source - Demon.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Demon.h"

//-----------------------------------------------------------------
// Demon Constructor(s)/Destructor
//-----------------------------------------------------------------
Demon::Demon(std::string _name, std::string _description, Sprite* _sprite, int _healthPoint, int _speed, POINT _mapPosition, 
	ControlStatus _controlStatus, Demon _demons_in_range[], int _base_number, int _warned_by_helpless_base_number, bool _menuHover)
	:Character(_name, _description, _sprite, _healthPoint, _speed, _mapPosition)
{
	name = _name;
	description = _description;
	sprite = _sprite;
	speed = _speed;
	healthPoint = _healthPoint;
	maxHealthPoint = _healthPoint;
	mapPosition = _mapPosition;
	controlStatus = _controlStatus;

}

Demon::~Demon()
{
}


//-----------------------------------------------------------------
// Demon General Methods
//-----------------------------------------------------------------


void Situations(Demon demon, Robot robot, map currentmap, Sprite _pEnemyBase, int _pEnemyBase_c) {

	int robot_amount_around_the_demon = 0;
	int demon_amount_in_the_base = 0;

	Demon robots_around_the_demon[] = seekTheRobots(demon, currentmap, robot_amount_around_the_demon);

	POINT demonBaseLocation;
	demonBaseLocation.x = _pEnemyBase[_pEnemyBase_c].GetMapPosition().x;
	demonBaseLocation.y = _pEnemyBase[_pEnemyBase_c].GetMapPosition().y;

	Demon demons_around_the_base[] = seekTheBaseDemons(demonBaseLocation, currentmap, demon_amount_in_the_base); //BASE DEMONLARI CLASS'TAN İŞARETLE.

	if (robot_amount_around_the_demon <= 2) { //TASK 2
		AttackByMaintainingTheDistance(demon, currentmap, robot, demons_around_the_base);
	}
	else if (robot_amount_around_the_demon > 2) { // TASK 3

		POINT demonBaseLocation;
		demonBaseLocation.x = _pEnemyBase[_pEnemyBase_c].GetMapPosition().x;
		demonBaseLocation.y = _pEnemyBase[_pEnemyBase_c].GetMapPosition().y;

		WarnTheBaseDemons(demon, currentmap, demonBaseLocation, demons_around_the_base, _pEnemyBase_c);

		if (demon_amount_in_the_base < 2 * robot_amount_around_the_demon) { // TASK 5

			POINT the_closest_base_location = FindTheClosestBase(demon, _pEnemyBase, _pEnemyBase_c);

			int demon_amount_in_the_closest_base = 0;
			Demon demons_around_the_closest_base[] = seekTheBaseDemons(the_closest_base_location, currentmap, demon_amount_in_the_closest_base); //BASE DEMONLARI CLASS'TAN İŞARETLE.
			
			WarnTheBaseDemons(demon, currentmap, the_closest_base_location, demons_around_the_closest_base, _pEnemyBase_c);

			if (demon_amount_in_the_closest_base > 2 * robot_amount_around_the_demon && demon_amount_in_the_base > 2) { // TASK 6

				for (size_t i = 0; i < demon_amount_in_the_base / 2; i++)
				{
					SendToTheHelplessBase(demons_around_the_base[i], the_closest_base_location);
				}
			}

		}
			
	}

	if (demon_amount_in_the_base >= 2 * robot_amount_around_the_demon) { //TASK 4

		Robot the_closest_robot = FindTheClosestRobot(demon, robots_around_the_demon);

		Attack(demon, the_closest_robot);
	}
	
}

void int seekTheRobots(Demon demon, map currentmap, int robot_amount_around_the_demon) {

	POINT demonposition;
	demonposition.x = demon.GetMapPosition().x;
	demonposition.y = demon.GetMapPosition().y;
	const int range = 2;

	int arr_x[2 * range + 1];// = //{ -2,-1,0,1,2 };
	int arr_y[2 * range + 1];// // { -2,-1,0,1,2 };
	
	for (size_t i = 0; i <= range; i++)
	{
		i++;
		arr_y[i] = i;
		arr_x[i] = i;
		if (i > 0) {
			arr_y[i] = -i;
			arr_x[i] = -i;
		}
	}

	demon.setCurrentTargets = NULL;
	Demon robots_in_range[sizeof(arr_x)* sizeof(arr_y) - 1]; // Demon tipinde olacak
	int array_c = 0;

	// Range içindeki düşmanları tespit eder ve bunları ateş edilecek düşman arrayine ekler. 
	for (size_t i = 0; i < sizeof(arr_x); i++)
	{
		for (size_t j = 0; j < sizeof(arr_y); j++)
		{
			if (!(i == 0 && j == 0)) {

				if (demonposition.x + arr_x[i] < 32 && demonposition.x + arr_x[i] >= 0 && demonposition.y + arr_y[j] < 24 && demonposition.y + arr_y[j] >= 0)
				{
					if (currentmap[demonposition.y + arr_y[j]][demonposition.x + arr_x[i]] == 3) // enemy 3
					{
						robots_in_range[array_c] = GetPlayer(demonposition.y + arr_y[j], demonposition.x + arr_x[i]);
						array_c++;
						robot_amount_around_the_demon++;
						break;
					}

				}

			}

		}
	}

	demon.setCurrentTargets(robots_in_range);
	return robots_in_range;
}

void seekTheBaseDemons(POINT demonBaseLocation, map currentmap, int demon_amount_in_the_base) {

	const int range = 2;

	int arr_x[2 * range + 1];// = //{ -2,-1,0,1,2 };
	int arr_y[2 * range + 1];// // { -2,-1,0,1,2 };

	for (size_t i = 0; i <= range; i++)
	{
		i++;
		arr_y[i] = i;
		arr_x[i] = i;
		if (i > 0) {
			arr_y[i] = -i;
			arr_x[i] = -i;
		}
	}

	demonBaseLocation.setCurrentDemons = NULL;
	Demon demons_in_range[sizeof(arr_x)* sizeof(arr_y) - 1]; // Demon tipinde olacak
	int array_c = 0;

	// Range içindeki düşmanları tespit eder ve bunları ateş edilecek düşman arrayine ekler. 
	for (size_t i = 0; i < sizeof(arr_x); i++)
	{
		for (size_t j = 0; j < sizeof(arr_y); j++)
		{
			if (!(i == 0 && j == 0)) {

				if (demonBaseLocation.x + arr_x[i] < 32 && demonBaseLocation.x + arr_x[i] >= 0 && demonBaseLocation.y + arr_y[j] < 24 && demonBaseLocation.y + arr_y[j] >= 0)
				{
					if (currentmap[demonBaseLocation.y + arr_y[j]][demonBaseLocation.x + arr_x[i]] == 3) // enemy 3
					{
						demons_in_range[array_c] = GetPlayer(demonBaseLocation.y + arr_y[j], demonBaseLocation.x + arr_x[i]);
						array_c++;
						demon_amount_in_the_base++;
						break;
					}

				}

			}

		}
	}

	demonBaseLocation.setCurrentDemons(demons_in_range);

	return demons_in_range;
}

void WarnTheBaseDemons(Demon demon, map currentmap, POINT demonBaseLocation, Demon demons_around_the_base[], int _pEnemyBase_c) {

	POINT startingposition;
	startingposition.x = demon.GetMapPosition().x;
	startingposition.y = demon.GetMapPosition().y;

	queue <POINT> finalroute = pathFinding(demonBaseLocation, startingposition, currentmap);

	demon.MoveOn(finalroute); //base'e gider.

	for (size_t i = 0; i < sizeof(demons_around_the_base); i++)
	{
		if (demons_around_the_base[i] != NULL) {
			demons_around_the_base[i].SetBaseNumberThatWarnedByTheHelplessDemon(_pEnemyBase_c); // warn the base demons
		}			
		else break;
	}
}

void AttackByMaintainingTheDistance(Demon demon, map currentmap, Robot robot, Demon demons_around_the_base, Sprite _pEnemyBase, int _pEnemyBase_c) {

	int distance = EuclideanDistance(demon, robot);

	if (distance > 4) {
		Chase(demon, robot);
	}
	else if (distance < 4) {
		Evade(demon, robot);
	}

	RestrictForTheBaseBoundaries(demon, _pEnemyBase, _pEnemyBase_c);

	Attack(demon, robot);
}

void int EuclideanDistance(Demon demon, Robot robot) {

	//HER KARAKTERİN UPDATE FONKU İÇİNDE DE ÇAĞRILICAK
	POINT startingposition;
	startingposition.x = demon.GetMapPosition().x;
	startingposition.y = demon.GetMapPosition().y;

	POINT targetposition;
	targetposition.x = robot.GetMapPosition().x;
	targetposition.y = robot.GetMapPosition().y;

	double x = startingposition.x - targetposition.x;
	double y = startingposition.y - targetposition.y;
	double distance = pow(x, 2) + pow(y, 2);

	int EuclideanDistance = sqrt(distance);
	return EuclideanDistance;
}

void Chase(Demon demon, Robot robot) {

	if ((rand() % 3) == 0) {
		if (demon.GetMapPosition().x > robot.GetMapPosition().x)
			demon.SetMapPosition(--demon.GetMapPosition().x, demon.GetMapPosition().y);
		else if (demon.GetMapPosition().x < robot.GetMapPosition().x)
			demon.SetMapPosition(++demon.GetMapPosition().x, demon.GetMapPosition().y);
	}
	if ((rand() % 3) == 0) {
		if (demon.GetMapPosition().y > robot.GetMapPosition().y)
			demon.SetMapPosition(--demon.GetMapPosition().y, demon.GetMapPosition().y);
		else if (demon.GetMapPosition().y < robot.GetMapPosition().y)
			demon.SetMapPosition(++demon.GetMapPosition().y, demon.GetMapPosition().y);
	}

}

void Evade(Demon demon, Robot robot) {

	if (demon.GetMapPosition().x > robot.GetMapPosition().x)
		demon.SetMapPosition(++demon.GetMapPosition().x, demon.GetMapPosition().y);
	else if (demon.GetMapPosition().x < robot.GetMapPosition().x)
		demon.SetMapPosition(--demon.GetMapPosition().x, demon.GetMapPosition().y);
	if (demon.GetMapPosition().y > robot.GetMapPosition().y)
		demon.SetMapPosition(++demon.GetMapPosition().y, demon.GetMapPosition().y);
	else if (demon.GetMapPosition().y < robot.GetMapPosition().y)
		demon.SetMapPosition(--demon.GetMapPosition().y, demon.GetMapPosition().y);

}

void Attack(Demon demon, Robot robot) {

}

void FindTheClosestRobot(Demon demon, Robot robots_around_the_demon) {

	int arr_distance[sizeof(robots_around_the_demon)];

	for (size_t i = 0; i < sizeof(robots_around_the_demon); i++)
	{
		int distance = EuclideanDistance(demon, robots_around_the_demon[i]);
		arr_distance[i] = distance;
	}

	int min_distance = arr_distance[0];
	int index_of_the_closest_robot = 0;

	for (size_t i = 0; i < sizeof(arr_distance); i++)
	{
		if (arr_distance[i] != NULL) {

			if (arr_distance[i] < min_distance) {
				min_distance = arr_distance[i];
				index_of_the_closest_robot = i;
			}
		}
		else break;
	}

	return robots_around_the_demon[index_of_the_closest_robot];
}

void FindTheClosestBase(Demon demon, Sprite _pEnemyBase, int _pEnemyBase_c) {

	int arr_distance[sizeof(_pEnemyBase)];

	for (size_t i = 0; i < sizeof(_pEnemyBase); i++)
	{
		if (_pEnemyBase_c != demon.GetBaseNumber()) { // kendi base'i dışındakilere bak.
			int distance = EuclideanDistance(demon, _pEnemyBase[i]);
			arr_distance[i] = distance;
		}

		if (_pEnemyBase[i] == NULL) break;
	}

	int min_distance = arr_distance[0];
	int index_of_the_closest_base = 0;

	for (size_t i = 0; i < sizeof(arr_distance); i++)
	{
		if (arr_distance[i] != NULL) {

			if (arr_distance[i] < min_distance) {
				min_distance = arr_distance[i];
				index_of_the_closest_base = i;
			}
		}
		else break;
	}

	POINT the_closest_base;
	the_closest_base.x = _pEnemyBase[index_of_the_closest_base].GetMapPosition().x;
	the_closest_base.y = _pEnemyBase[index_of_the_closest_base].GetMapPosition().y;

	return the_closest_base;
}

void RestrictForTheBaseBoundaries(Demon demon, Sprite _pEnemyBase, int _pEnemyBase_c) {

	POINT enemyBaseLocation;
	enemyBaseLocation.x = _pEnemyBase[_pEnemyBase_c].GetMapPosition().x;
	enemyBaseLocation.y = _pEnemyBase[_pEnemyBase_c].GetMapPosition().y;

	if (demon.GetMapPosition().x > enemyBaseLocation.x && demon.GetMapPosition().x < enemyBaseLocation.x)
		demon.SetMapPosition(enemyBaseLocation.x, demon.GetMapPosition().y);

	if (demon.GetMapPosition().y > enemyBaseLocation.y && demon.GetMapPosition().y < enemyBaseLocation.y)
		demon.SetMapPosition(demon.GetMapPosition().x, enemyBaseLocation.y);

}