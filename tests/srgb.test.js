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
      r: 0.22,
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
      r: 1.0,
      g: 1.0,
      b: 1.0
    })
  })
})

describe('Creating XYZ from SRGB', () => {
  it('Expect to create XYZ from SRGB', async () => {
    const { data } = await lib.toXYZ({
      input: {
        r: 0.216668,
        g: 0.010423,
        b: 0.379375
      },
      type: 'Srgb',
      clamp: 10000
    })

    expect(data).to.be.deep.equal({
      x: 0.0376,
      y: 0.0174,
      z: 0.1138
    })
  })

  it('Expect to create bright XYZ from SRGB', async () => {
    const { data } = await lib.toXYZ({
      input: {
        r: 1.0,
        g: 1.0,
        b: 1.0
      },
      type: 'Srgb',
      clamp: 10000
    })

    expect(data).to.be.deep.equal({
      x: 0.9505,
      y: 1,
      z: 1.0888
    })
  })

  it('Expect to create dark XYZ from SRGB', async () => {
    const { data } = await lib.toXYZ({
      input: {
        r: 0,
        g: 0,
        b: 0
      },
      type: 'Srgb',
      clamp: 10000
    })

    expect(data).to.be.deep.equal({
      x: 0.0,
      y: 0.0,
      z: 0.0
    })
  })
})
