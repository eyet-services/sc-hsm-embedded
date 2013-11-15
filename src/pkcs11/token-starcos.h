/**
 * SmartCard-HSM PKCS#11 Module
 *
 * Copyright (c) 2013, CardContact Systems GmbH, Minden, Germany
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of CardContact Systems GmbH nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL CardContact Systems GmbH BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * @file    token-starcos.h
 * @author  Andreas Schwier
 * @brief   Token implementation for a Starcos 3.5 ID ECC C1 based card
 */

#ifndef ___TOKEN_STARCOS_H_INC___
#define ___TOKEN_STARCOS_H_INC___

#include <pkcs11/cryptoki.h>
#include <pkcs11/p11generic.h>
#include <pkcs11/bytestring.h>

#define STARCOS_ESIGN1          0
#define STARCOS_ESIGN2          1
#define STARCOS_EUSERPKI        2
#define STARCOS_DEFAULT         STARCOS_EUSERPKI


struct starcosApplication {
	char *name;
	struct bytestring_s aid;
	int aidId;
	unsigned char pinref;
	int qESKeyDRec;
	struct p15PrivateKeyDescription *privateKeys;
	size_t privateKeysLen;
	struct p15CertificateDescription *certs;
	size_t certsLen;
};

struct starcosPrivateData {
	struct starcosApplication   *application;
	int                         selectedApplication;
	unsigned char               *publickeys[256];
	void                        *mutex;
	unsigned char               sopin[8];
};

int encodeF2B(unsigned char *pin, int pinlen, unsigned char *f2b);
int createStarcosToken(struct p11Slot_t *slot, struct p11Token_t **token, struct p11TokenDriver *drv, struct starcosApplication *application);

#endif /* ___TOKEN_STARCOS_H_INC___ */