//-----------------------------------------------------------------
// Demon Object
// C++ Source - Demon.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Demon.h"
#include "DemonBase.h"

//-----------------------------------------------------------------
// Demon Constructor(s)/Destructor
//-----------------------------------------------------------------
Demon::Demon(std::string _name, std::string _description, Sprite* _sprite, int _healthPoint, int _speed, POINT _mapPosition,
	DemonBase* base, int _fireSpeed, DemonBase* _base_needs_help)
	:Character(_name, _description, _sprite, _sprite, _healthPoint, _speed, _mapPosition, _fireSpeed)
{
	name = _name;
	description = _description;
	sprite = _sprite;
	speed = _speed;
	healthPoint = _healthPoint;
	maxHealthPoint = _healthPoint;
	mapPosition = _mapPosition;
}

Demon::~Demon()
{
}


//-----------------------------------------------------------------
// Demon General Methods
//-----------------------------------------------------------------


void Demon::Situations(Demon* demon, Robot* robot, Map currentmap, vector<DemonBase*> demonBaseArray) {

	seekTheRobots(demon, currentmap);

	POINT demonBasePosition;
	demonBasePosition.x = demon->GetBase()->GetMapPosition().x;
	demonBasePosition.y = demon->GetBase()->GetMapPosition().y;

	int robot_amount_in_the_base = demon->GetCurrentTargets().size();
	int demon_amount_in_the_base = demon->GetBase()->GetCurrentDemons().size();

	if (robot_amount_in_the_base <= 2) { //TASK 2
		AttackByMaintainingTheDistance(demon, currentmap, robot);
	}
	else if (robot_amount_in_the_base > 2) { // TASK 3

		WarnTheBaseDemons(demon, currentmap, demon->GetBase());

		if (demon_amount_in_the_base < 2 * robot_amount_in_the_base) { // TASK 5

			DemonBase* the_closest_base = FindTheClosestBase(demon, demon->GetBaseNumber(), demonBaseArray);

			WarnTheBaseDemons(demon, currentmap, the_closest_base);

			if (the_closest_base->GetCurrentDemons().size() > 2 * robot_amount_in_the_base && demon_amount_in_the_base > 2) { // TASK 6

				for (size_t i = 0; i < demon_amount_in_the_base / 2; i++)
				{
					// move to closest base
					//SendToTheHelplessBase(demon->GetBase()->GetCurrentDemons()[i], the_closest_base); //en yakýn base'e yardýma gider.
				}
			}

		}

	}

	if (demon_amount_in_the_base >= 2 * robot_amount_in_the_base) { //TASK 4

		Robot* the_closest_robot = FindTheClosestRobot(demon, demon->GetCurrentTargets());

		Attack(demon, the_closest_robot);
	}

}

void Demon::seekTheRobots(Demon* demon, Map currentmap) {

	POINT demonposition;
	demonposition.x = demon->GetMapPosition().x;
	demonposition.y = demon->GetMapPosition().y;
	const int range = 2;

	vector<int> arr_x;
	vector<int> arr_y;
	int i = 0;
	int value = 0;
	while (value < 2 * range + 1) {
		arr_y.push_back(value);
		arr_x.push_back(value);
		if (i > 0) {
			i++;
			arr_y.push_back(-value);
			arr_x.push_back(-value);

		}

		value++;
	}


	vector<Robot*> robots_in_range; // Demon tipinde olacak

									// Range içindeki düþmanlarý tespit eder ve bunlarý ateþ edilecek düþman arrayine ekler.
	for (size_t i = 0; i < sizeof(arr_x); i++)
	{
		for (size_t j = 0; j < sizeof(arr_y); j++)
		{
			if (!(i == 0 && j == 0)) {

				if (demonposition.x + arr_x[i] < 32 && demonposition.x + arr_x[i] >= 0 && demonposition.y + arr_y[j] < 24 && demonposition.y + arr_y[j] >= 0)
				{
					if (currentmap[demonposition.y + arr_y[j]][demonposition.x + arr_x[i]] == 3) // enemy 3
					{
						// get instance of the robot at position
						/*robots_in_range.push_back(GetPlayer(demonposition.y + arr_y[j], demonposition.x + arr_x[i]));*/
						break;
					}

				}

			}

		}
	}

	demon->SetCurrentTargets(robots_in_range);
}

