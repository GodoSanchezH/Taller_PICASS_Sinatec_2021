
global contador1,contador2,contador3,contador4
  
PSECT udata_acs
contador1: db 1
contador2: db 1
contador3: db 1
contador4: db 1 
 
 ;__DELAY 
 
PSECT code
rutina_1ms:
	movlw	250
	movwf	contador2,f,a
laso2:
	NOP
	DECFSZ	contador1,f,a
	GOTO	laso2
    	return

PSECT code
 rutina_100ms:
    MOVLW   100
    movwf   contador3,f,a
lazo3:
	call rutina_1ms
	decfsz contador3,f,a
	goto lazo3
    	return

PSECT code
 
 rutina_1s:
    MOVLW   10
    movwf   contador4,f,a
lazo4:
	call rutina_100ms
	decfsz contador4,f,a
	goto lazo4
 	return

PSECT code
rutina_15ms:
	    MOVLW   15
	    MOVWF   contador1,f,a
laso:	    
	nop
	DECFSZ	contador1,f,a
	goto	laso
	return
	
	