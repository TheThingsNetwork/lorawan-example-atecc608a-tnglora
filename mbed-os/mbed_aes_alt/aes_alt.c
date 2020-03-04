/**
 * @file aes_alt.c
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

#include "mbedtls/aes.h"

#if defined(MBEDTLS_AES_C)
#if defined(MBEDTLS_AES_ALT)

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "mbed_toolchain.h"
#include "mbed_assert.h"
#include "mbed_error.h"

#include "atca_basic.h"

/* Implementation that should never be optimized out by the compiler */
static void mbedtls_zeroize( void *v, size_t n )
{
    volatile unsigned char *p = (unsigned char*)v;
    while( n-- ) *p++ = 0;
}

void mbedtls_aes_init( mbedtls_aes_context *ctx )
{
    memset( ctx, 0, sizeof( mbedtls_aes_context ) );
}

void mbedtls_aes_free( mbedtls_aes_context *ctx )
{
    if( ctx == NULL )
        return;

    mbedtls_zeroize( ctx, sizeof( mbedtls_aes_context ) );
}

static int identify_key_slot(uint8_t *key_id, uint8_t *key_block, const unsigned char *key_string)
{
    *key_id = 0xFF;
    *key_block = 0;

    char input[12];
    sprintf(input, "%s", (char *) key_string);
    // we expect 3 parts separated by two tokens
    // SLOT - need the next two
    char *tok = strtok (input, "_");

    //Key ID and Key block
    while (tok != NULL) {
      tok = strtok (NULL, "_");
      if (*key_id == 0xFF) {
          *key_id = atoi(tok);
      } else {
          *key_block = atoi(tok);
          // don't go any further
          break;
      }
    }

    return 0;
}

int mbedtls_aes_setkey_enc( mbedtls_aes_context *ctx, const unsigned char *key_string,
                            unsigned int key_len )
{
    return identify_key_slot(&ctx->key_id, &ctx->key_block, key_string);
}

int mbedtls_aes_setkey_dec( mbedtls_aes_context *ctx, const unsigned char *key_string,
                            unsigned int key_len )
{
    return identify_key_slot(&ctx->key_id, &ctx->key_block, key_string);
}

static int perform_kdf(uint8_t source_id,
                       uint8_t source_block,
                       const unsigned char *target_slot_string,
                       const unsigned char message[16])
{
    //Source key slot is the LSB and target key slot is the MSB
    uint16_t source_target_ids = 0;
    uint8_t target_key_id;
    uint8_t target_key_block;

    if (identify_key_slot(&target_key_id, &target_key_block, target_slot_string) != 0) {
        return -1;
    }

    MBED_ASSERT(target_key_block == 0);

    source_target_ids = target_key_id << 8;
    source_target_ids += source_id;

    uint32_t detail = source_block;

    return atcab_kdf(KDF_MODE_ALG_AES | KDF_MODE_SOURCE_SLOT | KDF_MODE_TARGET_SLOT,
            source_target_ids, detail, message, NULL, NULL);

}


int mbedtls_internal_aes_encrypt( mbedtls_aes_context *ctx,
                          const unsigned char input[16],
                          unsigned char output[16] )
{
    if (ctx->kdf) {
        return perform_kdf(ctx->key_id, ctx->key_block, output, input);
    } else {
        return atcab_aes_encrypt(ctx->key_id, ctx->key_block, input, output);
    }

}

int mbedtls_internal_aes_decrypt( mbedtls_aes_context *ctx,
                          const unsigned char input[16],
                          unsigned char output[16] )
{
    if (ctx->kdf) {
        return perform_kdf(ctx->key_id, ctx->key_block, output, input);
    } else {
        return atcab_aes_decrypt(ctx->key_id, ctx->key_block, input, output);
    }
}

int mbedtls_aes_crypt_ecb( mbedtls_aes_context *ctx,
                           int mode,
                           const unsigned char input[16],
                           unsigned char output[16] )
{
    if( mode == MBEDTLS_AES_ENCRYPT ) {
        return mbedtls_internal_aes_encrypt( ctx, input, output );
    }

    return mbedtls_internal_aes_decrypt( ctx, input, output );
}

#ifdef MBEDTLS_CIPHER_MODE_CBC
int mbedtls_aes_crypt_cbc( mbedtls_aes_context *ctx,
                    int mode,
                    size_t length,
                    unsigned char iv[16],
                    const unsigned char *input,
                    unsigned char *output )
{
    return MBEDTLS_ERR_AES_FEATURE_UNAVAILABLE;
}
#endif /* MBEDTLS_CIPHER_MODE_CBC */

#endif /* MBEDTLS_AES_ALT */


#endif /* MBEDTLS_AES_C */
