/*
 * Copyright 2023-2024 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Includes */

#include "fsl_ele.h"
#include "fsl_mu.h"
#include "crc.h"
#if defined(DEBUG_ELE)
#include <stdio.h>
#endif

/* Local Defines */

#define ELE_STAT(X)          ((X) & 0x000000FFUL)
#define ELE_ID(X)            ((X) & 0x00FFFFFFUL)
#define ELE_VER(X)           ((X) & 0x7FFFFFFFUL)
#define ELE_DIRTY_VER(X)     (((X) >> 31) & 0x1UL)

#define ELE_MSG_VER             0x06U
#define ELE_MSG_TAG             0x17U
#define ELE_MSG_TAG_RESP        0xE1U
#define ELE_MSG_MIN_SIZE        3U
#define ELE_MSG_MAX_SIZE        23U

/* Local Types */

typedef enum
{
    ELE_PING_REQ                = 0x01,
    ELE_FW_AUTH_REQ             = 0x02,
    ELE_RESTART_RST_TIMER_REQ   = 0x04,
    ELE_DUMP_DEBUG_BUFFER_REQ   = 0x21,
    ELE_OEM_CNTN_AUTH_REQ       = 0x87,
    ELE_VERIFY_IMAGE_REQ        = 0x88,
    ELE_RELEASE_CONTAINER_REQ   = 0x89,
    ELE_WRITE_SECURE_FUSE_REQ   = 0x91,
    ELE_FWD_LIFECYCLE_UP_REQ    = 0x95,
    ELE_READ_FUSE_REQ           = 0x97,
    ELE_GET_FW_VERSION_REQ      = 0x9D,
    ELE_RET_LIFECYCLE_UP_REQ    = 0xA0,
    ELE_GET_EVENTS_REQ          = 0xA2,
    ELE_START_RNG_REQ           = 0xA3,
    ELE_GET_TRNG_STATE_REQ      = 0xA4,
    ELE_ENABLE_PATCH_REQ        = 0xC3,
    ELE_RELEASE_RDC_REQ         = 0xC4,
    ELE_GET_FW_STATUS_REQ       = 0xC5,
    ELE_ENABLE_OTFAD_REQ        = 0xC6,
    ELE_RESET_REQ               = 0xC7,
    ELE_UPDATE_OTP_CLKDIV_REQ   = 0xD0,
    ELE_POWER_DOWN_REQ          = 0xD1,
    ELE_ENABLE_APC_REQ          = 0xD2,
    ELE_ENABLE_RTC_REQ          = 0xD3,
    ELE_ENABLE_AUX_REQ          = 0xD4,
    ELE_STOP_RST_TIMER_REQ      = 0xD5,
    ELE_WRITE_FUSE_REQ          = 0xD6,
    ELE_RELEASE_CAAM_REQ        = 0xD7,
    ELE_RESET_A35_CTX_REQ       = 0xD8,
    ELE_MOVE_TO_UNSECURED_REQ   = 0xD9,
    ELE_GET_INFO_REQ            = 0xDA,
    ELE_ATTEST_REQ              = 0xDB,
    ELE_RELEASE_PATCH_REQ       = 0xDC,
    ELE_OTP_SEQ_SWITH_REQ       = 0xDD,
    ELE_REL_IMG_RAM_REQ         = 0xDE,
    ELE_SIGN_VERIFY_REQ         = 0xE5,
    ELE_ABORT                   = 0xFF
} ele_cmd_type_t;

typedef struct
{
    uint8_t ver;
    uint8_t size;
    ele_cmd_type_t cmd;
    uint8_t tag;
} msg_hdr_t;

typedef struct
{
    ele_msg_status_t status;
    ele_msg_ind_t ind;
    uint16_t abortCode;
} ele_msg_resp_t;

typedef union
// coverity[misra_c_2012_rule_19_2_violation:FALSE]
{
    msg_hdr_t hdr;
    uint32_t word[ELE_MSG_MAX_SIZE];
// coverity[misra_c_2012_rule_19_2_violation:FALSE]
} ele_mu_msg_t;

typedef union
// coverity[misra_c_2012_rule_19_2_violation:FALSE]
{
    msg_hdr_t hdr;
    uint32_t word[ELE_MSG_MIN_SIZE];
// coverity[misra_c_2012_rule_19_2_violation:FALSE]
} ele_mu_min_t;

/* Local Functions */

static void ELE_Call(ele_mu_msg_t *msg, ele_cmd_type_t cmd,
    uint8_t size);
static void ELE_MuTx(ele_mu_msg_t *msg);
static void ELE_MuRx(ele_mu_msg_t *msg, uint8_t maxLen,
    ele_cmd_type_t cmd);

/* Local Variables */

// coverity[misra_c_2012_rule_19_2_violation:FALSE]
static ele_mu_msg_t s_msgMax;
static MU_Type *s_eleMuBase = MU_ELE0;

