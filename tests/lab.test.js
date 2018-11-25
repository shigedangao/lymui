const { expect } = require('chai')
const SegfaultHandler = require('segfault-handler')
const lib = require('../build/Debug/lymuilib')

SegfaultHandler.registerHandler('lab_convert.log')

describe('Creating LAB from XYZ', () => {
  it('Expect to create LAB object from XYZ with type SRGB', async () => {
    const lab = await lib.convertSpace({
      input: {
        x: 0.9505,
        y: 1,
        z: 1.0888
      },
      output: 'lab',
      clamp: 1
    })

    expect(lab.data).to.be.deep.equal({
      l: 100,
      a: 0.0,
      b: 0.0
    })
  })

  it('Expect to create LAB object from XYZ with type SRGB (unprecise)', async () => {
    const lab = await lib.convertSpace({
      input: {
        x: 0.0348,
        y: 0.0172,
        z: 0.1097
      },
      output: 'lab',
      clamp: 1000
    })

    expect(lab.data).to.be.deep.equal({
      l: 13.943,
      a: 36.963,
      b: -41.437
    })
  })

  it('Expect to throw when nothing is passed', async () => {
    try {
      await lib.convertSpace();
    } catch(e) {
      expect(e).to.be.deep.equal({
        err: 'Missing arguments'
      })
    }
  })

  it('Expect to throw when param data is missing', async () => {
    try {
      await lib.convertSpace({
        input: {},
        output: 'lab'
      })
    } catch(e) {
      expect(e).to.be.deep.equal({
        err: 'Wrong argument(s) type'
      })
    }
  })

  it('Expect to return a Lab object when xyz is pass', async () => {
    const rgb = {
      r: 50,
      g: 10,
      b: 95
    }

    const { data } = await lib.convertRegular({
      input: rgb,
      output: 'xyz',
      profile: 'srgb'
    })

    const lab = await lib.convertSpace({
      input: data,
      output: 'lab',
      clamp: 1000
    })

    expect(lab.data).to.be.deep.equal({
      l: 13.951,
      a: 37.071,
      b: -41.431
    })
  })
})

describe('Creating XYZ from LAB', () => {
  it('Expect to create XYZ from LAB', async () => {
    const { data } = await lib.toXYZ({
      input: {
        l: 13.951,
        a: 37.071,
        b: -41.431
      },
      type: 'lab',
      clamp: 10000
    })

    expect(data).to.be.deep.equal({
      x: 0.0349,
      y: 0.0172,
      z: 0.1097
    })
  })

  it('Expect to create a bright XYZ from LAB', async () => {
    const { data } = await lib.toXYZ({
      input: {
        l: 100,
        a: 0,
        b: 0
      },
      type: 'lab',
      clamp: 10000
    })

    expect(data).to.be.deep.equal({
      x: 0.9505,
      y: 1,
      z: 1.0888
    })
  })

  it('Expect to create a dark XYZ from LAB', async () => {
    const { data } = await lib.toXYZ({
      input: {
        l: 0,
        a: 0,
        b: 0
      },
      type: 'lab',
    })

    expect(data).to.be.deep.equal({
      x: 0,
      y: 0,
      z: 0
    })
  })

  // it('Expect to throw an error when the type is wrong', async () => {
  //   const { data } = await lib.toXYZ({
  //     input: {
  //       l: 0,
  //       a: 0,
  //       b: 0
  //     },
  //     type: 'yuv',
  //   })

  //   expect(data).to.be.deep.equal({
  //     x: 0,
  //     y: 0,
  //     z: 0
  //   })
  // })
})
