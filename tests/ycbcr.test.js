const { expect } = require('chai')
const SegfaultHandler = require('segfault-handler')
const lib = require('../build/Debug/lymuilib')

SegfaultHandler.registerHandler('ycbcr_crash.log')

describe('Creating Ycbcr from RGB Object', () => {
  it('Expect to create Ycbcr object from RGB Object', async () => {
    const ycbcr = await lib.convertRegular({
      input: {
        r: 0,
        g: 100,
        b: 200
      },
      output: 'ycbcr'
    })

    expect(ycbcr.data).to.be.deep.equal({
      y: 86,
      cb: 187,
      cr: 77
    })
  })

  it('Expect to create Ycbcr object from RGB black value object', async () => {
    const ycbcr = await lib.convertRegular({
      input: {
        r: 0,
        g: 0,
        b: 0
      },
      output: 'ycbcr'
    })

    expect(ycbcr.data).to.be.deep.equal({
      y: 16,
      cb: 128,
      cr: 128
    })
  })

  it('Expect to create Ycbcr object from RGB white value object', async () => {
    const ycbcr = await lib.convertRegular({
      input: {
        r: 255,
        g: 255,
        b: 255
      },
      output: 'ycbcr'
    })

    expect(ycbcr.data).to.be.deep.equal({
      y: 235,
      cb: 128,
      cr: 128
    })
  })

  it('Expect to throw when a missing prop is founded', async () => {
    try {
      await lib.convertRegular({
        input: {
          r: 1,
          b: 20
        },
        output: 'ycbcr'
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Wrong argument(s) type'
      })
    }
  })
})

describe('Creating RGB from Ycbcr', () => {
  it('Expect to convert a Ycbcr to an RGB object', async () => {
    const rgb = await lib.toRGB({
      input: {
        y: 86,
        cb: 187,
        cr: 77
      },
      type: 'ycbcr'
    })
    
    expect(rgb.data).to.be.deep.equal({
      r: 0,
      g: 100,
      b: 201
    });
  });

  it('Expect to retrieve a black value RGB object from YCbCr', async () => {
    const rgb = await lib.toRGB({
      input: {
        y: 16,
        cb: 128,
        cr: 128
      },
      type: 'ycbcr'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 0,
      g: 0,
      b: 0
    })
  })

  it('Expect to retrieve a white value RGB object from YCbCr', async () => {
    const rgb = await lib.toRGB({
      input: {
        y: 235,
        cb: 128,
        cr: 128
      },
      type: 'ycbcr'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 255,
      g: 255,
      b: 255
    })
  })

  it('Expect to throw when a missing param in object is pass', async () => {
    try {
      await lib.toRGB({
        input: {
          y: 235,
          cb: 'lol',
          cr: 128
        }
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Missing arguments'
      })
    }
  })
})
