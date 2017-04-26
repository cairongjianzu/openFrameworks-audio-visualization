#include "par.h"



par::par()
{
	setInitialCondition(0, 0, 0, 0);
	//��������ϵ��
	damping = 0.12f;
}
par::~par()
{
}
//����λ��
void par::update() {
	vel = vel + frc;
	pos = pos + vel;
}
//������
void par::draw(ofColor c) {
	ofPushStyle();
	ofSetColor(c);
    ofCircle(pos.x, pos.y, 2);
	ofPopStyle();
}
//��ʼ�����ӵ�λ������
void par::setInitialCondition(float px, float py, float vx, float vy)
{
	pos.set(px, py);
	vel.set(vx, vy);
}
//��������СΪ��
void par::resetForce() {
	frc.set(0, 0);
}
//ʹ���仯
void par::addForce(float x, float y) {
	frc.x = frc.x + x;
	frc.y = frc.y + y;
}
//ʹ��������Ӧ������ų���
void par::addRepulsionForce(float x, float y, float radius, float scale) {
	ofVec2f posOfForce;
	posOfForce.set(x, y);
	//ʹ�÷����Ķ�����봫����ʸ�����������
	ofVec2f diff = pos - posOfForce;
	float length = diff.length();
	//�޶�radius��Χ������������Ч
	bool bAmCloseEnough = true;
	if (radius > 0) {
		if (length > radius) {
			bAmCloseEnough = false;
		}
	}
	if (bAmCloseEnough == true) {
		//��radius��Χ�ڵĶ������ӣ��봫�����볤��Խ�������ӣ���������ϵ��pctԽ��0.0-1.0��
		float pct = 1 - (length / radius); 
		diff.normalize();
		//��������ϵ��pctԽ�󣬴����Ը������ų���Խ��
		frc.x = frc.x + diff.x * scale * pct;
		frc.y = frc.y + diff.y * scale * pct;
	}
}

//ʹ��������Ӧ�����������
void par::addAttractionForce(float x, float y, float radius, float scale) {
	
	ofVec2f posOfForce;
	posOfForce.set(x, y);

	ofVec2f diff = pos - posOfForce;
	float length = diff.length();

	bool bAmCloseEnough = true;
	if (radius > 0) {
		if (length > radius) {
			bAmCloseEnough = false;
		}
	}
	if (bAmCloseEnough == true) {
		float pct = 1 - (length / radius); 
		diff.normalize();
		frc.x = frc.x - diff.x * scale * pct;
		frc.y = frc.y - diff.y * scale * pct;
	}
}
//��������������֮����໥�ų���
void par::addRepulsionForce(par &p, float radius, float scale) {
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x, p.pos.y);
	ofVec2f diff = pos - posOfForce;
	float length = diff.length();

	bool bAmCloseEnough = true;
	if (radius > 0) {
		if (length > radius) {
			bAmCloseEnough = false;
		}
	}
	if (bAmCloseEnough == true) {
		float pct = 1 - (length / radius);  
		diff.normalize();
		frc.x = frc.x + diff.x * scale * pct;
		frc.y = frc.y + diff.y * scale * pct;
		p.frc.x = p.frc.x - diff.x * scale * pct;
		p.frc.y = p.frc.y - diff.y * scale * pct;
	}
}
//��������������֮����໥������
void par::addAttractionForce(par &p, float radius, float scale) {
    ofVec2f posOfForce;
	posOfForce.set(p.pos.x, p.pos.y);
	ofVec2f diff = pos - posOfForce;
	float length = diff.length();

	bool bAmCloseEnough = true;
	if (radius > 0) {
		if (length > radius) {
			bAmCloseEnough = false;
		}
	}
	if (bAmCloseEnough == true) {
		float pct = 1 - (length / radius); 
		diff.normalize();
		frc.x = frc.x - diff.x * scale * pct;
		frc.y = frc.y - diff.y * scale * pct;
		p.frc.x = p.frc.x + diff.x * scale * pct;
		p.frc.y = p.frc.y + diff.y * scale * pct;
	}
}
//��������
void par::addDampingForce() {
	frc.x = frc.x - vel.x * damping;
	frc.y = frc.y - vel.y * damping;
}


