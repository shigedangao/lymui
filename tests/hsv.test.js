const { expect } = require('chai')
const SegfaultHandler = require('segfault-handler')
const lib = require('../build/Debug/lymuilib')

SegfaultHandler.registerHandler('hsv_crash.log');

describe('Creating HSV Object from RGB', () => {
  it('Expect to create HSV from RGB Object', async () => {
    const hsv = await lib.convertRegular({
      input: {
        r: 5,
        g: 10,
        b: 98
      },
      output: 'hsv'
    })

    expect(hsv.data).to.be.deep.equal({
      h: 237,
      s: 94.9,
      v: 38.4
    })
  })

  it('Expect to create black HSV from RGB Object', async () => {
    const hsv = await lib.convertRegular({
      input: {
        r: 0,
        g: 0,
        b: 0
      },
      output: 'hsv'
    })

    expect(hsv.data).to.be.deep.equal({
      h: 0,
      s: 0,
      v: 0
    })
  })

  it('Expect to create white HSV from RGB Object', async () => {
    const hsv = await lib.convertRegular({
      input: { 
        r: 255,
        g: 255,
        b: 255
      },
      output: 'hsv'
    })

    expect(hsv.data).to.be.deep.equal({
      h: 0,
      s: 0,
      v: 100
    })
  })

  it('Expect to create a HSV object from RGB', async () => {
    const hsv = await lib.convertRegular({
      input: {
        r: 100,
        g: 200,
        b: 120
      },
      output: 'hsv'
    })

    expect(hsv.data).to.be.deep.equal({
      h: 132,
      s: 50,
      v: 78.4
    })
  })

  it('Expect to throw when missing props in rgb object', async () => {
    try {
      await lib.convertRegular({
        input: {
          r: 0,
          b: 100
        }
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Missing arguments'
      })
    }
  })
})

describe('Creating RGB Object from HSV Object', () => {
  it('Creating RGB from HSV', async () => {
    const rgb = await lib.toRGB({
      input: {
        h: 237,
        s: 94.9,
        v: 38.4
      },
      type: 'hsv'
    });

    expect(rgb.data).to.be.deep.equal({
      r: 5,
      g: 10,
      b: 98
    })
  })

  it('Creating RGB from HSV', async () => {
    const rgb = await lib.toRGB({
      input: {
        h: 237,
        s: 94.7,
        v: 37.3
      },
      type: 'hsv'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 5,
      g: 10,
      b: 95
    })
  })


  it('Creating black RGB from HSV', async () => {
    const rgb = await lib.toRGB({
      input: {
        h: 0,
        s: 0,
        v: 0
      },
      type: 'hsv'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 0,
      g: 0,
      b: 0
    })
  })

  it('Creating white RGB from HSV', async () => {
    const rgb = await lib.toRGB({
      input: {
        h: 0,
        s: 0,
        v: 100
      },
      type: 'hsv'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 255,
      g: 255,
      b: 255
    })
  })

  it('Expect to throw when missing property is founded in HSV object', async () => {
    try {
      await lib.toRGB({
        input: 'foo'
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Missing arguments'
      })
    }
  })
})