const { expect } = require('chai')
const SegfaultHandler = require('segfault-handler')
const lib = require('../build/Debug/lymuilib')

SegfaultHandler.registerHandler('argb_crash.log')

describe('Creating ARGB from Xyz', () => {
  it('Expect to create ARGB from Adobe profile XYZ Object', async () => {
    const xyz = await lib.convertRegular({
      input: {
        r: 50,
        g: 10,
        b: 95
      },
      output: 'xyz',
      profile: 'adobe'
    })

    const { data } = await lib.convertSpace({
      input: xyz.data,
      output: 'argb',
      clamp: 100
    })

    expect(data).to.be.deep.equal({
      r: 0.2,
      g: 0.04,
      b: 0.37
    })
  })

  it('Expect to create dark ARGB from XYZ Object', async () => {
    const xyz = await lib.convertRegular({
      input: {
        r: 0,
        g: 0,
        b: 0
      },
      output: 'xyz'
    })

    const { data } = await lib.convertSpace({
      input: xyz.data,
      output: 'argb',
      clamp: 100
    })

    expect(data).to.be.deep.equal({
      r: 0,
      g: 0,
      b: 0
    })
  })

  it('Expect to create white ARGB from XYZ Object', async () => {
    const xyz = await lib.convertRegular({
      input: {
        r: 255,
        g: 255,
        b: 255
      },
      output: 'xyz'
    })

    const { data } = await lib.convertSpace({
      input: xyz.data,
      output: 'argb',
      clamp: 100
    })

    expect(data).to.be.deep.equal({
      r: 1.0,
      g: 1.0,
      b: 1.0
    })
  })
})
