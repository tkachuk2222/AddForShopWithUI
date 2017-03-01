// ShopWithUI.cpp: определяет точку входа для приложения.
//
#include<iostream>
#include "stdafx.h"
#include "ShopWithUI.h"

#include<memory>
#include<string>
#include<exception>
#include<vector>
//#include"List.h"
//#include"Cassa.h"
//#include"products.h"
//#include"storage.h"
//#include"Market.h"

using namespace std;

INT passDir = 1111;
INT passAdm = 1111;
INT passCas = 1111;
INT enterPass();
INT percentDisc = 10;

void openWriteInFile(FILE *f, const char* nameFile, int newPass);
INT openFileAndReadPass(FILE *f, const char* nameFile);
HWND hDirec, hAdmin, hCash, hClient;

#define MAX_LOADSTRING 100
#define CONST const

HINSTANCE		hInst;                                // текущий экземпляр
WCHAR			szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR			szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
INT					enterPass();
void				openWriteInFile(FILE *f, const char* nameFile, int newPass);
INT					openFileAndReadPass(FILE *f, const char* nameFile);

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);

INT_PTR CALLBACK	DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK    DirectorWindow(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AdminWindow(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    CashierWindow(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ClientWindow(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	
	
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
	ShowWindow(hDirec, SW_SHOW);
	ShowWindow(hAdmin, SW_SHOW);
	ShowWindow(hCash, SW_SHOW);
	ShowWindow(hClient, SW_SHOW);

	MSG msg;
	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{


		DispatchMessage(&msg);

	}

	return (int)msg.wParam;
}


INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	//shared_ptr<Market>market(Market::getMarket());
	FILE *f;
	static const wchar_t* passD = TEXT("director.txt");
	static const wchar_t* passA = TEXT("admin.txt");
	static const wchar_t* passC = TEXT("cashier.txt");
	static INT radioCheck;
	

	bool exit = true;

    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:{
		radioCheck = 1;
		CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO4, IDC_RADIO1);

		_wfopen_s(&f, passD, L"wb+");
		if (&f)
			fwrite(&passDir, sizeof(INT), 1, f);
		fclose(f);

		_wfopen_s(&f, passA, L"wb+");
		if (&f)
			fwrite(&passAdm, sizeof(INT), 1, f);
		fclose(f);

		_wfopen_s(&f, passC, L"wb+");
		if (&f)
			fwrite(&passCas, sizeof(INT), 1, f);
		fclose(f);
	}return (INT_PTR)TRUE;
		
	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
			case IDC_RADIO1: {
				radioCheck = 1;
			}return (INT_PTR)TRUE;
			case IDC_RADIO2: {
				radioCheck = 2;
			}return (INT_PTR)TRUE;
			case IDC_RADIO3: {
				radioCheck = 3;
			}return (INT_PTR)TRUE;
			case IDC_RADIO4: {
				radioCheck = 4;
			}return (INT_PTR)TRUE;
			case IDOKCONT: {
					if (radioCheck == 1) {
						wchar_t passworBuffer[30] = TEXT("");
						GetWindowText(GetDlgItem(hDlg, IDC_EDITPASS), passworBuffer, 30);
						INT password = _ttoi(passworBuffer);
						if (password == ::passDir) {
							hDirec = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOGDIRECTOR), hDlg, DirectorWindow);
							ShowWindow(hDirec, SW_SHOW);
						}
						else {
							MessageBox(hDlg, L"Пароль недійсний!", L"Error", MB_OK | MB_ICONERROR);
						}
					}
					else if (radioCheck == 2) {
						wchar_t passworBuffer[30] = TEXT("");
						GetWindowText(GetDlgItem(hDlg, IDC_EDITPASS), passworBuffer, 30);
						INT password = _ttoi(passworBuffer);
						if (password == ::passAdm) {
							hAdmin = CreateDialog(hInst, MAKEINTRESOURCE(IDD_ADMIN), hDlg, AdminWindow);
							ShowWindow(hAdmin, SW_SHOW);
						}
						else {
							MessageBox(hDlg, L"Пароль недійсний!", L"Error", MB_OK | MB_ICONERROR);
						}
					}
					else if (radioCheck == 3) {
						wchar_t passworBuffer[30] = TEXT("");
						GetWindowText(GetDlgItem(hDlg, IDC_EDITPASS), passworBuffer, 30);
						INT password = _ttoi(passworBuffer);
						if (password == ::passCas) {
							hCash = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CASHIER), hDlg, CashierWindow);
							ShowWindow(hCash, SW_SHOW);
						}
						else {
							MessageBox(hDlg, L"Пароль недійсний!", L"Error", MB_OK | MB_ICONERROR);
						}
					}
					else if (radioCheck == 4) {
						hClient = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CLIENT), hDlg, ClientWindow);
						ShowWindow(hClient, SW_SHOW);
					}
			}return (INT_PTR)TRUE;
		}return (INT_PTR)TRUE;
	}
	if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
	{
		EndDialog(hDlg, LOWORD(wParam));
		return (INT_PTR)TRUE;
	}
	break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK    DirectorWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_CLOSE:
	{
		DestroyWindow(hDlg);
		hDirec = NULL;
		return (INT_PTR)TRUE;
	}
	case WM_DESTROY:
		//PostQuitMessage(0);
		SendMessage(hDlg, WM_CLOSE, 0, 0);

		return (INT_PTR)TRUE;
	case WM_COMMAND:

		/*if (LOWORD(wParam) == IDC_BUTTON1)
		{

		hModeless = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hDlg, Modeless);
		return (INT_PTR)TRUE;

		}*/
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			//EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}



INT_PTR CALLBACK    AdminWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_CLOSE:
	{
		DestroyWindow(hDlg);
		hAdmin = NULL;
		return (INT_PTR)TRUE;
	}
	case WM_DESTROY:
		//PostQuitMessage(0);
		SendMessage(hDlg, WM_CLOSE, 0, 0);

		return (INT_PTR)TRUE;
	case WM_COMMAND:

		/*if (LOWORD(wParam) == IDC_BUTTON1)
		{

		hModeless = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hDlg, Modeless);
		return (INT_PTR)TRUE;

		}*/
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			//EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}



INT_PTR CALLBACK    CashierWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_CLOSE:
	{
		DestroyWindow(hDlg);
		hCash = NULL;
		return (INT_PTR)TRUE;
	}
	case WM_DESTROY:
		//PostQuitMessage(0);
		SendMessage(hDlg, WM_CLOSE, 0, 0);

		return (INT_PTR)TRUE;
	case WM_COMMAND:

		/*if (LOWORD(wParam) == IDC_BUTTON1)
		{

		hModeless = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hDlg, Modeless);
		return (INT_PTR)TRUE;

		}*/
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			//EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}



INT_PTR CALLBACK    ClientWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_CLOSE:
	{
		DestroyWindow(hDlg);
		hClient = NULL;
		return (INT_PTR)TRUE;
	}
	case WM_DESTROY:
		//PostQuitMessage(0);
		SendMessage(hDlg, WM_CLOSE, 0, 0);

		return (INT_PTR)TRUE;
	case WM_COMMAND:

		/*if (LOWORD(wParam) == IDC_BUTTON1)
		{

		hModeless = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hDlg, Modeless);
		return (INT_PTR)TRUE;

		}*/
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			//EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}