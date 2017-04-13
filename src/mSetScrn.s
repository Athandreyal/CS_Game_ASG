        xdef _mySetScreen
        xdef _myPhysBase
        xdef _fst_blk

base    equ         8

_mySetScreen:
        link        a6,#0
        movem.l	    d0/a0,-(a7)
        move.l      base(a6),d0
            ;d0 contains 00ff8000
            ;want ff80 in word
        lsr.l       #8,d0
            ;ff8000 should now be ff80
            ;prime a0 with register address
        move.l      #$00ff8200,a0
            ;load the registers with the passed data
        movep.w     d0,1(a0)
        movem.l	    (a7)+,d0/a0
        unlk        a6
        rts
        
_myPhysBase:
        link        a6,#0
        movem.l	    d0/a0,-(a7)
        move.l      #$00ff8200,a0
        clr.l       d0
        move.b      1(a0),d0
        lsl.l       #8,d0
        move.b      3(a0),d0
        lsl.l       #8,d0
        move.l      d0,base(a6)
        movem.l	    (a7)+,d0/a0
        unlk        a6
        rts
        

_fst_blk:
        link        a6,#0
        movem.l	    d0-7/a0-5,-(a7)
        move.l      base(a6),a5
        adda.l      #32000,a5
        move.l      #$ffffffff,d0
        move.l      #$ffffffff,d1
        move.l      #$ffffffff,d2
        move.l      #$ffffffff,d3
        move.l      #$ffffffff,d4
        move.l      #$ffffffff,d5
        move.l      #$ffffffff,d6
        move.l      #$ffffffff,a0
        move.l      #$ffffffff,a1
        move.l      #$ffffffff,a2
        move.l      #$ffffffff,a3
        move.l      #$ffffffff,a4
        move.l      #665,d7
loop:
        movem.l     d0-d6/a0-a4,-(a5)    ;load 12 longs into mem
        dbra        d7,loop
        movem.l     d0-d6/a0,-(a5)       ;need 8 moreto hit end of buffer
        movem.l	    (a7)+,d0-7/a0-5
        unlk        a6
        rts
        