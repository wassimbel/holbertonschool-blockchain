#include "hblk_crypto.h"

/**
 * ec_from_pub -  creates an EC_KEY structure given a public key
 * @pub: contains the public key to be converted
 * Return: a pointer to the created EC_KEY structure upon success,
 * or NULL upon failure
 **/

EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *key;
	EC_POINT *p;
	EC_GROUP *group;

	key = EC_KEY_new_by_curve_name(EC_CURVE);
	if (!key)
		return (NULL);
	group = EC_GROUP_new_by_curve_name(EC_CURVE);
	if (!group)
		return (NULL);
	p = EC_POINT_new(group);
	if (!p)
	{
		EC_GROUP_free(group);
		return (NULL);
	}
	if (!EC_POINT_oct2point(group, p, pub, EC_PUB_LEN, NULL))
		return (NULL);
	if (!EC_KEY_set_public_key(key, p))
	{
		EC_POINT_free(p);
		EC_GROUP_free(group);
		return (NULL);
	}
	EC_POINT_free(p);
	EC_GROUP_free(group);
	return (key);
}
