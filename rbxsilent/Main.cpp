
#include <Windows.h>
#include <iostream>


using namespace std;

LPARAM show_windows = 0;


void instructionCout(int windowStatus) {
    system("cls");
    cout << "Roblox-Headless" << endl;
    cout << "Made By cBass" << endl;
    cout << "Rshift to hide/maximize clients" << endl;
    cout << "END to kill all running Roblox processes and the program" << endl;
    if (windowStatus == 0) {
        cout << "Windows: Hidden" << endl;
    }
    else {
        cout << "Windows: Shown" << endl;
    }
}


static BOOL CALLBACK windcallback(HWND hWnd, LPARAM lparam) {
    int length = GetWindowTextLength(hWnd) + 1;
    char* buffer = new char[length];
    GetWindowTextA(hWnd, buffer, length);
    std::string title(buffer);
    if (lparam == 0) {

        if (title == "Roblox" && IsWindowVisible(hWnd)) {
            cout << "Wait for 30 sec to inject your stuff" << endl;
            Sleep(30000);
            cout << "Doin stuff" << endl;
            system("wmic process where name='RobloxPlayerBeta.exe' CALL setpriority 64");
            //system("PowerShell Get-Process RobloxPlayerBeta | Select-Object ProcessorAffinity"); //seems to not work (Fix)
            //system("PowerShell \"$Process = Get - Process RobloxPlayerBeta; $Process.ProcessorAffinity = 13\""); //seems to not work (Fix)
            ShowWindow(hWnd, SW_HIDE);
            PostMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
            cout << "Found roblox window " << hWnd << " hiding it" << endl;
            instructionCout(0);
            Sleep(1000);
        }
    }
    if (lparam == 1) {
        if (title == "Roblox" && !IsWindowVisible(hWnd)) {
            cout << "Doin Stuff" << endl;
            system("wmic process where name='RobloxPlayerBeta.exe' CALL setpriority 32");
            ShowWindow(hWnd, SW_SHOW);
            PostMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 1);
            cout << "Found roblox window " << hWnd << " showing it" << endl;
            instructionCout(1);
            Sleep(1000);
        }
    }


    delete[] buffer;
    return true;
}


int main(int argc, char** argv) {
    instructionCout(0);
    while (true) {
        if (GetKeyState(VK_RSHIFT) & 0x8000 && show_windows == 0) {
            show_windows = 1;
        }
        else if (GetKeyState(VK_RSHIFT) & 0x8000 && show_windows == 1) {
            show_windows = 0;
        }
        else if (GetKeyState(VK_END) & 0x8000) {
            cout << "Killing all Roblox Instances" << endl;
            system("taskkill /F /T /IM RobloxPlayerBeta.exe");
            break;

        }
        
        EnumWindows(windcallback, show_windows);
        Sleep(5);
    }

    return 0;
}
