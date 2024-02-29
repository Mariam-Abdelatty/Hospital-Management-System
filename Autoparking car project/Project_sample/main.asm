


TITLE MASM Template						(main.asm)

INCLUDE Irvine32.inc
.data

bs dd 0 ;define bs as doubleword
forward dd 0  ;define forward as doubleword

readBuffer db 256 dup(0) ;define readBuffer as data byte

msgReadBs db 'Read Bs: ', 0  
msgReadFs db 'Read Fs: ', 0
msgBsIsLess db 'Bs is less than 5.', 0
msgFsIsLess db 'Fs is less than 5.', 0
msgMoveBackward db 'Move Backward.', 0
msgMoveForward db 'Move Forward.', 0
msgStop db 'Stop.', 0

.code
atodw PROC    ;ASCII to doward convert ascii to 32 bit data type
    ; Input: EDX points to the ASCII string
    ; Output: EAX contains the converted 32-bit integer

    xor eax, eax  ; Clear EAX to store the result

convert_loop:
    movzx ecx, byte ptr [edx]  ; Load the next character from the string into ECX
    test  ecx, ecx              ; Test if it's the null terminator (end of string)
    jz    convert_done          ; If yes, exit the loop

    sub   ecx, '0'              ; Convert ASCII character to integer ('0' -> 0, '1' -> 1, ..., '9' -> 9)
    imul  eax, eax, 10          ; Multiply the current result by 10
    add   eax, ecx              ; Add the current digit to the result

    inc   edx                   ; Move to the next character in the string
    jmp   convert_loop          ; Repeat the process for the next character

convert_done:
    ret
atodw ENDP

CheckBs PROC

    
    cmp [bs], 5
    jl elseBranch

    ifBranch:
    call MoveBackward
    ret

    elseBranch:
    call BsIsLess
     ret
CheckBs ENDP

BsIsLess PROC

     
    mov edx, OFFSET msgBsIsLess
    call WriteString
    call Crlf
    test ebx, ebx		;test if ebx is equal to zero

    jnz elseBranch  ; Jump to stop when ebx not equal to zero
    
    ifBranch:
    call ReadFs
    ret

   elseBranch:
    call Stop
     ret

BsIsLess ENDP

MoveForward PROC

    
    mov edx, OFFSET msgMoveForward
    call WriteString
    call Crlf

    
    mov edx, OFFSET msgReadFs
    call WriteString
    call Crlf

    
    lea edx, readBuffer
    mov ecx, 256
    call ReadString
    call atodw
    mov [forward], eax
    call CheckFs

    ret
MoveForward ENDP

CheckFs PROC

 
    cmp [forward], 5
    jl elseBranch

   ifBranch:
   call MoveForward
   ret

    elseBranch:
    mov edx, OFFSET msgFsIsLess
    call WriteString
    call Crlf
    call Stop
    ret

CheckFs ENDP

MoveBackward PROC

 
    inc ebx			;increment ebx
    mov edx, OFFSET msgMoveBackward
    call WriteString
    call Crlf

    
    mov edx, OFFSET msgReadBs
    call WriteString
    call Crlf

   
    lea edx, readBuffer
    mov ecx, 256
    call ReadString
    call atodw
    mov [bs], eax

    
    call CheckBs    
    ret

MoveBackward ENDP

Stop PROC


    mov edx, OFFSET msgStop
    call WriteString
    call Crlf
    int 20h         ; Terminate the program

    ret

Stop ENDP

ReadFs PROC

; Additional steps for reading Fs when Bs is less than 5
    mov edx, OFFSET msgReadFs
    call WriteString
    call Crlf

    lea edx, readBuffer
    mov ecx, 256
    call ReadString
    call atodw
    mov [forward], eax

    call CheckFs  ; Continue the logic from CheckFs
    ret

ReadFs ENDP

main PROC
    ; write the assembly code here
	
     mov ebx, 0      ;to initialize ebx with 0


    
    mov edx, OFFSET msgReadBs
    call WriteString
    call Crlf

    
    lea edx, readBuffer
    mov ecx, 256
    call ReadString
    call atodw
    mov [bs], eax
    call CheckBs

        
main ENDP

END main