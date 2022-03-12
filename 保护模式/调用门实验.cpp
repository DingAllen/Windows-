#include <stdio.h>
#include <windows.h>

BYTE GDT[6] = {0};
DWORD dwH2GValue;

void __declspec(naked) woshiheike() {

	_asm {

		pushad
		pushfd

		mov eax, 0x8003f00c
		mov ebx, [eax]
		mov dwH2GValue, ebx
		sgdt GDT

		popfd
		popad

		retf
	}
}

int main() {

	char buffer[6];

	*((DWORD *)(&buffer[0])) = 0x12345678;
	*((WORD *)(&buffer[4])) = 0x48; // 9 = 0b1001  ->  0»·¶ÎÑ¡Ôñ×Ó£º0100 1000 ¼´0x48

	_asm {
		call fword ptr[buffer]
	}

	DWORD GDT_ADDR = *(PDWORD)(&GDT[2]);
	WORD GDT_LIMIT = *(PWORD)(&GDT[0]);

	printf("%x %x %x\n", dwH2GValue, GDT_ADDR, GDT_LIMIT);

	getchar();
	return 0;
}