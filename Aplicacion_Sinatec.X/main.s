
PROCESSOR 18F4550
#include <xc.inc>
#include "Config.inc"  
#include "Retardo   s_picass.inc"
#include "uart.inc"    
    
PSECT MMJ,global,class=CODE,RELOC=2
MMJ:
    goto    inicio
    
    global Cadena
psect SmallConst,global,reloc=2,class=SMALLCONST,delta=1   
  Cadena:     db 'S','I','N','A','T','E','C',' ','2','0','2','1',' '
	      db 'I','E','E','E',' ','U','N','A','C',' ','P','E','R','U',' '

psect code
inicio:

    ;Configurar el Clock
    ;OSCCONbits.IRCF = 0b110 
    bsf	BANKMASK(OSCCON),6,c ; IRCF2
    bsf BANKMASK(OSCCON),5,c ; IRCF1
    bcf BANKMASK(OSCCON),4,c ; IRCF0
    
    ;Configuracion de la GPIO
    ;TRISX -> 0: SALIDA <> 1: ENTRADA
    ;TRISDbits.TRD7 = 1 //0  TRISD &= ~(1<<7)
    MOVLW   00H
    MOVWF   BANKMASK(TRISD),c
    MOVLW   255
    MOVWF   BANKMASK(LATD),c
    call    ConfigEUSART
    NOP
bucle:
    MOVLW   0
    CALL    Serial_String_TX   
    call    rutina_1s
    
    
    goto bucle ;for(;;) while(1)
    
    end MMJ
    


