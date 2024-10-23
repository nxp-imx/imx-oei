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

#ifndef DRV_ELE_H
#define DRV_ELE_H

/*!
 * @addtogroup ele_driver
 * @{
 */

/*! @file */

/* Includes */

#include "fsl_mu.h"

/* Defines */

/*!
 * @name Macros for version parsing
 */
/** @{ */
#define ELE_HOTFIX_VER(X)   (((X) >> 28) & 0x3UL)   /*!< Extract ELE hotfix ver */
#define ELE_AUTH_VER(X)     (((X) >> 27) & 0x1UL)   /*!< Extract ELE authenticated flag */
#define ELE_ALT_VER(X)      (((X) >> 24) & 0x1UL)   /*!< Extract ELE alternative flag */
#define ELE_MAJOR_VER(X)    (((X) >> 16) & 0xFFUL)  /*!< Extract ELE major ver */
#define ELE_MINOR_VER(X)    (((X) >> 4) & 0xFFFUL)  /*!< Extract ELE minor ver */
#define ELE_PATCH_VER(X)    ((X) & 0xFUL)           /*!< Extract ELE patch ver */
/** @} */

#ifdef NO_DEVICE_ACCESS
/*!
 * This variable is used to access fake ELE.
 */
extern uint32_t temp_ele[];
#define HAS_TEMP_ELE
#endif

/* Types */

/*!
 * This type is used to communicate ELE indication codes.
 */
typedef enum
{
    ELE_ROM_PING_FAILURE_IND                = 0x0A,
    ELE_FW_PING_FAILURE_IND                 = 0x1A,
    ELE_NO_AUTHENTICATION_FAILURE_IND       = 0xEE,
    ELE_BAD_SRK_SET_FAILURE_IND             = 0xEF,
    ELE_BAD_SIGNATURE_FAILURE_IND           = 0xF0,
    ELE_BAD_HASH_FAILURE_IND                = 0xF1,
    ELE_INVALID_LIFECYCLE_IND               = 0xF2,
    ELE_PERMISSION_DENIED_FAILURE_IND       = 0xF3,
    ELE_INVALID_MESSAGE_FAILURE_IND         = 0xF4,
    ELE_BAD_VALUE_FAILURE_IND               = 0xF5,
    ELE_BAD_FUSE_ID_FAILURE_IND             = 0xF6,
    ELE_BAD_CONTAINER_FAILURE_IND           = 0xF7,
    ELE_BAD_VERSION_FAILURE_IND             = 0xF8,
    ELE_INVALID_KEY_FAILURE_IND             = 0xF9,
    ELE_BAD_KEY_HASH_FAILURE_IND            = 0xFA,
    ELE_NO_VALID_CONTAINER_FAILURE_IND      = 0xFB,
    ELE_BAD_CERTIFICATE_FAILURE_IND         = 0xFC,
    ELE_BAD_UID_FAILURE_IND                 = 0xFD,
    ELE_BAD_MONOTONIC_COUNTER_FAILURE_IND   = 0xFE,
    ELE_MUST_SIGNED_FAILURE_IND             = 0xE0,
    ELE_UNALIGNED_PAYLOAD_FAILURE_IND       = 0xA6,
    ELE_WRONG_SIZE_FAILURE_IND              = 0xA7,
    ELE_ENCRYPTION_FAILURE_IND              = 0xA8,
    ELE_DECRYPTION_FAILURE_IND              = 0xA9,
    ELE_OTP_PROGFAIL_FAILURE_IND            = 0xAA,
    ELE_OTP_LOCKED_FAILURE_IND              = 0xAB,
    ELE_OTP_INVALID_IDX_FAILURE_IND         = 0xAD,
    ELE_TIME_OUT_FAILURE_IND                = 0xB0,
    ELE_BAD_PAYLOAD_FAILURE_IND             = 0xB1,
    ELE_WRONG_ADDRESS_FAILURE_IND           = 0xB4,
    ELE_DMA_FAILURE_IND                     = 0xB5,
    ELE_DISABLED_FEATURE_FAILURE_IND        = 0xB6,
    ELE_MUST_ATTEST_FAILURE_IND             = 0xB7,
    ELE_RNG_NOT_STARTED_FAILURE_IND         = 0xB8,
    ELE_CRC_ERROR_IND                       = 0xB9,
    ELE_AUTH_SKIPPED_OR_FAILED_FAILURE_IND  = 0xBB,
    ELE_INCONSISTENT_PAR_FAILURE_IND        = 0xBC,
    ELE_RNG_INST_FAILURE_FAILURE_IND        = 0xBD,
    ELE_LOCKED_REG_FAILURE_IND              = 0xBE,
    ELE_BAD_ID_FAILURE_IND                  = 0xBF,
    ELE_INVALID_OPERATION_FAILURE_IND       = 0xC0,
    ELE_NON_SECURE_STATE_FAILURE_IND        = 0xC1,
    ELE_MSG_TRUNCATED_IND                   = 0xC2,
    ELE_BAD_IMAGE_NUM_FAILURE_IND           = 0xC3,
    ELE_BAD_IMAGE_ADDR_FAILURE_IND          = 0xC4,
    ELE_BAD_IMAGE_PARAM_FAILURE_IND         = 0xC5,
    ELE_BAD_IMAGE_TYPE_FAILURE_IND          = 0xC6,
    ELE_CORRUPTED_SRK_FAILURE_IND           = 0xD0,
    ELE_OUT_OF_MEMORY_IND                   = 0xD1,
    ELE_CSTM_FAILURE_IND                    = 0xCF,
    ELE_OLD_VERSION_FAILURE_IND             = 0xCE,
    ELE_WRONG_BOOT_MODE_FAILURE_IND         = 0xCD,
    ELE_APC_ALREADY_ENABLED_FAILURE_IND     = 0xCB,
    ELE_RTC_ALREADY_ENABLED_FAILURE_IND     = 0xCC,
    ELE_FASBOOT_DISABLED_FAILURE_IND        = 0x90,
    ELE_FASTBOOT_ILLEGAL_STATE_FAILURE_IND  = 0x91,
    ELE_GENERIC_AUTH_FW_FAILURE_IND         = 0x92,
    ELE_GENERIC_AUTH_OEM_FAILURE_IND        = 0x93,
    ELE_FAST_IMAGE_VERIFY_FAILURE_IND       = 0x94,
    ELE_ABORT_IND                           = 0xFF
} ele_msg_ind_t;

