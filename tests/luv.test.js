const { expect } = require('chai')
const SegfaultHandler = require('segfault-handler')
const lib = require('../build/Debug/lymuilib')

SegfaultHandler.registerHandler('lch_convert.log')

describe('Creating LUV from RGB', () => {
  it('Expect to create LUV from RGB with type SRGB', async () => {
    const { data } = await lib.convertSpace({
      input: {
        x: 0.034889,
        y: 0.017213,
        z: 0.109727
      },
      output: 'luv',
      clamp: 1000
    })

    expect(data).to.be.deep.equal({
      l: 13.951,
      u: 4.794,
      v: -39.787
    })
  })

  it('Expect to create LUV from RGB with type ARGB', async () => {
    const rgb = {
      r: 5,
      g: 10,
      b: 98
    }

    const { data } = await lib.convertRegular({
      input: rgb,
      output: 'xyz',
      profile: 'srgb'
    })

    const luv = await lib.convertSpace({
      input: data,
      output: 'luv',
      clamp: 1000
    })

    expect(luv.data).to.be.deep.equal({
      l: 10.037,
      u: -2.977,
      v: -36.642
    })
  })

  it('Expect to create a valid LUV from a white SRGB', async () => {
    const luv = await lib.convertSpace({
      input: {
        x: 0.9505,
        y: 1,
        z: 1.0888
      },
      output: 'luv',
      clamp: 10
    })

    expect(luv.data).to.be.deep.equal({
      l: 100,
      u: 0,
      v: 0
    })
  })

  it('Expect to create a valid LUV from a white ARGB', async () => {
    const rgb = {
      r: 255,
      g: 255,
      b: 255
    }

    const { data } = await lib.convertRegular({
      input: rgb,
      output: 'xyz',
      profile: 'adobeRgb'
    })

    const luv = await lib.convertSpace({
      input: data,
      output: 'luv',
      clamp: 1000
    })

    expect(luv.data).to.be.deep.equal({
      l: 100,
      u: 0,
      v: 0
    })
  })

  it('Expect to throw when a params is missing on the Rgb object', async () => {
    try {
      await lib.convertSpace({
        output: 'luv',
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Missing arguments'
      })
    }
  })

  it('Expect to return a valid luv from an xyz value', async () => {
    const xyz = {
      x: 0.196341,
      y: 0.101518,
      z: 0.994060
    }
    
    const luv = await lib.convertSpace({
      output: 'luv',
      input: xyz,
      clamp: 1000
    })

    expect(luv.data).to.be.deep.equal({
      l: 38.114,
      u: -15.254,
      v: -135.757
    })
  })
})

describe('Creating XYZ from LUV', () => {

  it('Expect to create XYZ from LUV', async () => {
    const { data } = await lib.toXYZ({
      input: {
        l: 13.951,
        u: 4.794,
        v: -39.787
      },
      type: 'luv',
      clamp: 1000000
    })

    expect(data).to.be.deep.equal({
      x: 0.034889,
      y: 0.017213,
      z: 0.109726
    })
  })

  it('Expect to create XYZ from a bright LUV', async () => {
    const { data } = await lib.toXYZ({
      input: {
        l: 100,
        u: 0,
        v: 0
      },
      type: 'luv',
      clamp: 100000
    })

    expect(data).to.be.deep.equal({
      x: 0.95047,
      y: 1,
      z: 1.08883
    })
  })

  it('Expect to throw when the input value contain bad params', async () => {
    try {
      await lib.toXYZ({
        input: {
          l: 100,
          u: 0,
          y: 0
        },
        type: 'luv',
        clamp: 100000
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Wrong argument(s) type'
      })
    }
  })

  it('Expect to throw when type is not a string', async () => {
    try {
      await lib.toXYZ({
        input: {
          l: 100,
          u: 0,
          v: 0
        },
        type: 33,
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Error while converting value to an other type'
      })
    }
  })

  it('Expect to throw when type is not a type of color space', async () => {
    try {
      await lib.toXYZ({
        input: {
          l: 100,
          u: 0,
          v: 0
        },
        type: '我想睡觉',
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Wrong argument(s) type'
      })
    }
  })
})