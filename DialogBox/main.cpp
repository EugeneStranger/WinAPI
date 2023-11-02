#include<Windows.h>
#include "resource.h"

CONST CHAR g_sz_LOGIN_INVITATION[] = "Введите имя пользователя";

BOOL CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, WPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, WPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LRESULT)hIcon);
		//SetFocus(GetDlgItem(hwnd, IDC_BUTTON_COPY));
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SendMessage(hEditLogin, WM_SETTEXT,0,(LPARAM)g_sz_LOGIN_INVITATION);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case IDC_EDIT_LOGIN:
			{
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE]{};
				HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
				SendMessage(hEditLogin,WM_GETTEXT,SIZE,(LPARAM)sz_buffer);
				if (HIWORD(wParam) == EN_SETFOCUS && strcmp(sz_buffer, g_sz_LOGIN_INVITATION) == 0)
					SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");
				if (HIWORD(wParam) == EN_KILLFOCUS && strcmp(sz_buffer, "") == 0)
					SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITATION);
			}
			break;
			case IDC_BUTTON_COPY:
			{
				//1. Создаём буфер чтения:
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				//2. Получаем обработчики текстовых полей:
				HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
				HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
				//HWND hPassword2 = GetDlgItem(hwnd, IDC_STATIC_PASSWORD);
				//Функция GetDlgItem() по ID-ресурса дочернего окна возвращает HWND соответствующего дочернего окна
				//3. Читаем текст из текстового поля:
				SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				//4. Загружаем содержимое текстового буфера в поле PASSWORD:
				SendMessage(hPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
				SendMessage(GetDlgItem(hwnd, IDC_STATIC_PASSWORD), WM_SETTEXT, 0, (LPARAM)sz_buffer);
				SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			}
			break;
			case IDOK: MessageBox(hwnd, "Была нажата кнопка ОК", "Info", MB_OK | MB_ICONINFORMATION); break;
			case IDCANCEL: EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}
