const { expect } = require('chai');
const { toFixed } = require('./util')
const SegfaultHandler = require('segfault-handler');
const lib = require('../build/Debug/lymuilib');

SegfaultHandler.registerHandler('cymk_crash.log');

describe('Creating Cymk from RGB', () => {
  it('Expect to create a Cymk object from a RGB object', async () => {
    const rgb = {
      r: 5,
      g: 10,
      b: 198
    }

    const cymk = await lib.convertRegular({
      input: rgb,
      output: 'cymk'
    })

    const data = toFixed(cymk.data)
    expect(data).to.be.deep.equal({
      c: 0.9747,
      y: 0,
      m: 0.9495,
      k: 0.2235
    })
  })

  it('Expect to create a cymk object from a black value RGB object', async () => {
    const rgb = {
      r: 0,
      g: 0,
      b: 0
    }

    const cymk = await lib.convertRegular({
      input: rgb,
      output: 'cymk'
    })

    expect(cymk.data).to.be.deep.equal({
      c: 0,
      y: 0,
      m: 0,
      k: 1
    })
  })

  it('Expect to create a cymk object from a white value RGB object', async () => {
    const rgb = {
      r: 255,
      g: 255,
      b: 255
    }

    const cymk = await lib.convertRegular({
      input: rgb,
      output: 'cymk'
    })

    expect(cymk.data).to.be.deep.equal({
      c: 0,
      y: 0,
      m: 0,
      k: 0
    })
  })

  it('Expect method to not throw when bad rgb value is pass', async () => {
    const rgb = {
      r: 300,
      g: 300,
      b: 500
    }

    expect(async () => await lib.convertRegular({
      input: rgb,
      output: 'cymk'
    })).to.not.throw()
  })

  it('Expect to throw when no param is pass', async () => {
    try {
      await lib.convertRegular()
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Missing arguments'
      })
    }
  });

  it('Expect to throw when no output is passed', async () => {
    const rgb = { r: 100, g: 200, b: 155 }
    
    try {
      await lib.convertRegular({
        input: rgb
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Missing arguments'
      })
    }
  })

  it('Expect to throw when an input has the wrong type', async () => {
    const rgb = { r: 20, b: 30 }

    try {
      await lib.convertRegular({
        input: rgb,
        output: 'cymk'
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Wrong argument(s) type'
      })
    }
  })
});

describe('Creation of a RGB object from a CYMK object', () => {
  it('Expect create RGB Object from CYMK Object', async () => {
    const cymk = {
      c: 0.973,
      y: 0,
      m: 0.949,
      k: 0.223
    }

    const rgb = await lib.toRGB({
      input: cymk,
      type: 'cymk'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 5,
      g: 10,
      b: 198
    })
  })

  it('Expect to create RGB Object from Black CYMK object', async () => {
    const cymk = {
      c: 0,
      y: 0,
      m: 0,
      k: 1
    }

    const rgb = await lib.toRGB({
      input: cymk,
      type: 'cymk'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 0,
      g: 0,
      b: 0
    })
  })

  it('Expect to create RGB Object from White CYMK object', async () => {
    const cymk = {
      c: 0,
      y: 0,
      m: 0,
      k: 0
    }

    const rgb = await lib.toRGB({
      input: cymk,
      type: 'cymk'
    })

    expect(rgb.data).to.be.deep.equal({
      r: 255,
      g: 255,
      b: 255
    })
  })

  it('Expect to throw when no param is pass', async () => {
    try {
      await lib.toRGB()
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Missing arguments'
      })
    }
  })

  it('Expect to throw when a wrong cymk object is pass', async () => {
    const cymk = {
      y: 0,
      m: 0,
      k: 0
    };

    try {
      await lib.toRGB({
        input: cymk
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Missing arguments'
      })
    }
  });

  it('Expect to throw when a param is of the wrong type', async () => {
    const cymk = {
      c: 'lol',
      y: 0,
      m: 0,
      k: 0
    }

    try {
      await lib.toRGB({
        input: cymk,
        type: 'cymk'
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Wrong argument(s) type'
      })
    }    
  })

  it('Expect to throw when the type param does not correspond to the input object', async () => {
    const cymk = {
      c: 20,
      y: 0,
      m: 0,
      k: 0
    }

    try {
      await lib.toRGB({
        input: cymk,
        type: 'hsl'
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Wrong argument(s) type'
      })
    }    
  })

  it('Expect to throw when the type param does not correspond to the input object (number pass)', async () => {
    const cymk = {
      c: 20,
      y: 0,
      m: 0,
      k: 0
    }

    try {
      await lib.toRGB({
        input: cymk,
        type: 5109895
      })
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Wrong argument(s) type'
      })
    }    
  })
});