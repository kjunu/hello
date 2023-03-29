package cmd

import (
	"bytes"
	"crypto/subtle"
	"encoding/json"
	"fmt"
	"math/big"

	"github.com/ethereum/go-ethereum/common/hexutil"
	"github.com/ethereum/go-ethereum/core/types"
	"github.com/ethereum/go-ethereum/rlp"
	"github.com/prysmaticlabs/prysm/shared/bls/common"
	"github.com/spf13/cobra"
	blst "github.com/supranational/blst/bindings/go"
	"github.com/tyler-smith/go-bip32"
	"github.com/tyler-smith/go-bip39"
)

func init() {
	ethCmd.AddCommand(ethTxCmd)
	ethCmd.AddCommand(ethBlsCmd)
	ethCmd.AddCommand(ethMnemonicCmd)
	rootCmd.AddCommand(ethCmd)
}

var ethCmd = &cobra.Command{
	Use:   "eth",
	Short: "eth",
	Long:  `ethereum commands`,
}

var ethTxCmd = &cobra.Command{
	Use:   "tx",
	Short: "tx",
	Long:  `ethereum transaction`,
	Args:  cobra.MinimumNArgs(1),
	RunE:  ethTx,
}

var ethBlsCmd = &cobra.Command{
	Use:   "bls",
	Short: "bls",
	Long:  `ethereum bls sign`,
	Args:  cobra.MinimumNArgs(1),
	RunE:  ethBls,
}

var ethMnemonicCmd = &cobra.Command{
	Use:   "mnemonic",
	Short: "m",
	Long:  `bip39 nmemonic`,
	RunE:  ethMnemonic,
}

func ethMnemonic(cmd *cobra.Command, args []string) error {
	// Generate a mnemonic for memorization or user-friendly seeds
	entropy, err := bip39.NewEntropy(256)
	if err != nil {
		return err
	}
	mnemonic, err := bip39.NewMnemonic(entropy)
	if err != nil {
		return err
	}

	// Generate a Bip32 HD wallet for the mnemonic and a user supplied password
	seed := bip39.NewSeed(mnemonic, "Secret Passphrase")

	masterKey, _ := bip32.NewMasterKey(seed)
	publicKey := masterKey.PublicKey()
	//fmt.Println(bip39.GetWordList())
	// Display mnemonic and keys
	fmt.Println("Mnemonic: ", mnemonic)
	fmt.Println("Master private key: ", masterKey)
	fmt.Println("Master public key: ", publicKey)
	type mnmonicT struct {
		Words []string
	}
	v := &mnmonicT{
		Words: []string{"a", "b", "c"},
	}
	result, err := json.Marshal(v)
	fmt.Println(string(result), err)
	jsonStr := []byte(`{"Words":["e","f","g"], "NotUnmarshal": "test"}`)

	d := json.NewDecoder(bytes.NewReader(jsonStr))
	d.DisallowUnknownFields()
	err = d.Decode(v)
	fmt.Println("err:", err)

	err = json.Unmarshal(jsonStr, &v)
	fmt.Println(v, err)
	return nil
}

func ethTx(cmd *cobra.Command, args []string) error {
	for _, rlpEncoded := range args {
		//fmt.Println(rlpEncoded)
		tx := types.NewTx(&types.DynamicFeeTx{})
		err := rlp.DecodeBytes(hexutil.MustDecode(rlpEncoded), tx)
		if err != nil {
			return err
		}
		msg, err := tx.AsMessage(types.NewLondonSigner(tx.ChainId()), big.NewInt(0))
		if err != nil {
			return err
		}
		cmd.Println("sender", msg.From().Hex())
		cmd.Println("chainId", tx.ChainId())
		cmd.Println("type", tx.Type())
		cmd.Println("cost", tx.Cost())
		cmd.Println("nonce", tx.Nonce())
		cmd.Println("cost", tx.Cost())
		cmd.Println("gas", tx.Gas())
		cmd.Println("gasPirce", tx.GasPrice())
		cmd.Println("gasTipCap", tx.GasTipCap())
		cmd.Println("gasFeeCap", tx.GasFeeCap())
		cmd.Println("value", tx.Value())
		cmd.Println("to", tx.To().Hex())
		cmd.Println("hash", tx.Hash().Hex())
	}
	return nil
}

type bls12SecretKey struct {
	p *blst.SecretKey
}

func (s *bls12SecretKey) PublicKey() common.PublicKey {
	//return &PublicKey{p: new(blstPublicKey).From(s.p)}
	return nil
}

// IsZero checks if the secret key is a zero key.
func IsZero(sKey []byte) bool {
	b := byte(0)
	for _, s := range sKey {
		b |= s
	}
	return subtle.ConstantTimeByteEq(b, 0) == 1
}

// Sign a message using a secret key - in a beacon/validator client.
//
// In IETF draft BLS specification:
// Sign(SK, message) -> signature: a signing algorithm that generates
//      a deterministic signature given a secret key SK and a message.
//
// In Ethereum proof of stake specification:
// def Sign(SK: int, message: Bytes) -> BLSSignature
func (s *bls12SecretKey) Sign(msg []byte) common.Signature {
	return nil
}

// Marshal a secret key into a LittleEndian byte slice.
func (s *bls12SecretKey) Marshal() []byte {
	keyBytes := s.p.Serialize()
	return keyBytes
}
func ethBls(cmd *cobra.Command, args []string) error {
	privKey := []byte("12345678901234567890123456789012")
	//sk, err := bls..SecretKeyFromBytes(privKey)
	//if err != nil {
	//	return err
	//}
	sk := new(blst.SecretKey).Deserialize(privKey)
	wk := &bls12SecretKey{p: sk}
	cmd.Println("sk:", string(wk.Marshal()))
	cmd.Println("input:", args[0])
	//cmd.Println("signed:", hexutil.Encode(sk.Sign([]byte(args[0])).Marshal()))
	return nil
}
