#include "blockchain.h"

/**
 * swap_endian - swap endianness
 * @block: address of the block
 **/

void swap_endian(block_t *block)
{
	_swap_endian((void *)&block->info.index,
				sizeof(block->info.index));
	_swap_endian((void *)&block->info.difficulty,
				sizeof(block->info.difficulty));
	_swap_endian((void *)&block->info.timestamp,
				sizeof(block->info.timestamp));
	_swap_endian((void *)&block->info.nonce,
				sizeof(block->info.nonce));
}
/**
 * read_block - reads a block from a file to struct
 * @blockchain: address of the blockchain
 * @fp: file descriptor
 * @endianness: endianness
 * @size: nunber of blocks
 * Return: retruns 0 on success otherwise -1
 **/
int read_block(blockchain_t *blockchain, FILE *fp,
			uint8_t endianness, int size)
{
	block_t *block;
	long int genesis;
	uint32_t len;
	int i;

	genesis = sizeof(block->info) + sizeof(block->hash) + 20L;
	fseek(fp, genesis, SEEK_CUR);
	for (i = 0; i < size - 1; i++)
	{
		block = malloc(sizeof(*block));
		if (!block)
			return (-1);
		fread(&block->info, sizeof(block->info), 1, fp);
		fread(&len, sizeof(len), 1, fp);
		if (endianness)
			_swap_endian(&len, sizeof(len));
		fread(&block->data.buffer, len + 1, 1, fp);
		fread(&block->hash, SHA256_DIGEST_LENGTH, 1, fp);
		if (endianness)
			swap_endian(block);
		block->data.len = len;
		llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
	}
	return (0);
}
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
	header_t header;
	int size;
	uint8_t endianness;

	if (!path)
		return (NULL);

	if (access(path, R_OK) == -1)
		return (NULL);

	fp = fopen(path, "r");

	if (!fp)
		return (NULL);

	fread(&header, sizeof(header), 1, fp);
	blockchain = blockchain_create();
	if (!blockchain)
	{
		fclose(fp);
		return (NULL);
	}
	endianness = _get_endianness() != header.hblk_endian;
	size = header.hblk_blocks;
	if (endianness)
		_swap_endian(&size, sizeof(size));
	if (read_block(blockchain, fp, endianness, size) == -1)
	{
		blockchain_destroy(blockchain);
		fclose(fp);
		return (NULL);
	}
	fclose(fp);
	return (blockchain);
}
