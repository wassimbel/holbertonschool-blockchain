#include "hblk_crypto.h"

/**
 * ec_load - loads an existing EC key pair from the disk
 * @folder: path to the folder from which to load the keys
 * Return: returns apointer to the EC key pair on success, NULL on failure
 **/
EC_KEY *ec_load(char const *folder)
{
	EC_KEY *key;
	FILE *fp;
	struct stat sb;
	char file[512] = {0};

	if (!folder)
		return (NULL);
	if (stat(folder, &sb) == -1)
		return (NULL);

	sprintf(file, "%s/%s", folder, PRI_FILENAME);
	fp = fopen(file, "r");
	if (!fp)
		return (NULL);
	if (!PEM_read_ECPrivateKey(fp, &key, NULL, NULL))
		return (NULL);
	fclose(fp);

	sprintf(file, "%s/%s", folder, PUB_FILENAME);
	fp = fopen(file, "r");
	if (!fp)
		return (NULL);
	if (!PEM_read_EC_PUBKEY(fp, &key, NULL, NULL))
		return (NULL);
	fclose(fp);
	return (key);
}
