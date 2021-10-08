package cmd

import (
	"bytes"
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/base64"
	"fmt"

	"github.com/ethereum/go-ethereum/common/hexutil"
	"github.com/spf13/cobra"
)

var (
	secret = []byte("AES256Key-32Characters1234567890")
)

func init() {
	encryptCmd.Flags().BoolVarP(&ForRuby, "ruby", "r", false, "for ruby on rails active support")
	decryptCmd.Flags().BoolVarP(&ForRuby, "ruby", "r", false, "for ruby on rails active support")
	rootCmd.AddCommand(encryptCmd)
	rootCmd.AddCommand(decryptCmd)
}

var ForRuby bool

var encryptCmd = &cobra.Command{
	Use:   "enc",
	Short: "enc",
	Long:  `encrypt aes 256 gcm`,
	RunE:  encrypt,
	Args:  cobra.MinimumNArgs(1),
}
var decryptCmd = &cobra.Command{
	Use:   "dec",
	Short: "d",
	Long:  `decrypt aes 256 gcm`,
	RunE:  decrypt,
	Args:  cobra.MinimumNArgs(1),
}

func newAesGcm(key []byte) (cipher.AEAD, error) {
	block, err := aes.NewCipher(key)
	if err != nil {
		return nil, err
	}
	aesgcm, err := cipher.NewGCM(block)
	if err != nil {
		return nil, err
	}
	return aesgcm, nil
}

func encrypt(cmd *cobra.Command, args []string) error {
	msg := []byte(args[0])
	var encrypted []byte
	var err error
	var result string
	if ForRuby {
		encrypted, err = _enc_with_ruby_active_support_spec(msg)
		result = string(encrypted)
	} else {
		encrypted, err = _enc(msg)
		result = hexutil.Encode(encrypted)
	}
	if err != nil {
		return err
	}
	fmt.Println("encrypted:", result)
	return nil
}

func decrypt(cmd *cobra.Command, args []string) error {
	var msg []byte
	var err error
	var decrypted []byte
	if ForRuby {
		msg = []byte(args[0])
		decrypted, err = _dec_with_ruby_active_support_spec(msg)
	} else {
		msg, err = hexutil.Decode(args[0])
		if err != nil {
			return err
		}
		decrypted, err = _dec(msg)
	}
	if err != nil {
		return err
	}
	fmt.Println("decrypted:", string(decrypted))
	return nil
}

func _dec(msg []byte) ([]byte, error) {
	aesgcm, err := newAesGcm(secret)
	if err != nil {
		return nil, err
	}
	size := aesgcm.NonceSize()
	nonce, cipherText := msg[:size], msg[size:]
	return aesgcm.Open(nil, nonce, cipherText, nil)
}

func _enc(msg []byte) ([]byte, error) {
	aesgcm, err := newAesGcm(secret)
	if err != nil {
		return nil, err
	}
	nonce := make([]byte, aesgcm.NonceSize())
	if _, err = rand.Read(nonce); err != nil {
		return nil, err
	}
	encrypted := aesgcm.Seal(nonce, nonce, msg, nil)
	return encrypted, nil
}

//ref: https://github.com/mattetti/goRailsYourself/blob/master/crypto/aes_gcm.go

func _enc_with_ruby_active_support_spec(msg []byte) ([]byte, error) {
	aesgcm, err := newAesGcm(secret)
	if err != nil {
		return nil, err
	}
	iv := make([]byte, aesgcm.NonceSize())
	if _, err = rand.Read(iv); err != nil {
		return nil, err
	}
	ciphertext := aesgcm.Seal(nil, iv, msg, nil)

	// Rails stores the GCM auth tag separately from the encrypted data,
	// unlike the cipher package, so a little munging is required.
	// Luckily aesgcm.Overhead() is the tag size (which is 16).
	tagStart := len(ciphertext) - aesgcm.Overhead()
	tag := ciphertext[tagStart:]
	enc := ciphertext[:tagStart]

	vectors := [][]byte{enc, iv, tag}
	for i, vec := range vectors {
		dst := make([]byte, base64.StdEncoding.EncodedLen(len(vec)))
		base64.StdEncoding.Encode(dst, vec)
		vectors[i] = dst
	}

	return bytes.Join(vectors, []byte("--")), nil
}

func _dec_with_ruby_active_support_spec(msg []byte) ([]byte, error) {
	aesgcm, err := newAesGcm(secret)
	if err != nil {
		return nil, err
	}
	vectors := bytes.SplitN([]byte(msg), []byte("--"), 3)
	if len(vectors) != 3 {
		return nil, fmt.Errorf("missing vectors, want 3, got %d", len(vectors))
	}
	for i, vec := range vectors {
		dst := make([]byte, base64.StdEncoding.DecodedLen(len(vec)))
		n, err := base64.StdEncoding.Decode(dst, vec)
		if err != nil {
			return nil, err
		}
		vectors[i] = dst[:n]
	}
	enc := vectors[0]
	// Rails splits the auth tag into a separate vector, which is unnecessary really, but fine.
	enc = append(enc, vectors[2]...)
	nonce := vectors[1]

	return aesgcm.Open(nil, nonce, enc, nil)
}
