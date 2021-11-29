#include "hblk_crypto.h"

/**
 * sha256 -  computes the hash of a sequence of bytes
 * @s: sequence of bytes to be hashed
 * @len: number of bytes to hash in s
 * @digest: resulting hash
 * Return: returns a pointer to digest or NULL on failure
 **/
uint8_t *sha256(int8_t const *s, size_t len,
		uint8_t digest[SHA256_DIGEST_LENGTH])
{
	if (!s || !digest)
		return (NULL);
	return (SHA256((const unsigned char *)s, len, digest));
}
