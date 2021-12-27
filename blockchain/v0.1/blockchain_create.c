#include "blockchain.h"

/**
 * genesis_block - creates genesis block
 * Return: returns pointer genesis block on success otherwise NULL
 **/

block_t *genesis_block(void)
{
	block_t *genesis = malloc(sizeof(*genesis));

	if (!genesis)
		return (NULL);

	genesis->info.index = 0;
	genesis->info.difficulty = 0;
	genesis->info.timestamp = 1537578000;
	genesis->info.nonce = 0;
	memcpy(genesis->data.buffer, "Holberton School", 16);
	genesis->data.len = 16;
	memcpy(genesis->hash,
		"c52c26c8b5461639635d8edf2a97d48d0c8e0009c817f2b1d3d7ff2f04515803",
			SHA256_DIGEST_LENGTH);
	return (genesis);

}

/**
 * blockchain_create - creates a blockchain structure
 * Return: returns pointer to blockchain on success otheriwse NULL
 *
 **/

blockchain_t *blockchain_create(void)
{
	blockchain_t *blockchain;
	block_t *genesis;

	blockchain = malloc(sizeof(*blockchain));
	if (!blockchain)
		return (NULL);
	genesis = genesis_block();
	if (!genesis)
	{
		free(blockchain);
		return (NULL);
	}
	blockchain->chain = llist_create(MT_SUPPORT_TRUE);
	if (!blockchain->chain)
	{
		free(blockchain);
		free(genesis);
		return (NULL);
	}
	if (llist_add_node(blockchain->chain, genesis, ADD_NODE_FRONT) == -1)
	{
		llist_destroy(blockchain->chain, 1, NULL);
		free(blockchain), free(genesis);
		return (NULL);
	}
	return (blockchain);
}
