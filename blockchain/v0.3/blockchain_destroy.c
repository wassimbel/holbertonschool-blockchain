#include "blockchain.h"

/**
 * blockchain_destroy - deletes an existing Blockchain,
 * along with all the Blocks it contains
 * @blockchain: points to the Blockchain structure to delete
 **/

void blockchain_destroy(blockchain_t *blockchain)
{
	if (!blockchain)
		return;
	llist_destroy(blockchain->chain, 1, (void (*)(llist_node_t))block_destroy);
	llist_destroy(blockchain->unspent, 1, NULL);
	free(blockchain);
}
