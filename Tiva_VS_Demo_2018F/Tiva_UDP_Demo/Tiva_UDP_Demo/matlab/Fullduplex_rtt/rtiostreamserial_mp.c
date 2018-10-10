
#include "rtiostream.h"
#include "uart_driver_mp.h"

#include "stellaris_runtime.h"


#if EXT_MODE==1

#define EXTMODE_PORT 0
#define EXTMODE_TX_BUF_SIZE  512
#define EXTMODE_RX_BUF_SIZE  512

unsigned char extmode_tx_buf[EXTMODE_TX_BUF_SIZE];
unsigned char extmode_rx_buf[EXTMODE_RX_BUF_SIZE];

/* Initialize Serial */
int rtIOStreamOpen(int argc, void *argv[])
{
    //BoardInit();
    //uart_init();
    uart_port_open(EXTMODE_PORT, extmode_rx_buf, EXTMODE_RX_BUF_SIZE, extmode_tx_buf, EXTMODE_TX_BUF_SIZE);
    return RTIOSTREAM_NO_ERROR;
}

/* Read data from serial */
int rtIOStreamRecv(
        int      streamID,  // A handle to the stream that was returned by a previous call to rtIOStreamOpen.
        void   * dst,       // A pointer to the start of the buffer where received data must be copied.
        size_t   size, 	    // Size of data to copy into the buffer. For byte-addressable architectures,
                            // size is measured in bytes. Some DSP architectures are not byte-addressable.
                            // In these cases, size is measured in number of WORDs, where sizeof(WORD) == 1.
        size_t * sizeRecvd) // The number of units of data received and copied into the buffer dst (zero if no data was copied).
{

    unsigned char * uc_dst =  (unsigned char *) dst;
    
    *sizeRecvd = 0U; // Initialize the number of received chars to zero.
    while (*sizeRecvd < size && uart_port_read_one(EXTMODE_PORT, uc_dst++) ) // Try to receive char as many times as commanded.
    {
        (*sizeRecvd)++;
    }
    
    return RTIOSTREAM_NO_ERROR;
}

/* Write data to serial */
int rtIOStreamSend(
        int          streamID,
        const void * src,
        size_t       size,
        size_t     * sizeSent)
{   
      //  led_debug_signal(LED_DEBUG_ALL_ON);
    unsigned char * uc_src =  (unsigned char *) src;
    
    *sizeSent = 0U;
    while (*sizeSent < size && uart_port_write_one(EXTMODE_PORT, uc_src++) ) // Try to send char as many times as commanded.
    {
        (*sizeSent)++;
    }
    //led_debug_signal(LED_DEBUG_ALL_OFF);
    return RTIOSTREAM_NO_ERROR;
}

int rtIOStreamClose(int streamID)
{
    return RTIOSTREAM_NO_ERROR;
}
#endif
//end
