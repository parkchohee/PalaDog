#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

//�ε� ������ �Լ� ������ ����
DWORD CALLBACK loadingThead( LPVOID prc )
{
	//��ü�� init �Լ��� �����Ѵ�.
	sceneManager::_readyScene->init();

	//���� ���� ��ü�� ������ �ٲ۴�.
	sceneManager::_currentScene = sceneManager::_readyScene;

	//�ε����� �����Ѵ�
	sceneManager::_loadingScene->release();
	sceneManager::_loadingScene = NULL;
	sceneManager::_readyScene = NULL;

	return 0;
}

gameNode * sceneManager::_currentScene = NULL; //���� ��
gameNode * sceneManager::_loadingScene = NULL; //�ε� ��
gameNode * sceneManager::_readyScene = NULL;   //��ü ��� ���� ��

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{
}


HRESULT sceneManager::init()
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;

	return S_OK;
}

void sceneManager::release()
{
	//�� ��ü�� ���鼭 �����
	mapSceneIter miSceneList = _mSceneList.begin();

	for ( ; miSceneList != _mSceneList.end(); )
	{
		//�������� �ݺ��ڸ� �������� �ʴ´�.
		if ( miSceneList->second != NULL )
		{
			if ( miSceneList->second == _currentScene ) miSceneList->second->release();
			SAFE_DELETE( miSceneList->second );
			miSceneList = _mSceneList.erase( miSceneList );
		}
		else
		{
			++miSceneList;
		}
	}

	_mSceneList.clear();
}

void sceneManager::update()
{
	if ( _currentScene ) _currentScene->update();
}

void sceneManager::render()
{
	if ( _currentScene ) _currentScene->render();
}

//�� �߰�
gameNode* sceneManager::addScene( string sceneName, gameNode *scene )
{
	if ( !scene ) return NULL;

	_mSceneList.insert( make_pair( sceneName, scene ) );

	return scene;
}

//�ε��� �߰�
gameNode* sceneManager::addLoadingScene( string loadingSceneName, gameNode *scene )
{
	if ( !scene ) return NULL;

	_mLoadingSceneList.insert( make_pair( loadingSceneName, scene ) );

	return scene;
}

//�� ü����
HRESULT	sceneManager::changeScene( string sceneName )
{
	//�ٲٷ��� ���� ã�´�.
	mapSceneIter find = _mSceneList.find( sceneName );

	//�ٲ��� ���ϸ� �޽���������
	if ( find == _mSceneList.end() ) return E_FAIL;

	//�ٲٷ� �ϴ� ���� ������� ������ �׳� ����
	if ( find->second == _currentScene ) return S_OK;

	//���Ӱ� ����Ǵ� ���� �ʱ�ȭ����
	if ( SUCCEEDED( find->second->init() ) )
	{
		//������ �ִ� ���� ������
		//if ( _currentScene ) _currentScene->release();
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}

HRESULT sceneManager::changeScene( string sceneName, string loadingSceneName )
{
	//�ٲٷ��� ���� ã�´�.
	mapSceneIter find = _mSceneList.find( sceneName );

	//�ٲ��� ���ϸ� �޽� ����
	if ( find == _mSceneList.end() ) return E_FAIL;

	//�ٲٷ� �ϴ� ���� ���� ���� ������
	if ( find->second == _currentScene ) return S_OK;

	//�ٲٷ��ϴ� ���� ã�´�
	mapSceneIter findLoading = _mLoadingSceneList.find( loadingSceneName );

	//ã�� ���ϸ� �Ϲ� �ε�...
	if ( findLoading == _mLoadingSceneList.end() ) return changeScene( sceneName );

	//�ε��� �ʱ�ȭ
	if ( SUCCEEDED( findLoading->second->init() ) )
	{
		//���� �ִٸ� ������
		if ( _currentScene ) _currentScene->release();

		//�ε���
		_loadingScene = findLoading->second;

		//�ε��� ���� �� ����� ��
		_readyScene = find->second;

		//�ε��� ȣ��
		CloseHandle( CreateThread( NULL, 0, loadingThead, NULL, 0, &_loadThreadID ) );

		return S_OK;
	}

	return E_FAIL;
}