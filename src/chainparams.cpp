// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The Dinero developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include <stdio.h> //
#include <assert.h>
#include <boost/assign/list_of.hpp>
using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};
#include "chainparamsseeds.h"
/**
 * Main network
 */
//! Convert the pnSeeds6 array into usable address objects.

static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count) {
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof (ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}
//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (0, uint256("0x00000fce7c04cd554a8116fc888f0d52c93ee3d61989b5940c351f6c64a160df"))
        (1, uint256("0x00000148139cad930de1d25b60249adf50d54e48f5da4b5a9223bdda2b9395eb"))
       (20, uint256("0x00000a620f0cacce535f5c08b9be5ed8b0bcaa348629b95eb56ddee55aeed4ca"))
       (85, uint256("0x000009ca1ce8026b12cad9d01aa7a0b36363ee416194475f3e7096f7934ac4ed"))
      (275, uint256("0x000001062cf5c44101f54c4c0d54bd032e9aead7f298f42c00dd208f0f14df0e"))
      (710, uint256("0x000000006fa702329c7420d7c5c516b524d9e0056d177152a6f519fd1ac3d59c"))
     (1440, uint256("0x000000000c888ba2eb7ce7efa46eb6f260f88b71a83b81ee904b0b1d1c7eb770"))
     (2435, uint256("0x0000000007fadbf658294bd83d6254f73af0207ab4881ac34f8c5d76a22a8c74"))
    (18293, uint256("0x000000003e1b755cda6940588ea4849a85bcabbdad960ee942b299f4a2383a2e"))
    (43201, uint256("0x000000000d9a4d836f16e0436aa23fc5cc0d80ff6392987cadda86ffcf111a1a"))
    (71752, uint256("0x0000000006cad6d5e094674a8b75ef0aa995c48d6023731e5de8c3fb2c22e500"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1515067692, // * UNIX timestamp of last checkpoint block
    100000, // * total number of transactions between genesis and last checkpoint
    //   (the tx=... number in the SetBestChain debug.log lines)
    2000 // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet = boost::assign::map_list_of
        (0, uint256("0x00000fce7c04cd554a8116fc888f0d52c93ee3d61989b5940c351f6c64a160df")); // =
// boost::assign::map_list_of(0, uint256("0x001"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1510533000,
    0,
    250
};
static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1510533000,
    0,
    100
};

class CMainParams : public CChainParams {
public:

    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x10;
        pchMessageStart[1] = 0x32;
        pchMessageStart[2] = 0x10;
        pchMessageStart[3] = 0xba;
        vAlertPubKey = ParseHex("047c906a23495711127dd92f059eb360bdb9f9c5d390ab5b25e9f9c5effc91e01327649533bf6a114033a36772b7a84b6beecd45cd423f79d23fbf3b6aaca3f41d");
        nDefaultPort = 11923;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Dinero starting difficulty is 1 / 2^12 = ~uint256(0) >> 15; // Dinero starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Dinero: 1 minute
        nTargetSpacing = 1 * 60; // Dinero: 1 minute
        nLastPOWBlock = 259200;
        nMaturity = 80;
        nModifierUpdateBlock = 1;
        const char* pszTimestamp = "Dinero 13112017";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*) pszTimestamp, (const unsigned char*) pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0481db387b05e19bc8d0c52b4ec97d7b8d82df30a7438a54bdda1f602d835875aefb9cc1c0f28314f97ec48eaac22d4debae5bb787b0bc92078e417dabc7f73a31") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1510533000;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 920691;
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000fce7c04cd554a8116fc888f0d52c93ee3d61989b5940c351f6c64a160df"));
        assert(genesis.hashMerkleRoot == uint256("0xc09b0e5aa184ff1370e44e5995c38542ee29647e5e4995b9207c5f817e1f7ebc"));

        vSeeds.push_back(CDNSSeedData("nanu.ddns.net", "nanu.ddns.net"));
        vSeeds.push_back(CDNSSeedData("nanu1.ddns.net", "nanu1.ddns.net"));
        vSeeds.push_back(CDNSSeedData("nanu2.ddns.net", "nanu2.ddns.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 53);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 43);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 202);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x6e)(0x61)(0x6e)(0x75).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x6f)(0x62)(0x6f)(0x76).convert_to_container<std::vector<unsigned char> >();
        //  BIP44 coin type is 'TBD'
        //base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x13)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;
        nPoolMaxTransactions = 3;
        strSporkKey = "04571d88b23974d67c65f3a28429a088a825d63a9cec8bd991a8447f756a9bed8986453c75c0699a645eec0bb00daad9b218e0477693fc3d2529ee2ab43ad66e5d";
        strObfuscationPoolDummyAddress = "NgH8d3ACoEdbPbHoL4TVAndyAP4iwwRMiR";
        nStartMasternodePayments = 1403728576; //Wed, 25 Jun 2014 20:36:16 GMT
    }

    const Checkpoints::CCheckpointData& Checkpoints() const {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:

    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        vAlertPubKey = ParseHex("041481e13291ee18568f3b19c7b5704d760004d55bca3c1212bed3c96952ab3674f7b2a80d513da3a76ba01668b529f19864ae4edd0c28bfd569fdae72ebd483db");
        nDefaultPort = 21923;
        bnProofOfWorkLimit = ~uint256(0) >> 15;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Dinero: 1 day
        nTargetSpacing = 1 * 60; // Dinero: 1 minute
        nLastPOWBlock = 12000;
        nMaturity = 10;
        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1510533000;
        genesis.nNonce = 920691;
        hashGenesisBlock = genesis.GetHash();

        //assert(hashGenesisBlock == uint256("0x00000fce7c04cd554a8116fc888f0d52c93ee3d61989b5940c351f6c64a160df"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("nanu.ddns.net", "nanu.ddns.net"));
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet dinero addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19); // Testnet dinero script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239); // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet dinero BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet dinero BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet dinero BIP44 coin type is '1' (All coin's testnet default)
        //base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
        nPoolMaxTransactions = 2;
        strSporkKey = "04a1ef0833644b51f0481773870e6a70e253fb41564bd2ccdfffaa378cd897caf40b134a35bcf7fadbb39af16e0883012484c0f7f8fa308027e9b84e1803a6b483";
        strObfuscationPoolDummyAddress = "xzAdcHiP3R8GMoLhGAdbgaFMDzsTJuyuEj";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
    }

    const Checkpoints::CCheckpointData& Checkpoints() const {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:

    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nSubsidyHalvingInterval = 150;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Dinero: 1 day
        nTargetSpacing = 1 * 60; // Dinero: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1454124731;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 12345;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 31923;
        //assert(hashGenesisBlock == uint256("0x"));
        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear(); //! Testnet mode doesn't have any DNS seeds.
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:

    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 41923;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear(); //! Unit test mode doesn't have any DNS seeds.
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }
    //! Published setters to allow changing values in unit test cases

    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) {
        nSubsidyHalvingInterval = anSubsidyHalvingInterval;
    }

    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) {
        fDefaultConsistencyChecks = afDefaultConsistencyChecks;
    }

    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {
        fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks;
    }

    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) {
        fSkipProofOfWorkCheck = afSkipProofOfWorkCheck;
    }
};
static CUnitTestParams unitTestParams;
static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams() {
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine() {
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;
    SelectParams(network);
    return true;
}