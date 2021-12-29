global puntero

psect udata_acs
puntero: db  1

 psect code  
ConfigInterruptUart:
		BSF	    PIE1,5,c;Habilitamos la Interrupción por Recepción
		BSF	    IPR1,5,c;RX High Priority
		BCF	    PIR1,5,c;Bandera de la recepción apagada
		return
 psect code 		
ConfigEUSART:
		;Configuramos la TX de la UART
		BSF	    TRISC,7,c;RX como entrada
		BCF	    TRISC,6,c;TX como salida
		BCF	    TXSTA,6,c;TX9; TX a 8 Bits
		BSF	    TXSTA,5,c;TXEN; TX habilitada
		BCF	    TXSTA,4,c;SYNC; UART ASÌNCRONO
		BSF	    TXSTA,2,c;BRGH; UART Alta velocidado
		;Configuramos la recepción
		BSF	    RCSTA,7,c;SPEN;Puerto Serial habilitado
		BCF	    RCSTA,6,c;RX9;Recepción a 8 Bits
		BSF	    RCSTA,4,c;CREN;Recepción continua
		;Configuramos la velocidad Baud rate
		BSF	    BAUDCON,3,c;BRG16;UART trabajando a 16 Bits
		MOVLW	    103
		MOVWF	    BANKMASK(SPBRG),c
		CLRF	    BANKMASK(SPBRGH),c;9600 Baudios para 4 Mhz 
		clrf	    puntero,c
		RETURN
		
 psect code 		
SerialWrite:
		MOVWF	BANKMASK(TXREG),C		
espera:	        
		;BANKSEL	TXSTA
		BTFSS   BANKMASK(TXSTA),1,c;TRMT
		goto	espera	
		return 
		
 psect code 	
Serial_String_TX:   
		MOVWF	puntero,c
		MOVLW	low highword	cadenas
		movwf	TBLPTRU,c
		movlw	HIGH	cadenas
		movwf	TBLPTRH,c
		MOVLW	LOW	cadenas
		MOVWF	TBLPTRL,c
		MOVF	puntero,W,c
		addwf	TBLPTRL,F,c
		clrf	WREG,c
		addwfc	TBLPTRH,F,c
		addwfc	TBLPTRU,F,c
LecturaUSART:
		TBLRD*+
Testeo:	
		MOVLW	0
		CPFSEQ	TABLAT,c
		goto	Transmite_Tx
		return
Transmite_Tx:
		MOVF	TABLAT,W,a
		CALL	SerialWrite	
		goto	LecturaUSART

