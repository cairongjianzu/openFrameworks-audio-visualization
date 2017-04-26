#pragma once
#include "ofMain.h"
class par
{
public:
	par();
	
	virtual ~par();

	ofVec2f pos;//��ʾ����λ��
	ofVec2f vel;//��ʾ�����ƶ��ٶȱ仯
	ofVec2f frc;//��ʾ���ı仯
	//����ϵ��
	float damping;
	//��ʼ�����ӵ�λ������
	void setInitialCondition(float px, float py, float vx, float vy);
	void update();
	//��ʾ����
	void draw(ofColor c);
	void resetForce();//��������СΪ��
	void addForce(float x, float y);//ʹ���仯
	//ʹ��������Ӧ������ų���
	void addRepulsionForce(float x, float y, float radius, float scale);
	//ʹ��������Ӧ�����������
	void addAttractionForce(float x, float y, float radius, float scale);
	//��������������֮����໥�ų���
	void addRepulsionForce(par &p, float radius, float scale);
	//��������������֮����໥������
	void addAttractionForce(par &p, float radius, float scale);
	//��������
	void addDampingForce();


};

