#pragma warning(disable : 4996)
//makerec.cc
//github: koust6u ���ε� �Ϸ� 
#include "buffile.h"
#include "recordng.h"
#include "delim.h"
#include <iostream>
#include "recfile.h"
#include <fstream>
#include <iomanip>
#include "iobuffer.h"
#include <string.h>

//file�� write �� �Ŀ� read�Ͽ� ����ϴ� ���α׷� �ۼ� �ǽ� 
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

	Recording* R[10]; //=> 1�忡�� ���� Student record�� �����Ѵ�.
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
		//TextIndex�� ������ index.Insert()
		IndexedFile.Write();
		recaddr = RecordedFile.Write(*R[i]);
		Recaddr[i] = recaddr;
		cout << "Recordin2 R[" << i << "] at recaddr " << recaddr << endl;
		delete R[i];
	}
	//IndexedFile, RecordFile�� write�� ���ڵ带 �д� �ڵ带 �߰��Ѵ�
	//IndexedFile�� ������ index�� ����
	IndexedFile.Close();
	RecordedFile.Close();
	

	char aa[100] = "recording.dat";
	RecordedFile.Open(aa,1);//�ٽ� open  //recFile
	//char *keyname = "DG18807"; ȭ�鿡�� �Է¹޾Ƽ� �ݺ� �����ϰ� ó��
	while(true){
		cout << "1. key �߰� �Է�  2. ����" << endl;
		int num;
		cin >> num;
		if (num == 1) {
			cout << "ã�� �л��� Label�� �Է��ϼ���. : ";
			char Label[20];
			cin >> Label;
			cout << "ã�� �л��� ID�� �Է��ϼ���. : ";
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

	
	//�Էµ� key�� ���� index�� search�� �Ŀ� �ش� ���ڵ带 ����ϴ� ���α׷� - makeind-2.cpp�� �����Ͽ�
	// �� ���α׷��� �����Ͽ� �ϼ�
	system("pause");
	return 1;
}