/* 
 * File:   Hero.h
 * Author: humera
 *
 * Created on August 20, 2011, 6:00 AM
 */

#ifndef HERO_H
#define	HERO_H
#include <glut.h>
#include "RGBA.h"
#include<Box2D\Box2D.h>
#include <vector>
const float M2P=100;
const float P2M=1/M2P;

#pragma region ENUM FOR COLLISION FILTERING 
	enum _entityCategory
	{
		FLOOR = 0x0001,		// 0x0001 means collide with everything (Box2d default)
		ENEMY = 0x0002,
		TANK = 0x0004,
		BOMB = 0x0008,
		BIRD = 0x0010,
		BIRDTWO = 0x0020,
		ENEMYSENSOR =0x0040,
		BG =0x0050
	};
#pragma endregion

typedef struct Frame
{
     // a single (s,t) texture coordinate
     float u,v;
     int currentFrames; // frameID
}FrameST;

class AnimatedSprite
{
public:



    static const int  FRAMES_PER_SECOND_SPRITE =1000;
    static const int FRAME_DELAY_SPRITE=1000/FRAMES_PER_SECOND_SPRITE;
     /* no animation can have more than 100 frames */
    static const int MAX_ANIM = 100 ;

    /* anim types */
    enum {ANIM_ACTION=0, ANIM_JUMP,ANIM_WALK_LEFT,ANIM_WALK_RIGHT,ANIM_IDLE};
    FrameST anim[6]; //because I only have 5 anim in this sheet

	//RGBpixmap sheet;
    RGBApixmap sheet;
    int sheetWidth,sheetHeight;
   

    // normalized width/height of sprite for texture
    float texWidth,texHeight;
    

    /* position info */
     float x,y;
     /* height of sprite in pixels on screen*/
     float w,h;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
     int currentAnimState;
     // the sprite comes from a sprite sheet
      unsigned long quadID;
      unsigned int texID;
      float sx,sy;
      
     /* For Box2d body definition */
	   b2Body* m_body;
       float m_radius;
	   float m_mass ;
	   b2FixtureDef myFixtureDef;
	   b2BodyDef myBodyDef;


	   //Ball class member variable
  bool m_contacting;


 
  
  //Ball class functions
  void startContact() { m_contacting = true; }
  void endContact() { m_contacting = false; }
  
  
  bool Istank;
  
  
     AnimatedSprite( char *name, int myWidth, int myHeight,float xx, float yy, int ID,b2World* world, float radius,bool istankflag, uint16 categoryBits, uint16 maskBits)
    {
		m_contacting = false;
     
         this->sheet.readBMPFile(name,1);
         //cout<<endl<<endl<<" Orig Image width is:" << sheet.nCols;
         // cout<<endl<<" Orig Image ht is:" << sheet.nRows;

         this->sheetWidth  = sheet.nCols;
         this->sheetHeight = sheet.nRows;
         
         this->x = xx;
         this->y = yy;
        
         this->w = myWidth;
         this->h = myHeight;
         
         this->texHeight = h /(float)sheetHeight;
         this->texWidth  = w /(float)sheetWidth;

         if(texWidth >1.0){ sx = texWidth;} else sx =1.0;
         if(texHeight >1.0){ sy = texHeight;} else sy =1.0;

         this->currentAnimState = ANIM_IDLE; //initializes the character's initial state

         this->texID = ID;
        //glGenTextures(1,&this->texID);
       
         this->anim->u =0;
         this->anim->v =0;
         
         this->anim[this->currentAnimState].currentFrames=0;


		 /* Box2d Bodydef initializations */
		 m_body = NULL;
		 m_radius = radius;
		 
		  //set up dynamic body, store in class variable
       myBodyDef.position.Set(x*P2M, y*P2M);
      myBodyDef.type = b2_dynamicBody;
	
      m_body = world->CreateBody(&myBodyDef);      
	 
	  //PolyShape
	  b2PolygonShape polyShape;
	  polyShape.SetAsBox(120*P2M,55*P2M);
	  //polyShape.m_centroid.SetZero();
	  //polyShape.m_
	  /*b2FixtureDef myFixtureDef;*/
	  myFixtureDef.shape = &polyShape;
      myFixtureDef.density = 0.06; 	  
	  myFixtureDef.friction=0.1;
	  myFixtureDef.restitution=0.7;
	 
	 //For Collision Filtering
	myFixtureDef.filter.categoryBits = categoryBits;
	myFixtureDef.filter.maskBits = maskBits;
    m_body->CreateFixture(&myFixtureDef);
	float speed=-4,angle=90*3.141/180;
	m_contacting = false;
	this->Istank = istankflag;
	m_body->SetUserData( this ); //set this class object in the body's user data


     }


