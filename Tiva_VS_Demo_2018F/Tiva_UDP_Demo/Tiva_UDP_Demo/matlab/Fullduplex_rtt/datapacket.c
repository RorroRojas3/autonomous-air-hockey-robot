#ifdef MATLAB_MEX_FILE
// build mex file
    #include "datapacket.h"
    // no code in this one.
#else

#include <stdlib.h>   // malloc
#include "stellaris_runtime.h"
#include "uart_driver_mp.h"
#include "datapacket.h"

unsigned char common_dummy_buf;

int init_datapacket(int port, int in_pkt_size, int out_pkt_size)
{
    unsigned char* in_buf;
    unsigned char* out_buf;
    int in_buf_size, out_buf_size;
    
    in_buf = out_buf = &common_dummy_buf;
    in_buf_size = out_buf_size = 1;
    if (in_pkt_size > 0)
    {
        // this port is intended to rx data
        // notice buf is not freed. this is not an issue for
        // simple bareboard implementation, but will cause problem if the 
        // program is running in a bigger framework.
        in_buf_size = in_pkt_size*2;
        in_buf = (unsigned char*)malloc(in_buf_size);
    }
    if (out_pkt_size > 0)
    {
        // this port is intended to tx data
        // notice buf is not freed. this is not an issue for
        // simple bareboard implementation, but will cause problem if the 
        // program is running in a bigger framework.
        out_buf_size = out_pkt_size*2;
        out_buf = (unsigned char*)malloc(out_buf_size);
    }
    
    if (uart_port_open(port, in_buf, in_buf_size, out_buf, out_buf_size) )
    {
        return 1;
    }else
    {
        return 0;
    }
}

int datapacket_get(int port, int in_pkt_size, unsigned char *data)
{
    if (!(in_pkt_size >0)) return 0;
    
    if (uart_port_read_pending(port)>=in_pkt_size)
    {
        while(in_pkt_size--)
        {
            uart_port_read_one(port, data++); // data copy
        }
        return 1;
    }
    else
    {
        return 0;
    }
    return 0;
}

int datapacket_put(int port, int out_pkt_size, unsigned char *data)
{
    if (!(out_pkt_size >0)) return 0;
   
    // the total buffer will be always 2x out_pkt_size
    // so if the part being used is less than one pkt size
    // there will be enough space
    if (uart_port_write_pending(port) <= out_pkt_size)
    {
        while(out_pkt_size--)
        {
            uart_port_write_one(port, data++); // data copy
        }
        return 1;
    }
    else
        return 0;
}

int datapacket_rw(int port, int in_pkt_size, unsigned char *in_data, 
                            int out_pkt_size, unsigned char *out_data)
{
    int ret;
    ret =  datapacket_get(port, in_pkt_size, in_data)<<16;
    ret |= datapacket_put(port, out_pkt_size, out_data);
    return ret;
}

#if 0
int init_datapacket(int pkt_size, int port, p_datapacket_reg p)
{
    p->in_buf = (unsigned char*)malloc(pkt_size*2);
    p->out_buf = (unsigned char*)malloc(1);
    
    if (p->in_buf &&  p->out_buf && uart_port_open(port, p->inbuf, pkt_size*2, p->out_buf, 1) )
    {
        p->port = port;
        p->pkt_size = pkt_size;
        input_synced = SYNC_THRESHOLD+1;
        return 1;
    }else
    {
        destroy_datapacket(p);
        return 0;
    }
}

void destroy_datapacket(p_datapacket_reg p)
{
    uart_port_close(p->port);
    
    if (p->in_buf)
        free(p->in_buf);
    if (p->out_buf)
        free(p->out_buf);

    p->port = UART_N_PORTS; // an invalid port , valid port [0..UART_N_PORTS-1]
    p->in_buf = p->out_buf = NULL;
}

int attemp_sync_input(p_datapacket_reg p)
{
    unsigned char ch;
    
    while (uart_port_read_one(p->port, &ch))
    {
        if (ch==SYNC_CHAR  )
        {
            if (p->input_synced<SYNC_THRESHOLD)
                p->input_synced++;
        }else if (ch==((~SYNC_CHAR)&0xFF) && p->input_synced==SYNC_THRESHOLD){
            p->input_synced ++;
        }else
        {
            p->input_synced=0;
        }
    }
    return 0;
}

void datapacket_get(p_datapacket_reg p, unsigned char * data)
{
    int n;
    if (p->input_synced<=SYNC_THRESHOLD)
    {
        if (!attemp_sync_input(p))
            return;
    }
    if (uart_port_read_pending(p->port)>=pkt_size)
    {
        n= pkt_size;
        while(n--)
        {
            uart_port_read_one(p->port,*data++); // data copy
        }
    }
}

void datapacket_put(p_datapacket_reg p, unsigned char * data)
{
    //do nothing
}
#endif //0


#endif
