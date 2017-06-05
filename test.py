COIN = 100 * 1000 * 1000
MAX_MONEY = 84000000 * COIN


nSubsidyHalvingInterval = MAX_MONEY / (100 * COIN)
print nSubsidyHalvingInterval
nSubsidy = 50 * COIN
nHeight = 0
total = 0
while nSubsidy != 0:
    nSubsidy = 50 * COIN
    nSubsidy >>= nHeight / nSubsidyHalvingInterval
    nHeight += 1
    total += nSubsidy

print total / float(COIN)
print MAX_MONEY / float(COIN)


### DUCATUS

COIN = 100 * 1000 * 1000
MAX_MONEY = 7778742049  * COIN


nSubsidyHalvingInterval = MAX_MONEY / (100 * COIN)
print nSubsidyHalvingInterval
nSubsidy = 50 * COIN
nHeight = 0
total = 0
while nSubsidy != 0:
    nSubsidy = 50 * COIN
    nSubsidy >>= nHeight / nSubsidyHalvingInterval
    nHeight += 1
    total += nSubsidy

print total / float(COIN)
print MAX_MONEY / float(COIN)
