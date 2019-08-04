// MailSlotServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <stdio.h>
using namespace std;
#define MAX_BUFFER_LEN 256 // 数据缓冲区大小

int main(int argc, char* argv[])
{
	HANDLE hslot;	// 定义服务器邮槽句柄
	char buffer[MAX_BUFFER_LEN];  // 定义接收数据缓冲区
	DWORD nReadBytes;  // 定义存放读取数据个数的变量
	hslot = CreateMailslot("\\\\.\\Mailslot\\slotsample", 0, MAILSLOT_WAIT_FOREVER, NULL);

	if (hslot == INVALID_HANDLE_VALUE)
	{
		// 循环从邮槽中读取数据，因为使用 MAILSLOT_WAIT_FOREVER，所以无限等待
		printf("创建邮槽失败，错误代码=%d\n", GetLastError());
		return 0;
	}
	while (ReadFile(hslot, buffer, MAX_BUFFER_LEN, &nReadBytes, NULL) != 0)
	{
		printf("接收到邮槽数据=%.*s\n", nReadBytes, buffer);
	}
	return 0;
}