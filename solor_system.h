#pragma once
#define STARS_NUM 10
#define TIMEPAST 1
#define SELFROTATE 3

#define REST 700
#define REST_Y (-REST)
#define REST_Z (REST)
//≥ı º ”Ω«Œª÷√

#include "stars.h"
#include <Windows.h>
using namespace std;


class SolorSystem {
public:
	SolorSystem();
	~SolorSystem();

	void onDisplay();
	void onUpdate();
	void onKeyboard(unsigned char key, int x, int y);

private:
	Star* stars[STARS_NUM];
	GLdouble viewX, viewY, viewZ;
	GLdouble centerX, centerY, centerZ;
	GLdouble upX, upY, upZ;
};