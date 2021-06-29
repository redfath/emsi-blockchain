# inclure  " blockchain.h " 

# définit  CLEAN_UP (free(chain), close(fd)) 
# définit  CLEAN_UP_BLOCKS (free(block), llist_destroy(list, 1 , NULL )) 
# définit  CHECK_ENDIAN ( x ) (endianness ? SWAPENDIAN(x) : ( void ) 0 ) 
/* * 
* blockchain_deserialize - désérialise la blockchain à partir d'un fichier 
* @path : chemin d'accès au fichier blockchain sérialisé 
* Retour : pointeur vers blockchain désérialisé ou null 
 */ 
blockchain_t * blockchain_deserialize ( char  const * chemin) 
{ 
	int fd; 
	blockchain_t  *chain =  NULL ; 
	uint8_t  endianness; 
	char buf[ 4096 ] = { 0 }; 
	uint32_t taille  ; 

	si (!chemin) 
		return ( NULL ); 
fd = ouvert (chemin, O_RDONLY); 
	si (fd == - 1 ) 
		return ( NULL ); 
	if ( read (fd, buf, strlen (HBLK_MAGIC)) != strlen (HBLK_MAGIC) || 
		strcmp (buf, HBLK_MAGIC)) 
		return (CLEAN_UP, NULL ); 
buf[ strlen (HBLK_VERSION)] = 0 ; 
	if ( read (fd, buf, strlen (HBLK_VERSION)) != strlen (HBLK_VERSION) || 
		strcmp (buf, HBLK_VERSION)) 
		return (CLEAN_UP, NULL ); 
chaine = calloc ( 1 , sizeof (*chain)); 
	si (!chaîne) 
		return (CLEAN_UP, NULL ); 
	if ( read (fd, &endianness, 1 ) != 1 ) 
		return (CLEAN_UP, NULL ); 
endianness = endianness != _get_endianness (); 
	if ( read (fd, &size, 4 ) != 4 ) 
		return (CLEAN_UP, NULL ); 
	CHECK_ENDIAN (taille); 
chain-> chain = deserialize_blocks (fd, size, endianness); 
	si (!chaîne) 
		return (CLEAN_UP, NULL ); 
	return ( close (fd), chaine); 
} 

/* * 
* deserialize_blocks - désérialise tous les blocs du fichier 
* @fd : ​​ouvrir fd pour enregistrer le fichier 
* @size : nombre de blocs dans le fichier 
* @endianness : si endianess a besoin de changer 
* Retour : pointeur vers la liste des blocs ou NULL 
 */ 
llist_t * deserialize_blocks ( int fd, uint32_t taille, uint8_t endianness) 
{ 
	block_t *bloc; 
	llist_t *list = llist_create (MT_SUPPORT_TRUE); 
	uint32_t  i =  0 ; 

	si (!liste) 
		return ( NULL ); 
	pour (i = 0 ; i < taille ; i++) 
	{ 
block = calloc ( 1 , sizeof (*block)); 
		si (!bloc) 
			return (CLEAN_UP_BLOCKS, NULL ); 
		if ( read (fd, &(block-> info ), sizeof (block-> info )) != sizeof (block-> info )) 
			return (CLEAN_UP_BLOCKS, NULL ); 
		CHECK_ENDIAN bloc- ( > info . index ); 
		CHECK_ENDIAN bloc- ( > info . difficulté ); 
		CHECK_ENDIAN bloc- ( > info . timestamp ); 
		CHECK_ENDIAN bloc- ( > info . nonce ); 
		si ( lire (fd, & ( séquencés> données . len ), 4 )! = 4 ) 
			return (CLEAN_UP_BLOCKS, NULL ); 
		CHECK_ENDIAN bloc- ( > données . len ); 
		if ( read (fd, block-> data . buffer , block-> data . len ) != block-> data . len ) 
			return (CLEAN_UP_BLOCKS, NULL ); 
		if ( read (fd, block-> hash , SHA256_DIGEST_LENGTH) != 
SHA256_DIGEST_LENGTH) 
			return (CLEAN_UP_BLOCKS, NULL ); 
		if ( llist_add_node (liste, bloc, ADD_NODE_REAR)) 
			return (CLEAN_UP_BLOCKS, NULL ); 
	} 
	retour (liste); 
} 
