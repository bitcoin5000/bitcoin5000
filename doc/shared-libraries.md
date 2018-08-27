Shared Libraries
================

## bitcoin5000consensus

The purpose of this library is to make the verification functionality that is critical to Bitcoin5000's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `bitcoin5000consensus.h` located in  `src/script/bitcoin5000consensus.h`.

#### Version

`bitcoin5000consensus_version` returns an `unsigned int` with the API version *(currently at an experimental `0`)*.

#### Script Validation

`bitcoin5000consensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `bitcoin5000consensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `bitcoin5000consensus_SCRIPT_FLAGS_VERIFY_NONE`
- `bitcoin5000consensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/bitcoin5000/bips/blob/master/bip-0016.mediawiki)) subscripts
- `bitcoin5000consensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/bitcoin5000/bips/blob/master/bip-0066.mediawiki)) compliance
- `bitcoin5000consensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY` - Enforce NULLDUMMY ([BIP147](https://github.com/bitcoin5000/bips/blob/master/bip-0147.mediawiki))
- `bitcoin5000consensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY` - Enable CHECKLOCKTIMEVERIFY ([BIP65](https://github.com/bitcoin5000/bips/blob/master/bip-0065.mediawiki))
- `bitcoin5000consensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY` - Enable CHECKSEQUENCEVERIFY ([BIP112](https://github.com/bitcoin5000/bips/blob/master/bip-0112.mediawiki))
- `bitcoin5000consensus_SCRIPT_FLAGS_VERIFY_WITNESS` - Enable WITNESS ([BIP141](https://github.com/bitcoin5000/bips/blob/master/bip-0141.mediawiki))

##### Errors
- `bitcoin5000consensus_ERR_OK` - No errors with input parameters *(see the return value of `bitcoin5000consensus_verify_script` for the verification status)*
- `bitcoin5000consensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `bitcoin5000consensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `bitcoin5000consensus_ERR_DESERIALIZE` - An error deserializing `txTo`
- `bitcoin5000consensus_ERR_AMOUNT_REQUIRED` - Input amount is required if WITNESS is used

### Example Implementations
- [NBitcoin5000](https://github.com/NicolasDorier/NBitcoin5000/blob/master/NBitcoin5000/Script.cs#L814) (.NET Bindings)
- [node-libbitcoin5000consensus](https://github.com/bitpay/node-libbitcoin5000consensus) (Node.js Bindings)
- [java-libbitcoin5000consensus](https://github.com/dexX7/java-libbitcoin5000consensus) (Java Bindings)
- [bitcoin5000consensus-php](https://github.com/Bit-Wasp/bitcoin5000consensus-php) (PHP Bindings)
