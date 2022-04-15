#pragma warning(disable : 4996)
//makerec.cc
//github: koust6u 업로드 완료 
#include "buffile.h"
#include "recordng.h"
#include "delim.h"
#include <iostream>
#include "recfile.h"
#include <fstream>
#include <iomanip>
#include "iobuffer.h"
#include <string.h>

//file에 write 한 후에 read하여 출력하는 프로그램 작성 실습 
// create two files with the recordings of Figure 7.2
//    the file "record.dat" is created using class BufferFile
//    the file "record2.dat" is created using class RecordFile<Recording>
using namespace std;
int main(void)
{
	int recaddr;
	int result;
	DelimFieldBuffer::SetDefaultDelim('|');
	DelimFieldBuffer Buffer;
	Recording::InitBuffer(Buffer);
	BufferFile IndexedFile(Buffer);

	char* myfile;
	myfile = new char[100];
	strcpy(myfile, "record.ing");
	result = IndexedFile.Create(myfile, ios::out);
	cout << "main()::create file " << result << endl;
	if (!result)
	{
		cout << "main()::Unable to create file " << myfile << endl;
		result = IndexedFile.Open(myfile, ios::out);
		cout << "main()::open file " << result << endl;
		if (!result)
		{
			cout << "main()::Unable to open file " << myfile << endl;
			system("pause");

			return 0;
		}
	}
	RecordFile<Recording> RecordedFile(Buffer);
	char* tmp = NULL;
	tmp = new char[100];
	strcpy(tmp, "recording.dat");
	RecordedFile.Create(tmp, ios::out);

	Recording* R[10]; //=> 1장에서 만든 Student record로 변경한다.
	char temp[10] = "LON"; char temp2[10] = "2312"; char temp3[30] = "201724425";
	char temp4[30] = "Kim minjong"; char temp5[30] = "KR"; char temp6[10] = "25"; char temp7[10] = "66.5";
	R[0] = new Recording(temp,  temp2, temp3,temp4 , temp5, temp6, temp7);
	char a[10] = "RCA"; char a2[10] = "2626"; char a3[30] = "201655245"; char a4[30] = "Hong gildong"; 
	char a5[30] = "LA"; char a6[10] = "24"; char a7[10] = "77.9";
	R[1] = new Recording(a, a2, a3, a4, a5, a6, a7);
	char b[10] = "WAR"; char b2[10] = "23699"; char b3[30] = "201922547"; char b4[30] = "Lionel Messi";
	char b5[30] = "Paris"; char b6[10] = "22"; char b7[10] = "59.9";
	R[2] = new Recording(b, b2, b3, b4, b5, b6, b7);
	char c[10] = "ANG"; char c2[10] = "3795"; char c3[30] = "202020094"; char c4[30] = "Sadio Mane";
	char c5[30] = "Liverpool"; char c6[10] = "28"; char c7[10] = "69.9";
	R[3] = new Recording(c, c2, c3, c4,c5,c6,c7);
	char d[10] = "COL"; char d2[10] = "38358"; char d3[30] = "201222575"; char d4[30] = "Ronaldo";
	char d5[30] = "Manchester"; char d6[10] = "31"; char d7[10] = "72.5";
	R[4] = new Recording(d,d2, d3, d4,d5,d6,d7);
	char e[10] = "DG"; char e2[10] = "18807"; char e3[30] = "202135914"; char e4[30] = "James";
	char e5[30] = "Columbia"; char e6[10] = "29"; char e7[10] = "68.5";
	R[5] = new Recording(e, e2, e3, e4, e5,e6,e7);
	char f[10] = "MER"; char f2[10] = "75016"; char f3[30] = "201852257"; char f4[30] = "Podolski";
	char f5[30] = "Turkey"; char f6[10] = "35"; char f7[10] = "71.2";
	R[6] = new Recording(f, f2,f3, f4,f5,f6,f7);
	char g[10] = "COL"; char g2[10] = "31809"; char g3[30] = "202215875"; char g4[30] = "Okajaki";
	char g5[30] = "Tokyo"; char g6[10] = "32"; char g7[10] = "75.5";
	R[7] = new Recording(g, g2, g3, g4, g5,g6,g7);
	char h[10] = "DG"; char h2[10] = "139201"; char h3[30] = "201766257"; char h4[30] = "XI jiping";
	char h5[30] = "Beijing"; char h6[10] = "59"; char h7[10] = "99.5";
	R[8] = new Recording(h, h2, h3, h4, h5,h6,h7);
	char i[10] = "FF"; char i2[10] = "245"; char i3[30] = "201955752"; char i4[30] = "Putin";
	char i5[30] = "Mosco"; char i6[10] = "67"; char i7[10] = "84.1";
	R[9] = new Recording(i, i2, i3, i4, i5,i6,i7);
	int Recaddr[10];
	for (int i = 0; i < 10; i++)
	{
		//TextIndex에 없으면 index.Insert()
		IndexedFile.Write();
		recaddr = RecordedFile.Write(*R[i]);
		Recaddr[i] = recaddr;
		cout << "Recordin2 R[" << i << "] at recaddr " << recaddr << endl;
		delete R[i];
	}
	//IndexedFile, RecordFile에 write한 레코드를 읽는 코드를 추가한다
	//IndexedFile에 생성된 index를 저장
	IndexedFile.Close();
	RecordedFile.Close();
	

	char aa[100] = "recording.dat";
	RecordedFile.Open(aa,1);//다시 open  //recFile
	//char *keyname = "DG18807"; 화면에서 입력받아서 반복 실행하게 처리
	while(true){
		cout << "1. key 추가 입력  2. 종료" << endl;
		int num;
		cin >> num;
		if (num == 1) {
			cout << "찾을 학생의 Label을 입력하세요. : ";
			char Label[20];
			cin >> Label;
			cout << "찾을 학생의 ID를 입력하세요. : ";
			char Id[20];
			cin >> Id;
			for (int i = 0; i < 10; i++) {
				RecordedFile.Read(*R[i], Recaddr[i]);
			}
			for (int i = 0; i < 10; i++) {
				if (!strcmp(R[i]->Label, Label)) {
					if (!strcmp(R[i]->IdNum, Id)) {
						R[i]->Print(cout);
						cout << endl;
					}
				}
			}
		}
		else if (num == 2) break;
	}

	
	//입력된 key에 대한 index를 search한 후에 해당 레코드를 출력하는 프로그램 - makeind-2.cpp를 참조하여
	// 본 프로그램을 수정하여 완성
	system("pause");
	return 1;
}