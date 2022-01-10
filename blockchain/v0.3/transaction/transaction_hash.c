#include "transaction.h"

/**
 * input_buffer - stores transaction input into arg
 * @node: transaction node to store
 * @idx: index of node
 * @arg: pointer to buffer to store bytes into
 * Return: returns 0 on success
 **/

int input_buffer(llist_node_t node, unsigned int idx, void *arg)
{

	memcpy((int8_t *)arg + idx * SHA256_DIGEST_LENGTH * 3, node,
						SHA256_DIGEST_LENGTH * 3);
	return (0);
}

/**
 * output_buffer - stores transaction output into arg
 * @node: transaction node to store
 * @idx: index of node
 * @arg: pointer to buffer to store bytes into
 * Return: returns 0 on success
 **/

int output_buffer(llist_node_t node, unsigned int idx, void *arg)
{

	memcpy((int8_t *)arg + idx * SHA256_DIGEST_LENGTH,
			((tx_out_t *)node)->hash, SHA256_DIGEST_LENGTH);
	return (0);
}

/**
 * transaction_hash - computes the ID (hash) of a transaction
 * @transaction:  points to the transaction to compute the hash of
 * @hash_buf: buffer in which to store the computed hash
 * Return: returns a pointer to hash_buf on success otherwise NULL
 **/

uint8_t *transaction_hash(transaction_t const *transaction,
			uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	int tx_input_size, tx_output_size;
	size_t len;
	int8_t *buff;

	if (!transaction || !hash_buf)
		return (NULL);

	tx_input_size = llist_size(transaction->inputs);
	tx_output_size = llist_size(transaction->outputs);
	len = SHA256_DIGEST_LENGTH * 3 * tx_input_size +
				SHA256_DIGEST_LENGTH * tx_output_size;
	buff = calloc(1, len);
	if (!buff)
		return (NULL);
	llist_for_each(transaction->inputs, input_buffer, buff);
	llist_for_each(transaction->outputs, output_buffer,
					buff + SHA256_DIGEST_LENGTH * 3 * tx_input_size);
	if (!sha256(buff, len, hash_buf))
	{
		free(buff);
		return (NULL);
	}
	free(buff);
	return (hash_buf);
}
