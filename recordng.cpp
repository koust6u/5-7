//Recording.cpp
#include "recordng.h"
#include <strstream>
#include <string.h>

Recording::Recording()
{
	IdNum[0] = 0;
	SID[0] = 0;
	Name[0] = 0;
	Address[0] = 0;
	Age[0] = 0;
	Weight[0] = 0;
}

Recording::Recording(char* label,char* idNum, char* sid,  char* name, char* add, char* age, char* weight)
{
	strcpy_s(Label, label);
	strcpy_s(SID, sid); strcpy_s(IdNum, idNum);
	strcpy_s(Name, name); strcpy_s(Address, add);
	strcpy_s(Age, age); strcpy_s(Weight, weight);
}

char* Recording::Key() const
{// produce key as concatenation of Label and IdNum
	ostrstream key;
	key << Label << IdNum << ends;
	return key.str();
}

int Recording::Pack(IOBuffer& Buffer) const
{// return TRUE if all succeed, FALSE o/w
	int numBytes;
	Buffer.Clear();
	numBytes = Buffer.Pack(Label);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(IdNum);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(SID);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Name);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Address);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Age);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Weight);
	if (numBytes == -1) return FALSE;
	return TRUE;
}

int Recording::Unpack(IOBuffer& Buffer)
{// unpack with maximum size, and add null termination to strings
	int numBytes;
	numBytes = Buffer.Unpack(Label, 9);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Unpack(IdNum, 6);
	if (numBytes == -1) return FALSE;
	IdNum[numBytes] = 0;
	numBytes = Buffer.Unpack(SID, 29);
	if (numBytes == -1) return FALSE;
	SID[numBytes] = 0;
	numBytes = Buffer.Unpack(Name, 29);
	if (numBytes == -1) return FALSE;
	Name[numBytes] = 0;
	numBytes = Buffer.Unpack(Address, 29);
	if (numBytes == -1) return FALSE;
	Address[numBytes] = 0;
	numBytes = Buffer.Unpack(Age, 9);
	if (numBytes == -1) return FALSE;
	Age[numBytes] = 0;
	numBytes = Buffer.Unpack(Weight, 9);
	if (numBytes == -1) return FALSE;
	Weight[numBytes] = 0;
	return TRUE;
}

void Recording::Print(ostream& stream, char* label) const
{
	stream << Label << '|' << IdNum << '|' << SID << '|' << Name << '|' << Address << '|'
		<< Age << '|' << Weight;
}
int Recording::InitBuffer(FixedFieldBuffer& Buffer)
// initialize a FixedFieldBuffer to be used for Persons
{
	int result = 0;
	result = result && Buffer.AddField(10);
	result = Buffer.AddField(7); // IdNum[7]
	result = result && Buffer.AddField(30); // Title[30]
	result = result && Buffer.AddField(30); // Composer[30]
	result = result && Buffer.AddField(30); // Artist[30]
	result = result && Buffer.AddField(10);
	result = result && Buffer.AddField(10);// Label[7]
	return result;
}
//char IdNum[7]; char Title[30]; char Composer[30];char Artist[30]; char Label[7];
int Recording::InitBuffer(DelimFieldBuffer& Buffer)
// initialize a DelimFieldBuffer to be used for Persons
{
	return TRUE;
}

int Recording::InitBuffer(LengthFieldBuffer& Buffer)
// initialize a LengthFieldBuffer to be used for Persons
{
	return TRUE;
}
