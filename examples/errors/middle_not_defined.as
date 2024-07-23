.entry LIST
.extern fn1
        prn #-5
MAIN:   add r3, BAD
        jsr fn1
LOOP:   prn #48
        prn #-5
        macr m_macr                   
        cmp r3, #-6
        bne END
        endmacr
        sub r3, r4
        lea STR, *r6
        inc r7
        inc *r6
        m_macr
        m_macr
        bne END
;comment line

.entry MAIN
        jmp LOOP
END:    stop
STR:    .string "abcd test"
LIST:   .data 6, -9 ,+8,10
        .data -100
K:      .data 31
.extern L3 
