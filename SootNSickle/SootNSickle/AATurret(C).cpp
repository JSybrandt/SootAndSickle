#include "Turret.h"

#include "SootNSickle.h"

using namespace turretNS;

AATurret::AATurret(): Turret() {
	radius = TURRET_RADIUS;
	collisionType = CIRCLE;
	base.setRadians(PI/4);
	checked = false;
	target = false;
	personalEngageDistanceSQRD = turretNS::ENGAGE_DISTANCE_SQRD;
	targetEntity = nullptr;
	active = false;
	weaponCooldown = 0;
	rebootCooldown = 0;
	damageType = GROUND;
	setCapacity(CAPACITY);
	setMaxHealth(HEALTH);
}

bool AATurret::initialize(SootNSickle * g, int width, int height, int ncols, TextureManager *turretTM, TextureManager *baseTM, TextureManager* hbTexM, TextDX * text) {
	game = g;
	bool result = true;
	result = result && Building::initialize(g,width,height,ncols,turretTM,hbTexM,text);
	result = result && base.initialize(g,BASE_WIDTH,BASE_HEIGHT,0,baseTM);
	return result;
}

void AATurret::update(float frametime) {
	if(getActive())
	{
		Building::update(frametime);

		if(getPower() && getStaff()>0)
		{

			checked = false;
			if(rebootCooldown > 0) {
				rebootCooldown -= frametime;
			}
			else if(targetEntity != nullptr && targetEntity->getActive()) {
				colorFilter = graphicsNS::WHITE;

				VECTOR2 toTarget = targetEntity->getCenter() - getCenter();
				float dirtoTarget = atan2(toTarget.y,toTarget.x);
				float distSqrdtoTarget = D3DXVec2LengthSq(&toTarget);
				float radians = getRadians();

				//if the player is close and in view
				if(distSqrdtoTarget < turretNS::ENGAGE_DISTANCE_SQRD)
				{

					//convert to principle arguments
					dirtoTarget = toPincipleArgument(dirtoTarget);
					radians = toPincipleArgument(radians);

					float diff = dirtoTarget - radians;

					diff = toPincipleArgument(diff);

					//if we got um
					if(abs(diff) <= turretNS::ROT_EPSILON)
					{
						setRadians(dirtoTarget);
						radians = getRadians();
					}
					//rotate towards him
					else 
					{
						if (diff < 0 )
						{
							rotVel = -turretNS::ROTATION_SPEED;
						}
						else if (diff > 0)
						{
							rotVel = turretNS::ROTATION_SPEED;
						}
						setRadians(radians+ rotVel*frametime);
					}

					//fire gun, he's nearby
					weaponCooldown -= frametime;
					if(weaponCooldown <= 0)
					{
						//VECTOR2 v1 = getCenter() + utilityNS::rotateVector(BULLET1_OFFSET,getRadians());
						//VECTOR2 v2 = getCenter() + utilityNS::rotateVector(BULLET2_OFFSET,getRadians());
						//game->spawnBullet(v1,radians,graphicsNS::RED,false);
						//game->spawnBullet(v2,radians,graphicsNS::RED,false);
						animComplete = false;
						game->spawnParticleCone(getCenter(),radians-PI,graphicsNS::GRAY, 25);
						//game->spawnParticleCone(getCenter()+BULLET2_OFFSET,radians-PI,graphicsNS::GRAY, 25);
						//game->spawnParticleCone(getCenter()+turretNS::BULLET2_OFFSET,radians,graphicsNS::RED);
						targetEntity->damage(25);
						setCurrentFrame(0);
						audio->playCue(SC_CANNON);
						weaponCooldown = turretNS::FIRE_RATE;
						//BLUB BLUB!============================================================================
					}
				}
				if(!targetEntity->getActive()) {
					targetEntity = nullptr;
					target = false;
				}
			}
			else
			{
				float radians = getRadians();
				if(radians > maxDir)
				{
					rotVel = -turretNS::ROTATION_SPEED;
				}
				if(radians < minDir)
				{
					//setRadians(minDir);
					rotVel = turretNS::ROTATION_SPEED;
				}
				else
					setRadians(radians+ rotVel*frametime);
			}

		}
	}
	//base.setCenter(getCenter());
	//base.update(frametime);
	//Image::update(frametime);


}

void AATurret::draw(VECTOR2 screenLoc) {
	if(getActive())
	{

		base.draw(screenLoc);

		Building::draw(screenLoc);

	}
}

void AATurret::create(VECTOR2 loc, float dir) {
	Building::create(loc);
	setActive(true);
	setRadians(PI/2);
	targetEntity = nullptr;
	minDir = dir - turretNS::ROTATION_WIDTH;
	maxDir = dir + turretNS::ROTATION_WIDTH;
	rotVel = turretNS::ROTATION_SPEED;
	setCenter(loc);
	base.setCenter(loc);
	weaponCooldown = 0;
	rebootCooldown = 0;
	colorFilter = graphicsNS::WHITE;
	heal(turretNS::HEALTH);

}

void AATurret::ai(float frameTime, ActorWithHealthBar &t) {
	if(active && t.getActive() && !checked) {
		float rad = 0;
		if(targetEntity != nullptr && targetEntity->getActive()) { //If previous target is still active and within range
			VECTOR2 toTarget = targetEntity->getCenter() - getCenter();
			float distSqrdToOldTarget = D3DXVec2LengthSq(&toTarget);

			if(distSqrdToOldTarget > personalEngageDistanceSQRD || !targetEntity->getActive()) {
				targetEntity = nullptr;
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

			if(distSqrdToNewTarget < personalEngageDistanceSQRD) {
				targetEntity = &t;
				checked = true;
				return;
			}
		}
	}

	return;
}

void AATurret::hit() {
	rebootCooldown = REBOOT_TIME;
	weaponCooldown = FIRE_RATE;
	colorFilter = graphicsNS::GRAY;
}

/*
BUGLIST:
Needs to properly lose target if it reactivates after target dies

*/