push ebp    ; ebp = 스택의 제일 밑단을 가리키는 변수
mov ebp, esp; esp = 스택포인터, 스택의 최상단을 가리키는 변수
            ; esp 값을 ebp에 넣는다.
sub esp, 0E4h; esp에 228바이트를 할당한다. >> 228바이트 크기의 스택을 할당한다. 끝에 h는 hex값을 의미하는 접미사 개념.
push ebx        ; ebx를 스택에 저장
push esi        ; esi를 스택에 저장
push edi        ; edi를 스택에 저장
lea edi, [ebp+FFFFFF1Ch]    ; edi에 베이스포인터 레지스터 값 + FFFFFF1Ch 값을 합친 메모리 주소 할당함.
mov ecx, 39h            ; ecx에 0x39 값을 할당
mov eax, 0CCCCCCCCh     ; eax에 0x0CCCCCCCC 값을 할당

rep stos dword ptr es:[edi] ; rep: 반복 프리픽스, 뒤에 오는 명령을 ecx 레지스터에 지정된 횟수만큼 반복하여 실행
                            ; stos: store string의 약자 메모리에 값을 저장하는 명령어.
                            ; dword ptr: 명령어의 크기를 지정하는 접미사 더블워드이므로 32비트 크기의 값을 저장한다는 것을 나타냄.
                            ; es:[edi] > 목적지 주소를 나타내는 부분으로, 여기서는 목적지 주소를 es 세그먼트 레지스터에 저장된 값과
                            ; edi 레지스터에 저장된 오프셋의 조합으로 나타냄.

; 따라서 ecx 레지스터에 지정된 횟수만큼 32비트 데이터를 es 세그먼트의 주소에 반복하여 저장하는 명령어임.

mov ecx, 9AC003h
call 009A1316
mov dword ptr [ebp-8], 1
mov dword ptr [ebp-14h], 2
mov eax, dword ptr [ebp-8]
add eax, dword ptr [ebp-14h]
mov dword ptr [ebp-20h], eax
mov eax, dword ptr [ebp-20h]
push eax
push 9A7D08h
call 009A10CD
add esp, 8
xor eax, eax
pop edi
pop esi
pop ebx
add esp, 0E4h
cmp ebp, esp
call 009A123F
mov esp, ebp
pop ebp
ret