#include "transaction.h"

/**
 * unspent_tx_out_create - allocates and initializes an unspent
 * transaction output structure
 * @block_hash: contains the hash of the Block
 * where the referenced transaction output is located
 * @tx_id: contains the hash of a transaction in the Block block_hash
 * @out: points to the referenced transaction output
 * Return: returns a pointer to the created unspent transaction
 * output upon success, or NULL upon failure
 **/
unspent_tx_out_t *unspent_tx_out_create(
					uint8_t block_hash[SHA256_DIGEST_LENGTH],
					uint8_t tx_id[SHA256_DIGEST_LENGTH],
					tx_out_t const *out)
{
	unspent_tx_out_t *unspent_out;

	unspent_out = calloc(1, sizeof(*unspent_out));
	if (!unspent_out)
		return (NULL);

	memcpy(unspent_out->block_hash, block_hash, SHA256_DIGEST_LENGTH);
	memcpy(unspent_out->tx_id, tx_id, SHA256_DIGEST_LENGTH);
	memcpy(&(unspent_out->out), out, sizeof(*out));
	return (unspent_out);
}
