#include <Windows.h>
#include "DebugModule.h"

void ShowWarnMessage(const char* message, const char* title) {
	MessageBox(NULL, message, title, MB_ICONEXCLAMATION);
}