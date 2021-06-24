#include "hblk_crypto.h"

/**
 * ec_to_pub - convert ec key to public key
 * @key: pointer to ec key
 * @pub: where we stock public key
 * Return: public key or NULL
 */

uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
const EC_POINT *point;
const EC_GROUP *group;
if (!key || !pub)
return (NULL);
point = EC_KEY_get0_public_key(key);
group = EC_KEY_get0_group(key);
if (EC_POINT_point2oct(group, point, POINT_CONVERSION_UNCOMPRESSED, pub,
EC_PUB_LEN, NULL))
return (pub);
return (NULL);
}
