.586
.model flat
public _Fasm
.code
_Fasm proc
push ebp
mov ebp, esp
push ebx
sub esp, 4

mov dword ptr[ebp-4], 0; i

c1 :
	mov edx, [ebp-4]
	cmp edx, [ebp+12]
	jge endc1
	mov ebx, [ebp-4]; j
	c2 :
		cmp ebx, [ebp+16]
		jge endc2
		mov ecx, ebx
		shl ecx, 2
		add ecx, [ebp+20]
		mov eax, [ebp-4]
		imul dword ptr [ebp+16]
		add eax, ebx
		shl eax, 2
		add eax, [ebp+8]
		mov eax, [eax]
		add [ecx], eax
		inc ebx
		jmp c2
	endc2 :
	inc dword ptr [ebp-4]
	jmp c1
endc1 :

add esp, 4
pop ebx
pop ebp
ret
_Fasm endp
end