/*
Trinket pro 3v & Uno (Both use Atmega328)
Interrupt Vectors in ATmega328 and ATmega328P
Address   Labels  Code    Comments
0x006     rjmp    PCINT0  ; PCINT0 Handler
0x008     rjmp    PCINT1  ; PCINT1 Handler
0x00A     rjmp    PCINT2  ; PCINT2 Handler
---------------------------
                Silkscreen
PCINT0  = PB0 = D8  
PCINT1  = PB1 = D9  
PCINT2  = PB2 = D10 
PCINT3  = PB3 = D11
PCINT4  = PB4 = D12
PCINT5  = PB5 = D13
PCINT6  = -   = -
PCINT7  = -   = -
PCINT8  = PC0 = A0
PCINT9  = PC1 = A1
PCINT10 = PC2 = A2
PCINT11 = PC3 = A3
PCINT12 = PC4 = A4
PCINT13 = PC5 = A5
PCINT14 = PC6 = -
PCINT15 = -   = -
PCINT16 = PD0 = RXD
PCINT17 = PD1 = TXD
PCINT18 = PD2 = D2  // Hardware int0
PCINT19 = PD3 = D3  // Hardware int1 (Trinket pro doesn't have this pin)
PCINT20 = PD4 = D4
----------------------------
setting PCICR:
0x1 = PCIE0
0x2 = PCIE1
0x3 = PCIE0 & PCIE1
0x4 = PCIE2
0x5 = PCIE0 & PCIE2
0x6 = PCIE1 & PCIE2
----------------------------
setting PCMSKx (For enabling pins in PCINT0)
set these in -> PCMSK0    PCMSK1    PCMSK2
bit_value       PCINTx    PCINTx    PCINTx
1               0         8         16
2               1         9         17  
4               2         10        18
8               3         11        19
16              4         12        20
32              5         13        21  
64              6         14        22
128             7         -         23  
add up the bit values and convert to hex to create the mask.
I.E. PCINT3 and PCINT5 enabled => 8 + 32 = 40 = 0x28           
*/

/*
Trinket 3v
set GMSK = 0x20 to enable PCIE (there is only the one Pin Change Interupt register on trinket)
-----------------------------
                Silkscreen
PCINT0  = PB0 = #0  
PCINT1  = PB1 = #1  
PCINT2  = PB2 = #2 
PCINT3  = PB3 = #3
PCINT4  = PB4 = #4
PCINT5  = PB5 = -
-----------------------------
setting PCMSK (For enabling pins in PCIE)
set these in -> PCMSK (There is only one register so only one mask)
bit_value       PCINTx
1               0
2               1  
4               2
8               3
16              4
32              5  
add up the bit values and convert to hex to create the mask.
I.E. PCINT3 and PCINT4 enabled => 8 + 16 = 24 = 0x18           
*/