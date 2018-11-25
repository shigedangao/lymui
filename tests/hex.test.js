const { expect } = require('chai')
const SegfaultHandler = require('segfault-handler')
const lib = require('../build/Debug/lymuilib')

SegfaultHandler.registerHandler('hex_crash.log')

describe('Creating HEX from RGB', () => {
  it('Expect to create an HEX from an RGB object', async () => {
    const hex = await lib.convertRegular({
      input: {
        r: 5,
        g: 10,
        b: 98
      },
      output: 'hex'
    })

    expect(hex.data).to.be.deep.equal({
      hex: '050A62'
    })
  })

  it('Expect to create an HEX with upper value', async () => {
    const hex = await lib.convertRegular({
      input: {
        r: 255,
        g: 255,
        b: 255
      },
      output: 'hex'
    })

    expect(hex.data).to.be.deep.equal({
      hex: 'FFFFFF'
    })
  })

  it('Expect to not throw when R, G, B value > uint8_t', async () => {
    try {
      await lib.convertRegular({
        input: {
          r: 300,
          g: 400,
          b: 1000
        },
        output: 'hex'
      })

    } catch (e) {
      throw e
    }    
  })
})

describe('Creating an RGB from an Hex', () => {
  it('Expect an Hex to return an RGB JS Object', async () => {
    const rgb = await lib.toRGB({
      input: '050A62',
      type: 'hex'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 5,
      g: 10,
      b: 98
    })
  })

  it('Expect a black color to return a black rgb JS Object', async () => {
    const rgb = await lib.toRGB({
      input: '000000',
      type: 'hex'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 0,
      g: 0,
      b: 0
    })
  })

  it('Expect a white color to return a white rgb JS Object', async () => {
    const rgb = await lib.toRGB({
      input: 'FFFFFF',
      type: 'hex'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 255,
      g: 255,
      b: 255
    })
  })

  it('Expect a short hexa to not throw', async () => {
    try {
      await lib.toRGB({
        type: 'hex'
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Missing arguments'
      })
    }
  })

  it('Expect a long hexa to not throw', async () => {
    try {
      const rgb = await lib.toRGB({
        input: 'LOL_NO_GENERIC',
        type: 'hex'
      })
      
    } catch (e) {
      throw e
    }
  })


  it('Expect to not throw when unknown character is pass', async () => {
    try {
      await lib.toRGB({
        input: 232323323,
        type: 'hex'
      });
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Error while creating JS Value'
      })
    }
  })
})