; Шаблон текста программы на ассемблере для модуля типа .COM
TESTPC SEGMENT
ASSUME CS:TESTPC, DS:TESTPC, ES:NOTHING, SS:NOTHING
ORG 100H
START: JMP BEGIN
; ДАННЫЕ

    UNREACHABLE_MEMORY      db 'Unreachable memory: 0000h', 0Dh, 0Ah, '$'
    ENVIRONMENT_MEMORY      db 'Environment memory: 0000h', 0Dh, 0Ah, '$'
    CMD_TAIL                db 'Tail of command:$'
    NEXT_LINE               db 0Dh, 0Ah, '$'
    ENVIRONMENT_CONTENT     db 'Environment content:', 0Dh, 0Ah, '$'
    PATH_COM_MODULE         db 'Path to the .com module:', 0Dh, 0Ah, '$'
    ;ПРОЦЕДУРЫ
    ;-----------------------------------------------------
    TETR_TO_HEX PROC near
        and AL,0Fh
        cmp AL,09
        jbe NEXT
        add AL,07
    NEXT: add AL,30h
        ret
    TETR_TO_HEX ENDP
    ;-------------------------------
    BYTE_TO_HEX PROC near
    ; байт в AL переводится в два символа шестн. числа в AX
        push CX
        mov AH,AL
        call TETR_TO_HEX
        xchg AL,AH
        mov CL,4
        shr AL,CL
        call TETR_TO_HEX ;в AL старшая цифра
        pop CX ;в AH младшая
        ret
    BYTE_TO_HEX ENDP
    ;-------------------------------
    WRD_TO_HEX PROC near
    ;перевод в 16 с/с 16-ти разрядного числа
    ; в AX - число, DI - адрес последнего символа
        push BX
        mov BH,AH
        call BYTE_TO_HEX
        mov [DI],AH
        dec DI
        mov [DI],AL
        dec DI
        mov AL,BH
        call BYTE_TO_HEX
        mov [DI],AH
        dec DI
        mov [DI],AL
        pop BX
        ret
    WRD_TO_HEX ENDP
    ;--------------------------------------------------
    BYTE_TO_DEC PROC near
    ; перевод в 10с/с, SI - адрес поля младшей цифры
        push CX
        push DX
        xor AH,AH
        xor DX,DX
        mov CX,10
    loop_bd: div CX
        or DL,30h
        mov [SI],DL
        dec SI
        xor DX,DX
        cmp AX,10
        jae loop_bd
        cmp AL,00h
        je end_l
        or AL,30h
        mov [SI],AL
    end_l: pop DX
        pop CX
        ret
    BYTE_TO_DEC ENDP
    ;-------------------------------

    
    PRINT_MESSAGE PROC near
        push ax

        ; сообщение должно быть в dx
        mov ah, 09
        int 21h
        
        pop ax
        ret
    PRINT_MESSAGE ENDP

    
    PRINT_UNREACHABLE_MEMORY PROC near
        push ax
        push dx

        mov ax, ds:[02h]
        mov di, offset UNREACHABLE_MEMORY
        add di, 23
        call WRD_TO_HEX
        mov dx, offset UNREACHABLE_MEMORY
        call PRINT_MESSAGE

        pop dx
        pop ax
        ret
    PRINT_UNREACHABLE_MEMORY ENDP

    PRINT_ENVIRONMENT_MEMORY PROC near
        push ax
        push dx

        mov ax, ds:[2ch]
        mov di, offset ENVIRONMENT_MEMORY
        add di, 23
        call WRD_TO_HEX
        mov dx, offset ENVIRONMENT_MEMORY
        call PRINT_MESSAGE

        pop dx
        pop ax
        ret
    PRINT_ENVIRONMENT_MEMORY ENDP

    
    PRINT_TAIL_CMD PROC near
        push ax
        push cx
        push dx

        mov dx, offset CMD_TAIL
        call PRINT_MESSAGE
        mov cx, 0h
        mov cl, ds:[80h]
        mov di, 0h
        cmp cl, 0h
        je EMPTY_TAIL
READ_TAIL_CMD:
        mov al, ds:[81h+di]
        inc di
        mov dl, al
        mov ah, 02h
        int 21h
        loop READ_TAIL_CMD
EMPTY_TAIL:
        mov dx, offset NEXT_LINE
        call PRINT_MESSAGE

        pop dx
        pop cx
        pop ax
        ret
    PRINT_TAIL_CMD ENDP


    PRINT_ENVIRONMENT_CONTENT_PATH PROC near
        push ax
        push bx
        push cx
        push dx

        mov dx, offset ENVIRONMENT_CONTENT
        call PRINT_MESSAGE

        mov di, 00h
        mov dx, 00h
        mov ds, ds:[2Ch]
START_READ_CONTENT:
        cmp byte ptr [di], 00h
        je END_LINE
        mov dl, [di]
        mov ah, 02h
        int 21h
        jmp IS_END_CONTENT
END_LINE:
        cmp byte ptr [di+1], 00h
        je IS_END_CONTENT
        push ds
        mov cx, cs
        mov ds, cx
        mov dx, offset NEXT_LINE
        call PRINT_MESSAGE
        pop ds
IS_END_CONTENT:
        inc di
        mov dx, word ptr [di]
        cmp dx, 0001h
        je READ_PATH
        jmp START_READ_CONTENT

READ_PATH:
        push ds
        mov ax, cs
        mov ds, ax
        mov dx, offset PATH_COM_MODULE
        call PRINT_MESSAGE
        pop ds
        add di, 2
PRINT_PATH:
        mov bl, [di]
        cmp bl, 00h
        je END_READ_CONTENT
        mov dl, bl
        mov ah, 02h
        int 21h
        inc di
        jmp PRINT_PATH
END_READ_CONTENT:
        mov cx, cs
        mov ds, cx
        mov dx, offset NEXT_LINE
        call PRINT_MESSAGE

        pop dx
        pop cx
        pop bx
        pop ax
        ret
    PRINT_ENVIRONMENT_CONTENT_PATH ENDP


    BEGIN:
        call PRINT_UNREACHABLE_MEMORY
        call PRINT_ENVIRONMENT_MEMORY
        call PRINT_TAIL_CMD
        call PRINT_ENVIRONMENT_CONTENT_PATH

    EXIT:
    ; Выход в DOS
        xor AL,AL
        mov AH,4Ch
        int 21H
    TESTPC ENDS
END START ;конец модуля, START - точка входа
