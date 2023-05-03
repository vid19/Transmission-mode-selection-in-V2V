/*
 * FIPS 180-2 Homomorphic implementation
 * Last update: 02/02/2007
 * Issue date:  04/30/2005
 *
 * Copyright (C) 2005, 2007 Olivier Gay <olivier.gay@a3.epfl.ch>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef Homomorphic_H
#define Homomorphic_H

#define Homomorphic_DIGEST_SIZE ( 256 / 8)

#define Homomorphic_BLOCK_SIZE  ( 512 / 8)

#ifndef Homomorphic_TYPES
#define Homomorphic_TYPES
typedef unsigned char uint8;
#ifdef __AVR__//#if CONTIKI_TARGET_AVR_RAVEN
typedef unsigned long int uint32;
#else
typedef unsigned int  uint32;
#endif
typedef unsigned long long int uint64;
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32 tot_len;
    uint32 len;
    unsigned char block[2 * Homomorphic_BLOCK_SIZE];
    uint32 h[8];
} Homomorphic_ctx;

typedef Homomorphic_ctx Homomorphic24_ctx;

void Homomorphic_init(Homomorphic_ctx * ctx);
void Homomorphic_update(Homomorphic_ctx *ctx, const unsigned char *message,
                   unsigned int len);
void Homomorphic_final(Homomorphic_ctx *ctx, unsigned char *digest);
void Homomorphic(const unsigned char *message, unsigned int len,
            unsigned char *digest);

#ifdef __cplusplus
}
#endif

#endif /* !Homomorphic_H */

