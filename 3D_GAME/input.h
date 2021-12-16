//================================================
//
//3Dアクション(input.h)
//Author:門脇勇斗
//
//================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//================================================
//プロトタイプ宣言
//================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nkey);
bool GetKeyboardTrigger(int nKey);

#endif // !_INPUT_H_