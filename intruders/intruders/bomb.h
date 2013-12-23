
#ifndef BOMB_H
#define	BOMB_H


b2FixtureDef fixturedef;


/* FUNCTIONS FOR PROJECTILE BOMB START */
b2Body* addBomb(int x,int y,int r,bool dyn=true)
{
	b2BodyDef bodydef;
	x += 100*P2M;
	y += 100*P2M;
        bodydef.position.Set(x,y);
		bodydef.angle=45;
        if(dyn)
		{
                bodydef.type=b2_dynamicBody;
				

		}
        b2Body* body=world->CreateBody(&bodydef);
		//bodyDef.bullet = true;
		b2CircleShape shape;
		shape.m_radius=r*P2M;
		shape.m_p.Set(0,0);
		
        fixturedef.shape=&shape;
        fixturedef.density=1.0;
		/*fixturedef.restitution=0.0;*/
		fixturedef.friction=1.0;
		fixturedef.restitution=3;
		/*fixturedef.filter.categoryBits =BOMB;
		fixturedef.filter.maskBits =ENEMY;*/
		body->CreateFixture(&fixturedef);

		

		return body;


}

void drawBomb(b2Vec2 center,float r,float angle)
{
	//glColor3f(1,1,1);
	glPushMatrix();
	glTranslatef(center.x*M2P,center.y*M2P,0);
	glRotatef(angle*180.0/3.141,0,0,1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 2012);
	glBegin(GL_TRIANGLE_FAN);
	glScalef(0.5,0.5,1);
	glVertex2f(0,0);
	
	for(float i=0.0;i<=360;i+=5)
	{
		//glColor3f(0,0,0);
		glVertex2f((cos(i*3.141/180))*r*M2P,(sin(i*3.141/180))*r*M2P);
		glTexCoord2f((cos(i*3.141/180))*r*M2P,(sin(i*3.141/180))*r*M2P);
		
	}
	
	glEnd();
	glPopMatrix();

}
/* FUNCTIONS FOR PROJECTILE BOMB END */




#endif