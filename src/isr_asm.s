			xdef	    _trap70_isr,_set_ipl,_trap28_isr
            xref        _keyRegister,_keyboard,_rndrRqst,_VBL
kbd_sr	    equ	        $fffffc00	; keyboard status register
kbd_cr	    equ	        $fffffc00	; keyboard control register
kbd_rdr	    equ	        $fffffc02	; keyboard receive data register			

inservB     equ         $FFFA11     ;   inservice register b



_trap70_isr:            ;keyboard/mouse
            move.b	    kbd_rdr,_keyRegister
            movem.l     d0-7/a0-7,-(sp)
            jsr         _keyboard
            movem.l     (sp)+,d0-7/a0-7
            and.b       #$BF,inservB
            rte

_trap28_isr:            ;VBL
            add.l       #1,$462
            movem.l     d0-7/a0-7,-(sp)
            jsr         _VBL
            movem.l     (sp)+,d0-7/a0-7
            move.b      #1,_rndrRqst
            rte
            
_set_ipl:               ;interrupt prevention via max priority at cpu
            move.w      sr,d0
            move.w      d0,-(sp)

            lsr.w       #8,d0
            and.w       #$007,d0

            andi.w      #$F8FF,(sp)
            move.w      d1,-(sp)
            move.w      8(sp),d1

            lsl.w       #8,d1
            and.w       #$0700,d1
            or.w        d1,2(sp)
            move.w      (sp)+,d1
            rte