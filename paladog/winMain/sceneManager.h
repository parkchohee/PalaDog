#pragma once

#include "singletonBase.h"
#include <map>
#include <string>

class gameNode;

using namespace std;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*> mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	static gameNode *_currentScene; //���� ��
	static gameNode *_loadingScene; //�ε� ��
	static gameNode *_readyScene;	//��ü ��� ���� ��

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadThreadID;

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//�� �߰�
	gameNode* addScene( string sceneName, gameNode *scene );

	//�ε��� �߰�
	gameNode* addLoadingScene( string loadingSceneName, gameNode *scene );

	//�� ü����
	HRESULT	changeScene( string sceneName );
	HRESULT changeScene( string sceneName, string loadingSceneName );

	//�ε� ������ �Լ� ������ ����
	friend DWORD CALLBACK loadingThead( LPVOID prc );
};