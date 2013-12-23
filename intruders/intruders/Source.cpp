/*Intruders By M.Shaheer , Siddique M.Butt and Yasir Ali*/
#include <iostream>
#include <string.h>
#include <fstream>
#include <time.h>
#include<Windows.h>
#include"wav.h"
#include "collisionListeners.h"
#include "Hero.h"
#include "enemy.h"
#include "bomb.h"
#include "menu.h"
#include "RGBA.h"
#include "pixMap.h"
#include <glut.h>

using namespace std;


#pragma region Function prototypes
	void pressKey(unsigned char key , int x, int y);
	//void bitmap_output(int x,int y,string s,void *font);
	void UpdateSpriteAnimation();
	void createGround();
	void drawFloor();
	void myTimer(int tt);
	void myTimer2(int t);
	void Write(char *string);
	void scoredisplay (int posx, int posy, int posz, int space_char, int scorevar);
	void gameOver();
	
#pragma endregion
#pragma region Box2d variable/object declarations
	AnimatedSprite* hero;
	AnimatedSprite* bird;
	AnimatedSprite* bird2;
	AnimatedSprite *bg , *fg ,*fg1 ,*menu;
	EnemySprite* enemy;
	EnemySprite *tempenemy1,*tempenemy2;
	b2CircleShape* c;
	b2Body *mybomb;
	b2CircleShape shape;
	
#pragma endregion
#pragma region Variable declarations
	RGBpixmap pix[1];
	GLdouble width , height;
	int currentAnim;
	int currentAnim_enemy,currentAnim_bird=1;
	int L = 0;
	int R = 800;
	int B = 0;
	int wd;
	int enemyposfirst= rand() % 1350+1380+1080;
	int birdposfirst= rand() % 1380+1280+600 ;
	int birdpossec= rand() % 1380+1280 ;
	int currentFramew=0;   
	char s[256];
	int n  = 10;
	bool ishit=false;
	float xangle=0;
	float speed=10,angle=(xangle)*3.141/180;
	void* bodyUserData1;
	bool drawFirstMethod = false,drawSecondMethod=true;
	void* bodyUserData2;
	bool pause =false;
	bool menuscreen =1;
	float box2dtimer =0.0;
	bool rightt;
	
#pragma endregion
#pragma region Vector containers for holding enemies and other assets
std::vector<EnemySprite*> enemies;
std::vector<AnimatedSprite*> birds;
std::vector<AnimatedSprite*> birds2;
#pragma endregion

MyContactListener listener;

void init(void)
{
		world=new b2World(b2Vec2(0.0,-9.8));	/* Instantiate a Box2d world with real world gravity */
		world->SetContactListener(&listener);	/* Register contact listener for the Box2d world */
		width  = 1366.0;						/* initial window width and height, */
		height = 768.0;							/* within which we draw. */

}

void mouse( int button, int state,int x,int y)
{
	
		   if(state==GLUT_DOWN)
		   {
			   if(box2dtimer)
			{
			   b2Vec2 pos = hero->m_body->GetPosition();
			   mybomb=addBomb(pos.x,(pos.y),8,true);
			   b2Vec2 vector = speed * b2Vec2(cos(angle), -sin(angle));
			   mybomb->SetLinearVelocity(vector);
			   PlayForegroundSound("shoot.wav");
		//	    //get the existing filter
		//	   b2Filter filter = mybomb->GetFixtureList()->GetFilterData();
  //
  ////change whatever you need to, eg.
  //filter.categoryBits = BOMB;
  //filter.maskBits = ENEMY;

  ////and set it back
  //mybomb->GetFixtureList()->SetFilterData(filter);
			   }  }
		  
}

