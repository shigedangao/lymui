const { expect } = require('chai')
const SegfaultHandler = require('segfault-handler')
const lib = require('../build/Debug/lymuilib')

SegfaultHandler.registerHandler('lch_lab_convert.log')

describe('Creating LchLab from XYZ', () => {
  it('Expect to create white LchLab from XYZ', async () => {
    const { data } = await lib.convertSpace({
      input: {
        x: 0.9505,
        y: 1,
        z: 1.0888
      },
      output: 'llab',
      clamp: 1
    })

    expect(data).to.be.deep.equal({
      l: 100,
      c: 0,
      h: 19
    })
  })

  it('Expect to create LchLab from XYZ', async () => {
    const { data } = await lib.convertSpace({
      input: {
        x: 0.023750,
        y: 0.011309,
        z: 0.116460
      },
      output: 'llab',
      clamp: 1
    })

    expect(data).to.be.deep.equal({
      l: 10,
      c: 60,
      h: 304
    })
  })

  it('Expect to create a dark LchLab from XYZ', async () => {
    const { data } = await lib.convertSpace({
      input: {
        x: 0,
        y: 0,
        z: 0
      },
      output: 'llab',
      clamp: 1
    })

    expect(data).to.be.deep.equal({
      l: 0,
      c: 0,
      h: 0
    })
  })

  it('Expect to output a Lab when the output is not within the list of supported type', async () => {
    const { data } = await lib.convertSpace({
      input: {
        x: 0,
        y: 0,
        z: 0
      },
      output: 'lol',
      clamp: 1
    })

    expect(data).to.be.deep.equal({
      l: 0,
      a: 0,
      b: 0
    })
  })
})

describe('Creating XYZ from LchLab', () => {
  it('Expect to create Xyz from LchLab', async () => {
    const { data } = await lib.toXYZ({
      input: {
        l: 10.0375,
        c: 60.4716,
        h: 304.1497
      },
      type: 'llab',
      clamp: 1000000
    })

    expect(data).to.be.deep.equal({
      x: 0.023750,
      y: 0.011309,
      z: 0.116460
    })
  })

  it('Expect to create White Xyz from LchLab', async () => {
    const { data } = await lib.toXYZ({
      input: {
        l: 100,
        c: 0,
        h: 19
      },
      type: 'llab',
      clamp: 10000
    })

    expect(data).to.be.deep.equal({
      x: 0.9505,
      y: 1,
      z: 1.0888
    })
  })
  
  it('Expect to create Black Xyz from LchLab', async () => {
    const { data } = await lib.toXYZ({
      input: {
        l: 0,
        c: 0,
        h: 0
      },
      type: 'llab',
      clamp: 1
    })

    expect(data).to.be.deep.equal({
      x: 0,
      y: 0,
      z: 0
    })
  })
})
