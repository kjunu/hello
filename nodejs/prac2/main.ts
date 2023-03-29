import { hdkey } from 'ethereumjs-wallet'

const bip39 = require('bip39')

const testMnemonic1 =
  'garment slender beef behave feed inmate galaxy input casino govern slot kangaroo coffee ahead hen purse clip chuckle arrive excuse index spirit own pause'
const testMnemonic1FirstAddress = '0x90cc4d930226d0e77a50d8d4c7f33f41ccad2fb2'

const VerifyMnemonic = async (
  mnemonic,
  queryAddress = ''
) => {
  const seed = bip39.mnemonicToSeedSync(mnemonic)
  console.log(seed.length, seed)
  const wallet = hdkey.fromMasterSeed(seed)
  const first = wallet.derivePath(`m/44'/60'/0'/0/0`)
  const child = wallet.deriveChild(0)
  console.log(first)
  console.log(child)

  return new Promise<string>((resolve, reject) => {
    if (!bip39.validateMnemonic(mnemonic)) {
      reject(new Error(`invalid mnemonic:${mnemonic}`))
    }
    resolve(queryAddress)
  })
}

const run = async () => {
    await VerifyMnemonic(testMnemonic1)
}

run()