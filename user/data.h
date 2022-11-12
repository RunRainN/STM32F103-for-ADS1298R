#include "sysinc.h"


#ifndef DATA_H__
#define DATA_H__

#ifdef __cplusplus
 extern "C" {
#endif

void convert_data(u8 *source, int32_t *res);
void pack_data(int32_t *data, u8 *buf);
void uart_send_data(u8 *tx_buf, u8 ch);

#endif
