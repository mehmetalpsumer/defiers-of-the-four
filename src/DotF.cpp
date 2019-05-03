//-----------------------------------------------------------------
// Defiers of the Four Application
// C++ Source - DotF.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "DotF.h"
#include <string> 

#include <cstdlib>
#include <ctime>
#include <random>

//-----------------------------------------------------------------
// Game Engine Functions
//-----------------------------------------------------------------

BOOL GameInitialize(HINSTANCE hInstance)
{
	// Create the game engine
	_pGame = new GameEngine(hInstance, (LPTSTR) TEXT("Defiers of the Four"),
		(LPTSTR) TEXT("Defiers of the Four"), (WORD) IDI_DOTF, (WORD) IDI_DOTF_SM, 1024, 768);
	if (_pGame == NULL)
		return FALSE;

	


	// Set the frame rate
	_pGame->SetFrameRate(30);

	// Store the instance handle
	_hInstance = hInstance;

	return TRUE;
}

void GameStart(HWND hWindow)
{
	//Create Map
	
   
	//map  maps[8];// = CreateMap();
	for (size_t i = 0; i < 8; i++)
	{
		if (i == 0) {
			
			map  newmap = CreateMap(true);
			maps[i] = newmap;
		}
		else
		{
			map  newmap = CreateMap(false);
			maps[i] = newmap;
		}
	}
	


	// Seed the random number generator
	srand(GetTickCount());
	HDC hDC = GetDC(hWindow);
	// Create the offscreen device context and bitmap
	_hOffscreenDC = CreateCompatibleDC(GetDC(hWindow));
	_hOffscreenBitmap = CreateCompatibleBitmap(GetDC(hWindow),
		_pGame->GetWidth(), _pGame->GetHeight());
	SelectObject(_hOffscreenDC, _hOffscreenBitmap);

	_robotbmp = new Bitmap(hDC, IDB_ROBOT, _hInstance);
	_pWallBitmap = new Bitmap(hDC, IDB_WALL, _hInstance);
	_pEnemyBaseBitmap = new Bitmap(hDC, IDB_ENEMYCENTER, _hInstance);
	// Create the golf ball sprites
	
	int _pEnemyBase_c = 0;
	int _pWalls_c = 0;
	for (size_t i = 0; i < maps[0].size(); i++)
	{
		for (size_t j = 0; j < maps[0][0].size(); j++)
		{
			if (maps[0][i][j]==1) // enemy center   // soldan sağa indexler 0: hangi ekranda olduğu ,2 :row , 3 : col
			{
				_pEnemyBase[_pEnemyBase_c] = new Sprite(_pEnemyBaseBitmap);

				_pEnemyBase[_pEnemyBase_c]->SetPosition(j*32,i*32);
				number_of_enemyCenter++;
				_pEnemyBase_c++;
			}
			if (maps[0][i][j] == 2) // wall
			{
				_pWalls[_pWalls_c] = new Sprite(_pWallBitmap);

				_pWalls[_pWalls_c]->SetPosition(j*32,i*32);
				_pWalls_c++;
			
			}
		}
	}
	
	maps[0][0][0] = 1;
	maps[0][5][17] = 1;
	_robot[0] = new Sprite(_pEnemyBaseBitmap);

	_robot[0]->SetPosition(0 * 32, 0 * 32);

	_robot[1] = new Sprite(_pEnemyBaseBitmap);

	_robot[1]->SetPosition(5 * 32, 17 * 32);
	/*
	RECT p1 = _robot[0]->GetPosition();
	RECT p2 = _robot[1]->GetPosition();
	POINT p11;
	POINT p12;
	p11.x = 0;
	p11.y = 0;
	p12.x = 5;
	p12.y = 17;
	queue <POINT> pf = pathFinding(p12, p11, maps[0], true);
	while (pf.size() > 0) {
		_robot[0]->SetPosition(pf.front().x, pf.front().y);
		pf.pop();
	}*/
	
}
//game_objects_positions
map CreateMap(bool _firstLevel)
{
	// Draw the sprites in the sprite vector
	int number_of_wall = 100;
	int wall_lenght;// yan yana gelebilecek duvar sayısı
	int number_of_enemy_center;
	int wall_width = 32;
	int wall_height = 32;
	int enemy_center_width = 32;
	int enemy_center_height = 32;
	const int screen_width = 1024; // column =x  
	const int screen_height = 700; // row =y
	srand(time(NULL));
	number_of_enemy_center = rand()%10+3;     //range 1 to 20
	int map_row = 0;
	if (_firstLevel)
	{
		map_row = 20;
	}
	else {
		map_row = 24;
	}
	int map_col = 32;
	vector< vector<int> > map(map_row, vector<int>(map_col, 0));
	vector< vector<int> > wall_positions(number_of_wall, vector<int>(2, 0)); // duvarların ve enemy centerların başlangıç noktalarını sol üst köşe referans noktası olarak tutar. 
	vector< vector<int> > enemy_center_positions(number_of_enemy_center, vector<int>(2, 0)); // duvarların ve enemy centerların başlangıç noktalarını sol üst köşe referans noktası olarak tutar. 
	game_objects_positions objects_positions(2);
	// 0 empty
	//1 enemy center
   // 2 wall
	int array_counter = 0;
	while (number_of_enemy_center > 0) {


		int row_a[] = { 4,11,18 };
		int col_a[] = { 4,11,18,25 };
		srand(time(NULL));
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng3(rd()); // seed the generator
		std::uniform_int_distribution<> distr3(0, 3);
		int col = distr3(eng3); //rand() % 5; //4,11,17,23,29
		col = col_a[col];
		srand(time(NULL));
		std::random_device rd2; // obtain a random number from hardware
		std::mt19937 eng4(rd2()); // seed the generator
		std::uniform_int_distribution<> distr4(0,2);
		int row = distr4(eng4); //4,11,17,23
		row = row_a[row];



		bool avaliable_for_enemyC = false;

		while (!avaliable_for_enemyC)
		{

			if (map[row][col] != 0)
			{
				std::random_device rd; // obtain a random number from hardware
				std::mt19937 eng3(rd()); // seed the generator
				std::uniform_int_distribution<> distr3(0, 3);
				col = distr3(eng3); //rand() % 5; //4,11,17,23,29
				col = col_a[col];
				srand(time(NULL));
				std::random_device rd2; // obtain a random number from hardware
				std::mt19937 eng4(rd2()); // seed the generator
				std::uniform_int_distribution<> distr4(0, 2);
				row = distr4(eng4);
				row = row_a[row];
				break;
			}
			else {
				avaliable_for_enemyC = true;
				enemy_center_positions[array_counter][0] = row*32;
				enemy_center_positions[array_counter][1] = col*enemy_center_height;
				array_counter++;
				number_of_enemy_center--;
				map[row][col] = 1;
			}


		}

	}
	array_counter = 0;
	while (number_of_wall > 0) {
		wall_lenght = rand() % 5 + 1;//range 1 to 5
		int wall_position;// = rand() % 4;
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng3(rd()); // seed the generator
		std::uniform_int_distribution<> distr3(0, 100);
		wall_position = distr3(eng3);
		if (number_of_wall - wall_lenght < 0) {
			wall_lenght = number_of_wall;
			number_of_wall -= wall_lenght;
		}
		else {
			number_of_wall = number_of_wall - wall_lenght;
		}
		if (wall_position < 65) //right
		{
			std::random_device rd; // obtain a random number from hardware
			std::mt19937 eng3(rd()); // seed the generator
			std::uniform_int_distribution<> distr3(0, map_col-1);
			int col1 = distr3(eng3);

			srand(time(NULL));
			std::random_device rd2; // obtain a random number from hardware
			std::mt19937 eng4(rd2());
			std::uniform_int_distribution<> distr4(0, map_row-1);
			int row1 = distr4(eng4);


			bool avaliable_for_wall = false;

			while (!avaliable_for_wall)
			{
				if ((wall_lenght + col1) < map_col)
				{

					avaliable_for_wall = true;

					for (int j = col1;j < (col1 + wall_lenght) && avaliable_for_wall; j++)
					{
						if (map[row1][j] != 0)
						{
							std::mt19937 eng3(rd()); // seed the generator
							std::uniform_int_distribution<> distr3(0, map_col - 1);
							col1 = distr3(eng3);
							srand(time(NULL));
							std::random_device rd2; // obtain a random number from hardware
							std::mt19937 eng4(rd2());
							std::uniform_int_distribution<> distr4(0, map_row-1);
							row1 = distr4(eng4);
							avaliable_for_wall = false;
							break;
						}
					}


				}
				else {
					std::mt19937 eng3(rd()); // seed the generator
					std::uniform_int_distribution<> distr3(0, map_col - 1);
					col1 = distr3(eng3);
					srand(time(NULL));
					std::random_device rd2; // obtain a random number from hardware
					std::mt19937 eng4(rd2());
					std::uniform_int_distribution<> distr4(0, map_row-1);
					row1 = distr4(eng4);
				}

			}
			for (size_t i = 0; i < wall_lenght; i++)
			{
				wall_positions[array_counter][0] = row1 * wall_width;
				wall_positions[array_counter][1] = (col1 + i)*wall_height;
				array_counter++;
			}
			for (int j = col1;j < (col1 + wall_lenght); j++)
			{
				map[row1][j] = 2;
			}

		}

		else if (wall_position >= 65) // up
		{

			std::mt19937 eng3(rd()); // seed the generator
			std::uniform_int_distribution<> distr3(0, map_col - 1);
			int col2 = distr3(eng3);
			srand(time(NULL));
			std::random_device rd2; // obtain a random number from hardware
			std::mt19937 eng4(rd2());
			std::uniform_int_distribution<> distr4(0, 20);
			int row2 = distr4(eng4);
			bool avaliable_for_wall = false;

			while (!avaliable_for_wall)
			{
				if ((wall_lenght + row2) < map_row)
				{

					avaliable_for_wall = true;

					for (int j = row2;j < (row2 + wall_lenght) && avaliable_for_wall; j++)
					{
						if (map[j][col2] != 0)
						{
							std::mt19937 eng3(rd()); // seed the generator
							std::uniform_int_distribution<> distr3(0, map_col - 1);
							col2 = distr3(eng3);
							srand(time(NULL));
							std::random_device rd2; // obtain a random number from hardware
							std::mt19937 eng4(rd2());
							std::uniform_int_distribution<> distr4(0, map_row-1);
							row2 = distr4(eng4);
							avaliable_for_wall = false;
							break;
						}
					}


				}
				else {
					std::mt19937 eng3(rd()); // seed the generator
					std::uniform_int_distribution<> distr3(0, map_col - 1);
					col2 = distr3(eng3);
					srand(time(NULL));
					std::random_device rd2; // obtain a random number from hardware
					std::mt19937 eng4(rd2());
					std::uniform_int_distribution<> distr4(0, map_row-1);
					row2 = distr4(eng4);
				}
			}
			for (size_t i = 0; i < wall_lenght; i++)
			{
				wall_positions[array_counter][0] = (row2 + i) * wall_width;
				wall_positions[array_counter][1] = col2 * wall_height;
				array_counter++;
			}
			for (int j = row2;j < (row2 + wall_lenght); j++)
			{
				map[j][col2] = 2;
			}
		}




	}


	objects_positions[0] = enemy_center_positions;
	objects_positions[1] = wall_positions;
	return map;

}
void GameEnd()
{
	// Cleanup the offscreen device context and bitmap
	DeleteObject(_hOffscreenBitmap);
	DeleteDC(_hOffscreenDC);

	// Cleanup the sprites
	_pGame->CleanupSprites();

	// Cleanup the game engine
	delete _pGame;
}

