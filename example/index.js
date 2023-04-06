#!/usr/bin/env node

import { getPublicKey } from '@noble/secp256k1'
import { keccak_256 } from '@noble/hashes/sha3'
import { bytesToHex as _bytesToHex, hexToBytes } from '@noble/hashes/utils'

const bytesToHex = (bytes) => {
    return '0x' + _bytesToHex(bytes)
}

const getSeed = () => {
    const [, , arg] = process.argv
    if (!arg) {
        console.error('defaulting to empty seed')
        return new Uint8Array()
    }

    const regex = /^(0x)?[0-9A-Fa-f]+$/
    if (arg.length % 2 !== 0 || !regex.test(arg)) {
        console.error('expecting even length hex string, instead got:')
        console.error(arg)
        process.exit(1)
    }

    try {
        return hexToBytes(arg.startsWith('0x') ? arg.substring(2) : arg)
    } catch (err) {
        console.error(err)
        process.exit(1)
    }
}

const computePrivateKey = (seed) => {
    return keccak_256(seed)
}

const computePublicKey = (privateKey) => {
    const digest = getPublicKey(privateKey, false)
    console.log('uncompressed key:', bytesToHex(digest))
    const slice = digest.subarray(1)
    const hash = keccak_256(slice)
    return hash.subarray(12)
}

const main = () => {
    const seed = getSeed()
    const privateKey = computePrivateKey(seed)
    const publicKey = computePublicKey(privateKey)

    console.log('seed', bytesToHex(seed))
    console.log('private', bytesToHex(privateKey))
    console.log('public', bytesToHex(publicKey))
    return 0;
}

main()
