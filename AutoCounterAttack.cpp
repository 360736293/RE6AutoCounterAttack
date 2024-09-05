#include <stdio.h>
#include <Windows.h> 

DWORD getFirstAddr(HANDLE hProcess){
	DWORD baseAddr = 0x17B8CF0;
	DWORD firstPointerAddr; 
	ReadProcessMemory(hProcess,(void *)baseAddr,&firstPointerAddr,sizeof(firstPointerAddr),NULL);
	firstPointerAddr += 0x19C0;
	DWORD secondPointerAddr;
	ReadProcessMemory(hProcess,(void *)firstPointerAddr,&secondPointerAddr,sizeof(secondPointerAddr),NULL);
	secondPointerAddr += 0x214;
	DWORD thirdPointerAddr;
	ReadProcessMemory(hProcess,(void *)secondPointerAddr,&thirdPointerAddr,sizeof(thirdPointerAddr),NULL);
	thirdPointerAddr += 0x1545;
	return thirdPointerAddr;
} 

int main(){
	HWND hWnd = FindWindowA(NULL,"RESIDENT EVIL 6");
    if(hWnd == NULL){
    	printf("窗口未找到");
    	return 0;
	}
    DWORD pid;
	GetWindowThreadProcessId(hWnd,&pid);
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid);
    if(hProcess == NULL){
    	printf("打开游戏进程失败");
    	return 0;
	}
	DWORD firstAddr = getFirstAddr(hProcess);
	DWORD secondAddr = firstAddr + 0x780;
	char autoCounterAttackFlag1; 
	char autoCounterAttackFlag2;
	while(true){
		ReadProcessMemory(hProcess,(void *)firstAddr,&autoCounterAttackFlag1,1,NULL);
		ReadProcessMemory(hProcess,(void *)secondAddr,&autoCounterAttackFlag2,1,NULL);
		if(autoCounterAttackFlag1 == 5 || (autoCounterAttackFlag1 == 4 && autoCounterAttackFlag2 == 5)){
			mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
			Sleep(100);
			mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
		}
		Sleep(10);
	}  
    return 0;
} 

