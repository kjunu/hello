package cmd

import (
	"encoding/base64"
	"testing"

	"github.com/ethereum/go-ethereum/common/hexutil"
	"github.com/stretchr/testify/assert"
)

var (
	TestAesGcmMsg  = "hello world, aes 256 gcm"
	TestAesGcmMsg2 = "\"hello world, aes 256 gcm\""
	TestDecryptMsg = "j6rMAWqMYSlfaXusJOMTbz6wmGB0owvC--j3+RXVNm7XAu0nmo--EnA8hdxzBsetMuEtNw17ag=="
)

func Test_encrypt(t *testing.T) {
	err := encrypt(nil, []string{TestAesGcmMsg})
	assert.NoError(t, err)
}

func Test_enc_dec(t *testing.T) {
	encrypted, err := _enc([]byte(TestAesGcmMsg))
	assert.NoError(t, err)
	t.Log(hexutil.Encode(encrypted))
	t.Log(base64.StdEncoding.EncodeToString(encrypted))
	decrypted, err := _dec(encrypted)
	assert.NoError(t, err)
	t.Log(string(decrypted))
}

func Test_dec_with_ruby_active_support_spec(t *testing.T) {
	decrypted, err := _dec_with_ruby_active_support_spec([]byte(TestDecryptMsg))
	assert.NoError(t, err)
	t.Log(string(decrypted))
	assert.EqualValues(t, TestAesGcmMsg, decrypted)
}

func Test_enc_with_ruby_active_support_spec(t *testing.T) {
	encrypted, err := _enc_with_ruby_active_support_spec([]byte(TestAesGcmMsg))
	assert.NoError(t, err)
	t.Log(string(encrypted))
	decrypted, err := _dec_with_ruby_active_support_spec(encrypted)
	assert.NoError(t, err)
	t.Log(string(decrypted))
	assert.EqualValues(t, TestAesGcmMsg, decrypted)

	encrypted2, err := _enc_with_ruby_active_support_spec([]byte(TestAesGcmMsg2))
	assert.NoError(t, err)
	t.Log(string(encrypted2))
	decrypted2, err := _dec_with_ruby_active_support_spec(encrypted2)
	assert.NoError(t, err)
	t.Log(string(decrypted2))
	assert.EqualValues(t, TestAesGcmMsg2, decrypted2)
}
