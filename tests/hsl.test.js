const { expect } = require('chai');
const { toFixed } = require('./util')
const SegfaultHandler = require('segfault-handler')
const lib = require('../build/Debug/lymuilib')

SegfaultHandler.registerHandler('hsl_crash.log');

describe('Creating HSL from RGB', () => {
  it('Expect to create HSL object from RGB object', async () => {
    const rgb = {
      r: 5,
      g: 10,
      b: 95
    }
    
    const hsl = await lib.convertRegular({
      input: rgb,
      output: 'hsl'
    })

    const data = toFixed(hsl.data)
    expect(data).to.be.deep.equal({
      h: 237,
      s: 90,
      l: 19.6
    })
  })

  it('Expect to create dark hsl', async () => {
    const rgb = {
      r: 0,
      g: 0,
      b: 0
    }

    const hsl = await lib.convertRegular({
      input: rgb,
      output: 'hsl'
    })

    expect(hsl.data).to.be.deep.equal({
      h: 0,
      s: 0,
      l: 0
    })
  })

  it('Expect to create a white hsl', async () => {
    const rgb = {
      r: 255,
      g: 255,
      b: 255
    }

    const hsl = await lib.convertRegular({
      input: rgb,
      output: 'hsl'
    })

    expect(hsl.data).to.be.deep.equal({
      h: 0,
      s: 0,
      l: 100
    })
  })

  it('Expect to create a high saturation hsl', async () => {
    const rgb = {
      r: 100,
      g: 150,
      b: 255
    }

    const hsl = await lib.convertRegular({
      input: rgb,
      output: 'hsl'
    })

    expect(hsl.data).to.be.deep.equal({
      h: 221,
      s: 100,
      l: 69.6
    })
  })

  it('Expect to throw when no param is passed', async () => {
    try {
      await lib.convertRegular()
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Missing arguments'
      })
    }
  })

  it('Expect to throw when missing props in rgb object', async () => {
    const rgb = {
      r: 0,
      b: 100
    };

    try {
      await lib.convertRegular({
        input: rgb,
        output: 'hsl'
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Wrong argument(s) type'
      })
    }
  })

  it('Expect to throw when wrong kind of argument is passed', async () => {
    try {
      await lib.convertRegular('lol')
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Missing arguments'
      })
    }
  })
});

describe('Creating RGB from HSL', () => {
  it('Expect to create RGB from HSL object', async () => {
    const rgb = await lib.toRGB({
      input: {
        h: 237,
        s: 90,
        l: 19.7
      },
      type: 'hsl'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 5,
      g: 9,
      b: 95
    })
  })

  it('Expect to convert HSL black color to RGB object', async () => {
    const rgb = await lib.toRGB({
      input: {
        h: 0,
        s: 0,
        l: 0
      },
      type: 'hsl'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 0,
      g: 0,
      b: 0
    })
  })

  it('Expect to convert HSL white color to RGB object', async () => {
    const hsl = {
      h: 0,
      s: 0,
      l: 100
    }

    const rgb = await lib.toRGB({
      input: hsl,
      type: 'hsl'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 255,
      g: 255,
      b: 255
    })
  })

  it('Expect to throw when missing property is founded in HSL object', async () => {
    const hsl = {
      h: 200,
      l: 30
    }

    try {
      await lib.toRGB({
        input: hsl,
        type: 'hsl'
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Wrong argument(s) type'
      })
    }
  })

  it('Expect to throw when an unknow value is pass', async () => {
    try {
      await lib.toRGB({
        input: 'foo',
        type: 'hsl'
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Wrong argument(s) type'
      })
    }
  })
})