void menumouse(int button, int state, int x, int y )
{
    //toggle draw modes
    if( state == GLUT_DOWN )
    {
		if( drawFirstMethod ){
			
			cout<<endl<<"drawFirstMethod before Mouse Click : " << drawFirstMethod;
			cout<<endl<<"drawSecondMethod before Mouse Click : " << drawSecondMethod;
			drawFirstMethod = false;
			drawSecondMethod = true;
			cout<<endl<<"drawFirstMethod after Mouse Click : " << drawFirstMethod;
			cout<<endl<<"drawSecondMethod after Mouse Click : " << drawSecondMethod;
			//glutSwapBuffers();
			glutPostRedisplay();
			//glFlush();

		}
		else if(drawSecondMethod){
			

			cout<<endl<<"drawFirstMethod before Mouse Click : " << drawFirstMethod;
			cout<<endl<<"drawSecondMethod before Mouse Click : " << drawSecondMethod;
			drawFirstMethod = true;
			drawSecondMethod = false;
			cout<<endl<<"drawFirstMethod after Mouse Click : " << drawFirstMethod;
			cout<<endl<<"drawSecondMethod after Mouse Click : " << drawSecondMethod;
			glutPostRedisplay();
		}
		

	

    }

}

void myDisplay2(void){
	
	glEnable(GL_TEXTURE_2D);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0,width,0,height);
	glOrtho(0,width,0,height,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	#pragma region Drawing game assets on the screen

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL,GL_ONE);
	
 if(menuscreen==true)
 {
  menu->drawSprite();
  glutSwapBuffers();
 }
 else
 {
	 if(health <= 0)
	{
		gameOver();	
		menuscreen=true;
		health=5;
	//	exit(1);
		}

	/* Drawing bg,fg & tank(hero)  on the screen*/
	
	 
	 bg->drawSprite();
	fg->drawSprite();
	currentAnim=hero->currentAnimState;
	hero->renderAtBodyPosition();
	
	 /* Drawing intruder enemies on the screen */
	  for (int i = 0; i < enemies.size(); i++){
		  currentAnim_enemy=enemies[i]->currentAnimState;
		  enemies[i]->renderAtBodyPosition();
		  enemies[i]->Isenemy=true;
	 }
	  
  	 /* Drawing birds on the screen */
	for (int i = 0; i < birds.size(); i++){
		  currentAnim_bird=birds[i]->currentAnimState;
		  birds[i]->renderAtBodyPosition();
		 
	}

	/* Drawing birds2 on the screen */
	for (int i = 0; i < birds2.size(); i++){
		  currentAnim_bird=birds2[i]->currentAnimState;
		  birds2[i]->renderAtBodyPosition();
	}

	glDisable(GL_ALPHA_TEST);
	glLoadIdentity();

	/* Drawing bomb on the screen */
	b2Body* tmp=world->GetBodyList();
	b2Vec2 points[4];
	
	while(tmp)
	{
		if(tmp->GetFixtureList()->GetShape()->GetType()==0)
			{
				b2CircleShape* c = ((b2CircleShape*)tmp->GetFixtureList()->GetShape());
				drawBomb(tmp->GetWorldCenter(),c->m_radius,tmp->GetAngle());
			}
	tmp=tmp->GetNext(); 
	}

	#pragma endregion

	#pragma region Drawing game assets on the screen
	/* Showing Score & other text on the screen */
	scoredisplay (1300, 20, 0, 22, score);
	//glColor3f(1.0, 1.0, 0.0);
	glRasterPos2f(0, 20);
	Write("Shoot the Intruders");
	glRasterPos2f(480, 20);
	Write("Developed by: M.Shaheer | Yasir Ali | Siddique M.Butt");
	#pragma endregion


	glutSwapBuffers();
		
}
}
void drawFloor()
{
	  b2BodyDef floorBodyDef;
	  floorBodyDef.type = b2_staticBody;
	  floorBodyDef.position.Set(0, 0);
	  b2EdgeShape edgeShape;
	  edgeShape.Set( b2Vec2(-30,30*P2M), b2Vec2(30,30*P2M) );
	  b2FixtureDef floorFixtureDef;
      floorFixtureDef.shape = &edgeShape;
      floorFixtureDef.density = 1;	
      world->CreateBody(&floorBodyDef)->CreateFixture(&floorFixtureDef);

}



  bool enemyTankCollide(b2Contact* contact, EnemySprite*& enemyEntity, AnimatedSprite*& tankEntity)
  {

	  //helper function to figure out if the collision was between
		//a radar and an aircraft, and sort out which is which
      b2Fixture* fixtureA = contact->GetFixtureA();
      b2Fixture* fixtureB = contact->GetFixtureB();
  
      //make sure only one of the fixtures was a sensor
      bool sensorA = fixtureA->IsSensor();
      bool sensorB = fixtureB->IsSensor();
      if ( ! (sensorA ^ sensorB) )
          return false;
  
      EnemySprite* entityA = static_cast<EnemySprite*>( fixtureA->GetBody()->GetUserData() );
	  AnimatedSprite* entityB = static_cast<AnimatedSprite*>( fixtureB->GetBody()->GetUserData() );
  
      if ( sensorA ) { 
		 //fixtureB must be an enemy 
          enemyEntity = entityA;
          tankEntity = entityB;
      }
      else { //fixtureA must be an enemy 
		   AnimatedSprite* entityB = static_cast<AnimatedSprite*>( fixtureA->GetBody()->GetUserData() );
		EnemySprite* entityA = static_cast<EnemySprite*>( fixtureB->GetBody()->GetUserData() );
          tankEntity = entityB;
          enemyEntity  = entityA;
      }
      return true;
  }