/*!
 * This type is used to communicate ELE status codes.
 */
typedef enum
{
    ELE_SUCCESS_IND = 0xD6,
    ELE_FAILURE_IND = 0x29
} ele_msg_status_t;

/*!
 * This type is used to return ELE info.
 */
typedef struct
{
    uint8_t cmd;             /*!< Command */
    uint8_t version;         /*!< Version of ELE */
    uint16_t len;            /*!< Data length */
    uint16_t socId;          /*!< SoC ID */
    uint16_t socRev;         /*!< SoC revision */
    uint16_t lifecycle;      /*!< LMDA lifecycle */
    uint8_t sssmState;       /*!< Security subsystem state */
    uint8_t attestApiVer;    /*!< Attesttion API version */
    uint32_t uid[4];         /*!< Chip unique ID */
    uint32_t shaPatch[8];    /*!< SHA256 ROM patch */
    uint32_t shaFw[8];       /*!< FW SHA */
    uint32_t oemSrkh[16];    /*!< OEM SRKh */
    uint8_t trngState;       /*!< TRNG state */
    uint8_t csalState;       /*!< CSAL state */
    uint8_t imemState;       /*!< IMEM state */
    uint8_t unused;          /*!< Unused */
    uint32_t oemPqcSrkh[16]; /*!< OEM PQC SRKH */
    uint32_t reserved[8];    /*!< Reserved */
} ele_info_t;

/* Functions */

/*!
 * This function signs a data array of specified size
 *
 * @param[in]     dataAddr    pointer to data array to be signed
 * @param[in]     dataSize    size of data array to be signed
 * @param[out]    macAddr     pointer to array of MAC_LENGTH size the signature to be stored
 * @param[out]    resp        pointer to response
 */
int ELE_SignData(const void *dataAddr, uint32_t dataSize,
                 const void *macAddr, uint32_t *resp);

/*!
 * This function verifies the signature of a data array of specified size
 *
 * @param[in]     dataAddr    pointer to data array to be verified
 * @param[in]     dataSize    size of data array to be verified
 * @param[out]    macAddr     pointer to the signature to be verified
 * @param[out]    resp        pointer to response
 */
int ELE_VerifyData(const void *dataAddr, uint32_t dataSize,
                   const void *macAddr, uint32_t *resp);

/*!
 * This function releases in RW mode the RAM region locked by ELE
 *
 * @param[in]     img_id   image ID for which the RAM will be released
 * @param[out]    resp     pointer to response
 */
int ELE_ReleaseImageRam(uint32_t img_id, uint32_t *resp);

#endif /* DRV_ELE_H */

/** @} */

