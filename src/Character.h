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
#include <queue>
#include "Sprite.h"
/*#ifndef SPRITE_H
#define SPRITE_H
#endif*/ // !SPRITE_H

using std::queue;
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

		POINT		fireDirection;
		int			fireSpeed;
		int			fireDelay;
		int			curFireDelay;

		queue<POINT> path;
		Character *target;
		AI_TASK task;
		POINT nextPosition;


	public:
		// Constructor(s)/Destructor
		Character(std::string _name, std::string _description, Sprite* _sprite, Sprite *_menuSprite, 
			int _healthPoint, int _speed, POINT _mapPosition, int _fireSpeed);
		virtual ~Character();

		// General methods
		inline void TakeHit(int _damage) { healthPoint -= _damage; };
		inline void Heal(int _healAmount) { 
			healthPoint += _healAmount;

			if (healthPoint > maxHealthPoint) {
				healthPoint = maxHealthPoint;
			}
		}
		inline void Move() {
			if (path.empty()) return;

			POINT next = (POINT)path.front();
			POINT current = { sprite->GetPosition().left, sprite->GetPosition().top };
			next.x *= 32;
			next.y *= 32;

			if (next.x == current.x && next.y == current.y) {
				path.pop();
				if (path.empty()) return;
				next = (POINT)path.front();
				next.x *= 32;
				next.y *= 32;
			}

			int dy = next.y - current.y;
			int dx = next.x - current.x;

			if (abs(dy + dx) <= speed) {
				// Reached to the position, move to there and pop
				if (dx == 0 && dy == 0) {
					sprite->SetPosition(next);
					path.pop();
				}
				else if (dy == 0) {
					current.x = next.x;
					sprite->SetPosition(current);
				}
				else if (dx == 0) {
					current.y = next.y;
					sprite->SetPosition(current);
				}
			}
			else {
				if (abs(dy) > abs(dx)) {
					current.y += speed * (dy/abs(dy));
					sprite->SetPosition(current);
				}
				else {
					current.x += speed * (dx / abs(dx));
					sprite->SetPosition(current);
				}
			}
		};

		// Accessor methods
		std::string GetName() { return name; };
		std::string GetDescription() { return description; };
		Sprite*		GetSprite() { return sprite; };
		Sprite*		GetMenuSprite() { return menuSprite; };
		int			GetHealthPoint() { return healthPoint; };
		int			GetMaxHealthPoint() { return maxHealthPoint; };
		int			GetSpeed() { return speed; };
		int			GetFireSpeed() { return fireSpeed; };
		void		SetFireSpeed(int _fs) { fireSpeed = _fs; };
		POINT		GetFireDirection() { return fireDirection; };
		void		SetFireDirection(POINT _fd) { fireDirection = _fd; };
		int			GetCurFireDelay() { return curFireDelay; };
		void		SetCurFireDelay(int _d) { curFireDelay = _d; };
		int			GetFireDelay() { return fireDelay; };
		POINT		GetMapPosition() { return mapPosition; };

		AI_TASK GetTask() { return task; };
		void SetTask(AI_TASK _at) { task = _at; };
		queue<POINT> GetPath() { return path; };
		void SetPath(queue<POINT> _path) { path = _path; };
		Character* GetTarget() { return target; };
		void SetTarget(Character *_ch) { target = _ch; };

		
};
