/**
 * @file aes_alt.h
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
#ifndef MBEDTLS_AES_ALT_H
#define MBEDTLS_AES_ALT_H

#include "mbedtls/aes.h"

#if defined(MBEDTLS_AES_ALT)

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief          AES context structure
 */
typedef struct {
    bool kdf;
    uint8_t  key_id;
    uint8_t  key_block;
}
mbedtls_aes_context;

/**
 * @brief          Initialize AES context
 *
 * @param ctx      AES context to be initialized
 */
void mbedtls_aes_init( mbedtls_aes_context *ctx );

/**
 * @brief          Clear AES context
 *
 * @param ctx      AES context to be freed
 */
void mbedtls_aes_free( mbedtls_aes_context *ctx );

/**
 * @brief          AES key schedule (encryption)
 *
 * @param ctx      AES context to be used
 * @param key_id   encryption key identifier
 * @param key_len  Length of key id
 *
 * @return         0 if successful, or MBEDTLS_ERR_AES_INVALID_INPUT_LENGTH
 */
int mbedtls_aes_setkey_enc( mbedtls_aes_context *ctx, const unsigned char *key_id,
                            unsigned int key_len );

/**
 * @brief          AES key schedule (decryption)
 *
 * @param ctx      AES context to be used
 * @param key_id   encryption key identifier
 * @param key_len  Length of key id
 *
 * @return         0 if successful, or MBEDTLS_ERR_AES_INVALID_INPUT_LENGTH
 */
int mbedtls_aes_setkey_dec( mbedtls_aes_context *ctx, const unsigned char *key_id,
                            unsigned int key_len );

/**
 * @brief          AES-ECB block encryption/decryption
 *
 * @param ctx      AES context
 * @param mode     MBEDTLS_AES_ENCRYPT or MBEDTLS_AES_DECRYPT
 * @param input    16-byte input block
 * @param output   16-byte output block
 *
 * @return         0 if successful
 */
int mbedtls_aes_crypt_ecb( mbedtls_aes_context *ctx,
                           int mode,
                           const unsigned char input[16],
                           unsigned char output[16] );

#if defined(MBEDTLS_CIPHER_MODE_CBC)
/**
 * @brief  This function performs an AES-CBC encryption or decryption operation
 *         on full blocks.
 *
 *         It performs the operation defined in the @p mode
 *         parameter (encrypt/decrypt), on the input data buffer defined in
 *         the @p input parameter.
 *
 *         It can be called as many times as needed, until all the input
 *         data is processed. mbedtls_aes_init(), and either
 *         mbedtls_aes_setkey_enc() or mbedtls_aes_setkey_dec() must be called
 *         before the first call to this API with the same context.
 *
 * @note   This function operates on aligned blocks, that is, the input size
 *         must be a multiple of the AES block size of 16 Bytes.
 *
 * @note   Upon exit, the content of the IV is updated so that you can
 *         call the same function again on the next
 *         block(s) of data and get the same result as if it was
 *         encrypted in one call. This allows a "streaming" usage.
 *         If you need to retain the contents of the IV, you should
 *         either save it manually or use the cipher module instead.
 *
 *
 * @param ctx      The AES context to use for encryption or decryption.
 * @param mode     The AES operation: #MBEDTLS_AES_ENCRYPT or
 *                 #MBEDTLS_AES_DECRYPT.
 * @param length   The length of the input data in Bytes. This must be a
 *                 multiple of the block size (16 Bytes).
 * @param iv       Initialization vector (updated after use).
 * @param input    The buffer holding the input data.
 * @param output   The buffer holding the output data.
 *
 * @return         0 on success.
 * @return         #MBEDTLS_ERR_AES_INVALID_INPUT_LENGTH
 *                 on failure.
 */
int mbedtls_aes_crypt_cbc( mbedtls_aes_context *ctx,
                    int mode,
                    size_t length,
                    unsigned char iv[16],
                    const unsigned char *input,
                    unsigned char *output );
#endif /* MBEDTLS_CIPHER_MODE_CBC */

#ifdef __cplusplus
}
#endif


#endif /* MBEDTLS_AES_ALT */

#endif /* MBEDTLS_AES_ALT_H */
