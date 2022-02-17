// Img2featureVector.cpp: определяет точку входа для консольного приложения.
//
// Player.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

extern "C"
{
//#pragma comment(lib, "awpipl2.lib")
//#pragma comment(lib, "awplflib.lib")
}

int Nout = 300;
void features(char* argv[], int sxbase, int sybase, int wbase, int hbase, TLFObjectList &list);
void tiles(char* argv[], int Levels, int sx, int sy, int wx, int wy, TLFObjectList &list);

int main(int argc, char* argv[])
{
	if (argc < 13) return 2;
		char FName[60];
		TLFImage img;
		ofstream sink;
		TLFObjectList list;
		tiles(argv, atoi(argv[1]), 0, 0, 159, 89, list);
		int Ncolumns = list.GetCount();
		sink.open(argv[9]);
		for (int VNumb = 1; VNumb <= atoi(argv[11]); VNumb++){
			for (int ImgNum = 1; ImgNum <= atoi(argv[12]); ImgNum++){
				sink << VNumb << ";" << ImgNum << ";";
				sprintf_s(FName, "%s\\%d_%d.awp",argv[10], VNumb, ImgNum);
				img.LoadFromFile(FName);
				for (int Column = 0; Column < Ncolumns; Column++){
					ILFFeature *f = (ILFFeature*)list.Get(Column);
					if (strcmp(f->GetName(), "TLFColorSensor9Bit") == 0){
						int temp = (int)f->fCalcValue(&img);
						int r = temp & 7;
						int g = ((temp & (7 << 3)) >> 3);
						int b = ((temp & (7 << 6)) >> 6);
						sink << r << ";";
						sink << g << ";";
						sink << b << ";";
					}
					else sink << f->fCalcValue(&img) << ";";
				}
				sink << endl;
			}
		}
		sink.close();
	_getch();
	return 0;
}

void features(char* argv[], int sxbase, int sybase, int wbase, int hbase, TLFObjectList &list){
	if (strcmp(argv[2], "1") == 0){
		TLFAFeature *f = new TLFAFeature(sxbase, sybase, wbase, hbase);
		list.Add(f);
	}
	if (strcmp(argv[3], "1") == 0){
		TLFSFeature *f = new TLFSFeature(sxbase, sybase, wbase, hbase);
		list.Add(f);
	}
	if (strcmp(argv[4], "1") == 0){
		TLFHFeature *f = new TLFHFeature(sxbase, sybase, wbase, hbase / 2);
		list.Add(f);
	}
	if (strcmp(argv[5], "1") == 0){
		TLFVFeature *f = new TLFVFeature(sxbase, sybase, wbase / 2, hbase);
		list.Add(f);
	}
	if (strcmp(argv[6], "1") == 0){
		TLFDFeature *f = new TLFDFeature(sxbase, sybase, wbase / 2, hbase / 2);
		list.Add(f);
	}
	if (strcmp(argv[7], "1") == 0){
		TLFCFeature *f = new TLFCFeature(sxbase, sybase, wbase, hbase);
		list.Add(f);
	}
	if (strcmp(argv[8], "1") == 0){
		TLFColorSensor9Bit *f = new TLFColorSensor9Bit(sxbase, sybase, wbase, hbase);
		list.Add(f);
	}

}
void tiles(char* argv[], int Levels, int sx, int sy, int wx, int wy, TLFObjectList &list){
	features(argv, sx, sy, wx, wy,list);
	if (Levels > 0){
		Levels--;
		tiles(argv, Levels, sx, sy, wx / 2, wy / 2, list);
		tiles(argv, Levels, sx + wx / 2, sy, wx / 2, wy / 2, list);
		tiles(argv, Levels, sx, sy + wy / 2, wx / 2, wy / 2, list);
		tiles(argv, Levels, sx + wx / 2, sy + wy / 2, wx / 2, wy / 2, list);
	}
}
