#include "blockchain.h"

/**
 * blockchain_difficulty - computes the difficulty to assign
 * to a potential next Block in the Blockchain.
 * @blockchain: points to the Blockchain to analyze
 * Return: return the difficulty to be assgned to potnetial next Block
 **/

uint32_t blockchain_difficulty(blockchain_t const *blockchain)
{
	block_t *tail, *last_block_adjust;
	uint64_t elapsed, expected;
	uint32_t last_adjust_index, diff;

	if (!blockchain)
		return (0);

	tail = llist_get_tail(blockchain->chain);
	if (!tail)
		return (0);

	last_adjust_index = llist_size(blockchain->chain) -
				DIFFICULTY_ADJUSTMENT_INTERVAL;
	last_block_adjust = llist_get_node_at(blockchain->chain,
						last_adjust_index);
	if (!last_block_adjust)
		return (0);
	elapsed = tail->info.timestamp - last_block_adjust->info.timestamp;
	expected = DIFFICULTY_ADJUSTMENT_INTERVAL * BLOCK_GENERATION_INTERVAL;
	diff = tail->info.difficulty;

	if (tail->info.index % DIFFICULTY_ADJUSTMENT_INTERVAL == 0 &&
						tail->info.index != 0)
	{
		if (elapsed * 2 < expected)
			diff++;
		else if (elapsed > expected * 2)
			diff = diff > 0 ? diff - 1 : 0;
	}
	return (diff);
}
