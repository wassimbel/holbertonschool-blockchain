#include "hblk_crypto.h"

/**
 * ec_verify - verifies the signature of a given set of bytes,
 * using a given EC_KEY public key
 * @key: points to the EC_KEY structure
 * @msg: points to the msglen characters to verify the signature of
 * @msglen: msg length
 * @sig:  points to the signature to be checked
 * Return: 1 if signature is valid, 0 otherwise
 **/

int ec_verify(EC_KEY const *key, uint8_t const *msg,
		size_t msglen, sig_t const *sig)
{
	if (!key || !msg || !sig)
		return (0);

	if (ECDSA_verify(0, msg, (int)msglen, sig->sig,
				sig->len, (EC_KEY *)key) < 1)
		return (0);
	return (1);
}