void GameActivate(HWND hWindow)
{
}

void GameDeactivate(HWND hWindow)
{
}

void GamePaint(HDC hDC)
{
	// Draw the background


	// Draw the sprites
	_pGame->DrawSprites(hDC);

	for (int i = 0; i < 100; i++)
		_pWalls[i]->Draw(hDC);
	for (int i = 0; i < number_of_enemyCenter; i++)
		_pEnemyBase[i]->Draw(hDC);
	for (int i = 0; i < 2; i++)
		_robot[i]->Draw(hDC);

}

void GameCycle()
{
	// Update the sprites
	_pGame->UpdateSprites();

	// Obtain a device context for repainting the game
	HWND  hWindow = _pGame->GetWindow();
	HDC   hDC = GetDC(hWindow);

	// Paint the game to the offscreen device context
	GamePaint(_hOffscreenDC);

	// Blit the offscreen bitmap to the game screen
	BitBlt(hDC, 0, 0, _pGame->GetWidth(), _pGame->GetHeight(),
		_hOffscreenDC, 0, 0, SRCCOPY);

	// Cleanup
	ReleaseDC(hWindow, hDC);

	
	//pf.front();
}

void HandleKeys()
{
	if (GetAsyncKeyState(VK_LEFT) < 0)
	{
		// Move left
		/*ptVelocity.x = max(ptVelocity.x - 32, -4);
		_pCarSprite->SetVelocity(ptVelocity);*/
	}
}

