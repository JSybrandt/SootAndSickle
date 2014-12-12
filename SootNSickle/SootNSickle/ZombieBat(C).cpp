#include "ZombieBat.h"
#include"SootNSickle.h"

ZombieBat::ZombieBat():ActorWithHealthBar(){
	edge.top = -32;
	edge.bottom = 32;
	edge.left = -12;
	edge.right = 12;
	collisionType = COLLISION_TYPE::BOX;
	colorFilter = zombiebatNS::COLOR;
	setHealth(250);
	personalSpeed = zombiebatNS::SPEED;
	setActive(false);
	target = false;
	shoot = false;
	type = GROUND;
	checked = false;
	targetEntity = nullptr;
}
ZombieBat::~ZombieBat(){}

bool ZombieBat::initialize(SootNSickle * g, int width, int height, int ncols,TextureManager *turretTM, TextureManager* hbTexM) {
	game = g;
	bool result = true;
	result = result && ActorWithHealthBar::initialize(g,width,height,ncols,turretTM,hbTexM);
	return result;
}


void ZombieBat::update(float frameTime)
{
	if(getActive())
	{
		ActorWithHealthBar::update(frameTime);
		if(health <= 0) {
			setActive(false);
			//audio->playCue(KILL1_CUE);
		}

		checked = false;
		VECTOR2 endLoc = getCenter()+(getVelocity()*personalSpeed*frameTime);
		//endLoc = game->getRealEndLoc(getCenter(),endLoc);
		setCenter(endLoc);
		if(targetEntity != nullptr && targetEntity->getActive()) {
			VECTOR2 toTarget = targetEntity->getCenter() - getCenter();
			float dirtoTarget = atan2(toTarget.y,toTarget.x);
			float distSqrdtoTarget = D3DXVec2LengthSq(&toTarget);		

			if(distSqrdtoTarget < personalEngageDistanceSQRD) {
				setVelocity(VECTOR2(0,0));
				if(weaponCooldown <= 0){
					weaponCooldown  = zombiebatNS::WEAPON_COOLDOWN;
					recoilCooldown = zombiebatNS::RECOIL_TIME;

					targetEntity->damage(zombiebatNS::DAMAGE);

					animComplete = false;
					setCurrentFrame(0);
					//audio->playCue(PISTOL_CUE);
					if(!targetEntity->getActive())
						targetEntity = nullptr;
				}
			}
			else if(distSqrdtoTarget < personalChaseDistanceSQRD) {
				vectorTrack(frameTime);
				
				if(velocity != VECTOR2(0,0)) {
					ActorWithHealthBar::update(frameTime);
				}

			}
		}
		else {
			vectorTrack(frameTime);

			if(velocity != VECTOR2(0,0)) {
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

void ZombieBat::evade(float frameTime)
{
	VECTOR2 disp = targetEntity->getCenter()-getCenter();
	D3DXVec2Normalize(&disp,&disp);
	setVelocity(-disp);
}

void ZombieBat::deltaTrack(float frametime)
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
void ZombieBat::vectorTrack(float frametime)
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

bool ZombieBat::ai(float frameTime, ActorWithHealthBar &t) { 
	if(active && t.getActive() && !checked) {
		if(targetEntity != nullptr && targetEntity->getActive()) { //If previous target is still active and within range
				checked = true;
				return true;							//No need to switch targets, continue firing
		}
		else if(targetEntity == nullptr || !targetEntity->getActive()) {
			VECTOR2 toTarget = t.getCenter() - getCenter();
			float distSqrdToNewTarget = D3DXVec2LengthSq(&toTarget);

			if(distSqrdToNewTarget < personalChaseDistanceSQRD) {
				targetEntity = &t;
				checked = true;
				return true;
			}
		}
		return false;
	}
	return false;
}

void ZombieBat::create(VECTOR2 loc)
{
	target = false;
	shoot = false;
	velocity = VECTOR2(0,0);
	targetEntity = nullptr;

	setActive(true);
	setCenter(loc);
	setHealth(100);

	personalChaseDistanceSQRD = randmax(2000)+zombiebatNS::CHASE_DISTANCE_SQRD;
	personalEngageDistanceSQRD = randmax(5000)+zombiebatNS::ENGAGE_DISTANCE_SQRD;
	personalSpeed = randmax(25)+zombiebatNS::SPEED;
}

void ZombieBat::nextWaypoint() {
	if(path.getChild() != nullptr)
		setWaypoint(path.getChild());
}

Waypoint* ZombieBat::getWaypoint() {
	return &path;
}

void ZombieBat::setWaypoint(Waypoint* wp) {
	path = *wp;
}