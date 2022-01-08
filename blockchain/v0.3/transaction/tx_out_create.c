#include "transaction.h"

/**
 * tx_out_create - allocates and initializes a transaction output structure
 * @amount: the amount of the transaction
 * @pub: the public key of the transaction receiver
 * Return: returns a pointer to the created transaction
 * output upon success, or NULL upon failure
 **/
tx_out_t *tx_out_create(uint32_t amount,
			uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *out;

	out = calloc(1, sizeof(*out));
	if (!out)
		return (NULL);

	out->amount = amount;
	memcpy(out->pub, pub, EC_PUB_LEN);
	if (!sha256((int8_t const *)out, sizeof(out->amount) + sizeof(out->pub),
								out->hash))
	{
		free(out);
		return (NULL);
	}
	return (out);
}
