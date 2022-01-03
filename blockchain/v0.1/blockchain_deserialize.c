#include "blockchain.h"

/**
 * blockchain_deserialize - deserializes a Blockchain from a file
 * @path: contains the path to a file to load the Blockchain from
 * Return: returns a pointer to the deserialized Blockchain upon success,
 * or NULL upon failure
 **/
blockchain_t *blockchain_deserialize(char const *path)
{
	FILE *fp;
	blockchain_t *blockchain;
	block_t *block;
	header_t header;
	size_t genesis;
	int i;
	uint8_t endianness;

	if (!path)
		return (NULL);

	endianness = _get_endianness();

	fp = fopen(path, "r");
	if (!fp)
		return (NULL);
	fread(&header, sizeof(header), 1, fp);
	if (endianness != header.hblk_endian)
		_swap_endian(&header.hblk_blocks,
				sizeof(header.hblk_blocks));
	blockchain = blockchain_create();
	if (!blockchain)
	{
		fclose(fp);
		return (NULL);
	}
	genesis = sizeof(block->info) + sizeof(block->hash) + 20;
	fseek(fp, genesis, SEEK_CUR);
	for (i = 0; i < header.hblk_blocks - 1; i++)
	{
		block = malloc(sizeof(*block));
		if (!block)
		{
			blockchain_destroy(blockchain);
			fclose(fp);
			return (NULL);
		}
		fread(&block->info, sizeof(block->info), 1, fp);
		fread(&block->data.len, sizeof(block->data.len), 1, fp);
		fread(&block->data, sizeof(block->data), 1, fp);
		fread(&block->hash, sizeof(block->hash), 1, fp);
		if (endianness != header.hblk_endian)
		{
			_swap_endian((void *)&block->info.index,
					sizeof(block->info.index));
			_swap_endian((void *)&block->info.difficulty,
					sizeof(block->info.difficulty));
			_swap_endian((void *)&block->info.timestamp,
					sizeof(block->info.timestamp));
			_swap_endian((void *)&block->info.nonce,
					sizeof(block->info.nonce));
			_swap_endian((void *)&block->data.len,
					sizeof(block->data.len));
		}
		*(block->data.buffer + block->data.len) = '\0';
		llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
	}
	fclose(fp);
	return (blockchain);
}
