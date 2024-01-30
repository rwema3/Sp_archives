# 1 "asembly_temblate.asm"
# 1 "<built-in>" 1
# 1 "asembly_temblate.asm" 2
;******************************************************************
; Very first program
; This program repeatedly adds a number to the Working Register.
; TJW 1.11.08 Tested 1.11.08
;******************************************************************
;
; use the org directive to force program start at reset vector
      org 00
; program starts here
      clrw ; clear W register

loop addlw 08 ; add the number 8 to W register

      goto loop
      end
