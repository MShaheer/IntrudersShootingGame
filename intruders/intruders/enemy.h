/* 
 * File:   Hero.h
 * Author: humera
 *
 * Created on August 20, 2011, 6:00 AM
 */

#ifndef ENEMY_H
#define	ENEMY_H
#include <glut.h>
#include "RGBA.h"
//#include "pixMap.h"
#include<Box2D\Box2D.h>
#include <vector>
#include <set>


typedef struct Frameenemy
{
     // a single (s,t) texture coordinate
     float u,v;
     int currentFrames; // frameID
}FrameenemyST;

class EnemySprite
{
public:

	

    static const int  FRAMES_PER_SECOND_SPRITE =10000;
    static const int FRAME_DELAY_SPRITE=1000/FRAMES_PER_SECOND_SPRITE;
     /* no animation can have more than 100 frames */
    static const int MAX_ANIM = 100 ;

    /* anim types */
    enum {ANIM_ACTION=0, ANIM_JUMP,ANIM_WALK_LEFT,ANIM_WALK_RIGHT,ANIM_IDLE};
    FrameenemyST anim[13]; //because I only have 5 anim in this sheet

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
	   b2FixtureDef myFixtureDefsensor;

	   //Ball class member variable
  bool m_contacting;


  bool Isenemy;
  
  
  
  //Ball class functions
  void startContact() { m_contacting = true; }
  void endContact() { m_contacting = false; }
  
  
  
  
  
     EnemySprite( char *name, int myWidth, int myHeight,float xx, float yy, int ID,b2World* world, float radius, bool isenemyflag, uint16 categoryBits, uint16 maskBits)
    {
		//in Ball class constructor
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

         this->currentAnimState = 1; //initializes the character's initial state

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
	  polyShape.SetAsBox(29*P2M,20*P2M);
	  /*b2FixtureDef myFixtureDef;*/
	  myFixtureDef.shape = &polyShape;
      myFixtureDef.density = 0.06; 	  
	  myFixtureDef.friction=1;
	  myFixtureDef.restitution=0.1;
	 //For Collision Filtering
	  myFixtureDef.filter.categoryBits = categoryBits;
	  myFixtureDef.filter.maskBits = maskBits;
      m_body->CreateFixture(&myFixtureDef);
	  float speed=-4,angle=90*3.141/180;
	  m_contacting = false;
	  myFixtureDef.isSensor = false;
	  this->Isenemy = isenemyflag;
	  m_body->SetUserData( this ); //set this class object in the body's user data


	  b2PolygonShape polyShapesensor;
   polyShape.SetAsBox(50*P2M,31*P2M);
  myFixtureDefsensor.shape = & polyShapesensor;
  myFixtureDefsensor.isSensor = true;
  myFixtureDefsensor.filter.categoryBits = ENEMYSENSOR;
  myFixtureDefsensor.filter.maskBits = TANK;   //radar only collides with aircraft
 m_body->CreateFixture(& myFixtureDefsensor);




      }

	 EnemySprite::~EnemySprite()
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
	  glTranslatef( (pos.x*M2P)-40, pos.y*M2P, 0 );
	 
	   // glTranslatef( (pos.x*M2P)-40, pos.y*M2P, 0 );
	  
      //glRotatef( angle * 180.0/3.141, 0, 0, 1 );//OpenGL uses degrees here
	   glScalef(this->sx, this->sy, 1.0f );
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

     FrameenemyST* UV = this->anim;
 
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
   
    int currentAnim = this->currentAnimState;
    int currentFrame = this->anim[currentAnim].currentFrames;

     FrameenemyST* UV = this->anim;
 
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



#endif