#include "hblk_crypto.h"
/**
 * ec_to_pub - extracts the public key from an EC_KEY opaque structure
 * @key: pointer to the EC_KEY structure
 * @pub: the address at which to store the extracted public key
 * Return: returns a pointer to pub or NULL on failure
 **/

uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	const EC_POINT *pub_key = NULL;
	const EC_GROUP *group = NULL;

	if (!key || !pub)
		return (NULL);
	pub_key = EC_KEY_get0_public_key(key);
	if (!pub_key)
		return (NULL);
	group = EC_KEY_get0_group(key);
	if (!group)
		return (NULL);
	if (!EC_POINT_point2oct(group, pub_key, POINT_CONVERSION_UNCOMPRESSED,
						pub, EC_PUB_LEN, NULL))
		return (NULL);
	return (pub);
}
