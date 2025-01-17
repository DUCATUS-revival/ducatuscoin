// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"
#include "arith_uint256.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "bc1c914c79e3612d5569d3b980e089edb016536e26f54791f3001206456da0d1";

    //const char* pszTimestamp = "NY Times 05/Oct/2011 Steve Jobs, Apple’s Visionary, Dies at 56";
    const CScript genesisOutputScript = CScript() << ParseHex("040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
	consensus.nSubsidyHalvingInterval = 77787420;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 710000;
        consensus.BIP34Hash = uint256S("fa09d204a83a768ed5a7c8d441fa62f2043abf420cff1226c7b4329aeb9d51cf");
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 1 * 1 * 16 * 60; // 16 minutes
        consensus.nPowTargetSpacing = 1 * 60; // 1 minute
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 12; // 75% of 12
        consensus.nMinerConfirmationWindow = 16; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1485561600; // January 28, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517356801; // January 31st, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1485561600; // January 28, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1517356801; // January 31st, 2018

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000005c13f99f6d0b1a908");


			// The best chain should have at least this much work.
			consensus.nMinimumChainWork = uint256S("0x00");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xeb;
        pchMessageStart[1] = 0xd0;
        pchMessageStart[2] = 0xc6;
        pchMessageStart[3] = 0xdc;
        nDefaultPort = 9691;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1483501153, 1, 0x207fffff, 1, 50 * COIN); 
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xc05fc63e3800e1067bc03af8874bdbc14d610ec0e9b6de8835d07366a8e5a403"));
        assert(genesis.hashMerkleRoot == uint256S("0x814de9ca2dce68ecbb8d4a71d96a1dd2d5b668dcc256b11e97fd22e95c061249"));

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.push_back(CDNSSeedData("ducatusdns.com", "dnsseed.ducatusdns.com", true));
        vSeeds.push_back(CDNSSeedData("ducatus.io", "dnsseed.ducatus.io"));
        vSeeds.push_back(CDNSSeedData("ducatus.io", "dnsseed1.ducatus.io", true));
        vSeeds.push_back(CDNSSeedData("ducatus.io", "dnsseed2.ducatus.io", false));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,49);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,6);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,51);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,177);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
			vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
			//vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

	//checkpointData = (CCheckpointData) {
	//	boost::assign::map_list_of
	//		(  1500, uint256S("0x841a2965955dd288cfa707a755d05a54e45f8bd476835ec9af4402a2b59a2967"))
	//		(  4032, uint256S("0x9ce90e427198fc0ef05e5905ce3503725b80e26afd35a987965fd7e3d9cf0846"))
	//		(  8064, uint256S("0xeb984353fc5190f210651f150c40b8a4bab9eeeff0b729fcb3987da694430d70"))
	//		( 16128, uint256S("0x602edf1859b7f9a6af809f1d9b0e6cb66fdc1d4d9dcd7a4bec03e12a1ccd153d"))
	//		( 23420, uint256S("0xd80fdf9ca81afd0bd2b2a90ac3a9fe547da58f2530ec874e978fce0b5101b507"))
	//		( 50000, uint256S("0x69dc37eb029b68f075a5012dcc0419c127672adb4f3a32882b2b3e71d07a20a6"))
	//		( 80000, uint256S("0x4fcb7c02f676a300503f49c764a89955a8f920b46a8cbecb4867182ecdb2e90a"))
	//		(120000, uint256S("0xbd9d26924f05f6daa7f0155f32828ec89e8e29cee9e7121b026a7a3552ac6131"))
	//		(161500, uint256S("0xdbe89880474f4bb4f75c227c77ba1cdc024991123b28b8418dbbf7798471ff43"))
	//		(179620, uint256S("0x2ad9c65c990ac00426d18e446e0fd7be2ffa69e9a7dcb28358a50b2b78b9f709"))
	//		(240000, uint256S("0x7140d1c4b4c2157ca217ee7636f24c9c73db39c4590c4e6eab2e3ea1555088aa"))
	//		(383640, uint256S("0x2b6809f094a9215bafc65eb3f110a35127a34be94b7d0590a096c3f126c6f364"))
	//		(409004, uint256S("0x487518d663d9f1fa08611d9395ad74d982b667fbdc0e77e9cf39b4f1355908a3"))
	//		(456000, uint256S("0xbf34f71cc6366cd487930d06be22f897e34ca6a40501ac7d401be32456372004"))
	//		(638902, uint256S("0x15238656e8ec63d28de29a8c75fcf3a5819afc953dcd9cc45cecc53baec74f38"))
	//		(721000, uint256S("0x198a7b4de1df9478e2463bd99d75b714eab235a2e63e741641dc8a759a9840e5")),
	//		1422681363, // * UNIX timestamp of last checkpoint block
	//		5502192,   // * total number of transactions between genesis and last checkpoint
	//		//   (the tx=... number in the SetBestChain debug.log lines)
	//		5500.0     // * estimated number of transactions per day after checkpoint
	//};
	checkpointData = (CCheckpointData){
		boost::assign::map_list_of
			( 0, uint256S("0xc05fc63e3800e1067bc03af8874bdbc14d610ec0e9b6de8835d07366a8e5a403")),
			0,
			0,
			0
	};

    }
};
static CMainParams mainParams;

