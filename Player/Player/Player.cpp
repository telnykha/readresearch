// Player.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
extern "C"
{
#pragma comment(lib, "awpipl2.lib")
}

//CvCapture* capture = NULL;
HCVVIDEO video;
int  num_frames;
int  frames;
const char _MODULE_[] = "";
awpRect rect;
awpImage* img = NULL;
//int process_video(const char* lpFileName, int mode);


int main(int argc, char* argv[])
{
	//capture = cvCaptureFromFile("c:\\1.mp4");
	video = awpcvConnect("c:\\1.mp4");
	if (awpcvQueryImagePos(video, &img,0) != S_OK)return 1;
	rect.bottom = img->sSizeY/12;
	rect.top = 1;//  10;
	rect.left = 1;// ->sSizeX - 1;
	rect.right = img->sSizeX/12;// /*img->sSizeX/12*/100;
	awpcvNumFrames(video, &num_frames );//(int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
	frames = 0;
	for (;;)
	{

		int c,i;
		awpcvWaitKey(10, &c);//c = cvWaitKey(10);
		if ((char)c == 27)
		{
			break;
		}

		img = NULL;
		//IplImage* frame = NULL;
		//awpcvQueryImage(video, &img);
		//frame = cvQueryFrame(capture);
		if (awpcvQueryImage(video, &img) != S_OK)
			break;
		//cvShowImage(_MODULE_, frame);
		awpFillRect(img, &rect, 2, 255);
		awpcvShowImage(_MODULE_, img);
		awpReleaseImage(&img);
		frames++;

	}
	awpcvDisconnect(video);
	//cvReleaseCapture(&capture);
	//capture = NULL;
	return 0;
}

