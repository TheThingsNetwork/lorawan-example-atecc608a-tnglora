/**
 * @file cmac_alt.c
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


#include "mbedtls/cmac.h"


#if defined(MBEDTLS_CMAC_C)
#if defined(MBEDTLS_CMAC_ALT)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "mbed_toolchain.h"

#include "atca_basic.h"

static int identify_key_slot(mbedtls_cmac_context_t *ctx, const unsigned char *key_id);

int mbedtls_cipher_cmac_starts( mbedtls_cipher_context_t *ctx,
                                const unsigned char *key_id, size_t keybits )
{
    identify_key_slot(ctx->cmac_ctx, key_id);
    ATCA_STATUS status = atcab_aes_cmac_init(&ctx->cmac_ctx->atca_ctx, ctx->cmac_ctx->key_id, ctx->cmac_ctx->key_block);
    if (ATCA_SUCCESS == status) {
        return 0;
    }
    return MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA;
}

int mbedtls_cipher_cmac_update( mbedtls_cipher_context_t *ctx,
                                const unsigned char *input, size_t ilen )
{
    ATCA_STATUS status = atcab_aes_cmac_update(&ctx->cmac_ctx->atca_ctx, input, ilen);
    if (ATCA_SUCCESS == status) {
        return 0;
    }
    return MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA;
}

int mbedtls_cipher_cmac_finish( mbedtls_cipher_context_t *ctx,
                                unsigned char *output )
{
    ATCA_STATUS status = atcab_aes_cmac_finish(&ctx->cmac_ctx->atca_ctx, output, 16);
    if (ATCA_SUCCESS == status) {
        return 0;
    }
    return MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA;
}

int mbedtls_cipher_cmac_reset( mbedtls_cipher_context_t *ctx )
{
    return MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE;
}

int mbedtls_cipher_cmac( const mbedtls_cipher_info_t *cipher_info,
                         const unsigned char *key, size_t keylen,
                         const unsigned char *input, size_t ilen,
                         unsigned char *output )
{
    return MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE;
}

static int identify_key_slot(mbedtls_cmac_context_t *ctx, const unsigned char *key_id)
{
    ctx->key_id = ATCA_TEMPKEY_KEYID;
    ctx->key_block = 0;

    char input[12];
    sprintf(input, "%s", (char *) key_id);
    // we expect 3 parts separated by two tokens
    // SLOT - need the next two
    char *tok = strtok (input, "_");

    //Key ID and Key block
    while (tok != NULL) {
      tok = strtok (NULL, "_");
      if (ctx->key_id == ATCA_TEMPKEY_KEYID) {
          ctx->key_id = atoi(tok);
      } else {
          ctx->key_block = atoi(tok);
          // don't go any further
          break;
      }
    }

    return 0;
}

#endif /* #if defined(MBEDTLS_AES_ALT) */
#endif /* #if defined(MBEDTLS_CMAC_C) */