/**
 * Testnet (v4)
 */
class CTestNetParams : public CChainParams {
	public:
		CTestNetParams() {
			strNetworkID = "test";
		consensus.nSubsidyHalvingInterval = 77787420;
			consensus.nMajorityEnforceBlockUpgrade = 750;
			consensus.nMajorityRejectBlockOutdated = 950;
			consensus.nMajorityWindow = 1000;
			consensus.BIP34Height = 710000;
			consensus.BIP34Hash = uint256S("fa09d204a83a768ed5a7c8d441fa62f2043abf420cff1226c7b4329aeb9d51cf");
			consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
			consensus.nPowTargetTimespan = 1 * 1 * 16 * 60; // 16 minutes
			consensus.nPowTargetSpacing = 1 * 30; // 1 minute
			consensus.fPowAllowMinDifficultyBlocks = true;
			consensus.fPowNoRetargeting = true;
			consensus.nRuleChangeActivationThreshold = 12; // 75% of 12
			consensus.nMinerConfirmationWindow = 60; // nPowTargetTimespan / nPowTargetSpacing
			
			// consensus.nPowTargetTimespan = 1 * 1 * 16 * 60; // 16 minutes
			// consensus.nPowTargetSpacing = 1 * 1; // 1 minute
			// consensus.fPowAllowMinDifficultyBlocks = true;
			// consensus.fPowNoRetargeting = true;
			// consensus.nRuleChangeActivationThreshold = 12; // 75% of 16
			// consensus.nMinerConfirmationWindow = 60; // nPowTargetTimespan / nPowA
			consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
			consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
			consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

			// Deployment of BIP68, BIP112, and BIP113.
			consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
			consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1485561600; // January 28, 2017
			consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517356801; // January 31st, 2018

			// Deployment of SegWit (BIP141, BIP143, and BIP147)
			consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
			consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1485561600; // January 28, 2017
			consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1517356801; // January 31st, 2018

			// The best chain should have at least this much work.
			consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000005c13f99f6d0b1a908");


				// The best chain should have at least this much work.
				consensus.nMinimumChainWork = uint256S("0x00");

			pchMessageStart[0] = 0xed;
			pchMessageStart[1] = 0xe2;
			pchMessageStart[2] = 0xd8;
			pchMessageStart[3] = 0xf2;
			nDefaultPort = 19692;
			nPruneAfterHeight = 1000;

			 //static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
			genesis = CreateGenesisBlock(1635635297, 471905, 0x1e0ffff0, 1, 50 * COIN); 
			// consensus.hashGenesisBlock = genesis.GetPoWHash();
			consensus.hashGenesisBlock = genesis.GetHash();
			std::cout << "hash: " << genesis.GetHash().ToString().c_str() << "\n";
			std::cout << "pow hash: " << genesis.GetPoWHash().ToString().c_str() << "\n";

/*
			// calculate Genesis Block
			// Reset genesis
			consensus.hashGenesisBlock = uint256S("0x000003ed28b873bd23bd63b7fd806300851f304e3162fd16cdbb816ff510cb15");
			std::cout << std::string("Begin calculating Mainnet Genesis Block:\n");
			if (true && (genesis.GetPoWHash() != consensus.hashGenesisBlock)) {
				LogPrintf("Calculating Testnet Genesis Block:\n");
				arith_uint256 hashTarget = arith_uint256().SetCompact(genesis.nBits);
				uint256 hash;
				genesis.nNonce = 0;
				// This will figure out a valid hash and Nonce if you're
				// creating a different genesis block:
				// uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
				// hashTarget.SetCompact(genesis.nBits, &fNegative, &fOverflow).getuint256();
				// while (genesis.GetHash() > hashTarget)
				while (UintToArith256(genesis.GetPoWHash()) > hashTarget)
				{
					++genesis.nNonce;
					if (genesis.nNonce == 0)
					{
						LogPrintf("NONCE WRAPPED, incrementing time");
						std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
						++genesis.nTime;
					}
					if (genesis.nNonce % 10000 == 0)
					{
						LogPrintf("Testnet: nonce %08u: pow hash = %s \n", genesis.nNonce, genesis.GetPoWHash().ToString().c_str());
						// std::cout << strNetworkID << " nonce: " << genesis.nNonce << " time: " << genesis.nTime << " hash: " << genesis.GetHash().ToString().c_str() << "\n";
					}
				}
				std::cout << "Testnet ---\n";
				std::cout << "  nonce: " << genesis.nNonce <<  "\n";
				std::cout << "   time: " << genesis.nTime << "\n";
				std::cout << "   hash: " << genesis.GetHash().ToString().c_str() << "\n";
				std::cout << "   PoW hash: " << genesis.GetPoWHash().ToString().c_str() << "\n";
				std::cout << "   merklehash: "  << genesis.hashMerkleRoot.ToString().c_str() << "\n";
				// Testnet --- nonce: 296277 time: 1390095618 hash: 000000bdd771b14e5a031806292305e563956ce2584278de414d9965f6ab54b0
			}
			std::cout << std::string("Finished calculating Testnet Genesis Block:\n");

*/	

			assert(consensus.hashGenesisBlock == uint256S("0x480a02392a0b1bb075a5abe021030e67450900e6bca4f11201f4049d697173b5"));
			assert(genesis.hashMerkleRoot == uint256S("0x814de9ca2dce68ecbb8d4a71d96a1dd2d5b668dcc256b11e97fd22e95c061249"));


			// nodes with support for servicebits filtering should be at the top
			//vSeeds.push_back(CDNSSeedData("tools.com", "testnet-seed.tools.com"));
			//vSeeds.push_back(CDNSSeedData("loshan.co.uk", "seed-b..loshan.co.uk", true));
			//vSeeds.push_back(CDNSSeedData("thrasher.io", "dnsseed-testnet.thrasher.io", true));

			base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,112);
			base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,197);
			base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,59);
			base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,240);
			base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
			base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

			vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));
			vFixedSeeds.clear();
			vSeeds.clear();

			fMiningRequiresPeers = false;
			fDefaultConsistencyChecks = false;
			fRequireStandard = false;
			fMineBlocksOnDemand = true;
			fTestnetToBeDeprecatedFieldRPC = true;


			checkpointData = (CCheckpointData) {
				boost::assign::map_list_of
					( 0, uint256S("0x480a02392a0b1bb075a5abe021030e67450900e6bca4f11201f4049d697173b5")),
					0,
					0
			};

		}
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
	public:
		CRegTestParams() {
			strNetworkID = "regtest";
			consensus.nSubsidyHalvingInterval = 150;
			consensus.nMajorityEnforceBlockUpgrade = 750;
			consensus.nMajorityRejectBlockOutdated = 950;
			consensus.nMajorityWindow = 1000;
			consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
			consensus.BIP34Hash = uint256();
			consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
			consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // two weeks
			consensus.nPowTargetSpacing = 2.5 * 60;
			consensus.fPowAllowMinDifficultyBlocks = true;
			consensus.fPowNoRetargeting = true;
			consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
			consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
			consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
			consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
			consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
			consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
			consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
			consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
			consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
			consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
			consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;

			// The best chain should have at least this much work.
			consensus.nMinimumChainWork = uint256S("0x00");

			pchMessageStart[0] = 0xfa;
			pchMessageStart[1] = 0xbf;
			pchMessageStart[2] = 0xb5;
			pchMessageStart[3] = 0xda;
			nDefaultPort = 19444;
			nPruneAfterHeight = 1000;

			genesis = CreateGenesisBlock(1296688602, 0, 0x207fffff, 1, 50 * COIN);
			consensus.hashGenesisBlock = genesis.GetHash();
			//assert(consensus.hashGenesisBlock == uint256S("0xb083dd15b59955281e1edfe902d811d9437bfd41af1e9db9c5b1627e939e263f"));
			//assert(genesis.hashMerkleRoot == uint256S("0x76eb9308373c704cbd64f78e42be0c5dbf2b5b5d45be43207171d28f2823f91d"));

			vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
			vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

			fMiningRequiresPeers = false;
			fDefaultConsistencyChecks = true;
			fRequireStandard = false;
			fMineBlocksOnDemand = true; 
			fTestnetToBeDeprecatedFieldRPC = false;

			checkpointData = (CCheckpointData){
				boost::assign::map_list_of
					( 0, uint256S("0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206")),
					0,
					0,
					0
			};

			base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
			base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
			base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,58);
			base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
			base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
			base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
		}

		void UpdateBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
		{
			consensus.vDeployments[d].nStartTime = nStartTime;
			consensus.vDeployments[d].nTimeout = nTimeout;
		}
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
	assert(pCurrentParams);
	return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
	if (chain == CBaseChainParams::MAIN)
		return mainParams;
	else if (chain == CBaseChainParams::TESTNET)
		return testNetParams;
	else if (chain == CBaseChainParams::REGTEST)
		return regTestParams;
	else
		throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
	SelectBaseParams(network);
	pCurrentParams = &Params(network);
}

void UpdateRegtestBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
	regTestParams.UpdateBIP9Parameters(d, nStartTime, nTimeout);
}

