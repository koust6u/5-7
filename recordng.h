// recordng.h

#ifndef RECORDING_H
#define RECORDING_H

#include <iostream>
#include "iobuffer.h"

#include "fixfld.h"
#include "length.h"
#include "delim.h"
using namespace std;
// class person with fixed field buffer

class Recording
	// a recording with a composite key
{
public:
	Recording();
	Recording( char* Label, char* idNum, char* sid,char* name,char* add, char* age, char* weight);
	char IdNum[7]; char SID[30]; char Name[30];
	char Address[30]; char Age[10]; char Weight[10];
	char Label[10];
	char* Key() const; // return key of object
	int Unpack(IOBuffer&);
	int Pack(IOBuffer&) const;
	void Print(ostream&, char* label = 0) const;
	static int InitBuffer(DelimFieldBuffer&);
	static int InitBuffer(LengthFieldBuffer&);
	static int InitBuffer(FixedFieldBuffer&);
};

ostream& operator << (ostream&, Recording&);
inline ostream& operator << (ostream& stream, Recording& rec)
{
	rec.Print(stream); return stream;
}

#endif
