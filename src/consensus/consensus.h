// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN5000_CONSENSUS_CONSENSUS_H
#define BITCOIN5000_CONSENSUS_CONSENSUS_H

#include <stdint.h>
#include <stdlib.h>
#include <string>

#include "uint256.h"

// To deal dynamically with the fork, we introduce a new structure called a
// conforksus (consensus | fork), with two instances: the base and fork
// version. The former uses Bitcoin5000 parameters, but if this fork is a fork
// of a fork, it should use the first fork values (no effort went into
// forking of a fork into a secondary fork, e.g. via nested list conforksus
// objects).

/** The maximum allowed size for a serialized block, in bytes (only for buffer
 * size limits) */
extern unsigned int MAX_BLOCK_SERIALIZED_SIZE;
/** The maximum allowed weight for a block, see BIP 141 (network rule) */
extern unsigned int MAX_BLOCK_WEIGHT;
/** The maximum allowed number of signature check operations in a block (network
 * rule) */
extern int64_t MAX_BLOCK_SIGOPS_COST;
/** Coinbase transaction outputs can only be spent after this number of new
 * blocks (network rule) */
extern int COINBASE_MATURITY;
/** Fork block number */
extern int FORK_BLOCK;
/** Whether fork should occur or not (-disablefork sets to false) */
extern bool FORK_ALLOWED;
/** Select the height that comes first - fork or the given height */
#define select_activation_height(height)                                       \
  (height > FORK_BLOCK ? 1 + FORK_BLOCK + (!FORK_BLOCK) : height)

/** Fork hash */
extern std::string FORK_HASH;
extern uint256 FORK_HASH_UINT256;

extern const int WITNESS_SCALE_FACTOR;

extern const size_t MIN_TRANSACTION_WEIGHT; // 60 is the lower bound for the
                                            // size of a valid serialized
                                            // CTransaction
extern const size_t MIN_SERIALIZABLE_TRANSACTION_WEIGHT; // 10 is the lower
                                                         // bound for the size
                                                         // of a serialized
                                                         // CTransaction

/** Flags for nSequence and nLockTime locks */
enum {
  /* Interpret sequence numbers as relative lock-time constraints. */
  LOCKTIME_VERIFY_SEQUENCE = (1 << 0),

  /* Use GetMedianTimePast() instead of nTime for end point timestamp. */
  LOCKTIME_MEDIAN_TIME_PAST = (1 << 1),
};

extern struct Conforksus base_conforksus;

struct Conforksus {
  unsigned int C_MAX_BLOCK_SERIALIZED_SIZE;
  unsigned int C_MAX_BLOCK_WEIGHT;
  int C_COINBASE_MATURITY;
  int64_t pow_target_spacing;
  int64_t pow_target_timespan;
  bool active;
  Conforksus(unsigned int mbss, unsigned int mbw, int cm, int64_t pts,
             int64_t ptt)
      : C_MAX_BLOCK_SERIALIZED_SIZE(mbss), C_MAX_BLOCK_WEIGHT(mbw),
        C_COINBASE_MATURITY(cm), pow_target_spacing(pts),
        pow_target_timespan(ptt), active(false) {}

  void enable() {
    active = true;
    MAX_BLOCK_SERIALIZED_SIZE = C_MAX_BLOCK_SERIALIZED_SIZE;
    MAX_BLOCK_WEIGHT = C_MAX_BLOCK_WEIGHT;
    COINBASE_MATURITY = C_COINBASE_MATURITY;
  }

  void elbane() {
    active = false;
    base_conforksus.enable();
  }
};

extern Conforksus fork_conforksus, base_conforksus;

void conforksus_init(int current_height, bool is_regtest);
void conforksus_block_tip_changed(int height);
void conforksus_will_validate_at_height(int height);

#endif // BITCOIN5000_CONSENSUS_CONSENSUS_H
