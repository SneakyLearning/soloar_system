#include "stars.h"

Star::Star(GLfloat radius, GLfloat distance, GLfloat speed, GLfloat selfSpeed, Star* parentStar)
{
}

void Star::drawStar()
{
}

void Star::update(long timeSpan)
{
}

Planet::Planet(GLfloat radius, GLfloat distance, GLfloat speed, GLfloat selfSpeed, Star* parentStar, GLfloat rgbColor[3]):Star(radius,distance,speed,selfSpeed,parentStar)
{
}

void Planet::drawPlanet()
{
}

LightPlanet::LightPlanet(GLfloat Radius, GLfloat Distance, GLfloat Speed, GLfloat SelfSpeed, Star* ParentStar, GLfloat rgbColor[3]):Planet(Radius, Distance, Speed, SelfSpeed, ParentStar, rgbColor)
{
}

void LightPlanet::drawLight()
{
}