void scoredisplay (int posx, int posy, int posz, int space_char, int scorevar)
{
        int j=0,p,k;
        GLvoid *font_style1 = GLUT_BITMAP_TIMES_ROMAN_24;
       
        p = scorevar;
        j = 0;
        k = 0;
        while(p > 9)
        {
            k = p % 10;
            glRasterPos3f ((posx-(j*space_char)),posy, posz);   
            glutBitmapCharacter(font_style1,48+k);
            j++;
            p /= 10;
        }
            glRasterPos3f ((posx-(j*space_char)), posy, posz);   
            glutBitmapCharacter(font_style1,48+p);
      
}

void Write(char *string){//Write string on the screen
	while(*string)
		
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *string++);

}

void pressKey(unsigned char key,int x, int y){

	switch(key)
	{
	
	case 'a':{

		if(box2dtimer)
		{
		//PlayForegroundSound("tankcut.wav");
		hero->currentAnimState = 1;
		currentAnim=hero->currentAnimState;
		//hero->anim[currentAnim].currentFrames =(int)(hero->anim[currentAnim].currentFrames++)%5;
		hero->anim[currentAnim].currentFrames++;
		hero->setFrame((hero->anim[currentAnim].currentFrames++)%6);

		hero->sx =1;
		hero->m_body->SetLinearVelocity(b2Vec2(-1,0));
		if(hero-> x >=L && hero->x<= R-10)
		{
		/*hero->x -=1.0;*/
			
		bg->anim[0].u -= 0.005;
		fg->anim[0].u -= 0.002;
		}
		break;
		}
		}

	case 'd':{
		if(box2dtimer)
		{
		 hero->currentAnimState = 1;
		currentAnim=hero->currentAnimState;
		//hero->anim[currentAnim].currentFrames =(int)(hero->anim[currentAnim].currentFrames++)%5;
		hero->anim[currentAnim].currentFrames++;
		hero->setFrame((hero->anim[currentAnim].currentFrames++)%6);

		hero->sx =1;
		hero->m_body->SetLinearVelocity(b2Vec2(1,0));
		//if(hero-> x >=L && hero->x<= R-10)
			if(hero->x<R)
		{
		/*hero->x +=1.0;*/
			
		bg->anim[0].u += 0.005;
		fg->anim[0].u += 0.002;
		}
		break;
		}

		}


		case 'w':
		{
						  
		hero->currentAnimState = 2;
				 
		currentAnim=hero->currentAnimState;
		//hero->anim[currentAnim].currentFrames =(int)(hero->anim[currentAnim].currentFrames++)%5;
		if(hero->anim[currentAnim].currentFrames>4)
			{
		hero->anim[currentAnim].currentFrames=5;}
		else
		{
		hero->anim[currentAnim].currentFrames++;
		hero->setFrame((hero->anim[currentAnim].currentFrames++)%6);
		}
		if(hero->anim[currentAnim].currentFrames==0)
			angle=0*3.141/180;
		if(hero->anim[currentAnim].currentFrames==1)
			angle=15*3.141/180;
		if(hero->anim[currentAnim].currentFrames==2)
			angle=30*3.141/180;
		if(hero->anim[currentAnim].currentFrames==3)
			angle=45*3.141/180;
		if(hero->anim[currentAnim].currentFrames==4)
			angle=60*3.141/180;
		if(hero->anim[currentAnim].currentFrames==5)
			angle=75*3.141/180;
		
		break;
			 }

								case 's':{
				 hero->currentAnimState = 2;
		currentAnim=hero->currentAnimState;
		//hero->anim[currentAnim].currentFrames =(int)(hero->anim[currentAnim].currentFrames++)%5;
		if(hero->anim[currentAnim].currentFrames<1)
		hero->anim[currentAnim].currentFrames=0;
		else
		{
		hero->anim[currentAnim].currentFrames--;
		hero->setFrame((hero->anim[currentAnim].currentFrames--)%6);
		}
		if(hero->anim[currentAnim].currentFrames==0)
			angle=5*3.141/180;
		if(hero->anim[currentAnim].currentFrames==1)
			angle=15*3.141/180;
		if(hero->anim[currentAnim].currentFrames==2)
			angle=25*3.141/180;
		if(hero->anim[currentAnim].currentFrames==3)
			angle=35*3.141/180;
		if(hero->anim[currentAnim].currentFrames==4)
			angle=45*3.141/180;
		if(hero->anim[currentAnim].currentFrames==5)
			angle=55*3.141/180;
		
		break;
			 }
			case 'p':{
						if(menuscreen==false)
						 {
								 if (box2dtimer) 
								{
									box2dtimer=0;
								 }
						 else 
								 {
									 box2dtimer=0.016;
								 }
						}
					 
    break;
    
   }
	   case 'm':
    
    if(menuscreen==true)
    {menuscreen=false;
    box2dtimer=0.016;}
    else
     {
      menuscreen=true;
      box2dtimer=0;
     }
    /*pause=false;*/
   

 }
 glutPostRedisplay();
}

