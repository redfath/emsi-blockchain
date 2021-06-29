# inclure  " blockchain.h " 

/* * 
* convert_endianness - Convertir les données d'un bloc 
* @block : bloc à convertir 
 */ 
void  convert_endianness ( block_t *block) 
{ 
_swap_endian block- (& > info . index , sizeof (block-> info . index )); 
_swap_endian bloc- (& > info . difficulté , sizeof (bloc-> info . difficulté )); 
_swap_endian block- (& > info . timestamp , sizeof (block-> info . timestamp )); 
_swap_endian block- (& > info . nonce , sizeof (block-> info . nonce )); 
} 
/* * 
* read_blocks - désérialise la blockchain du fichier 
* @fp : fichier qui contient les données blockchain 
* @swap_endian : pointeur vers les données à convertir 
* @blockchain : la blockchain qui contiendra la blockchain 
* @size : la taille de la blockchain 
* Retour : pointeur vers blockchain désérialisé ou null 
 */ 
int  read_blocks (FILE *fp, uint8_t swap_endian, 
		blockchain_t *blockchain, int taille ) 
{ 
int je; 
block_t *bloc; 
uint32_t  data_len; 
long  int genesis_size; 
genesis_size = sizeof (block-> info ) + sizeof (block-> hash ) + 20L ; 
fseek (fp, genesis_size, SEEK_CUR); 
pour (i = 0 ; i < taille - 1 ; ++i) 
{ 
block = malloc ( sizeof (*block)); 
si (!bloc) 
retour (- 1 ); 
fread (&block-> info , sizeof (block-> info ), 1 , fp); 
fread (&data_len, sizeof (data_len), 1 , fp); 
si (swap_endian) 
_swap_endian (&data_len, sizeof (data_len)); 
fread (&block-> data . buffer , data_len, 1 , fp); 
fread (&block-> hash , SHA256_DIGEST_LENGTH, 1 , fp); 
si (swap_endian) 
convert_endianness (bloc); 
bloc-> données . len = data_len; 
*(block-> data . buffer + data_len) = ' \0 ' ; 
llist_add_node (blockchain-> chaîne , bloc, ADD_NODE_REAR); 
} 
retour ( 0 ); 
} 

/* * 
* blockchain_deserialize - désérialise la blockchain à partir d'un fichier 
* @path : chemin d'accès au fichier blockchain sérialisé 
* Retour : pointeur vers blockchain désérialisé ou null 
 */ 
blockchain_t * blockchain_deserialize ( char  const * chemin) 
{ 
FICHIER *fp; 
uint8_t hblk_magic[ 4 ]; 
uint8_t  hblk_version[ 3 ]; 
uint8_t  hblk_endian; 
int32_t hblk_blocks ; 
blockchain_t * blockchain; 
entière taille  ; 
uint8_t swap_endian; 
si (!chemin) 
return ( NULL ); 
fp = fopen (chemin, " r " ); 
si (!fp) 
return ( NULL ); 
fread (&hblk_magic, sizeof (hblk_magic), 1 , fp); 
fread (&hblk_version, sizeof (hblk_version), 1 , fp); 
fread (&hblk_endian, sizeof (hblk_endian), 1 , fp); 
fread (&hblk_blocks, sizeof (hblk_blocks), 1 , fp); 
if ( memcmp (hblk_magic, " HBLK " , 4 ) || 
memcmp (version_hblk, " 0.1 " , 3 )) 
return ( fclose (fp), NULL ); 
blockchain = blockchain_create (); 
si (!blockchain) 
return ( fclose (fp), NULL ); 
swap_endian = _get_endianness () != hblk_endian; 
taille = hblk_blocks ; 
si (swap_endian) 
_swap_endian (&size, sizeof (taille)); 
if ( read_blocks (fp, swap_endian, blockchain, size) == - 1 ) 
return ( blockchain_destroy (blockchain), fclose (fp), NULL ); 
ffermer (fp); 
retour (blockchain); 
} 
