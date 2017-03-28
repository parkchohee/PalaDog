// winMain.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "gameStudy.h"

/* #### �������� #### */
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = {0, 0};
bool _leftButtonDown = false;
bool _rightButtonDown = false;

gameStudy _gs;

/* #### �Լ� #### */
LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
void setWindowSize( int x, int y, int width, int height );

/* #### ���� #### */
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow )
{
	_hInstance = hInstance;

	//MSG : �ü������ �����ϴ� �޽��� ������ �����ϱ� ���� ����ü
	MSG message;

	//WNDCLASS : �������� ������ �����ϱ� ���� ����ü
	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;             //Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;             //������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH) GetStockObject( WHITE_BRUSH ); //��׶���
	wndClass.hCursor = LoadCursor( NULL, IDC_ARROW );  //Ŀ��
	wndClass.hIcon = LoadIcon( NULL, IDI_APPLICATION );//������
	wndClass.hInstance = hInstance;              //�ν��Ͻ�
	wndClass.lpfnWndProc = (WNDPROC) WndProc;    //������ ���ν���
	wndClass.lpszClassName = WINNAME;            //Ŭ�����̸�
	wndClass.lpszMenuName = NULL;                //�޴��̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;    //������ ��Ÿ��

	//������ Ŭ���� ���
	RegisterClass( &wndClass );

	//������ ����
	_hWnd = CreateWindow(
		WINNAME,     //������ Ŭ������ �̸�
		WINNAME,     //������ Ÿ��Ʋ�� �̸�
		WINSTYLE,    //������ ��Ÿ��
		WINSTARTX,   //������ ȭ����ǥ x
		WINSTARTY,   //������ ȭ����ǥ y
		WINSIZEX,    //������ ȭ����ǥ width
		WINSIZEY,    //������ ȭ����ǥ height
		NULL,        //�θ� ������
		(HMENU) NULL,//�޴��ڵ�
		hInstance,   //�ν��Ͻ� ����
		NULL );      //������ �� �ڽ� �����츦 �����ϸ�
					 //�������ֵ� �׷��� ������ NULL

	//ȭ�� �۾� ������ ���� ���
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//ȭ�鿡 ������ �����ش�
	ShowWindow( _hWnd, nCmdShow );

	//���� ���͵��� �ʱ�ȭ�� ���������� �̷����� �ʾҴٸ� �׳� ������
	if ( FAILED( _gs.init() ) )
	{
		return 0;
	}

	//�޽��� ����~~

	//GetMessage : GetMessage�� �޽����� ������ �� ���������� �����ִ� �Լ��̰�,
	//PeekMessage : PeekMessage�� �޽����� ������ ���ϵǴ� �Լ��μ�,
	//��� �����Ǵ� �Լ��̴�.


	while ( true ) //���ӿ�
	{
		if ( PeekMessage( &message, NULL, 0, 0, PM_REMOVE ) )
		{
			if ( message.message == WM_QUIT ) break;
			TranslateMessage( &message );
			DispatchMessage( &message );
		}
		else
		{
			TIMEMANAGER->update( 70.f );
			_gs.update();
			_gs.render();
		}
	}

	//TranslateMessage : Ű���� �Է¸޽��� ó���� ����Ѵ�.
	//�Էµ� Ű�� ����Ű���� Ȯ���� �빮�� Ȥ�� �ҹ���, �ѱ�, ����,
	//������ ���� WM_CHAR�޽����� �߻���Ų��.

	//DispatchMessage : ������ ���ν������� ���޵� �޽����� ����
	//������� �������ش�

	//�޽��� ť�� �޽����� ������ �޽��� ó��...
	//while ( GetMessage( &message, 0, 0, 0 ) ) //�Ϲ� ���α׷���
	//{
	//	TranslateMessage( &message );
	//	DispatchMessage( &message );
	//}

	//���͵� ����
	_gs.release();

	//������ Ŭ���� ��� ����
	UnregisterClass( WINNAME, hInstance );

	return message.wParam;
}

//������ ���ν��� : �޽����� �ü���� ����
//������ �ü���� ȣ�����ش�

//hWnd : ��� �����쿡�� �߻��� �޽������� ����
//iMessage : �޽��� ���� ��ȣ
//wParam : unsigned int ���콺 ��ư�� ����, Ű���� ����Ű�� ���¸� ����
//lParam : unsigned long ���콺 Ŭ�� ��ǥ ����
LRESULT CALLBACK WndProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam )
{
	return _gs.MainProc( hWnd, iMessage, wParam, lParam );
}

//������ ������ WINSIZEX, WINSIZEY �� �°�
void setWindowSize( int x, int y, int width, int height )
{
	RECT rc;

	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	AdjustWindowRect( &rc, WINSTYLE, false );

	SetWindowPos( _hWnd, NULL, x, y, ( rc.right - rc.left ),
		( rc.bottom - rc.top ), SWP_NOZORDER | SWP_NOMOVE );
}
