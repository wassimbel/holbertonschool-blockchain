#include "blockchain.h"

/**
 * block_is_valid - verifies that a Block is valid
 * @block: points to block to check
 * @prev_block: points to the previous block in the blockchain
 * Return: returns 0 on success, -1 otherwise
 **/

int block_is_valid(block_t const *block, block_t const *prev_block)
{
	block_t const genesis = GENESIS;
	uint8_t prev_hash[SHA256_DIGEST_LENGTH] = {0};
	uint8_t block_hash256[SHA256_DIGEST_LENGTH] = {0};

	if (!block || (!prev_block && block->info.index != 0))
		return (-1);
	if (block->info.index == 0)
		return (memcmp(block, &genesis, sizeof(genesis)));
	if (block->info.index != prev_block->info.index + 1)
		return (-1);
	if (!block_hash(prev_block, prev_hash) ||
		memcmp(prev_block->hash, prev_hash, SHA256_DIGEST_LENGTH))
		return (-1);
	if (!block_hash(block, block_hash256) ||
		memcmp(block->hash, block_hash256, SHA256_DIGEST_LENGTH) ||
		memcmp(block->info.prev_hash, prev_hash, SHA256_DIGEST_LENGTH))
		return (-1);
	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (-1);
	return (0);
}
