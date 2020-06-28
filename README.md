# How-to-Understand-Program-Memory-Structure
Easy Program Memory Structure in Pictures

Computer Organization and Memory-Mapped Areas     June 27, 2020

Computer organization is likened to computer architecture. How bus topology is designed 
determines whether a computer is Von Neumann or Harvard architecture. A computer is said 
to be Von Neumann when data and instructions are stored in the same memory implying that 
they share a common or single bus desing. Departing from that design where data and 
instructions are on separate memories explicitly employing independent buses makes them
Harvard architecture. Therefore, Harvard types have dedicated buses.

Computers may also be classified according to their instruction set design and use of
register files. Register files employ the use of the LOAD-STORE concept. Instruction sets
can be designed to fetch multiple instructions in a single cycle making them VLIW or very
long instruction design that exploits instruction level parallelism. Lately, computers
have been labeled as 32-bit RISC processors.

When they are 32 bits, they have an addressable memory space of 4GB or 2 to the 32 power.
This memory space are allocated or divided into 6 regions according to their use. You
can find more details in the silicon vendor reference manuals.

Bit-Banding Memory-Map Area

There is this concept of bit-banding memory areas and aliases which designates a memory
address to computer peripherals. In addition to being byte addressable, they are also bit
addressable. This means we can do operations on those peripherals simply by reading/writing
to those bit-banded areas.

Take for example, lifted from the reference manual, device user guide, stm32l1xx.h, 
startup_stm32l1xx_md.s. etc., the bit-banded memory map for peripheral starts at 0x40000000.

These hex numbers are referenced a lot so they are used in assembly and C programs  usually
as defines. From there on, they are at your disposal for your own creativity.

In Assembly:

PERIPH_BASE     EQU   0x40000000 

AHBPERIPH_BASE  EQU   (PERIPH_BASE + 0x20000)

GPIOB_BASE      EQU   (AHBPERIPH_BASE + 0x0400)

GPIO_ODR	EQU   0x14	; uint16_t

	; Turn on LED
  
	LDR r7, =GPIOB_BASE		; Load GPIO port B base address
  
	LDR r1, [r7, #GPIO_ODR]		; r1 = GPIOB->ODR
  
	ORR r1, r1, #(1 << 6)		; Set output/bit pin 6 high
  
	STR r1, [r7, #GPIO_ODR]		; Write to output data register 

Moreover, typedef struct is utilized to aid in accessing and assigning values to 
respective members of a register like GPIO register.

typedef struct
{

  __IO uint32_t MODER;	// __IO is equal to volatile
  
  __IO uint16_t OTYPER;
  
  uint16_t RESERVED0;
  
  __IO uint32_t OSPEEDR;
  
  __IO uint32_t PUPDR;
  
  __IO uint16_t IDR;
  
  uint16_t RESERVED1;
  
  __IO uint16_t ODR;
  
  uint16_t RESERVED2;
  
  __IO uint16_t BSRRL; /* BSRR register is split to 2 * 16-bit fields BSRRL */
  
  __IO uint16_t BSRRH; /* BSRR register is split to 2 * 16-bit fields BSRRH */
  
  __IO uint32_t LCKR;
  
  __IO uint32_t AFR[2];
  
} GPIO_TypeDef;


// pointer pointing to memory address or cast memory address to pointer

#define GPIOB        ((GPIO_TypeDef *) GPIOB_BASE)	// macro definition

;************ General Purpose IO ************

GPIO_MODER		EQU   0x00;

GPIO_OTYPER		EQU   0x04; uint16_t

GPIO_RESERVED0  EQU   0x06; uint16_t

GPIO_OSPEEDR	EQU   0x08;

GPIO_PUPDR		EQU   0x0C;

GPIO_IDR		EQU   0x10; uint16_t

GPIO_RESERVED1  EQU   0x12; uint16_t

GPIO_ODR		EQU   0x14; uint16_t

GPIO_RESERVED2  EQU   0x16; uint16_t

GPIO_BSRRL		EQU   0x18; uint16_t BSRR register is split to 2 * 16-bit fields BSRRL 

GPIO_BSRRH		EQU   0x1A; uint16_t BSRR register is split to 2 * 16-bit fields BSRRH 

GPIO_LCKR		EQU   0x1C;

GPIO_AFR0		EQU   0x20;  AFR[0]

GPIO_AFR1		EQU   0x24;  AFR[1]

GPIO_AFRL       EQU   0x20

GPIO_AFRH       EQU   0x24

Lastly, in C:

// |= is bitwise OR. Bitwise logical OR |= is friendly compared to =. When changing multiple
bits, it is good practice to clear first before updating these bits. For example, we want 
b3b2b1b0 in register R to be 1001, we need to clear these four bits by adding R &= ~0xF; then 
R |= 0x9;

GPIOB->ODR   |= 1UL<<6;	// Set bit 6 to 1, UL is unsigned long making sure it is a long variable 

(*GPIOB).ODR |= 1UL<<6;	// Set bit 6 to 1

NVIC_SetPriority(7, 6);

NVIC->IP[7] = (6 << 4) & 0xFF;  // Set from bit 4 the 0x6 (0b0110)   

				// final =>  0110 0000 
        
				// 	bit  7654 3210
        
Happy coding!

	