#define ELE_SIGN    0x00d50000
#define ELE_VERIFY  0x002a0000
/*--------------------------------------------------------------------------*/
/* ELE Sign Data                                                            */
/*--------------------------------------------------------------------------*/
int ELE_SignData(const void *dataAddr, uint32_t dataSize,
                 const void *macAddr, uint32_t *resp)
{
    /* Fill in parameters */
    s_msgMax.word[1] = (uint32_t)dataAddr;
    s_msgMax.word[2] = (uint32_t)macAddr;
    s_msgMax.word[3] = ELE_SIGN | dataSize;

    /* Call ELE */
    ELE_Call(&s_msgMax, ELE_SIGN_VERIFY_REQ, 4U);

    if (resp)
    {
        *resp = s_msgMax.word[1];
    }

    return (s_msgMax.word[1] & 0xFF);
}

/*--------------------------------------------------------------------------*/
/* ELE Verify Data                                                          */
/*--------------------------------------------------------------------------*/
int ELE_VerifyData(const void *dataAddr, uint32_t dataSize,
                   const void *macAddr, uint32_t *resp)
{
    /* Fill in parameters */
    s_msgMax.word[1] = (uint32_t)dataAddr;
    s_msgMax.word[2] = (uint32_t)macAddr;
    s_msgMax.word[3] = ELE_VERIFY | dataSize;

    /* Call ELE */
    ELE_Call(&s_msgMax, ELE_SIGN_VERIFY_REQ, 4U);

    if (resp)
    {
        *resp = s_msgMax.word[1];
    }

    return (s_msgMax.word[1] & 0xFF);
}

/*--------------------------------------------------------------------------*/
/* ELE Release Image RAM                                                    */
/*--------------------------------------------------------------------------*/
int ELE_ReleaseImageRam(uint32_t img_id, uint32_t *resp)
{
    /* Fill in parameters */
    s_msgMax.word[1] = (uint32_t)(1 << img_id);
    s_msgMax.word[2] = 0;
    s_msgMax.word[3] = 0;

    /* Call ELE */
    ELE_Call(&s_msgMax, ELE_REL_IMG_RAM_REQ, 2U);

    if (resp)
    {
        *resp = s_msgMax.word[1];
    }

    return (s_msgMax.word[1] & 0xFF);

}

/*--------------------------------------------------------------------------*/
/* Call ELE function                                                        */
/*--------------------------------------------------------------------------*/
// coverity[misra_c_2012_rule_19_2_violation:FALSE]
static void ELE_Call(ele_mu_msg_t *msg, ele_cmd_type_t cmd, uint8_t size)
{
    /* Setup message */
    msg->hdr.tag = ELE_MSG_TAG;
    msg->hdr.cmd = cmd;
    msg->hdr.size = size;
    msg->hdr.ver = ELE_MSG_VER;

    /* Send message */
    ELE_MuTx(msg);

    /* Receive response */
    msg->word[1] = 0U;
    ELE_MuRx(msg, ELE_MSG_MAX_SIZE, cmd);
}

/*--------------------------------------------------------------------------*/
/* Send MU message to ELE                                                   */
/*--------------------------------------------------------------------------*/
// coverity[misra_c_2012_rule_19_2_violation:FALSE]
static void ELE_MuTx(ele_mu_msg_t *msg)
{
    const uint32_t *buf = (const uint32_t*) msg;
    uint32_t size;
    uint32_t pos = 1U;

    /* Calculate CRC */
    if (msg->hdr.size > 4U)
    {
        msg->hdr.size++;
        s_msgMax.word[msg->hdr.size - 1U] = CRC_Xor(&msg->word[0],
            ((uint32_t)msg->hdr.size) - 1UL);
    }

    /* Send header and NMI */
    MU_SendMsg(s_eleMuBase, 0, buf[0]);
#if defined(DEBUG_ELE)
    printf("ELE tx: 0x%08x ", buf[0]);
#endif
    /* Send message body */
    size = ((uint32_t) msg->hdr.size) - 1UL;
    while (size > 0U)
    {
        MU_SendMsg(s_eleMuBase, pos % 8UL, buf[pos]);
#if defined(DEBUG_ELE)
        printf("0x%08x ", buf[pos]);
#endif
        pos++;
        size--;
    }

#if defined(DEBUG_ELE)
    printf("\n");
#endif
}

/*--------------------------------------------------------------------------*/
/* Receive MU message from ELE                                              */
/*--------------------------------------------------------------------------*/
// coverity[misra_c_2012_rule_19_2_violation:FALSE]
static void ELE_MuRx(ele_mu_msg_t *msg, uint8_t maxLen,
    ele_cmd_type_t cmd)
{
    uint32_t *buf = (uint32_t*) msg;

    /* Get message header */
    buf[0] = MU_ReceiveMsg(s_eleMuBase, 0U);
#if defined(DEBUG_ELE)
    printf("ELE rx: 0x%08x ", buf[0]);
#endif

    /* Check response */
    if ((msg->hdr.tag == ELE_MSG_TAG_RESP)
       && (msg->hdr.ver == ELE_MSG_VER))
    {
        uint8_t size;
        uint8_t pos = 1U;

        /* Get message size */
        size = MIN(msg->hdr.size - 1U, maxLen - 1U);

        /* Get message body */
        while (size > 0U)
        {
            buf[pos] = MU_ReceiveMsg(s_eleMuBase, ((uint32_t) pos) % 8UL);
#if defined(DEBUG_ELE)
            printf("0x%08x ", buf[pos]);
#endif
            pos++;
            size--;
        }
    }

#if defined(DEBUG_ELE)
    printf("\n");
#endif
}
