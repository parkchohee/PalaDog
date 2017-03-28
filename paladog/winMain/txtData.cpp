#include "stdafx.h"
#include "txtData.h"


txtData::txtData()
{
}


txtData::~txtData()
{
}

HRESULT txtData::init()
{
	return S_OK;
}

void txtData::release()
{
}

void txtData::txtSave( const char * saveFileName, vector<string> vStr )
{
	HANDLE file;

	//���� ���� ũ�� �÷���... ���� ������ ��
	char str[2048];
	DWORD write;

	strncpy_s( str, 2048, vectorArrayCombine( vStr ), 2046);

	//���� ����
	file = CreateFile( saveFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL );

	//���� ���Ͽ� ����
	WriteFile( file, str, 2048, &write, NULL );

	//�� �� ������ �ݾ� �ش�
	CloseHandle( file );
}

char * txtData::vectorArrayCombine( vector<string> vArray )
{
	char str[2048];

	ZeroMemory( str, sizeof(str) );

	for ( int i = 0; i < vArray.size(); i++ )
	{
		strncat_s( str, 2048, vArray[i].c_str(), 2046);
		if ( i + 1 < vArray.size() ) strcat_s( str, "," );
	}

	return str;
}

vector<string> txtData::txtLoad( const char * loadFileName )
{
	HANDLE file;

	char str[2048];
	DWORD read;

	memset( str, 0, 2048);

	//�ڵ鿡 �о���� ���� �Ӽ� ����(����)
	file = CreateFile( loadFileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

	if (file != INVALID_HANDLE_VALUE)
	{
		//�̶� �о����
		ReadFile(file, str, 2048, &read, NULL);

		CloseHandle(file);
	}
	else
	{
		// ������ ���� ���
		// �׳� ����......
		vector<string> vStr;
		return vStr;


		// ������ ���� ���...
		// ���ο� ���� �����...............
		/*vStr.push_back("test");

		txtSave(loadFileName, vStr);

		memset(str, 0, 128);

		file = CreateFile(loadFileName, GENERIC_READ, 0, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, str, 128, &read, NULL);

		CloseHandle(file);*/
	}

	return charArraySeparation(str);
}

vector<string> txtData::charArraySeparation( char charArray[] )
{
	vector<string> vArray;

	char* temp;
	char* separator = ",";
	char* token;

	token = strtok_s( charArray, separator, &temp );
	vArray.push_back( token );

	while ( NULL != ( token = strtok_s( NULL, separator, &temp ) ) )
	{
		vArray.push_back( token );
	}

	return vArray;
}
