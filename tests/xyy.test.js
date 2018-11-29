const { expect } = require('chai')
const SegfaultHandler = require('segfault-handler')
const lib = require('../build/Debug/lymuilib')

SegfaultHandler.registerHandler('xyy_crash.log')

describe('Creating XYY from XYZ', () => {
  it('Expect to create a bright XYY from an XYZ Object', async () => {
    const { data } = await lib.convertSpace({
      input: {
        x: 0.950470,
        y: 1.0,
        z: 1.088830
      },
      output: 'xyy',
      clamp: 100000
    })

    expect(data).to.be.deep.equal({
      x: 0.31273,
      y: 0.32902,
      Y: 1.0
    })
  })

  it('Expect to create a normal XYY from an XYZ Object', async () => {
    const { data } = await lib.convertSpace({
      input: {
        x: 0.023750,
        y: 0.011309,
        z: 0.116460
      },
      output: 'xyy',
      clamp: 100000
    })

    expect(data).to.be.deep.equal({
      x: 0.15675,
      y: 0.07464,
      Y: 0.01131
    })
  })

  it('Expect to create a dark XYY from an XYZ Object', async () => {
    const { data } = await lib.convertSpace({
      input: {
        x: 0,
        y: 0,
        z: 0
      },
      output: 'xyy',
      clamp: 100000
    })

    expect(data).to.be.deep.equal({
      x: 0.31271,
      y: 0.32902,
      Y: 0
    })
  })
})

describe('Creating XYZ from XYY', () => {
  it('Creating white XYZ from XYY', async () => {
    const { data } = await lib.toXYZ({
      input: {
        x: 0.31273,
        y: 0.329023,
        Y: 1.0
      },
      type: 'xyy',
      clamp: 10000
    })

    expect(data).to.be.deep.equal({
      x: 0.9505,
      y: 1.0,
      z: 1.0888
    })
  })

  it('Creating normal XYZ from XYY', async () => {
    const { data } = await lib.toXYZ({
      input: {
        x: 0.485566,
        y: 0.356183,
        Y: 0.327715
      },
      type: 'xyy',
      clamp: 10000
    })

    expect(data).to.be.deep.equal({
      x: 0.4468,
      y: 0.3277,
      z: 0.1456
    })
  })

  it('Creating dark XYZ from XYY', async () => {
    const { data } = await lib.toXYZ({
      input: {
        x: 0.31271,
        y: 0.32902,
        Y: 0
      },
      type: 'xyy',
      clamp: 10000
    })

    expect(data).to.be.deep.equal({
      x: 0,
      y: 0,
      z: 0
    })
  })
})