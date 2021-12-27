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
		"\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03",
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
	blockchain_t *blockchain = NULL;
	block_t *genesis = NULL;

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
