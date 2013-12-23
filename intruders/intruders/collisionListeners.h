#include "Hero.h"
#include "enemy.h"
#include<Box2D\Box2D.h>


bool enemyTankCollide(b2Contact* contact, EnemySprite*& enemyEntity, AnimatedSprite*& tankEntity);
void enemyTankAlert();

b2World* world;
std::set<EnemySprite*> enemiesScheduledForRemoval;
std::set<b2CircleShape*> bombsScheduledForRemoval;
EnemySprite* b1;
EnemySprite* b2;
int score = 0;
bool flagg1=false, flagg2=false;
int health=5;
/* LISTENERS FOR COLLISION START */
class MyContactListener : public b2ContactListener
  {
    
	void BeginContact(b2Contact* contact2) {
		AnimatedSprite* tankEntity;
        EnemySprite* enemyEntity;
        if ( enemyTankCollide(contact2,enemyEntity,tankEntity ) )
            enemyTankAlert();  // If enemy touch ground, it returns true.
	}
	  
	void EndContact(b2Contact* contact2) {
				bool flag1=false, flag2=false;
				
		


				//check if fixture A was a an enemy intruder
				void* bodyUserData1 = contact2->GetFixtureA()->GetBody()->GetUserData();	
				//check if fixture B was a enemy intruder
				void* bodyUserData2 = contact2->GetFixtureB()->GetBody()->GetUserData();
				if( bodyUserData1 ){
				flag1=static_cast<EnemySprite*>( bodyUserData1 )->Isenemy;
				if(flag1==true ){
			
				enemiesScheduledForRemoval.insert(static_cast<EnemySprite*>( bodyUserData1));
				score+=10;
				b2Fixture* tempfix=contact2->GetFixtureB();
				b2Body* tempbody=tempfix->GetBody();
				tempbody->SetGravityScale(9.8);
				//b2Fixture* tempf=tempbody->GetFixtureList();
				

					
				
				}

				
				if( bodyUserData2 ){
				flag2=static_cast<EnemySprite*>( bodyUserData2 )->Isenemy;
				if(flag2==true){
				enemiesScheduledForRemoval.insert(static_cast<EnemySprite*>( bodyUserData2));
				//score+=10;
				
				health--;
				cout<<"Health:"<<health;
				}
				}
				}
		}

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold){}
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){}
	
	 };  



void enemyTankAlert()
{
	health--;
	cout<<"Enemy reached tank";
}

/* LISTENERS FOR COLLISION END */
