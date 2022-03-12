#include <stdio.h>
#include <windows.h>

DWORD x1, x2, x3;

void __declspec(naked) woshiheike() {

	_asm {
		pushad
		pushfd
		mov eax, [esp+0x24+0x8+0x8]
		mov dword ptr ds:[x1], eax
		mov eax, [esp+0x24+0x8+0x4]
		mov dword ptr ds:[x2], eax
		mov eax, [esp+0x24+0x8+0x0]
		mov dword ptr ds:[x3], eax
		popfd
		popad
		// 要注意平衡堆栈
		retf 0xc
	}
}

int main() {

	char buffer[6];

	*((DWORD *)(&buffer[0])) = 0x12345678;
	*((WORD *)(&buffer[4])) = 0x48; // 9 = 0b1001  ->  0环段选择子：0100 1000 即0x48

	_asm {
		push 0x12345678
		push 0x19990711
		push 0x19491001
		call fword ptr[buffer]
	}

	printf("%x %x %x", x1, x2, x3);

	getchar();
	return 0;
}