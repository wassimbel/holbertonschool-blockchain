#include "hblk_crypto.h"

/**
 * ec_save - saves an existing EC key pair on the disk
 * @key: pointer to EC key pair to be saved on disk
 * @folder: path to the folder in which to save the keys
 * Return: returns 1 on success, 0 on failure
 **/
int ec_save(EC_KEY *key, char const *folder)
{
	FILE *fp;
	struct stat sb;
	int ret;
	char file[512] = {0};

	if (!key || !folder)
		return (0);
	if (stat(folder, &sb) == -1)
	{
		ret = mkdir(folder, 700);
		if (ret == -1)
			return (0);
	}
	sprintf(file, "%s/%s", folder, PRI_FILENAME);
	fp = fopen(file, "w");
	if (!fp)
		return (0);
	if (!PEM_write_ECPrivateKey(fp, key, NULL, NULL, 0, NULL, NULL))
		return (0);
	fclose(fp);

	sprintf(file, "%s/%s", folder, PUB_FILENAME);
	fp = fopen(file, "w");
	if (!fp)
		return (0);
	if (!PEM_write_EC_PUBKEY(fp, key))
		return (0);
	fclose(fp);
	return (1);
}
