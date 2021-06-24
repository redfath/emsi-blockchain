#include "blockchain.h"
/**
 * blockchain_difficulty - gives a potential difficulty.
 * @blockchain: the blockchain to analyze.
 * Return: the potential difficulty.
 */
uint32_t blockchain_difficulty(blockchain_t const *blockchain)
{
uint8_t block_index;
uint32_t elapsedTime, expectedElapsedTime;
block_t *tail_block = llist_get_tail(blockchain->chain), *last;
if (tail_block->info.index % DIFFICULTY_ADJUSTMENT_INTERVAL == 0
&& tail_block->info.index != 0)
{
block_index = llist_size(blockchain->chain) - DIFFICULTY_ADJUSTMENT_INTERVAL;
last = llist_get_node_at(blockchain->chain, block_index + 1);
expectedElapsedTime =
DIFFICULTY_ADJUSTMENT_INTERVAL *BLOCK_GENERATION_INTERVAL;
elapsedTime = tail_block->info.timestamp - last->info.timestamp;
if (elapsedTime < (expectedElapsedTime * 2))
return (last->info.difficulty + 1);
else if (elapsedTime > (expectedElapsedTime * 2))
return (last->info.difficulty - 1);
return (last->info.difficulty);
}
return (tail_block->info.difficulty);
}
