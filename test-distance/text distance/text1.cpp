#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace cv;
using namespace std;

/// ȫ�ֱ���
Mat src, srcGray;
int maxCorners = 10;	//�ǵ���������ֵ 
int maxCornersThresh = 20;	//�ǵ�������ֵ�����ޣ���������Χ0-20�� 
char* detectWindow = "detection";
char* refineWindow = "refinement";

/// �ǵ㾫׼����������
void doCornerRefinement(int, void*);

int main(int argc, char** argv)
{
	/// ����ͼ�񲢻ҶȻ� 
	src = imread("D:\picture\PIC00017.bmp", 1);
	cvtColor(src, srcGray, CV_BGR2GRAY);

	/// ������ʾ�����Լ�������  
	namedWindow(detectWindow, CV_WINDOW_AUTOSIZE);
	createTrackbar("max  num:", detectWindow, &maxCorners, maxCornersThresh, doCornerRefinement);
	imshow(detectWindow, src);

	doCornerRefinement(0, 0);

	waitKey(0);
	return(0);
}

/// ʹ��Shi-Tomasi�������ǵ㣬�ٶԽǵ�λ�ý��о�׼��
void doCornerRefinement(int, void*)
{
	if (maxCorners < 1)
		maxCorners = 1;

	/// Shi-Tomasi�Ĳ�������
	vector<Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = false;	//��ʹ��Harris����㷨
	double k = 0.04;

	/// ��ȿ���ԭͼ�����ڻ��ƽǵ�
	Mat detectSrcCopy = src.clone();
	Mat refineSrcCopy = src.clone();

	/// Ӧ��Shi-Tomasi�ǵ����㷨 
	goodFeaturesToTrack(srcGray,
		corners,
		maxCorners,
		qualityLevel,
		minDistance,
		Mat(),	//δѡ�����Ȥ���� 
		blockSize,
		useHarrisDetector,
		k);

	/// ��maxCorners��ֵ��Сʱ����������ֵ������һ���ģ�  
	/// ��maxCorners��ֵ�ϴ�ʱ��ʵ�ʼ�⵽�Ľǵ���Ŀ�п���С��maxCorners����������ֵ��һ����  
	cout << "*  detected corners : " << corners.size() << endl;
	cout << "** max corners: " << maxCorners << endl;

	/// 1--��ʾ�ǵ�����
	int r = 3;
	cout << "-- Before refinement: " << endl;
	for (int i = 0; i < corners.size(); i++)
	{
		// ��ʾ���ǵ�
		circle(detectSrcCopy, corners[i], r, Scalar(255, 0, 255), -1, 8, 0);
		// ����ǵ�����
		cout << "	[" << i << "]  (" << corners[i].x << "," << corners[i].y << ")" << endl;
	}
	namedWindow(detectWindow, CV_WINDOW_AUTOSIZE);
	imshow(detectWindow, detectSrcCopy);

	/// �ǵ�λ�þ�׼������
	Size winSize = Size(5, 5);
	Size zeroZone = Size(-1, -1);
	TermCriteria criteria = TermCriteria(
		CV_TERMCRIT_EPS + CV_TERMCRIT_ITER,
		40, //maxCount=40
		0.001);	//epsilon=0.001
	/// ���㾫׼����Ľǵ�λ��
	cornerSubPix(srcGray, corners, winSize, zeroZone, criteria);

	/// 2--��ʾ��׼����Ľǵ�
	cout << "-- After refinement: " << endl;
	for (int i = 0; i < corners.size(); i++)
	{
		// ��ʾ���ǵ�
		circle(refineSrcCopy, corners[i], r, Scalar(255, 0, 255), -1, 8, 0);
		// ����ǵ�����
		cout << "	[" << i << "]  (" << corners[i].x << "," << corners[i].y << ")" << endl;
	}
	namedWindow(refineWindow, CV_WINDOW_AUTOSIZE);
	imshow(refineWindow, refineSrcCopy);

	cout << endl;
}