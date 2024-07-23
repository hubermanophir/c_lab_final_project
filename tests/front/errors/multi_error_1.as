.entry LIST
.extern fn1 fn2
MAIN:   add r3, LIST
        jsr fn1
LOOP:   prn #48
        prn #-5
        lea STR, *r6
        inc r9
        inc *r6
        bne END
;comment line

.entry MAIN
        jmp LOOP
END:    stop
STR:    .string "abcd test
LIST:   .data 6, -9 ,+8,10, invalid
        .data -100
K:      .data 31
.extern L3 


