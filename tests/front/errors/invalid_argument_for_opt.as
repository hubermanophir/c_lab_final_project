.entry LIST
.extern fn1
MAIN:   add r3, LIST
        jsr fn1
LOOP:   prn #48
        lea *r2, r6
        inc r6
        bne END
;comment line

.entry MAIN
        jmp LOOP
END:    stop
STR:    .string “abcd”
LIST:   .data 6, -9
        .data -100
K:      .data 31
.extern L3 