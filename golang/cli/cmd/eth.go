package cmd

import (
	"fmt"

	"github.com/ethereum/go-ethereum/common/hexutil"
	"github.com/ethereum/go-ethereum/core/types"
	"github.com/ethereum/go-ethereum/rlp"
	"github.com/spf13/cobra"
)

func init() {
	ethCmd.AddCommand(ethTxCmd)
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

func ethTx(cmd *cobra.Command, args []string) error {
	for _, rlpEncoded := range args {
		//fmt.Println(rlpEncoded)
		tx := types.NewTx(&types.LegacyTx{})
		err := rlp.DecodeBytes(hexutil.MustDecode(rlpEncoded), tx)
		if err != nil {
			return err
		}
		fmt.Println("chainId", tx.ChainId())
		fmt.Println("type", tx.Type())
		fmt.Println("cost", tx.Cost())
		fmt.Println("gas", tx.Gas())
		fmt.Println("value", tx.Value())
		fmt.Println("to", tx.To().Hex())

		fmt.Printf("%+v\n", tx)
	}
	return nil
}
