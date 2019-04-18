// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2015-2017 The ALQO developers
// Copyright (c) 2018 The ZARCASH developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>


using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"
#include "test/bignum.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
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
	(0, uint256("0x000006401f2c8c99028f6ad458d737c48c26b0440c99ca86e3daa4207623b165"))
        (1, uint256("0x000001e51faf70c6593e02db76173e734c7a8d8fa94ddd35ea30999a8d9ca0c3"))
	(2, uint256("0x000001c116688ede2fc603a7b7192e8f51aa3b8d6e3a335a789776a68b2d3e6d"))
	(3, uint256("0x0000069ee24c16cf55bfdaf4e292c0f2d3af342532761dee043d1f3490c47241"))
	(4, uint256("0x00000b30c6c7218b292330e4071dac5bd0c346d4abe066cf46d8701ab92a1298"))
	(5, uint256("0x000004f5a0d9699fdf83df7946e179e1dd4d841bc5347bda375080c47e41ac7a"))
	(6, uint256("0x00000c90132b8e423115abe92f403609527db557a3110a7e8016a63b03dabb4d"))
	(7, uint256("0x00000158644392c5eec183775ab13fafd66f1823b4989bf4db06c98edc4c1036"))
	(8, uint256("0x000000cc151620849fcd992147095b7efff641341cf3da65de532e2ebfa9b2fd"))
	(9, uint256("0x00000ea7c42f0028c864d31557f4b23e1d64d06db1bba1736e6f834998ded9f9"))
	(10, uint256("0x00000da2fc7c01ce0097796f6987763799d81de2a5b1b0a1a83c897e5f9a5c08"))
	(11, uint256("0x000000eafdf1ca984d7ea1f34102778b02a40d0d2b28d86555b2fea516138a3f"))
	(12, uint256("0x000002776b72ccaedc901770079751d0604109af891f7e11b2fcba04a88e9d47"))
	(13, uint256("0x000000fe8712c00771b420f229d4622055360858bfe4a77676d2b5ca2349ae3b"))
	(14, uint256("0x000006145c395185b3f55fe864eaf5fcb3913348172708346395792459fb9290"))
	(15, uint256("0x00000787555c2658b815524b901c10d5aaa2ece5370383f793e22a45320202ea"))
	(1000, uint256("0x000000000005b8c4f36ceaeafac53bb847daa232a7a0f7ea9828c8d9cdb3e04f"))
	(2000, uint256("0x000000000004bf85c0521379afb20e67fee1e3deadc681b6e7e581c649d375cf"))
	(3000, uint256("0x000000000001c4f2e8b41e11ec7d0059e28bd1f166f4b7017bbdd31cdde52d7a"))
	(4000, uint256("0x00000000000b6f576e5a50ae408aa53a2897ad9e212efb63aac777cb034b3eca"))
	(5000, uint256("0x00000000000147e28a7dc74e5b10ca2439396ddc31adf0ad13c2c632fd0edef7"))
	(6000, uint256("0x00000000000093c13f82684422508d7d40db4c16755c178edf212f9b394f1bc3"))
	(7000, uint256("0x0000000000021a7044e06e5cccaca5e4c291ba23f613938dc486b80fbcd4e12d"))
	(8000, uint256("0x0000000000155d652ea011bfd2d4c98b1f43cb6b3e1410b535c8c3444d41efba"))
	(8400, uint256("0x00000000000962ea55764ef5a6db6752f8ee89993cab78c48b66afe486a424f8")) 
	(9000, uint256("0x0000000000059271314d4d8fa5b18a28c801fe979f5d27c401f919d2a0399197"))
 	(9500, uint256("0x000000000001f72066c61bb17e52df9898f989c7eb9e0efe2a8c231412a077f2"))
	(10000, uint256("0x0000000000020981866020916e42eb2f8ec62579d53357d1014ecdc3522ae171"))
	(10500, uint256("0x000000000008535058f42111ee4a54af8834cec4d324fd0c1cc71c938a78d358"))
	(11000, uint256("0x000000000009a359b15f275cc706170de2b57248e11cd0c6809e4e3c24a13298"))
	(11500, uint256("0x00000000000729d202f6664180e93db1c072196c06ea8dc53bf11fe0a054f265"))
	(12000, uint256("0x00000000000bade780d61380311b01042cf2cf61bc4f160fcc5a96064b038e65"))
	(12500, uint256("0x00000000001418559e2ae6c68c1ad5bfe0e2dd65ea6ada9d98fab757e85feb28"))
	(13000, uint256("0x000000000003b7d5ccad187a01bdcfd1d7644a471e41594a5bd444ad94b936ec"))
	(13200, uint256("0x000000000f85f75705640dba7af4a071d992795ee7611d4d2694a8d1114ef5d7")) ;


	
        
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1553367420, // * UNIX timestamp of last checkpoint block
    0,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    750        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x0"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1553367419,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x0"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1553367419,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xaa;
        pchMessageStart[1] = 0xab;
        pchMessageStart[2] = 0x35;
        pchMessageStart[3] = 0x27;
        vAlertPubKey = ParseHex("04e9e460859546e1018f555aec03a9e84aca0934ef22677528e424d0ed17173e97b5e2a0e9ed66729c5484b334adf7d5a05d15fddf0a825c25088efa136e740e45");
        nDefaultPort = 40444;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // ZARCASH starting difficulty is 1 / 2^12  //20
        nSubsidyHalvingInterval = 500000; // ZARCASH - Halving  every 500000
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // ZARCASH: 1 day
        nTargetSpacing = 1.5 * 60;  // ZARCASH: 90 Sec Block 
        nLastPOWBlock = 15200; //Test longterm effect with trade margin issue with all currencies-LONG LIVE MINERS 
        nMaturity = 90; // Maturity to block 
        nMasternodeCountDrift = 20;
	nMasternodeColleteralLimxDev = 5000000; //Params().MasternodeColleteralLimxDev()  Para
        nModifierUpdateBlock = 1; // we use the version 2 for dmd
        nMaxMoneyOut = 2946796875 * COIN;

        const char* pszTimestamp = "This is genesis block for Zarcash network 20190322 Relaunch";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04e9e460859546e1018f555aec03a9e84aca0934ef22677528e424d0ed17173e97b5e2a0e9ed66729c5484b334adf7d5a05d15fddf0a825c25088efa136e740e45") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1553367420;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 5688368;



        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000006401f2c8c99028f6ad458d737c48c26b0440c99ca86e3daa4207623b165"));
        assert(genesis.hashMerkleRoot == uint256("0x1fba8dfabca6f444063c3739ed0b21ce31085468b219dfc79d22c1070daa1252"));

        vSeeds.push_back(CDNSSeedData("seed1.zarbitcoin.net","51.75.162.95"));             // seed 1
        vSeeds.push_back(CDNSSeedData("seed2.zarbitcoin.net","51.75.162.92"));             // seed 2
        vSeeds.push_back(CDNSSeedData("seed3.zarbitcoin.net","51.75.170.189"));             // seed 3
	vSeeds.push_back(CDNSSeedData("seed5.zarbitcoin.net","51.38.71.12"));             // seed 5
        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 80); //Prefix Zarcash Z
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 83); //Prefix Zarcash a
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);//Prefix Zarcash A
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x01)(0x1D)(0x22)(0x34).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x03)(0x22)(0x21)(0x1B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 109 	0x8000006d
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x40)(0x10)(0x00)(0x67).convert_to_container<std::vector<unsigned char> >();

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
        strSporkKey = "04cd66b21f8273bf8c6ddd2b97fe5f830271637ceb82bc6269b010fef7090aa05657b78178f3605c11abd8567dbca949012e864a5132b355dcfa4d33346eaeee1f";
        strDarksendPoolDummyAddress = "ZJNjrGEVYg1LwoLKgsBpZaquXa1KtRaurr";
        nStartMasternodePayments = 1524781746; //11/10/2017 @ 12:00am (UTC)
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x34;
        pchMessageStart[1] = 0x44;
        pchMessageStart[2] = 0x75;
        pchMessageStart[3] = 0x14;
        vAlertPubKey = ParseHex("043c47d222b60d18aa2f7dc790fb9486fdeb48c8ec82ba92484080ac2c0ccd9475e2d0d5cb8015fbb9bef36514c64337a9bf6bd1fba7842ffe0e699a7f991aa1be");
        nDefaultPort = 55600;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // ZARCASH: 1 day
        nTargetSpacing = 1.5 * 60;  // ZARCASH: 2 minute
        nLastPOWBlock = 262800;
        nMaturity = 15;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 100000000 * COIN;

        genesis.nTime = 1553367419;
        genesis.nNonce = 5688368;

 
      




        hashGenesisBlock = genesis.GetHash();
     //   assert(hashGenesisBlock == uint256("0x000000b8099430a4804c27719187e997438f4bbff044633ee7a6897c2919f692"));

        vFixedSeeds.clear();
        vSeeds.clear();
	
	//vSeeds.push_back(CDNSSeedData("160.119.102.145", "51.38.71.12")); //SEEDERS1 

		
	base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 84);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 195);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0xb2)(0x21)(0x14)(0x11).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x42)(0x31)(0x59)(0x21).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x42)(0x22)(0x13)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));


        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "049e53e687fdafd78fd42d730fad0e7ea1819396176a2cb85d7a76fa4559cdbd2c2f05330a6f5cbadb44a6c1d324f167e679e9f3e95d9d5649761a3e7f59bf4500";
        strDarksendPoolDummyAddress = "bADWWVV4XPDfe6xNB7vrd9oGqNAFcrtqd8";
        nStartMasternodePayments = 1562531573;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x14;
        pchMessageStart[1] = 0x54;
        pchMessageStart[2] = 0x95;
        pchMessageStart[3] = 0x64;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // ZARCASH: 1 day
        nTargetSpacing = 1 * 60;        // ZARCASH: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1509321603;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 129915;
		
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 43444;
//        assert(hashGenesisBlock == uint256("0x00000fea76c2e8523777b3dce649c363b4c5e0234605cae551f8d822d17fcc16"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
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

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
