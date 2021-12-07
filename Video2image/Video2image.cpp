// Video2image.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <conio.h>
extern "C"
{
  #pragma comment(lib, "awpipl2.lib")
}

int main(int argc, char* argv[])
{
	//char VName[40];
	//printf("%s\n",argv[0]);
	//printf("%s\n", argv[1]);
	HCVVIDEO video = awpcvConnect(argv[1]);
	if (video == NULL){
		printf("Could not open video \n");
		_getch();
		return 1;
	}
	awpImage * Img = NULL;//&CurrImg;
	awpImage * CpyImg = NULL;
	int NumFrames, NImg = atoi(argv[2]), Dec, VNum = atoi(argv[5]);
	char FName[40];
	awpcvNumFrames(video, &NumFrames);
	printf("%d\n",NumFrames);
	/*printf("Enter number of images\n");
	scanf_s("%d", &NImg);*/
	Dec = NumFrames/NImg;
	awpcvQueryImagePos(video, &Img, 0);
	int NewHeight = atoi(argv[4]), Height = Img->sSizeY;
	int NewWidth = atoi(argv[3]), Width = Img->sSizeX;
	printf("%d x %d\n", Width,Height);
	/*printf("Enter new width\n");
	scanf_s("%d", &NewWidth);
	printf("Enter new heigth\n");
	scanf_s("%d", &NewHeight);
	printf("Enter number of video\n");
	scanf_s("%d", &VNum);*/
	for (int pos = 0; pos < NImg; pos++){
		awpcvQueryImagePos(video, &Img, pos*Dec);
		awpCopyImage(Img, &CpyImg);
		awpResizeBilinear(CpyImg, NewWidth, NewHeight);
		awpConvert(CpyImg, AWP_CONVERT_3TO1_BYTE);
		FName[0] = '\0';
		//sprintf_s(FName, "C:\\Users\\Авас yuri\\Desktop\\2\\%d_%d.awp", VNum,pos);
		sprintf_s(FName, argv[6], VNum, pos);
		awpSaveImage(FName, CpyImg);
		awpReleaseImage(&CpyImg);
	}
	awpcvFreeImage(Img);
	awpcvDisconnect(video);
	_getch();
	return 0;
} 