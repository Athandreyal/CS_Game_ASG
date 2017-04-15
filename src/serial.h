#include "types.h"

#define TRAP_73 73
#define TRAP_74 74
#define TRAP_75 75
#define TRAP_76 76

void serial_setup();/*init*/
void serial_teardown();/*clean up/restore*/
int serial_write(const char *buf,UINT16 size);/*buffer the output, size is ammount actually queued*/
int serial_read(char *buff,UINT16 size);  /*buffer the input, size is ammount actually dequeued*/
int serial_can_write();/*amount of bytes that can be written at call time*/
int serial_can_read();/*like write*/
int TxMtIsr();/*ISR for transmit, triggers when USART is empty*/
int RxFulIsr();/*ISR for receive, triggers when full*/
void TxErIsr();/*ISR for transmit Error, triggers when USART is empty*/
void RxErIsr();/*ISR for receive Error, triggers when USART is empty*/

