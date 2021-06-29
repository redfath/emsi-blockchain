# inclure  " blockchain.h " 

/* * 
* swap_endianness - échanger l'endianness d'un bloc 
* @block : un bloc blockchain 
*/ 

void  swap_endianness ( block_t *block) 
{ 
	_swap_endian block- (& > info . index , sizeof (block-> info . index )); 
	_swap_endian bloc- (& > info . difficulté , sizeof (bloc-> info . difficulté )); 
	_swap_endian block- (& > info . timestamp , sizeof (block-> info . timestamp )); 
	_swap_endian block- (& > info . nonce , sizeof (block-> info . nonce )); 
} 

/* * 
* load_blocks - lit les blocs d'un fichier 
* @fp : pointeur de fichier 
* @swap_endian : un drapeau pour échanger le boutisme 
* @blockchain : blockchain 
* @size : nombre de blocs à lire 
* Retour : 0 en cas de succès, -1 en cas d'échec 
*/ 

int  load_blocks (FILE *fp, uint8_t swap_endian, 
				blockchain_t *blockchain, int taille ) 
{ 
	block_t *bloc; 
	uint32_t  data_len; 
	long  int genesis_size; 
	int je; 

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
			swap_endianness (bloc); 
bloc-> données . len = data_len; 
*(block-> data . buffer + data_len) = ' \0 ' ; 
		llist_add_node (blockchain-> chaîne , bloc, ADD_NODE_REAR); 
	} 
	retour ( 0 ); 
} 

/* * 
* blockchain_deserialize - charger la blockchain 
* @path : fichier à lire 
* Retour : blockchain chargée, NULL en cas d'échec 
*/ 

blockchain_t * blockchain_deserialize ( char  const * chemin) 
{ 
	header_t en- tête ; 
	blockchain_t * blockchain; 
	entière taille  ; 
	uint8_t swap_endian; 
FICHIER *fp = NULL ; 
	
	si (!chemin) 
		return ( NULL ); 
	if ( accès (chemin, R_OK) == - 1 ) 
		return ( NULL ); 
fp = fopen (chemin, " r " ); 
	si (!fp) 
		return ( NULL ); 
	fread (&header, sizeof (en-tête), 1 , fp); 
	if ( memcmp (header. hblk_magic , " HBLK " , 4 ) || 
		memcmp (en-tête. hblk_version , " 0.1 " , 3 )) 
		return ( fclose (fp), NULL ); 
blockchain = blockchain_create (); 
	si (!blockchain) 
		return ( fclose (fp), NULL ); 
swap_endian = _get_endianness () != en-tête. hblk_endian ; 
taille = en-tête. hblk_blocks ; 
	si (swap_endian) 
		_swap_endian (&size, sizeof (taille)); 
	if ( load_blocks (fp, swap_endian, blockchain, size) == - 1 ) 
		return ( blockchain_destroy (blockchain), fclose (fp), NULL ); 
	ffermer (fp); 
	retour (blockchain); 
} 
