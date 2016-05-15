
#include "stdafx.h"
#include "EKF.h"
#include "quatern2euler.h"
#include <math.h>

#define sampleFreq	256.0f			// sample frequency in Hz

const float u = 0.01f;
const float dt = ( 1.0f / sampleFreq );
float phi_bias = 0.0f;
float theta_bias = 0.0f;
volatile float phi_Karman = 0.0f;
volatile float theta_Karman = 0.0f;
float pa = 0.0f;
float pg = 0.0f;
float Q = 0.01f; //ϵͳ����
float Ra = 3.8034f;//��������
float Rg = 58.2f;//��������



void EKF(float gx, float gy, float gz, float ax, float ay, float az)
{
	float phi_acc = 0.0f, theta_acc = 0.0f;
	float Kga = 0.0f , Kgg = 0.0f;
	float Xx = 0.0f , Xy = 0.0f;
	float recipNorm = 0.0f;

	//--------------------acc_angle calculate-------------------//
	// Normalise accelerometer measurement
	recipNorm = sqrt(ax * ax + ay * ay + az * az);
	ax /= recipNorm;
	ay /= recipNorm;
	az /= recipNorm;

	phi_acc = atan2(ay, sqrt(az * az + ax * ax));
	theta_acc = -atan2(ax, sqrt(az * az+ u * ay * ay));   
	phi_acc *=   180 / PI;   // �õ��ǶȲ�ת��Ϊ�� ROLL
	theta_acc  *= 180 / PI;   // �õ��ǶȲ�ת��Ϊ�� Pitch

    //--------------------Gyro_angle calculate-------------------//
	gx *= 180 / PI;
	gy *= 180 / PI;
	gz *= 180 / PI;

	phi += gx * dt;
	theta += gy * dt;
	psi += gz * dt;

/*	
	phi = phi_acc;
	theta = theta_acc;
	psi = gz * dt;
*/

	//--------------------EFK---------------------//
	/*
	phi -= 0.1*phi_bias;
	theta -= 0.1*theta_bias;

	phi_bias += phi - phi_acc;	
	theta_bias += theta - theta_acc;
*/
/*	Xx = phi_Karman;
	Xy = theta_Karman;

	pa += Q;
	pg += Q;

	Kga = pa / (pa + Ra);//����������(4)
	Kgg = pg / (pg + Rg);//����������(4)

	phi_Karman = Xx + Kga*(phi_acc - Xx) + Kgg*(phi - Xx);//���Ż�����ֵ(3)
	theta_Karman = Xy + Kga*(theta_acc - Xy) + Kgg*(theta - Xy);//���Ż�����ֵ(3)

	pa = (1 - Kga)*pa;//����t״̬��Э����(5)
	pg = (1 - Kgg)*pg;//����t״̬��Э����(5)
*/
}