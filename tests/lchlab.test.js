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
})