void gameOver()
{
	glRasterPos2f(650, 550);
	Write("Game Over");
}


void idle (void)
{
		
	  if(box2dtimer){

	 if(health <= 0)
	{
		gameOver();	
	//	exit(1);
		}

	  }



	//Movement of Birds start
  if(box2dtimer){
  for (int i = 0; i < birds.size(); i++){
   currentAnim_bird=birds[i]->currentAnimState;
   float t = birds[i]->m_body->GetPosition().x;
   
   birds[i]->anim[currentAnim_bird].currentFrames++;
   birds[i]->setFrame((birds[i]->anim[currentAnim_bird].currentFrames++)%9);

   if(t<-15){rightt=true;}
   if(t>25){rightt=false;}


   if(rightt==true)
   { 

   birds[i]->sx =1;
   birds[i]->m_body->SetLinearVelocity(b2Vec2(0.6,0));
  
    }

  
   else if(rightt==false){
  // FOR LIST IMPLEMENTATION
  birds[i]->sx =-1;
  birds[i]->m_body->SetLinearVelocity(b2Vec2(-0.8,0));
  

   }
  } } //Movement of Birds end

    //Movement of Birds2 start
  
  if(box2dtimer){
  for (int i = 0; i < birds2.size(); i++){
   currentAnim_bird=birds2[i]->currentAnimState;
   float t = birds2[i]->m_body->GetPosition().x;
   birds2[i]->anim[currentAnim_bird].currentFrames++;
   birds2[i]->setFrame((birds2[i]->anim[currentAnim_bird].currentFrames++)%4);

   if(t<-25){rightt=true;}
   if(t>35){rightt=false;}


   if(rightt==true)
   { 

   birds2[i]->sx =-1;
   birds2[i]->m_body->SetLinearVelocity(b2Vec2(0.6,0));
  
    }

  
   else if(rightt==false){
  // FOR LIST IMPLEMENTATION
  birds2[i]->sx =1;
  birds2[i]->m_body->SetLinearVelocity(b2Vec2(-0.5,0));
  

   }
  } } //Movement of Birds2 end
  
  //Movement of Enemies start
  if(box2dtimer){
  for (int i = 0; i < enemies.size(); i++){

	  if(enemies[i]->m_body->GetPosition().x*M2P<=hero->m_body->GetPosition().x*M2P+20){
	   enemies[i]->m_body->SetLinearVelocity(b2Vec2(0.0,0));
	  
	  
	  }

	  else{
  currentAnim_enemy=enemies[i]->currentAnimState;
  
  // FOR LIST IMPLEMENTATION
  enemies[i]->anim[currentAnim_enemy].currentFrames++;
  enemies[i]->setFrame((enemies[i]->anim[currentAnim_enemy].currentFrames++)%13);
  enemies[i]->sx =1;
 
  enemies[i]->m_body->SetLinearVelocity(b2Vec2(-0.5,0));
	  }
  } }  //Movement of Enemies end


  
	  std::set<EnemySprite*>::iterator it = enemiesScheduledForRemoval.begin();
	  std::set<EnemySprite*>::iterator end = enemiesScheduledForRemoval.end();
	  
	  for (; it!=end; ++it) {
		  EnemySprite* dyingEnemy = *it;
			
		  //delete ball... physics body is destroyed here
		  delete dyingEnemy;
  
		  //... and remove it from main list of balls
		  std::vector<EnemySprite*>::iterator it = std::find(enemies.begin(), enemies.end(), dyingEnemy);
		  if ( it != enemies.end() )
			  enemies.erase( it );
		}
  
		//clear this list for next time
		enemiesScheduledForRemoval.clear();


		
		glutPostRedisplay();
}


