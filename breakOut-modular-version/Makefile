# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:breakOut.elf

#additional rules for files
breakOut.elf: ${COMMON_OBJECTS} breakOut_Main.o ball.o  paddle.o blocks.o hearts.o scoreBoard.o wdt_handler.o p2_interrupt_handler.o switches.o buzzer.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load: breakOut.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
