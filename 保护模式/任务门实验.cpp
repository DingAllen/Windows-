#include <stdio.h>
#include <windows.h>

DWORD dwOK;
DWORD dwESP;
DWORD dwCS;

void __declspec(naked) woshiheike() {

	_asm {
		mov eax, 0x1
		mov dwOK, eax
		mov eax, esp
		mov dwESP, eax
		mov ax, cs
		mov word ptr [dwCS], ax
		iretd
	}
}

int main() {

	char bu[0x10];
	int iCr3;

	printf("plz input CR3:");
	scanf("%x", &iCr3);

	DWORD iTss[0x68] = {
            0x00000000,//link
            0x00000000,//(DWORD) bu,//esp0
            0x00000000,//ss0
            0x00000000,//esp1
            0x00000000,//ss1
            0x00000000,//esp2
            0x00000000,//ss2
            (DWORD) iCr3,//cr3
            0x00401020,//eip
            0x00000000,//eflags
            0x00000000,//eax
            0x00000000,//ecx
            0x00000000,//edx
            0x00000000,//ebx
            (DWORD) bu,//esp
            0x00000000,//ebp
            0x00000000,//esi
            0x00000000,//edi
            0x00000023,//es
            0x00000008,//cs 0x0000001B
            0x00000010,//ss 0x00000023
            0x00000023,//ds
            0x00000030,//fs 0x0000003B
            0x00000000,//ldt
            0x20ac0000
    };

	char buffer[6];
	*((DWORD *)(&buffer[0])) = 0x12345678;
	*((WORD *)(&buffer[4])) = 0x48; // 9 = 0b1001  ->  0»·¶ÎÑ¡Ôñ×Ó£º0100 1000 ¼´0x48

	_asm {
		// call fword ptr[buffer]
		int 0x20
	}

	printf("ok: %d, ESP = %x, CS = %x", dwOK, dwESP, dwCS);

	getchar();
	getchar();
	getchar();
	return 0;
}