void Timer(int t)
{
	world->Step(box2dtimer,8,3);
	glutPostRedisplay();
	glutTimerFunc(1500/150,Timer,1);
}

void myTimer2(int t)
{
	
		glutTimerFunc(1,myTimer2,10);
		glutPostRedisplay();

}



int main(int argc, char **argv)
{
	#pragma region Usual glut initializations
	init();
	glutInit(&argc,argv);
	//glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);	
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowSize((int) width, (int) height);
	glutInitWindowPosition(30,30);
	glutCreateWindow("*INTRUDERS - PROJECTILE SHOOTING GAME -  By : MShaheer | Yasirali | SiddiqueMbutt*");
	#pragma endregion


	//PlayBackgroundSound("ToughGuy.wav");
	PlayBackgroundSound("game_face.wav");
	pix[0].readBMPFile("ball01.bmp");
	pix[0].setTexture(2012);	
	drawFloor();		/* Draw static floor */

	#pragma region Creation of hero(tank)
	/*hero2 =new AnimatedSprite("animspritefinal.bmp",277,110,400,300,2001,world, 1);*/
	//hero =new AnimatedSprite("tankspritefinalll2.bmp",277,110,100,100,2004,world, 1);
	hero =new AnimatedSprite("animspritefinal.bmp",277,110,100,100,2004,world, 1,true,TANK,FLOOR|BOMB|TANK|ENEMY);
	hero->colorKey(255,0,255);
	#pragma endregion
		
	#pragma region Creation of enemy intruders
	// Instantiating intruder enemy and pushing it in enemies container
	for(int i=0; i<30 ; i++){
	EnemySprite* enemy = new EnemySprite("enemynew.bmp",51,45,enemyposfirst,100,2093,world, 1,true,ENEMY,FLOOR|BOMB|TANK);
	//EnemySprite* enemy = new EnemySprite("modernsold.bmp",68,104,enemyposfirst,100,2003,world, 1,true,ENEMY,FLOOR|BOMB|TANK);
	enemy->colorKey(255,0,255);
	enemies.push_back( enemy );
	//enemyposfirst-=25;
	enemyposfirst=rand() % 1350+1380+1080;
	}
	#pragma endregion

	#pragma region Creation of birds
	// Instantiating bird and pushing it in birds container
	for(int i=0; i<7 ; i++){
	AnimatedSprite* bird = new AnimatedSprite("bird1.bmp",77,90,birdposfirst,700,3001,world, 1,false,BIRD,FLOOR);
	bird->colorKey(255,0,255);
	birds.push_back( bird );
	birdposfirst=rand() % 1380+1350+600;
	bird->m_body->SetGravityScale(0.0);
	}
	#pragma endregion

	#pragma region Creation of birds2
	// Instantiating bird2 and pushing it in birds2 container
	for(int i=0; i<12 ; i++){
	AnimatedSprite* bird2 = new AnimatedSprite("bird2.bmp",33,34,birdpossec,600,3002,world, 1,false,BIRDTWO,FLOOR);
	bird2->colorKey(255,0,255);
	b2Fixture * myFixture = bird2->m_body->GetFixtureList(); //this assumes there is only 1 fixture on your body
	bird2->m_body->DestroyFixture(myFixture);
	b2FixtureDef newfixturedef;
	b2PolygonShape newpolyShape;
	newpolyShape.SetAsBox(16*P2M,17*P2M);
	newfixturedef.shape=&newpolyShape;
	bird2->m_body->CreateFixture(&newfixturedef);
	birds2.push_back( bird2 );
	birdpossec=rand() % 1380+1350;
	bird2->m_body->SetGravityScale(0.0);
	}
	#pragma endregion

	#pragma region Loading foregrounds
	//Load clouds foreground
	//fg=new AnimatedSprite("cloudspink2.bmp",1702,459,L,468,2005,world, 1);
	fg=new AnimatedSprite("bgcloudss.bmp",2429,431,L,468,3009,world, 1,false,BG,0);
	fg->colorKey(79,153,242);
	#pragma endregion

	#pragma region Loading background
	
	
	menu=new AnimatedSprite("mainscreen.bmp",1436,778,L,B,202,world, 1,false,BG,0);
	menu->colorKey(255,0,255);
	//Load background
	bg=new AnimatedSprite("bg22.bmp",2429,778,L,B,2002,world, 1,false,BG,0xFFFF);
	//bg=new AnimatedSprite("bg1ubit3.bmp",4500,769,L,B,2002,world, 1);
	//bg=new AnimatedSprite("bg3.bmp",2429,586,L,B,2002,world, 1);
	bg->colorKey(255,0,255);

	

	#pragma endregion
		
	glutReshapeFunc(reshape); /* register function to handle window resizes */
	glutDisplayFunc(myDisplay2);        /* game display function */
	//glutDisplayFunc (combinedisplay);  /*combined display function for menu*/
	
	#pragma region Glut keyboard & mouse functions
	//glutSpecialFunc(pressKeySpecial); 
	//glutSpecialUpFunc(releaseKeySpecial);
	glutMouseFunc(mouse);
	glutKeyboardFunc(pressKey);
	#pragma endregion

	glutTimerFunc(1000/30,Timer,1);
	glutTimerFunc(10,myTimer2,1);
	//glutTimerFunc(1000,myTimer,1);	//OLD ONLY MARIO STANDING & BG
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
