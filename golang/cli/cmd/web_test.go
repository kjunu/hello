package cmd

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func Test_driver(t *testing.T) {
	assert.NoError(t, driver(nil, nil))
	t.Log("run driver")
}