void Demon::WarnTheBaseDemons(Demon* demon, Map currentmap, DemonBase* base) {

	POINT startingposition;
	startingposition.x = demon->GetMapPosition().x;
	startingposition.y = demon->GetMapPosition().y;

	POINT targetposition;
	targetposition.x = base->GetMapPosition().x;
	targetposition.y = base->GetMapPosition().y;

	/*queue <POINT> finalroute = FindPath(startingposition, targetposition, currentmap);*/

	/*demon->MoveOn(finalroute);*/ //base'e gider.

	vector<Demon*> demons_around_the_base = base->GetCurrentDemons();

	for (size_t i = 0; i < demons_around_the_base.size(); i++)
	{
		if (demons_around_the_base.size() > 0) {
			demons_around_the_base[i]->SetBaseNumberThatWarnedByTheHelplessDemon(base->GetBaseNumber()); // warn the base demons
		}
		else break;
	}
}

void Demon::AttackByMaintainingTheDistance(Demon* demon, Map currentmap, Robot* robot) {

	int distance = EuclideanDistance(demon, robot, NULL);

	if (distance > 4) {
		Chase(demon, robot);
	}
	else if (distance < 4) {
		Evade(demon, robot);
	}

	RestrictForTheBaseBoundaries(demon);

	Attack(demon, robot);
}

int Demon::EuclideanDistance(Demon* demon, Robot* robot, DemonBase* demonBase) {

	//HER KARAKTERÝN UPDATE FONKU ÝÇÝNDE DE ÇAÐRILICAK
	POINT startingposition;
	startingposition.x = demon->GetMapPosition().x;
	startingposition.y = demon->GetMapPosition().y;

	POINT targetposition;

	if (robot != NULL) {
		targetposition.x = robot->GetMapPosition().x;
		targetposition.y = robot->GetMapPosition().y;
	}
	else if (demonBase != NULL) {
		targetposition.x = demonBase->GetMapPosition().x;
		targetposition.y = demonBase->GetMapPosition().y;
	}

	double x = startingposition.x - targetposition.x;
	double y = startingposition.y - targetposition.y;
	double distance = pow(x, 2) + pow(y, 2);

	int EuclideanDistance = sqrt(distance);
	return EuclideanDistance;
}

void Demon::Chase(Demon* demon, Robot* robot) {

	POINT demonPosition;
	demonPosition.x = demon->GetMapPosition().x;
	demonPosition.y = demon->GetMapPosition().y;

	POINT robotPosition;
	robotPosition.x = robot->GetMapPosition().x;
	robotPosition.y = robot->GetMapPosition().y;

	if ((rand() % 3) == 0) {

		if (demonPosition.x > robotPosition.x) {

			POINT changedDemonPosition;
			changedDemonPosition.x = demon->GetMapPosition().x - 1;
			changedDemonPosition.y = demon->GetMapPosition().y;
			demon->SetMapPosition(changedDemonPosition);
		}

		else if (demonPosition.x < robotPosition.x) {

			POINT changedDemonPosition;
			changedDemonPosition.x = demon->GetMapPosition().x + 1;
			changedDemonPosition.y = demon->GetMapPosition().y;
			demon->SetMapPosition(changedDemonPosition);
		}

	}

	if ((rand() % 3) == 0) {

		if (demonPosition.y > robotPosition.y) {

			POINT changedDemonPosition;
			changedDemonPosition.x = demon->GetMapPosition().x;
			changedDemonPosition.y = demon->GetMapPosition().y - 1;
			demon->SetMapPosition(changedDemonPosition);
		}

		else if (demonPosition.y < robotPosition.y) {

			POINT changedDemonPosition;
			changedDemonPosition.x = demon->GetMapPosition().x;
			changedDemonPosition.y = demon->GetMapPosition().y + 1;
			demon->SetMapPosition(changedDemonPosition);
		}

	}

}

