#include "stars.h"
#include <cmath>

#define PI 3.1415926535

Star::Star(GLfloat radius, GLfloat distance, GLfloat speed, GLfloat selfSpeed, Star* parentStar)
{
	this->radius = radius;
	this->selfSpeed = selfSpeed;
	this->alphaSelf = this->alpha = 0;
	this->distance = distance;

	for (int i = 0; i < 4; i++)
		this->rgbaColor[i] = 1.0f;

	this->parentstar = parentStar;
	if (speed > 0)
		this->speed = 360.0f / speed;
	else
		this->speed = 0.0f;

	std::cout << "construct star" << std::endl;
}

void Star::drawStar()
{
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);

	int n = 1440;

	glPushMatrix();
	{
		if (parentstar != 0 && parentstar->distance > 0)
		{
			//旋转aplha
			glRotatef(parentstar->alpha, 0, 0, 1);
			//z平移distance
			glTranslatef(parentstar->distance, 0.0, 0.0);
		}
		glBegin(GL_LINES);
		for(int i=0;i<n;++i)
		{
			glVertex2f(distance * cos(2 * PI * i / n), distance * sin(2 * PI * i / n));
		}
		glEnd();
		glRotatef(alpha, 0, 0, 1);
		glTranslatef(distance, 0.0, 0.0);

		glRotatef(alpha, 0, 0, 1);

		glColor3f(rgbaColor[0], rgbaColor[1], rgbaColor[2]);
		glutSolidSphere(radius, 40, 32);
	}

	glPopMatrix();
}

void Star::update(long timeSpan)
{
	alpha += timeSpan * speed;
	alphaSelf += selfSpeed;
}

Planet::Planet(GLfloat radius, GLfloat distance, GLfloat speed, GLfloat selfSpeed, Star* parentStar, GLfloat rgbColor[3]):
	Star(radius,distance,speed,selfSpeed,parentStar)
{
	rgbaColor[0] = rgbColor[0];
	rgbaColor[1] = rgbColor[1];
	rgbaColor[2] = rgbColor[2];
	rgbaColor[3] = 1.0f;

	std::cout << "construct Planet" << std::endl;
}

void Planet::drawPlanet()
{
	GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
	GLfloat mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
	GLfloat mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat mat_emission[] = { rgbaColor[0], rgbaColor[1], rgbaColor[2], rgbaColor[3] };
	GLfloat mat_shininess = 90.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}

LightPlanet::LightPlanet(GLfloat Radius, GLfloat Distance, GLfloat Speed, GLfloat SelfSpeed, Star* ParentStar, GLfloat rgbColor[3]):
	Planet(Radius, Distance, Speed, SelfSpeed, ParentStar, rgbColor)
{
	std::cout << "construct lighting planet" << std::endl;;
}

void LightPlanet::drawLight()
{
	GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // 指定零号光源的位置
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);  // 表示各种光线照射到该材质上，经过很多次反射后追踪遗留在环境中的光线强度
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);  // 漫反射后的光照强度
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); // 镜面反射后的光照强度
}
