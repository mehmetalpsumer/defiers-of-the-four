//-----------------------------------------------------------------
// Character Object
// C++ Header - Character.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include <string>
#include <stack>
#include <vector>
#include "Sprite.h"

/*#ifndef SPRITE_H
#define SPRITE_H
#endif*/ // !SPRITE_H

using std::stack;
using std::vector;
typedef vector<vector<int>> Map;
//class Sprite;

//-----------------------------------------------------------------
// Class data
//-----------------------------------------------------------------
enum AI_TASK {
	AT_IDLE,
	AT_ROAM,
	AT_FOLLOW,
	AT_ATTACK
};
enum ControlStatus {
	PLAYER_1,
	PLAYER_2,
	AI
};
//-----------------------------------------------------------------
// Character Class
//-----------------------------------------------------------------
class Character {
	protected:
		std::string name;
		std::string description;
		Sprite		*sprite;
		Sprite		*menuSprite;
		int			healthPoint;
		int			maxHealthPoint;
		int			speed;
		POINT		mapPosition;
		bool		firstCreated = true;
		POINT		fireDirection;
		int			fireSpeed;
		int			fireDelay;
		int			curFireDelay;
		vector<Character*> currentTargets;
		stack<POINT> path;
		Character *target;
		AI_TASK task;
		bool isRobot;
		bool ready;

	public:
		// Constructor(s)/Destructor
		Character(std::string _name, std::string _description, Sprite* _sprite, Sprite *_menuSprite, 
			int healthPoint, int _speed, POINT _mapPosition, int _fireSpeed);
		virtual ~Character();

		// Overload operator
		bool operator==(const Character& other) {
			return sprite->GetPosition().left == other.sprite->GetPosition().left
				&& sprite->GetPosition().top == other.sprite->GetPosition().top
				&& sprite->GetPosition().right == other.sprite->GetPosition().right
				&& sprite->GetPosition().bottom == other.sprite->GetPosition().bottom;
		}

		// General methods
		inline void ClearPath() { while (!path.empty()) path.pop(); };
		inline void TakeHit(int _damage) { healthPoint -= _damage; };
		inline void Heal(int _healAmount) { 
			healthPoint += _healAmount;

			if (healthPoint > maxHealthPoint) {
				healthPoint = maxHealthPoint;
			}
		}
		inline void Move() {
			if (path.empty()) return;

			POINT next = (POINT)path.top();			
			POINT current = { sprite->GetPosition().left, sprite->GetPosition().top };

			int dy = next.y - current.y;
			int dx = next.x - current.x;
			ready = false;
			if (dx == 0 && dy == 0) {
				sprite->SetPosition(next);
				path.pop();
				ready = true;
			}
			else if (dy != 0 && abs(dy) <= speed) {
				current.y = next.y;
				sprite->SetPosition(current);
			} 
			else if (dx != 0 && abs(dx) <= speed) {
				current.x = next.x;
				sprite->SetPosition(current);
			}
			else if (abs(dx) > abs(dy)) {
				current.x += speed * (dx / abs(dx));
				sprite->SetPosition(current);
			}
			else {
				current.y += speed * (dy / abs(dy));
				sprite->SetPosition(current);			
			}
		};
		virtual void Update();

		// Accessor methods
		std::string GetName() { return name; };
		std::string GetDescription() { return description; };
		Sprite*		GetSprite() { return sprite; };
		Sprite*		GetMenuSprite() { return menuSprite; };
		int			GetHealthPoint() { return healthPoint; };
		int			GetMaxHealthPoint() { return maxHealthPoint; };
		int			GetSpeed() { return speed; };
		void		SetSpeed(int _speed) { speed = _speed; };
		int			GetFireSpeed() { return fireSpeed; };
		void		SetFireSpeed(int _fs) { fireSpeed = _fs; };
		POINT		GetFireDirection() { return fireDirection; };
		void		SetFireDirection(Character *closestEnemy) {
						POINT enemypoint;
						enemypoint.x = closestEnemy->GetMapPosition().x;
						enemypoint.y = closestEnemy->GetMapPosition().y;
						fireDirection.x = enemypoint.x-mapPosition.x;
						fireDirection.y = enemypoint.y-mapPosition.y;		
		};
		void		SetFireDirection(POINT pt) { fireDirection = pt; };
		int			GetCurFireDelay() { return curFireDelay; };
		void		SetCurFireDelay(int _d) { curFireDelay = _d; };
		int			GetFireDelay() { return fireDelay; };
		void		SetFireDelay(int _fd) { fireDelay = _fd; };
		POINT		GetMapPosition() { return mapPosition; };
		void		SetMapPosition(POINT _pos) { mapPosition = _pos; };
		BOOL		IsRobot() { return isRobot; };
		BOOL		IsReady() { return ready; }
		void		SetReady(BOOL _ready) { ready = _ready; };

		AI_TASK		GetTask() { return task; };
		void		SetTask(AI_TASK _at) { task = _at; };
		stack<POINT> GetPath() { return path; };
		Character*	GetTarget() { return target; };
		void		SetTarget(Character *_ch) { target = _ch; };
		void		SetPath(stack<POINT> _path) { path = _path; };
		bool		GetFirstCreated() { return firstCreated; };
		void		SetFirstCreated(bool _f) { firstCreated = _f; };
		vector<Character*>	GetCurrentTargets() { return currentTargets; };
		void			SetCurrentTargets(vector<Character*> _currentTargets) { currentTargets = _currentTargets; };
		int			getHealPoint() { return healthPoint; };

};
