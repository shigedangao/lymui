const { expect } = require('chai')
const SegfaultHandler = require('segfault-handler')
const lib = require('../build/Debug/lymuilib')

SegfaultHandler.registerHandler('lch_convert.log')

describe('Creating LCH from XYZ', () => {
  it('Expect to create LCH from XYZ', async () => {
    const { data } = await lib.convertSpace({
      input: {
        x: 0.03488,
        y: 0.01721,
        z: 0.10972
      },
      output: 'lch',
      clamp: 10000
    })

    expect(data).to.be.deep.equal({
      l: 13.9492,
      c: 40.0716,
      h: 276.8616
    })
  })

  it('Expect to create LCH from RGB', async () => {
    const rgb = {
      r: 5,
      g: 10,
      b: 98
    }

    const xyz = await lib.convertRegular({
      input: rgb,
      output: 'xyz',
      profile: 'srgb'
    })

    const { data } = await lib.convertSpace({
      input: xyz.data,
      output: 'lch',
      clamp: 1000
    })
    
    expect(data).to.be.deep.equal({
      l: 10.037,
      c: 36.763,
      h: 265.356
    })
  })

  it('Expect to create LCH from a bright XYZ', async () => {
    const { data } = await lib.convertSpace({
      input: {
        x: 0.950470,
        y: 1.0,
        z: 1.088830
      },
      output: 'lch',
      clamp: 10
    })

    expect(data).to.be.deep.equal({
      l: 100,
      c: 0,
      h: 360
    })
  })

  it('Expect to create LCH from a dark XYZ', async () => {
    const { data } = await lib.convertSpace({
      input: {
        x: 0,
        y: 0,
        z: 0
      },
      output: 'lch',
      clamp: 10
    })

    expect(data).to.be.deep.equal({
      l: 0,
      c: 0,
      h: 180
    })
  })
})
