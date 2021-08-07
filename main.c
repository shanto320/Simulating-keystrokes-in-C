//
// sendkey.c - Send a key press to a specific window
// Written by Ted Burke
// Last updated 13-2-2013
//
// To compile using gcc:
//
//      gcc -o sendkey.exe sendkey.c
//
// To send the letter 'a' to a WordPad window:
//
//      sendkey.exe a WordPad
//
 
#define WINVER 0x0500
#include <windows.h>
#include <stdio.h>
 
int main(int argc, char* argv[])
{
    // Check number of command line arguments
    if (argc < 3)
    {
        fprintf(stderr, "Too few command line arguments\n");
        fprintf(stderr, "Usage: sendkey.exe KEY_TO_SEND");
        fprintf(stderr, " WORD_FROM_TARGET_WINDOW_TITLE\n");
        return 1;
    }
     
    // Get the character to send from the first command
    // line argument
    char char_to_send = toupper(argv[1][0]);
     
    // Get first window on desktop
    HWND firstwindow = FindWindowEx(NULL, NULL, NULL, NULL);
    HWND window = firstwindow;
    TCHAR windowtext[MAX_PATH];
     
    // We need to get the console title in case we
    // accidentally match the search word with it
    // instead of the intended target window.
    TCHAR consoletitle[MAX_PATH];
    GetConsoleTitle(consoletitle, MAX_PATH);
     
    while(1)
    {
        fprintf(stderr, ".");
         
        // Check window title for a match
        GetWindowText(window, windowtext, MAX_PATH);
        if (strstr(windowtext, argv[2]) != NULL &&
            strcmp(windowtext, consoletitle) != 0) break;
         
        // Get next window
        window = FindWindowEx(NULL, window, NULL, NULL);
        if (window == NULL || window == firstwindow)
        {
            fprintf(stderr, "Window not found\n");
            return 1;
        }
    }
    fprintf(stderr, "Window found: %s\n", windowtext);
     
    // Bring specified window into focus
    SetForegroundWindow(window);
 
    // Create the desired keyboard event
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wVk = char_to_send;
    ip.ki.wScan = 0;
    ip.ki.dwFlags = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
     
    // Send the keyboard event to the specified window
    SendInput(1, &ip, sizeof(INPUT));
     
    // Exit normally
    return 0;
}
