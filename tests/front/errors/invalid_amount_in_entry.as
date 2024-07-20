.entry LIST MAIN
.extern fn1
MAIN:   add r3, LIST
        jsr fn1
LOOP:   prn #48
        prn #-5
        lea STR, *r6
        inc r7
        inc *r6
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