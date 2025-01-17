#include "stdafx.h"
#include "gameNode.h"
//=============================================================
//	## 초기화 ## init()
//=============================================================
HRESULT gameNode::init()
{
	SetTimer(_hWnd, 1, 10, NULL);		//타이머 초기화
	INPUT->init();						//입력매니져 초기화
	RANDOM->init();						//랜덤매니져 초기화

	return S_OK;
}

//=============================================================
//	## 해제 ## release()
//=============================================================
void gameNode::release()
{
	//타이머 해제
	KillTimer(_hWnd, 1);
	//입력매니져 해제
	INPUT->release();
	INPUT->releaseSingleton();
	//랜덤매니져 해제
	RANDOM->release();
	RANDOM->releaseSingleton();
}

//=============================================================
//	## 업데이트 ## update()
//=============================================================
void gameNode::update()
{
	//새로고침 (나중에 고성능 타이머를 만든후에는 사용하지 않는다)
	//더블버퍼링 이후 사용하지 않는다 (true => false)
	InvalidateRect(_hWnd, NULL, TRUE);
}

//=============================================================
//	## 렌더 ## render()
//=============================================================
void gameNode::render(HDC hdc)
{
}

//=============================================================
//	## 메인프로시져 ## MainProc()
//=============================================================
LRESULT gameNode::MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;		
	PAINTSTRUCT ps; 
	switch (message)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:			
		hdc = BeginPaint(hWnd, &ps);
		this->render(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:		
		switch (wParam)
		{
		case VK_ESCAPE:		
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:		
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, message, wParam, lParam));
}