void Demon::Evade(Demon* demon, Robot* robot) {

	POINT demonPosition;
	demonPosition.x = demon->GetMapPosition().x;
	demonPosition.y = demon->GetMapPosition().y;

	POINT robotPosition;
	robotPosition.x = robot->GetMapPosition().x;
	robotPosition.y = robot->GetMapPosition().y;

	if (demonPosition.x > robotPosition.x) {

		POINT changedDemonPosition;
		changedDemonPosition.x = demon->GetMapPosition().x + 1;
		changedDemonPosition.y = demon->GetMapPosition().y;
		demon->SetMapPosition(changedDemonPosition);
	}

	else if (demonPosition.x < robotPosition.x) {

		POINT changedDemonPosition;
		changedDemonPosition.x = demon->GetMapPosition().x - 1;
		changedDemonPosition.y = demon->GetMapPosition().y;
		demon->SetMapPosition(changedDemonPosition);
	}

	if (demonPosition.y > robotPosition.y) {

		POINT changedDemonPosition;
		changedDemonPosition.x = demon->GetMapPosition().x;
		changedDemonPosition.y = demon->GetMapPosition().y + 1;
		demon->SetMapPosition(changedDemonPosition);
	}

	else if (demonPosition.y < robotPosition.y) {

		POINT changedDemonPosition;
		changedDemonPosition.x = demon->GetMapPosition().x;
		changedDemonPosition.y = demon->GetMapPosition().y - 1;
		demon->SetMapPosition(changedDemonPosition);
	}



}

void Demon::Attack(Demon* demon, Robot* robot) {

}

Robot* Demon::FindTheClosestRobot(Demon* demon, vector<Robot*> robots_around_the_demon) {

	vector<int> arr_distance;

	for (size_t i = 0; i < robots_around_the_demon.size(); i++)
	{
		int distance = EuclideanDistance(demon, (Robot*)robots_around_the_demon[i], NULL);
		arr_distance.push_back(distance);
	}

	int min_distance = arr_distance[0];
	int index_of_the_closest_robot = 0;

	for (size_t i = 0; i < arr_distance.size(); i++)
	{

		if (arr_distance[i] < min_distance) {
			min_distance = arr_distance[i];
			index_of_the_closest_robot = i;
		}

	}

	return robots_around_the_demon[index_of_the_closest_robot];
}

DemonBase* Demon::FindTheClosestBase(Demon* demon, int _pEnemyBase_c, vector<DemonBase*> demonBaseArray) {

	vector<int> arr_distance;
	vector<DemonBase*> demonBasesAccordingToDistances;

	for (size_t i = 0; i < demonBaseArray.size(); i++)
	{
		if (i != demon->GetBaseNumber()) { // kendi base'i dýþýndakilere bak.

			int distance = EuclideanDistance(demon, NULL, (DemonBase*)demonBaseArray[i]);
			arr_distance.push_back(distance);
		}
	}

	int min_distance = arr_distance[0];
	int index_of_the_closest_base = 0;

	for (size_t i = 0; i < arr_distance.size(); i++)
	{
		if (arr_distance[i] < min_distance) {

			min_distance = arr_distance[i];
			index_of_the_closest_base = i;

			demonBasesAccordingToDistances.push_back((DemonBase*)demonBaseArray[i]);
		}
	}

	return demonBasesAccordingToDistances[index_of_the_closest_base];
}

void Demon::RestrictForTheBaseBoundaries(Demon* demon) {

	POINT demonPosition;
	demonPosition.x = demon->GetMapPosition().x;
	demonPosition.y = demon->GetMapPosition().y;

	POINT demonBasePosition;
	demonBasePosition.x = demon->GetBase()->GetMapPosition().x;
	demonBasePosition.y = demon->GetBase()->GetMapPosition().y;

	if (demonPosition.x > demonBasePosition.x && demonPosition.x < demonBasePosition.x) {

		POINT changedDemonPosition;
		changedDemonPosition.x = demonBasePosition.x;
		changedDemonPosition.y = demonPosition.y;
		demon->SetMapPosition(changedDemonPosition);
	}

	if (demonPosition.y > demonBasePosition.y && demonPosition.y < demonBasePosition.y) {

		POINT changedDemonPosition;
		changedDemonPosition.x = demonPosition.x;
		changedDemonPosition.y = demonBasePosition.y;
		demon->SetMapPosition(changedDemonPosition);
	}

}