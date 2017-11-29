#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;

#define WINDOW_NAME " 线性混合示例 "      //为窗口标题定义的宏

int g_nAlphaValueSlier;                 //滑动条对应的变量
const int g_nMaxAlphaValue = 100;         //Alpha 值的最大值
double g_dAlpaValue;
double g_dBetaValue;

//声明存储图像的变量
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

void on_Trackbar(int, void*)
{
	g_dAlpaValue = (double)g_nAlphaValueSlier / g_nMaxAlphaValue;
	g_dBetaValue = (1.0 - g_dAlpaValue);
	addWeighted(g_srcImage1, g_dAlpaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);

	imshow(WINDOW_NAME, g_dstImage);
}

int main()
{
	g_srcImage1 = imread("3091.jpg");
	g_srcImage2 = imread("3117.jpg");
	if (!g_srcImage1.data)
	{
		printf("读取第一幅图片失败\n");
		return -1;
	}
	if (!g_srcImage2.data)
	{
		printf("读取第二幅图片失败\n");
		return -1;
	}

	
	g_nAlphaValueSlier = 70;
	namedWindow(WINDOW_NAME, WINDOW_NORMAL);

	char TrackbarName[50];
	sprintf(TrackbarName, "透明值 %d", g_nMaxAlphaValue);
	createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlier , g_nMaxAlphaValue, on_Trackbar);

	on_Trackbar(g_nAlphaValueSlier, 0);

	waitKey(0);

	return 0;



}
