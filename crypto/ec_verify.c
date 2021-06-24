#include "hblk_crypto.h"
/**
 * ec_verify - Verifies a given set of bytes, using a given EC_KEY private key
 * @key: EC key pair already generated
 * @msg: hash
 * @msglen: length of the hash
 * @sig: the signature to be verified
 * Return: 1 if sucess, 0 if failure
 */
int ec_verify(EC_KEY const *key, uint8_t const *msg, size_t msglen,
sig_t const *sig)
{
unsigned char hash[SHA256_DIGEST_LENGTH];
if (!key || !msg || !sig || !(sig->len) || !msglen || !ECDSA_verify(0,
hash, SHA256_DIGEST_LENGTH, msg, msglen, (EC_KEY *)key))
return (0);
return (1);
}
