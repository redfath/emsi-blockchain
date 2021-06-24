#include "hblk_crypto.h"
/*
 * - @ec_load : returns the key or NULL
 **/
EC_KEY *ec_load(char const *folder)
{
EC_KEY *key = NULL;
char buf[500];
FILE *fp;
sprintf(buf, "%s/%s", folder, PUB_FILENAME);
fp = fopen(buf, "r");
if (!fp || !folder)
return (NULL);
if (!PEM_read_EC_PUBKEY(fp, &key, NULL, NULL))
return (NULL);
sprintf(buf, "%s/%s", folder, PRI_FILENAME);
fp = fopen(buf, "r");
if (!fp || !PEM_read_ECPrivateKey(fp, &key, NULL, NULL))
return (NULL);
fclose(fp);
return (key);
}
