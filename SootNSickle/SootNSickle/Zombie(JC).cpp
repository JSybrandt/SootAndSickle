#include "Zombie.h"
#include"SootNSickle.h"

Zombie::Zombie():ActorWithHealthBar(){
	edge.top = -32;
	edge.bottom = 32;
	edge.left = -12;
	edge.right = 12;
	collisionType = COLLISION_TYPE::BOX;
	colorFilter = zombieNS::COLOR;
	health = 500;
	setActive(false);
	target = false;
	shoot = false;
	type = GROUND;
	checked = false;
	targetEntity = nullptr;
}
Zombie::~Zombie(){}

bool Zombie::initialize(SootNSickle * g, int width, int height, int ncols,TextureManager *turretTM, TextureManager* hbTexM) {
	game = g;
	bool result = true;
	result = result && ActorWithHealthBar::initialize(g,width,height,ncols,turretTM,hbTexM);
	return result;
}


void Zombie::update(float frameTime)
{
	if(getActive())
	{
		ActorWithHealthBar::update(frameTime);
		if(health <= 0) {
			setActive(false);
			//audio->playCue(KILL1_CUE);
		}

		checked = false;
		VECTOR2 endLoc = getCenter()+(getVelocity()*zombieNS::SPEED*frameTime);
		//endLoc = game->getRealEndLoc(getCenter(),endLoc);
		setCenter(endLoc);
		if(targetEntity != nullptr) {
			VECTOR2 toTarget = targetEntity->getCenter() - getCenter();
			float dirtoTarget = atan2(toTarget.y,toTarget.x);
			float distSqrdtoTarget = D3DXVec2LengthSq(&toTarget);		

			if(distSqrdtoTarget < zombieNS::ENGAGE_DISTANCE_SQRD) {
				setVelocity(VECTOR2(0,0));
				if(weaponCooldown <= 0){
					weaponCooldown  = zombieNS::WEAPON_COOLDOWN;
					recoilCooldown = zombieNS::RECOIL_TIME;

					targetEntity->damage(25);

					animComplete = false;
					setCurrentFrame(0);
					//audio->playCue(PISTOL_CUE);
					if(!targetEntity->getActive())
						targetEntity = nullptr;
				}
			}
			else if(distSqrdtoTarget < zombieNS::CHASE_DISTANCE_SQRD) {
				vectorTrack(frameTime);
				VECTOR2 aim(targetEntity->getCenterX() - endLoc.x,targetEntity->getCenterY() - endLoc.y);
				float aimDir = atan2(aim.y,aim.x);
				
				if(velocity != VECTOR2(0,0)) {
					setRadians(atan2(velocity.y,velocity.x));
					ActorWithHealthBar::update(frameTime);
				}
				else
					setRadians(aimDir);

			}

			//else {
			//	VECTOR2 aim(targetEntity->getCenterX() - endLoc.x,targetEntity->getCenterY() - endLoc.y);
			//	float aimDir = atan2(aim.y,aim.x);
			//	setRadians(aimDir+PI/2);
			//}
		}
		else {
			vectorTrack(frameTime);
			VECTOR2 aim(path.getCenterX() - endLoc.x,path.getCenterY() - endLoc.y);
			float aimDir = atan2(aim.y,aim.x);

			if(velocity != VECTOR2(0,0)) {
				setRadians(atan2(velocity.y,velocity.x));
				ActorWithHealthBar::update(frameTime);
			}

		}

		weaponCooldown -= frameTime;
		if(weaponCooldown < 0) weaponCooldown =0;

		recoilCooldown -= frameTime;
		if(recoilCooldown < 0)recoilCooldown = 0;

		if(targetEntity != nullptr && !targetEntity->getActive()) shoot = false;
	}

}

void Zombie::evade(float frameTime)
{
	VECTOR2 disp = targetEntity->getCenter()-getCenter();
	D3DXVec2Normalize(&disp,&disp);
	setVelocity(-disp);
}

void Zombie::deltaTrack(float frametime)
{

	VECTOR2 v(0,0);

	if(targetEntity->getCenterX() < getCenterX())
		v.x = -1;
	if(targetEntity->getCenterX() > getCenterX())
		v.x = 1;

	if(targetEntity->getCenterY() < getCenterY())
		v.y = -1;
	if(targetEntity->getCenterY() > getCenterY())
		v.y = 1;

	D3DXVec2Normalize(&v, &v);
	setVelocity(v);

}
void Zombie::vectorTrack(float frametime)
{
	if(targetEntity != nullptr && targetEntity->getActive()) {
		VECTOR2 disp = targetEntity->getCenter()-getCenter();
		D3DXVec2Normalize(&disp,&disp);
		setVelocity(disp);
	}
	else {
		VECTOR2 disp = path.getCenter()-getCenter();
		D3DXVec2Normalize(&disp,&disp);
		setVelocity(disp);
	}

}

void Zombie::ai(float frameTime, ActorWithHealthBar &t)
{ 
	if(active && t.getActive() && !checked) {
		float rad = 0;
		if(targetEntity != nullptr && target) { //If previous target is still active and within range
			VECTOR2 toTarget = targetEntity->getCenter() - getCenter();
			float distSqrdToOldTarget = D3DXVec2LengthSq(&toTarget);

			if(distSqrdToOldTarget > personalEngageDistanceSQRD || !targetEntity->getActive()) {
				shoot = false;
				target = false;
			}
			else {
				checked = true;
				return;							//No need to switch targets, continue firing

			}
		}
		if(!target) {
			VECTOR2 toTarget = t.getCenter() - getCenter();
			float distSqrdToNewTarget = D3DXVec2LengthSq(&toTarget);

			if(distSqrdToNewTarget < personalChaseDistanceSQRD) {
				targetEntity = &t;
				checked = true;
				return;
			}
		}
	}

	return;
}

void Zombie::create(VECTOR2 loc)
{
	target = false;
	shoot = false;
	velocity = VECTOR2(0,0);
	targetEntity = nullptr;

	setActive(true);
	setCenter(loc);
	setHealth(100);

	personalChaseDistanceSQRD = /*(rand01()+0.5) *  */zombieNS::CHASE_DISTANCE_SQRD;
	personalEngageDistanceSQRD =/* (rand01()+0.5) * */zombieNS::ENGAGE_DISTANCE_SQRD;
}

void Zombie::nextWaypoint() {
	if(path.getChild() != nullptr)
		setWaypoint(path.getChild());
}

Waypoint* Zombie::getWaypoint() {
	return &path;
}

void Zombie::setWaypoint(Waypoint* wp) {
	path = *wp;
}