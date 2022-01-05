#include "blockchain.h"

/**
 * hash_matches_difficulty - checks a given hash matches a given difficulty
 * @hash: the hash to check
 * @difficulty: the min difficulty the hash should match
 * Return: returns 1 if the difficulty is respected otherwise 0
 **/
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
					uint32_t difficulty)
{
	int i;
	uint32_t diff = 0;
	uint8_t *p = (uint8_t *)hash;

	if (!hash)
		return (0);
	for (; p < hash + SHA256_DIGEST_LENGTH; p++)
	{
		for (i = 7; i >= 0; i--)
		{
			if ((*p >> i) & 1)
			{
				if (diff == difficulty)
					return (1);
				return (0);
			}
			diff++;
		}
	}
	if (diff != difficulty)
		return (0);
	return (1);
}
