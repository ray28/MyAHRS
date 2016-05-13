
#include "stdafx.h"
#include "quatern2euler.h"
#include <math.h>

volatile float phi = 0.0f, theta = 0.0f, psi = 0.0f;		// 
const float PI=3.141592f;

/*
void quatern2euler(float Q0, float Q1, float Q2, float Q3) 
{
	float R11=0.0f, R21=0.0f, R31=0.0f, R32=0.0f, R33=0.0f;

	R11 = 2*Q0*Q0-1+2*Q1*Q1;
    R21 = 2*(Q1*Q2-Q0*Q3);
    R31 = 2*(Q1*Q3+Q0*Q2);
    R32 = 2*(Q2*Q3-Q0*Q1);
    R33 = 2*Q0*Q0-1+2*Q3*Q3;

    phi = atan2(R32, R33);
    theta = -atan(R31 / sqrt(1-R31*R31) );
    psi = atan2(R21, R11);

	phi *= 180/PI;
    theta *= 180/PI;
    psi *= 180/PI;

}*/

void quatern2euler(float Q0, float Q1, float Q2, float Q3) 
{

    phi = atan2(2*(Q0*Q1+Q2*Q3),(1-2*(Q1*Q1+Q2*Q2)));
    theta = -asin(2*(Q1*Q3-Q0*Q2));
    psi = atan2(2*(Q1*Q2+Q0*Q3),(1-2*(Q2*Q2+Q3*Q3)));

	phi *= 180/PI;
    theta *= 180/PI;
    psi *= 180/PI;

}