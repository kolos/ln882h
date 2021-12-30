#ifndef __USR_SEND_DATA_H__
#define __USR_SEND_DATA_H__



#define DATA_TRANS_SVR_UUID 0xdd,0xdd,0xb4,0xf8,0xcd,0xf3,0x45,0xe9,0xa3,0x2f,0x2a,0x2a,0xe2,0xdb,0xcc,0xe4   //ccddb4f8-cdf3-11e9-a32f-2a2ae2dbcce4
#define DATA_TRANS_RX_UUID 0xff,0xcc,0xdb,0xe2,0x2a,0x2a,0x32,0xa3,0xe9,0x11,0x67,0xcd,0x4a,0x4a,0xbe,0x28 //28be4a4a-cd67-11e9-a32f-2a2ae2dbcce4
#define DATA_TRANS_TX_UUID  0xee,0xcc,0xdb,0xe2,0x2a,0x2a,0x23,0xa3,0xe9,0x11,0x67,0xcd,0xb6,0x4c,0xbe,0x28//28be4cb6-cd67-11e9-a32f-2a2ae2dbcce4

#define DATA_TRANS_MAX_LEN 1024

enum trans_data_svc{
    DATA_TRANS_DECL_CHAR_RX = 0,
    DATA_TRANS_CHAR_VAL_RX,
    DATA_TRANS_DECL_CHAR_TX,
    DATA_TRANS_CHAR_VAL_TX,
    DATA_TRANS_CLIENT_CHAR_CFG_TX,
};

void  data_trans_svc_add(void);


#endif /* __USR_APP_H__ */


