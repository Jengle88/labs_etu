; Шаблон текста программы на ассемблере для модуля типа .COM
TESTPC SEGMENT
ASSUME CS:TESTPC, DS:TESTPC, ES:NOTHING, SS:NOTHING
ORG 100H
START: JMP BEGIN
; ДАННЫЕ
    ; Типы PC
    TYPE_PC_PC              db 'PC', 0Dh, 0Ah, '$'
    TYPE_PC_PC_XT           db 'PC/XT', 0Dh, 0Ah, '$'
    TYPE_PC_AT              db 'AT', 0Dh, 0Ah, '$'
    TYPE_PC_PS2_30          db 'PS2 model 30', 0Dh, 0Ah, '$'
    TYPE_PC_PS2_50_60       db 'PS2 model 50 or 60', 0Dh, 0Ah, '$'
    TYPE_PC_PS2_80          db 'PS2 model 80', 0Dh, 0Ah, '$'
    TYPE_PC_PCjr            db 'PCjr', 0Dh, 0Ah, '$'
    TYPE_PC_PC_CONVERTIBLE  db 'PC Convertible', 0Dh, 0Ah, '$'
    TYPE_PC_UNKNOWN         db 'Unknown type, HEX: 0?', 0Dh, 0Ah, '$'
    ; Информация для вывода
    TYPE_PC_LABLE           db 'Type PC: $'
    MS_DOS_VERSION          db 'MS DOS version: 0?.0?', 0Dh, 0Ah, '$'
    OEM_SERIAL_NUMBER       db 'OEM serial number: ??', 0Dh, 0Ah, '$'
    USER_SERIAL_NUMBER      db 'User serial number: ??????', 0Dh, 0Ah, '$'
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

    PRINT_TYPE_PC PROC near
        ; TODO Добавить добавление используемых регистров в стек, а в конце - достать их
        push ax
        push dx
        push bx

        mov ah, 09
        mov dx, offset TYPE_PC_LABLE
        int 21h
        ; получение информации о типе PC
        mov ax, 0f000H
        mov es, ax
        mov bh, 0
        mov bl, es:[0FFFEH]
        mov ax, 0
        ; выявление типа PC
        cmp bx, 0FFh
        je PC
        cmp bx, 0FEh
        je PC_XT
        cmp bx, 0FBh
        je PC_XT
        cmp bx, 0FCh
        je AT
        cmp bx, 0FAh
        je PS2_30
        cmp bx, 0FCh
        je PS2_50_60
        cmp bx, 0F8h
        je PS2_80
        cmp bx, 0FDh
        je PCjr
        cmp bx, 0F9h
        je PC_CONVERTIBLE
        jmp PC_UNKNOWN
        ; вывод информации
        PC:
        mov ah, 09
        mov dx, offset TYPE_PC_PC
        int 21h
        jmp END_COMP_TYPE_PC
        
        PC_XT:        
        mov ah, 09
        mov dx, offset TYPE_PC_PC_XT
        int 21h
        jmp END_COMP_TYPE_PC

        AT:        
        mov ah, 09
        mov dx, offset TYPE_PC_AT
        int 21h
        jmp END_COMP_TYPE_PC

        PS2_30:        
        mov ah, 09
        mov dx, offset TYPE_PC_PS2_30
        int 21h
        jmp END_COMP_TYPE_PC

        PS2_50_60:
        mov ah, 09
        mov dx, offset TYPE_PC_PS2_50_60
        int 21h
        jmp END_COMP_TYPE_PC    
        
        PS2_80:        
        mov ah, 09
        mov dx, offset TYPE_PC_PS2_80
        int 21h
        jmp END_COMP_TYPE_PC

        PCjr:
        mov ah, 09
        mov dx, offset TYPE_PC_PCjr
        int 21h
        jmp END_COMP_TYPE_PC    
        
        PC_CONVERTIBLE:        
        mov ah, 09
        mov dx, offset TYPE_PC_PC_CONVERTIBLE
        int 21h
        jmp END_COMP_TYPE_PC

        PC_UNKNOWN:
        mov ah, 00h
        mov al, bl
        call BYTE_TO_HEX
        mov di, offset TYPE_PC_UNKNOWN
        add di, 19
        mov [di], al
        inc di
        mov [di], ah
        mov ah, 09
        mov dx, offset TYPE_PC_UNKNOWN
        int 21h
        jmp END_COMP_TYPE_PC

        END_COMP_TYPE_PC:
        pop bx
        pop dx
        pop ax
        ret
    PRINT_TYPE_PC ENDP

    PRINT_MSDOS_VERS PROC near
        push ax
        push dx
        mov AH,30h
        int 21h

        mov di, offset MS_DOS_VERSION
        add di, 17
        cmp al, 0
        je LESS_2_VERS

        mov si, di
        mov dh, ah
        call BYTE_TO_DEC
        mov al, dh
        add si, 4
        call BYTE_TO_DEC
        jmp PRINT_VERS
        
        LESS_2_VERS:
        mov byte ptr [di], '<'
        mov byte ptr [di+1], '2'
        add di, 3
        mov byte ptr [di], '0'
        mov byte ptr [di+1], '0'
        
        PRINT_VERS:
        mov ah, 09
        mov dx, offset MS_DOS_VERSION
        int 21h
        pop dx
        pop ax
        ret
    PRINT_MSDOS_VERS ENDP

    PRINT_OEM_SERIAL_NUMBER PROC near
        push ax
        push bx
        push dx
        mov AH,30h
        int 21h

        mov di, offset OEM_SERIAL_NUMBER
        add di, 19
        mov al, bh
        call BYTE_TO_HEX
        mov [di], ah
        mov [di+1], al

        mov ah, 09
        mov dx, offset OEM_SERIAL_NUMBER
        int 21h
        pop dx
        pop bx
        pop ax
        ret
    PRINT_OEM_SERIAL_NUMBER ENDP

    PRINT_USER_SERIAL_NUMBER PROC near
        push ax
        push dx
        mov AH,30h
        int 21h

        mov di, offset USER_SERIAL_NUMBER
        add di, 25
        mov ax, cx
        call WRD_TO_HEX
        dec di
        mov al, bl
        call BYTE_TO_HEX
        mov [di], ah
        mov [di-1], al

        mov ah, 09
        mov dx, offset USER_SERIAL_NUMBER
        int 21h
        pop dx
        pop ax
        ret
    PRINT_USER_SERIAL_NUMBER ENDP

    BEGIN:
        call PRINT_TYPE_PC 
        call PRINT_MSDOS_VERS
        call PRINT_OEM_SERIAL_NUMBER
        call PRINT_USER_SERIAL_NUMBER

    EXIT:
    ; Выход в DOS
        xor AL,AL
        mov AH,4Ch
        int 21H
    TESTPC ENDS
END START ;конец модуля, START - точка входа
