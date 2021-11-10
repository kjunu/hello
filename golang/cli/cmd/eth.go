package cmd

import (
	"fmt"

	"github.com/ethereum/go-ethereum/common/hexutil"
	"github.com/ethereum/go-ethereum/core/types"
	"github.com/ethereum/go-ethereum/rlp"
	"github.com/prysmaticlabs/prysm/shared/bls"
	"github.com/spf13/cobra"
)

func init() {
	ethCmd.AddCommand(ethTxCmd)
	ethCmd.AddCommand(ethBlsCmd)
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

func ethTx(cmd *cobra.Command, args []string) error {
	for _, rlpEncoded := range args {
		//fmt.Println(rlpEncoded)
		tx := types.NewTx(&types.DynamicFeeTx{})
		err := rlp.DecodeBytes(hexutil.MustDecode(rlpEncoded), tx)
		if err != nil {
			return err
		}
		cmd.Println("chainId", tx.ChainId())
		cmd.Println("type", tx.Type())
		cmd.Println("cost", tx.Cost())
		cmd.Println("gas", tx.Gas())
		cmd.Println("gasPirce", tx.GasPrice())
		cmd.Println("gasTipCap", tx.GasTipCap())
		cmd.Println("gasFeeCap", tx.GasFeeCap())
		cmd.Println("value", tx.Value())
		cmd.Println("to", tx.To().Hex())

		fmt.Printf("%+v\n", tx)
	}
	return nil
}

func ethBls(cmd *cobra.Command, args []string) error {
	seed := []byte("12345678901234567890123456789012")
	sk, err := bls.SecretKeyFromBytes(seed)
	if err != nil {
		return err
	}
	cmd.Println("sk:", string(sk.Marshal()))
	cmd.Println("input:", args[0])
	cmd.Println("signed:", hexutil.Encode(sk.Sign([]byte(args[0])).Marshal()))
	return nil
}
