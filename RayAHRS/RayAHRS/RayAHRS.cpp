// RayAHRS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include "MahonyAHRS.h"
#include "quatern2euler.h"
#include "EKF.h"

using namespace std;

int ReadData(vector<float> &b, char *FileName)
{
	string a;

	FILE *fp;
	int i = 0;
	int Piont_count = 0;

	if((fp=fopen(FileName,"r+"))==NULL) //读取1.txt的文件
	{
		printf("读取文件失败 \n ");
		exit(1);
	}
		cout<<"读取"<<"成功\n";

	while(!feof(fp))
	{
		
		a += fgetc(fp);
		if(a[i]=='\n')
		{
			b.push_back((float)atof(a.c_str()));
			//cout<<b[Piont_count]<<'\n';
			a="";//清空该字符串
			i=0;
			Piont_count++;
		}	
		else 
		{
			if(a[i]=='\0') 
			{
				b.push_back((float)atof(a.c_str()));
				//cout<<b[Piont_count]<<'\n';
				break;
			}
			i++;
		}	 
	}
	fclose(fp);
	return Piont_count;

/*	//------------------------------------------------从这里开始
	printf(" 现在写入文件 \n "); 
	char ch[] = "I'am input something ! \n";
	while(ch[i] != '\0')
	{
		fputc(ch[i],fp);
		i++;
	}
*/  //------------------------------------------------
}

void WriteData(vector<float> &c,int num, char *FileName)
{
	FILE *fp;
	int j = 0;
	ostringstream buffer;

	if((fp=fopen(FileName,"w+"))==NULL) //读取1.txt的文件
	{
		printf("打开文件失败 \n ");
		exit(1);
	}
		cout<<"打开"<<"成功\n";
	
	for(int i=0;i<num;i++)
	{
		buffer<<c[i];
		string str = buffer.str();
		while(str[j] != '\0')
		{
			fputc(str[j],fp);
			j++;
		}
		fputc('\n',fp);
		str="";//清空该字符串
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int count=0;
	int k=0;
	vector<float> Gx;
	vector<float> Gy;
	vector<float> Gz;

	vector<float> Ax;
	vector<float> Ay;
	vector<float> Az;
	 
	vector<float> Qq0;
	vector<float> Qq1;
	vector<float> Qq2;
	vector<float> Qq3;
	
	vector<float> Pphi;
	vector<float> Ttheta;
	vector<float> Ppsi;

	count=ReadData(Gx,"Gx.txt");
	count=ReadData(Gy,"Gy.txt");
	count=ReadData(Gz,"Gz.txt");

	count=ReadData(Ax,"Ax.txt");
	count=ReadData(Ay,"Ay.txt");
	count=ReadData(Az,"Az.txt");

	cout<<count<<'\n';
	
	

	for(k=0;k<count;k++)
	{
		Gx[k]*=(PI/180.0f);
		Gy[k]*=(PI/180.0f);
		Gz[k]*=(PI/180.0f);

		/*	
		MahonyAHRSupdateIMU( Gx[k], Gy[k], Gz[k], Ax[k], Ay[k], Az[k]);
		quatern2euler( q0,  q1,  q2,  q3) ;
	*/
		EKF(Gx[k], Gy[k], Gz[k], Ax[k], Ay[k], Az[k]);

		//Qq0.push_back((float)Gx[k]);
		Qq0.push_back((float)q0);
		Qq1.push_back((float)q1);
		Qq2.push_back((float)q2);
		Qq3.push_back((float)q3);
	/*	
		Pphi.push_back((float)phi);
		Ttheta.push_back((float)theta);
		Ppsi.push_back((float)psi);*/
		Pphi.push_back((float)phi_Karman);
		Ttheta.push_back((float)theta_Karman);
		Ppsi.push_back((float)psi);
	}
	
	WriteData(Qq0,count,"D:\\github\\MyAHRS\\RayAHRS\\RayAHRS\\output\\Q0.txt");
	WriteData(Qq1,count,"D:\\github\\MyAHRS\\RayAHRS\\RayAHRS\\output\\Q1.txt");
	WriteData(Qq2,count,"D:\\github\\MyAHRS\\RayAHRS\\RayAHRS\\output\\Q2.txt");
	WriteData(Qq3,count,"D:\\github\\MyAHRS\\RayAHRS\\RayAHRS\\output\\Q3.txt");

	WriteData(Pphi,count,"D:\\github\\MyAHRS\\RayAHRS\\RayAHRS\\output\\Phi.txt");
	WriteData(Ttheta,count,"D:\\github\\MyAHRS\\RayAHRS\\RayAHRS\\output\\Theta.txt");
	WriteData(Ppsi,count,"D:\\github\\MyAHRS\\RayAHRS\\RayAHRS\\output\\Psi.txt");
	//cout<<q0<<'\n';
	//cout<<phi<<'\n';
	//cout<<theta<<'\n';
	//cout<<psi<<'\n';

	return 0;
}