void MouseButtonDown(int x, int y, BOOL bLeft)
{

}

void MouseButtonUp(int x, int y, BOOL bLeft)
{
}

void MouseMove(int x, int y)
{

}

void HandleJoystick(JOYSTATE jsJoystickState)
{
}

BOOL SpriteCollision(Sprite* pSpriteHitter, Sprite* pSpriteHittee)
{
	// Swap the sprite velocities so that they appear to bounce
	POINT ptSwapVelocity = pSpriteHitter->GetVelocity();
	pSpriteHitter->SetVelocity(pSpriteHittee->GetVelocity());
	pSpriteHittee->SetVelocity(ptSwapVelocity);
	return TRUE;
}
queue <POINT> pathFinding(POINT targetposition,POINT startingposition,map currentmap,bool first_map) { // map_index hangi harita olduğu 1,2..8

	bool reach_starting_point = false;
	queue <POINT> adjacents;
	queue <int> weights;
	adjacents.push(targetposition);
	weights.push(0);
	int current_num = -1;
	int row;
	if (first_map)
	{
		row = 20;
	}
	else {
		row = 24;
	}
	
	
	int arr_x[3] = { -1,0,1 };
	int arr_y[3] = { -1,0,1 };
	while (!reach_starting_point) {
		
		if (adjacents.size() < 1)
			break;
		if (adjacents.front().x== startingposition.x&&adjacents.front().y== startingposition.y)
		{
			reach_starting_point = true;
			break;
		}
		
		for (size_t i = 0; i < 3&&!reach_starting_point; i++)
		{
			for (size_t j = 0; j < 3&&!reach_starting_point; j++)
			{
				if (!(i == 0 && j == 0)) {
					if (adjacents.size()>0)
					{
											
						if (adjacents.front().x + arr_x[i] < row && adjacents.front().x + arr_x[i]>0 && adjacents.front().y + arr_y[j] < 32 && adjacents.front().y + arr_y[j] > 0)
						{
							if (currentmap[adjacents.front().x + arr_x[i]][adjacents.front().y + arr_y[j]] == 0)
							{
								currentmap[adjacents.front().x + arr_x[i]][adjacents.front().y + arr_y[j]] = current_num;
								POINT np;
								np.x = adjacents.front().x + arr_x[i];
								np.y = adjacents.front().y + arr_y[j];
								adjacents.push(np);
								weights.push(current_num);
							}
							else if (adjacents.front().x + arr_x[i]==startingposition.x&&adjacents.front().y + arr_y[j]==startingposition.y) {
								currentmap[adjacents.front().x + arr_x[i]][adjacents.front().y + arr_y[j]] = current_num;
								POINT np;
								np.x = adjacents.front().x + arr_x[i];
								np.y = adjacents.front().y + arr_y[j];
								adjacents.push(np);
								weights.push(current_num);
								reach_starting_point = true;
								break;
							}

						}
				}
				}

			}
		}
		int temp1 = weights.front();
		weights.pop();
		adjacents.pop();
		int temp2;
		if (weights.size()>0)
		{
			temp2 = weights.front();
			if (temp1 != temp2)
			{
				current_num--;
			}
		}
		
		
		
			
	}
	
	   bool reach_target_point = false;
	POINT currentpoint;
	queue <POINT> finalroute;
	currentpoint=startingposition;
	finalroute.push(startingposition);
	while (!reach_target_point) {

		if (currentpoint.x == targetposition.x&&currentpoint.y == targetposition.y)
		{
			reach_target_point = true;
			break;
		}
		int temp_x = 0;
		int temp_y = 0;
		int minpoint = -10000;
		for (size_t i = 0; i < 3&&!reach_target_point; i++)
		{
			for (size_t j = 0; j < 3&&!reach_target_point; j++)
			{
				if (!(i == 0 && j == 0)) {
					if (currentpoint.x + arr_x[i] < row&& currentpoint.x + arr_x[i] > 0 && currentpoint.y + arr_y[j] < 32&& currentpoint.y + arr_y[j] > 0)
					{
						if (currentmap[currentpoint.x + arr_x[i]][currentpoint.y + arr_y[j]] <0) // eksi değerlere bakılır .
						{
							if (currentmap[currentpoint.x + arr_x[i]][currentpoint.y + arr_y[j]]>minpoint)
							{
								minpoint = currentmap[currentpoint.x + arr_x[i]][currentpoint.y + arr_y[j]];
								temp_x = currentpoint.x + arr_x[i];
								temp_y= currentpoint.y + arr_y[j];
							}
											
						}
						else if (currentpoint.x + arr_x[i] == targetposition.x&&currentpoint.y+ arr_y[j] == targetposition.y) {
							temp_x = currentpoint.x + arr_x[i];
							temp_y = currentpoint.y + arr_y[j];
							reach_target_point = true;
							break;
						}

					}
				}

			}
		}
		
		POINT np;
		np.x = temp_x;
		np.y = temp_y;
		currentpoint = np;
		finalroute.push(np);


	}
	return finalroute;
}

POINT attack(POINT robotposition, map currentmap, bool first_map) {
	POINT enemy_position;
	enemy_position.x = -1; // eğer -1 değilse range içinde düşman vardır.
	int row;
	if (first_map)
	{
		row = 20;
	}
	else {
		row = 24;
	}

	int row_range = 2;
	int col_range = 2;
	int arr_x[5] = { -2,-1,0,1,2 };
	int arr_y[5] = { -2,-1,0,1,2 };
	bool in_range = false;
			
		for (size_t i = 0; i < 5 && !in_range; i++)
		{
			for (size_t j = 0; j < 5 && !in_range; j++)
			{
				if (!(i == 0 && j == 0)) {
					
						if (robotposition.x + arr_x[i] < row && robotposition.x + arr_x[i]>0 && robotposition.y + arr_y[j] < 32 && robotposition.y + arr_y[j] > 0)
						{
							if (currentmap[robotposition.x + arr_x[i]][robotposition.y + arr_y[j]] == 3) // enemy 3
							{
								enemy_position.x = robotposition.x + arr_x[i];
								enemy_position.y = robotposition.y + arr_y[j];
								in_range = true;
								break;
							}
							

						}
					
				}

			}
		}
		

		return enemy_position;


	
}