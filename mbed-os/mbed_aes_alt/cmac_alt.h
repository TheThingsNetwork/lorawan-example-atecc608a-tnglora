/**
 * @file cmac_alt.h
 *
 * @brief AES block cipher
 *
 *  Copyright (C) 2018, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */
#ifndef MBEDTLS_CMAC_ALT_H
#define MBEDTLS_CMAC_ALT_H

#include "cipher.h"

#ifdef MBEDTLS_CMAC_ALT

#ifdef __cplusplus
extern "C" {
#endif

#include "atca_basic.h"

struct mbedtls_cmac_context_t
{
    atca_aes_cmac_ctx_t atca_ctx;
    uint16_t key_id;
    uint8_t  key_block;
};



/**
 * @brief               This function sets the CMAC key, and prepares to authenticate
 *                      the input data.
 *                      Must be called with an initialized cipher context.
 *
 * @param ctx           The cipher context used for the CMAC operation, initialized
 *                      as one of the following types: MBEDTLS_CIPHER_AES_128_ECB,
 *                      MBEDTLS_CIPHER_AES_192_ECB, MBEDTLS_CIPHER_AES_256_ECB,
 *                      or MBEDTLS_CIPHER_DES_EDE3_ECB.
 * @param key           The CMAC key.
 * @param keybits       The length of the CMAC key in bits.
 *                      Must be supported by the cipher.
 *
 * @return               0 on success.
 * @return              A cipher-specific error code on failure.
 */
int mbedtls_cipher_cmac_starts( mbedtls_cipher_context_t *ctx,
                                const unsigned char *key, size_t keybits );

/**
 * @brief               This function feeds an input buffer into an ongoing CMAC
 *                      computation.
 *
 *                      It is called between mbedtls_cipher_cmac_starts() or
 *                      mbedtls_cipher_cmac_reset(), and mbedtls_cipher_cmac_finish().
 *                      Can be called repeatedly.
 *
 * @param ctx           The cipher context used for the CMAC operation.
 * @param input         The buffer holding the input data.
 * @param ilen          The length of the input data.
 *
 * @return              0 on success.
 * @return             #MBEDTLS_ERR_MD_BAD_INPUT_DATA
 *                     if parameter verification fails.
 */
int mbedtls_cipher_cmac_update( mbedtls_cipher_context_t *ctx,
                                const unsigned char *input, size_t ilen );

/**
 * @brief               This function finishes the CMAC operation, and writes
 *                      the result to the output buffer.
 *
 *                      It is called after mbedtls_cipher_cmac_update().
 *                      It can be followed by mbedtls_cipher_cmac_reset() and
 *                      mbedtls_cipher_cmac_update(), or mbedtls_cipher_free().
 *
 * @param ctx           The cipher context used for the CMAC operation.
 * @param output        The output buffer for the CMAC checksum result.
 *
 * @return               0 on success.
 * @return              #MBEDTLS_ERR_MD_BAD_INPUT_DATA
 *                      if parameter verification fails.
 */
int mbedtls_cipher_cmac_finish( mbedtls_cipher_context_t *ctx,
                                unsigned char *output );

/**
 * @brief               This function prepares the authentication of another
 *                      message with the same key as the previous CMAC
 *                      operation.
 *
 *                      It is called after mbedtls_cipher_cmac_finish()
 *                      and before mbedtls_cipher_cmac_update().
 *
 * @param ctx           The cipher context used for the CMAC operation.
 *
 * @return               0 on success.
 * @return              #MBEDTLS_ERR_MD_BAD_INPUT_DATA
 *                      if parameter verification fails.
 */
int mbedtls_cipher_cmac_reset( mbedtls_cipher_context_t *ctx );

/**
 * @brief               This function calculates the full generic CMAC
 *                      on the input buffer with the provided key.
 *
 *                      The function allocates the context, performs the
 *                      calculation, and frees the context.
 *
 *                      The CMAC result is calculated as
 *                      output = generic CMAC(cmac key, input buffer).
 *
 *
 * @param cipher_info   The cipher information.
 * @param key           The CMAC key.
 * @param keylen        The length of the CMAC key in bits.
 * @param input         The buffer holding the input data.
 * @param ilen          The length of the input data.
 * @param output        The buffer for the generic CMAC result.
 *
 * @return               0 on success.
 * @return              #MBEDTLS_ERR_MD_BAD_INPUT_DATA
 *                      if parameter verification fails.
 */
int mbedtls_cipher_cmac( const mbedtls_cipher_info_t *cipher_info,
                         const unsigned char *key, size_t keylen,
                         const unsigned char *input, size_t ilen,
                         unsigned char *output );


#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_CMAC_ALT */

#endif //MBEDTLS_CMAC_ALT_H
