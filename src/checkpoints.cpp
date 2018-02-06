// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double fSigcheckVerificationFactor = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        ( 0,     uint256("0x00000b9cf0b9bb2437283f28d378e5f9644c643f25e1c80b2cd9fdd6510d33f1"))
		(500,    uint256("0x0000000042cefd7b9607c5a0dc7d3ebcf73bb0896aa865a2fc8a9033bdb6dd70"))
		(5000,   uint256("0x00000000243e05144f99dc1423b0d5c46d70f3a1d6e26f2bcbe8af2a721f4dfa"))
		(25000,  uint256("0x000000002f5a52feedae716155b5ad39adbbc21c992f7a3d25f784792fc0f2df"))
		(50000,  uint256("0x00000000b8b1c548e51ef353dadca194e9713d1f0571724727980d06a7f8add7"))
		(75000,  uint256("0x00000000e015163b83ccd8795343144c73cf863535fcfca519fff716f03b5776"))
		(150000, uint256("0x00000000fc7a9bba0a37c20cc3a842a815cdc68e4840880c0e0868671349da73"))
		(200001, uint256("0x00000000731f067486bd41c9fa06100fe7c09047924cd0b83b3f94049985f468"))
		(205000, uint256("0x000000009ca55a4b7919bdbf5f642b19cecf811c6611130d4bda4d492b00e827"))
		(225000, uint256("0x0000000046338f49b9ac921674351c8eaae211411352a8f1f68c55007e657de3"))
		(255000, uint256("0x00000000ab81e659bf706d7462a3cad386fba3017111005f14aff5f3fd53b9c9"))
		(265000, uint256("0x000000002ae1022e5f10d60fb9b13bb77fb657046c23102178bd7edbaf76d3a9"))
		(310000, uint256("0x000000010e58ab78a6d23ec1ec4ec3e941adabba8c29cf1370ceabeecbb38f17"))
        ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1403337306, // * UNIX timestamp of last checkpoint block
        310000,     // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        2880.0      // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet = 
        boost::assign::map_list_of
        ( 0, uint256("0x00000e5e37c42d6b67d0934399adfb0fa48b59138abb1a8842c88f4ca3d4ec96"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1373481000,
        0,
        2880.0
    };

    const CCheckpointData &Checkpoints() {
        if (fTestNet)
            return dataTestnet;
        else
            return data;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (!GetBoolArg("-checkpoints", true))
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
//        return hash == i->second;
//REMOVE
      return true;

    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex) {
        if (pindex==NULL)
            return 0.0;

        int64 nNow = time(NULL);

        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (!GetBoolArg("-checkpoints", true))
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

//        return checkpoints.rbegin()->first;
//REMOVE
      return 0;


    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (!GetBoolArg("-checkpoints", true))
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
//                return t->second;
//REMOVE
            return NULL;
        }
        return NULL;
    }
}
