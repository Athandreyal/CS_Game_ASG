Vector orig_vector73 = 0;
Vector orig_vector74 = 0;
Vector orig_vector75 = 0;
Vector orig_vector76 = 0;

const int bufferSize = 256
UINT8 TxBuf[bufferSize];
UINT8 Txhead;
UINT8 TxTail;
UINT8 TxFill;
UINT8 RxBuf[bufferSize];
UINT8 Rxhead;
UINT8 RxTail;
UINT8 RxFill;
const long *MFP_UAD = 0xFFFFFA2F;    /* USART data register */

void serial_setup(){
    orig_vector73 = install_vector(TRAP_73,trap73_isr);  /*  Tx Error  */
    orig_vector74 = install_vector(TRAP_74,trap74_isr);  /*  Tx Empty  */
    orig_vector75 = install_vector(TRAP_75,trap75_isr);  /*  Rx Error  */
    orig_vector76 = install_vector(TRAP_76,trap76_isr);  /*  Rx Full   */
}

void serial_teardown();{
    install_vector(TRAP_73,orig_vector73);
    install_vector(TRAP_74,orig_vector74);
    install_vector(TRAP_75,orig_vector75);
    install_vector(TRAP_76,orig_vector76);
}

/*buffer the output, size is ammount actually queued*/
int serial_write(const char *buf,UINT16 size){
    int wrote = 0;
    int index;
    
    for(index = 0;TxFill < 256 && wrote < size;index++){
        wrote++;
        TxFill++;
        TxBuf[Tail++] = buf[Index];
    }
    return wrote;
}

/*buffer the input, size is ammount actually dequeued*/
int serial_read(char *buff,UINT16 size){
    int read = 0;
    int index;
    
    for(index = 0;TxFill > 0 & read < size;index++){
        txFill--;
        read++;
        buf[index] = RxBuf[RxHead++];
    }
    return read;
}  

int serial_tx_pending(){
    int pending = 0;
    
    return pending;
}

/*amount of bytes that can be written at call time*/
int serial_can_write(){
    return bufferSize-TxFill;
}
/*amount of bytes that can be read at call time*/
int serial_can_read(){
    return bufferSize-RxFill;
}
/*ISR for transmit, triggers when USART is empty*/
int TxMtIsr(){
    if(serial_can_write()){/*have data to send*/
        /*place one in register*/
        *MFP_UAD = TxBuf[TxHead++];
    }
}
/*ISR for receive, triggers when USART is full*/
int RxFulIsr(){
    if(serial_can_read){
        /*take from buffer, and insert*/
        RxBuf[RxTail++] = *MFP_UAD;
    }
}

void TxErIsr(){
    printf("we done fucked transmitting....oops\n");
}

void RxErIsr(){
    printf("we done fucked receiving....oops\n");
}

