const { expect } = require('chai')
const SegfaultHandler = require('segfault-handler')
const lib = require('../build/Debug/lymuilib')

SegfaultHandler.registerHandler('yuv_crash.log')

describe('Creating YUV from RGB', () => {
  it('Expect to create YUV from RGB', async () => {
    const yuv = await lib.convertRegular({
      input: {
        r: 50,
        g: 10,
        b: 95
      },
      output: 'yuv'
    })

    expect(yuv.data).to.be.deep.equal({
      y: 0.124,
      u: 0.122,
      v: 0.063
    })
  })

  it('Expect to create an other YUV from RGB', async () => {
    const yuv = await lib.convertRegular({
      input: {
        r: 50,
        g: 10,
        b: 98
      },
      output: 'yuv',
      clamp: 100
    })

    expect(yuv.data).to.be.deep.equal({
      y: 0.13,
      u: 0.13,
      v: 0.06
    })
  })

  it('Expect to create dark YUV from black RGB', async () => {
    const yuv = await lib.convertRegular({
      input: {
        r: 0,
        g: 0,
        b: 0
      },
      output: 'yuv'
    })

    expect(yuv.data).to.be.deep.equal({
      y: 0,
      u: 0,
      v: 0
    })
  })

  it('Expect to create white YUV from white RGB', async () => {
    const yuv = await lib.convertRegular({
      input: {
        r: 255,
        g: 255,
        b: 255
      },
      output: 'yuv'
    })

    expect(yuv.data).to.be.deep.equal({
      y: 1,
      u: 0,
      v: 0
    })
  })

  it('Expect to throw when wrong kind of RGB is pass', async () => {
    try {
      await lib.convertRegular({
        input: {
          r: 10,
          g: 10
        }
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Missing arguments'
      })
    }
  })
})

describe('Creating RGB from YUV', () => {
  it('Expect to create RGB from YUV value', async () => {
    const rgb = await lib.toRGB({
      input: {
        y: 0.123,
        u: 0.122,
        v: 0.063
      },
      type: 'yuv'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 50,
      g: 10,
      b: 95
    })
  })

  it('Expect to create black RGB from dark YUV value', async () => {
    const rgb = await lib.toRGB({
      input: {
        y: 0,
        u: 0,
        v: 0
      },
      type: 'yuv'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 0,
      g: 0,
      b: 0
    })
  })

  it('Expect to create white RGB from bright YUV value', async () => {
    const rgb = await lib.toRGB({
      input: {
        y: 1,
        u: 0,
        v: 0
      },
      type: 'yuv'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 255,
      g: 255,
      b: 255
    })
  })

  it('Expect to throw when missing property in the YUV object is pass', async () => {
    try {
      await lib.toRGB({
        input: {
          y: 0,
          v: 0
        }
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Missing arguments'
      })
    }    
  })
})