const { expect } = require('chai')
const SegfaultHandler = require('segfault-handler')
const lib = require('../build/Debug/lymuilib')

SegfaultHandler.registerHandler('srgb_crash.log')

describe('Creating SRGB from Xyz', () => {
  it('Expect to create SRGB from XYZ Object', async () => {
    const xyz = await lib.convertRegular({
      input: {
        r: 50,
        g: 10,
        b: 95
      },
      output: 'xyz'
    })

    const { data } = await lib.convertSpace({
      input: xyz.data,
      output: 'Srgb',
      clamp: 100
    })

    expect(data).to.be.deep.equal({
      r: 0.21,
      g: 0.01,
      b: 0.38
    })
  })

  it('Expect to create dark SRGB from XYZ Object', async () => {
    const xyz = await lib.convertRegular({
      input: {
        r: 0,
        g: 0,
        b: 0
      },
      output: 'xyz'
    })

    const { data } = await lib.convertSpace({
      input: xyz.data,
      output: 'Srgb',
      clamp: 100
    })

    expect(data).to.be.deep.equal({
      r: 0,
      g: 0,
      b: 0
    })
  })

  it('Expect to create white SRGB from XYZ Object', async () => {
    const xyz = await lib.convertRegular({
      input: {
        r: 255,
        g: 255,
        b: 255
      },
      output: 'xyz'
    })

    const { data } = await lib.convertSpace({
      input: xyz.data,
      output: 'Srgb',
      clamp: 100
    })

    expect(data).to.be.deep.equal({
      r: 0.98,
      g: 1.0,
      b: 1.0
    })
  })
})
