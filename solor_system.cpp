#include "solor_system.h"

#define TIMEPAST 1
#define SELFROTATE 3
#define TIMEPAST 1 // ����ÿ�θ��¶�������һ��
#define OFFSET 20

// ��ת�뾶
#define SUN_RADIUS 48.74
#define MER_RADIUS  7.32
#define VEN_RADIUS 18.15
#define EAR_RADIUS 19.13
#define MOO_RADIUS  6.15
#define MAR_RADIUS 10.19
#define JUP_RADIUS 42.90
#define SAT_RADIUS 36.16
#define URA_RADIUS 25.56
#define NEP_RADIUS 24.78

// ��̫���ľ���
#define MER_DIS   62.06
#define VEN_DIS  115.56
#define EAR_DIS  168.00
#define MOO_DIS   26.01
#define MAR_DIS  228.00
#define JUP_DIS  333.40
#define SAT_DIS  428.10
#define URA_DIS 848.00
#define NEP_DIS 949.10

// �˶��ٶ�
#define MER_SPEED   87.0
#define VEN_SPEED  225.0
#define EAR_SPEED  365.0
#define MOO_SPEED   30.0
#define MAR_SPEED  687.0
#define JUP_SPEED 1298.4
#define SAT_SPEED 3225.6
#define URA_SPEED 3066.4
#define NEP_SPEED 6014.8

// ��ת�ٶ�
#define SELFROTATE 3

// Ϊ�˷���������飬����һ�����ö�Ϊ����ĺ�
#define SET_VALUE_3(name, value0, value1, value2)((name)[0])=(value0), ((name)[1])=(value1), ((name)[2])=(value2)

enum STARS {
	Sun,        // ̫��
	Mercury,    // ˮ��
	Venus,      // ����
	Earth,      // ����
	Moon,       // ����
	Mars,       // ����
	Jupiter,    // ľ��
	Saturn,     // ����
	Uranus,     // ������
	Neptune     // ������
};

SolorSystem::SolorSystem()
{
	viewX = 0;
	viewY = REST_Y;
	viewZ = REST_Z;
	centerX = centerY = centerZ = 0;
	upX = upY = 0;
	upZ = 1;

	// ̫��
	GLfloat rgbColor[3] = { 1, 0, 0 };
	stars[Sun] = new LightPlanet(SUN_RADIUS, 0, 0, SELFROTATE, 0, rgbColor);
	// ˮ��
	SET_VALUE_3(rgbColor, .2, .2, .5);
	stars[Mercury] = new Planet(MER_RADIUS, MER_DIS, MER_SPEED, SELFROTATE, stars[Sun], rgbColor);
	// ����
	SET_VALUE_3(rgbColor, 1, .7, 0);
	stars[Venus] = new Planet(VEN_RADIUS, VEN_DIS, VEN_SPEED, SELFROTATE, stars[Sun], rgbColor);
	// ����
	SET_VALUE_3(rgbColor, 0, 1, 0);
	stars[Earth] = new Planet(EAR_RADIUS, EAR_DIS, EAR_SPEED, SELFROTATE, stars[Sun], rgbColor);
	// ����
	SET_VALUE_3(rgbColor, 1, 1, 0);
	stars[Moon] = new Planet(MOO_RADIUS, MOO_DIS, MOO_SPEED, SELFROTATE, stars[Earth], rgbColor);
	// ����
	SET_VALUE_3(rgbColor, 1, .5, .5);
	stars[Mars] = new Planet(MAR_RADIUS, MAR_DIS, MAR_SPEED, SELFROTATE, stars[Sun], rgbColor);
	// ľ��
	SET_VALUE_3(rgbColor, 1, 1, .5);
	stars[Jupiter] = new Planet(JUP_RADIUS, JUP_DIS, JUP_SPEED, SELFROTATE, stars[Sun], rgbColor);
	// ����
	SET_VALUE_3(rgbColor, .5, 1, .5);
	stars[Saturn] = new Planet(SAT_RADIUS, SAT_DIS, SAT_SPEED, SELFROTATE, stars[Sun], rgbColor);
	// ������
	SET_VALUE_3(rgbColor, .4, .4, .4);
	stars[Uranus] = new Planet(URA_RADIUS, URA_DIS, URA_SPEED, SELFROTATE, stars[Sun], rgbColor);
	// ������
	SET_VALUE_3(rgbColor, .5, .5, 1);
	stars[Neptune] = new Planet(NEP_RADIUS, NEP_DIS, NEP_SPEED, SELFROTATE, stars[Sun], rgbColor);
}

SolorSystem::~SolorSystem()
{
	for (int i = 0; i < STARS_NUM; i++)
		delete stars[i];
}

void SolorSystem::onDisplay()
{
	// ��� viewport ������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ��ղ�������ɫ����
	glClearColor(.7f, .7f, .7f, .1f);
	// ָ����ǰ����ΪͶӰ����
	glMatrixMode(GL_PROJECTION);
	// ��ָ���ľ���ָ��Ϊ��λ����
	glLoadIdentity();
	// ָ����ǰ�Ĺ۲��Ӿ���
	gluPerspective(75.0f, 1.0f, 1.0f, 40000000);
	// ָ����ǰ����Ϊ�Ӿ������ջӦ������ľ������
	glMatrixMode(GL_MODELVIEW);
	// ָ����ǰ�ľ���Ϊ��λ����
	glLoadIdentity();
	// ������ͼ���󣬲��뵱ǰ�������
	gluLookAt(viewX, viewY, viewZ, centerX, centerY, centerZ, upX, upY, upZ);

	// ���õ�һ����Դ(0�Ź�Դ)
	glEnable(GL_LIGHT0);
	// ���ù�Դ
	glEnable(GL_LIGHTING);
	// ������Ȳ��ԣ����������Զ���Զ����ر���ס��ͼ��
	glEnable(GL_DEPTH_TEST);

	// ��������
	for (int i = 0; i < STARS_NUM; i++)
		stars[i]->draw();

	// ������ main �����г�ʼ����ʾģʽʱʹ���� GLUT_DOUBLE
	// ��Ҫʹ�� glutSwapBuffers �ڻ��ƽ�����ʵ��˫����Ļ���������
	glutSwapBuffers();
}

void SolorSystem::onUpdate()
{
	for (int i = 0; i < STARS_NUM; i++)
		stars[i]->update(TIMEPAST); // ���������λ��
	
	this->onDisplay(); // ˢ����ʾ
}

void SolorSystem::onKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w': viewY += OFFSET; break; // �����Y ��λ������ OFFSET
	case 's': viewZ += OFFSET; break;
	case 'S': viewZ -= OFFSET; break;
	case 'a': viewX -= OFFSET; break;
	case 'd': viewX += OFFSET; break;
	case 'x': viewY -= OFFSET; break;
	case 'r':
		viewX = 0; viewY = REST_Y; viewZ = REST_Z;
		centerX = centerY = centerZ = 0;
		upX = upY = 0; upZ = 1;
		break;
	case 27: exit(0); break;
	default: break;
	}
}