	  AnimatedSprite::~AnimatedSprite()
	{
		m_body->GetWorld()->DestroyBody( m_body );
	}



 void colorKey(int r, int g, int b)
     {
          this->sheet.setChromaKey(r,g,b);
          this->sheet.setTexture(this->texID);
     }

 void setFrame(int frame)
     {
         this->anim[this->currentAnimState].currentFrames = frame;
     }

 void renderAtBodyPosition() {
          
      //get current position from Box2D
      b2Vec2 pos = m_body->GetPosition();
      float angle = m_body->GetAngle();
  
      //call normal render at different position/rotation
      glPushMatrix();

	/*  glTranslatef(this->x,this->y,0);
     glScalef(this->sx, this->sy, 1.0f );*/
	  
	
	   //glTranslatef( (pos.x*M2P)-40, pos.y*M2P, 0 );
	   //glScalef(this->sx, this->sy, 1.0f );
	  //  glScalef(1.0f,1.0f,1.0f);
	  glTranslatef( (pos.x*M2P)-130, (pos.y*M2P)-35, 0 );
	  glScalef(this->sx, this->sy, 1.0f );
	  // glTranslatef( (pos.x*M2P)-40, pos.y*M2P, 0 );
	  
      //glRotatef( angle * 180.0/3.141, 0, 0, 1 );//OpenGL uses degrees here
	  
	  drawSprite2();//normal render at (0,0)
      glPopMatrix();
    
	
 
	 }

 void drawSprite()
 {

    
   glPushMatrix();
     glTranslatef(this->x,this->y,0);
     glScalef(this->sx, this->sy, 1.0f );
  
    int currentAnim = this->currentAnimState;
    int currentFrame = this->anim[currentAnim].currentFrames;

     FrameST* UV = this->anim;
 
     float u = UV->u+this->texWidth*currentFrame; 
     float v = UV->v+this->texHeight*currentAnim;
  
    /* bind the appropriate texture frame */
    glBindTexture(GL_TEXTURE_2D,this->texID);

    glBegin(GL_QUADS);
	   //glTexCoord2f(0,0);
	   glTexCoord2f(u,v);
	   glVertex2f(0,0);

	   //glTexCoord2f(0,1);
	   glTexCoord2f(u,v+this->texHeight);
	   glVertex2f(0,this->h);

	   //glTexCoord2f(1,1);
	   glTexCoord2f(u+this->texWidth,v+this->texHeight);
	   glVertex2f(this->w,this->h);

	   //glTexCoord2f(1,0);
	   glTexCoord2f(u+this->texWidth,v);
	   glVertex2f(this->w,0);
		glEnd();
		glPopMatrix();
 
  //glDisable(GL_BLEND);
  
 }// end drawSprite

 void drawSprite2()
 {
    //cout <<endl<<"@@@@@@@@@@@@@@New Sprite@@@@@@@@@@@@@@"<<endl;
	   
  //glEnable(GL_BLEND);
  //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
    
  
    
  
    int currentAnim = this->currentAnimState;
    int currentFrame = this->anim[currentAnim].currentFrames;

     FrameST* UV = this->anim;
 
     float u = UV->u+this->texWidth*currentFrame; 
     float v = UV->v+this->texHeight*currentAnim;
  
    /* bind the appropriate texture frame */
    glBindTexture(GL_TEXTURE_2D,this->texID);

    glBegin(GL_QUADS);
	   //glTexCoord2f(0,0);
	   glTexCoord2f(u,v);
	   glVertex2f(0,0);

	   //glTexCoord2f(0,1);
	   glTexCoord2f(u,v+this->texHeight);
	   glVertex2f(0,this->h);

	   //glTexCoord2f(1,1);
	   glTexCoord2f(u+this->texWidth,v+this->texHeight);
	   glVertex2f(this->w,this->h);

	   //glTexCoord2f(1,0);
	   glTexCoord2f(u+this->texWidth,v);
	   glVertex2f(this->w,0);   
	   glEnd();
		
	   	//in Ball::render
	   if ( m_contacting ){
	   
		   //cout<<"Enemy HIt"<<std::endl;
	   
	   }
   
	   else{
	   
	   //cout<<"not working"<<std::endl;
	   
	   
	   }
   
 
  //glDisable(GL_BLEND);
  
 }// end drawSprite


};

//class Enemy : public AnimatedSprite
//{
//	//int	ENEMY == 1;
//	 int getEntityType() { return 1; }
//};

//  //FooTest class member variable
//std::vector<AnimatedSprite*> enemies;


#endif