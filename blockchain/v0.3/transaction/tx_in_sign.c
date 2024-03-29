#include "transaction.h"

/**
 * identify_transaction_out_hash - identifies a node
 * @node: Pointer to the node to identify
 * @hash: hash to compare
 * Return: returns 1 if node identified otherwise 0
 **/
int identify_transaction_out_hash(llist_node_t node, void *hash)
{
	if (memcmp(((unspent_tx_out_t *)node)->out.hash, hash,
					SHA256_DIGEST_LENGTH) != 0)
		return (0);
	return (1);
}

/**
 * tx_in_sign -  signs a transaction input, given the transaction id it is from
 * @in: points to the transaction input structure to sign
 * @tx_id:  contains the ID (hash) of the transaction
 * the transaction input to sign is stored in
 * @sender: contains the private key of the receiver of the coins
 * contained in the transaction output referenced by the transaction input
 * @all_unspent: list of all unspent transaction outputs to date
 * Return:  return a pointer to the resulting signature structure upon success,
 * or NULL upon failure
 **/

sig_t *tx_in_sign(tx_in_t *in, uint8_t const tx_id[SHA256_DIGEST_LENGTH],
			EC_KEY const *sender, llist_t *all_unspent)
{
	unspent_tx_out_t *unspent;
	uint8_t pub[EC_PUB_LEN];

	if (!in || !tx_id || !sender || !all_unspent)
		return (NULL);
	ec_to_pub(sender, pub);
	unspent = llist_find_node(all_unspent,
			identify_transaction_out_hash, in->tx_out_hash);
	if (!unspent)
		return (NULL);
	if (memcmp(pub, unspent->out.pub, EC_PUB_LEN) != 0)
		return (NULL);
	if (!ec_sign(sender, tx_id, SHA256_DIGEST_LENGTH, &(in->sig)))
		return (NULL);
	return (&(in->sig));
}
